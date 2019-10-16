//
//  ModelClassFile.cpp
//  naivebayes
//
//  Created by Ayusha Ayalur on 3/21/19.
//  Copyright © 2019 Ayusha Ayalur. All rights reserved.
//

#include "TrainerClassFile.hpp"


void Trainer::putStorageForOneDimensionalVector() {
    for (int i = 0; i < 10; i++) {
        numberOfTimesDigitOccurs.push_back(0);
        priors.push_back(0);
    }
}

void Trainer::putStorageForModel() {
    for(int i = 0; i < 10; i++) {
        model.push_back(std::vector<std::vector<float>>());
        for (int j = 0; j < 28; j++) {
            model[i].push_back(std::vector<float>());
            for (int k = 0; k < 28; k++) {
                model[i][j].push_back(0);
            }
        }
    }
}

void Trainer::putStorageForTrainingImages() {
    for(int i = 0; i < 5000; i++) {
        trainingImages.push_back(std::vector<std::vector<char>>());
        for (int j = 0; j < 28; j++) {
            trainingImages[i].push_back(std::vector<char>());
            for (int k = 0; k < 28; k++) {
                trainingImages[i][j].push_back(0);
            }
        }
    }
}

std::vector<int> Trainer::getNumberOfTimesVector() {
    return numberOfTimesDigitOccurs;
}

std::vector<float> Trainer::getPriorsVector() {
    return priors;
}

std::vector<std::vector<std::vector<float>>> Trainer::getModel() {
    return model;
}

std::vector<std::vector<std::vector<char>>> Trainer::getTrainingImages() {
    return trainingImages;
}

std::vector<int> Trainer::getTrainingLabels() {
    return trainingLabels;
}

std::vector<std::vector<std::vector<char>>> Trainer::setTrainingImages(std::string fileName) {
    std::ifstream infile(fileName);
    putStorageForTrainingImages();
    int i = 0;
    int j = 0;
    std::string line;
    if (infile.good()) {
        while (getline(infile, line)) {
            std::vector<char> data(line.begin(), line.end());
            trainingImages[i][j] = data;
            j++;
            if (j % 28 == 0) {
                i++;
                j = 0;
            }
        }
    }
    return trainingImages;
}

std::vector<int> Trainer::setTrainingLabels(std::string fileName) {
    std::ifstream infile(fileName);
    int tempData;
    if (infile.good()) {
        while (!infile.eof()) {
            infile >> tempData;
            trainingLabels.push_back(tempData);
        }
    }
    infile.close();
    return trainingLabels;
}

std::vector<int> Trainer::setNumberOfTimesDigitOccurs(std::vector<int> trainingLabels) {
    for (int i = 0; i < trainingLabels.size() - 1; i++) {
        numberOfTimesDigitOccurs[trainingLabels.at(i)]++;
    }
    return numberOfTimesDigitOccurs;
}

std::vector<float> Trainer::setPriors() {
    for (int i = 0; i < 10; i++) {
        priors.at(i) = (float) numberOfTimesDigitOccurs.at(i) / 5000;
    }
    return priors;
}

void Trainer::setModel(std::vector<int> trainingLabels, std::vector<std::vector<std::vector<char>>> trainingImages) {
    putStorageForModel();
    for (int digit = 0; digit < 10; digit++) {
        std::vector<int> indexesOfImages = populateIndexesOfImages(trainingLabels, digit);
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                int onCounter = 0;
                for (int iOfImage = 0; iOfImage < indexesOfImages.size(); iOfImage++) {
                    if (trainingImages[indexesOfImages[iOfImage]][i][j] == '#'
                        || trainingImages[indexesOfImages[iOfImage]][i][j] == '+') {
                        onCounter++;
                    }
                }
                float kValue = 5;
                model[digit][i][j] = findNaiveBayesResult(kValue, onCounter, numberOfTimesDigitOccurs[digit]);
            }
        }
    }
}

std::vector<int> Trainer::populateIndexesOfImages(std::vector<int> trainingLabels, int digit) {
    std::vector<int> indexesOfImages;
    for (int i = 0; i < trainingLabels.size() - 1; i++) {
        if (trainingLabels.at(i) == digit) {
            indexesOfImages.push_back(i);
        }
    }
    return indexesOfImages;
}

float Trainer::findNaiveBayesResult(float kValue, int timesDigitWasFound, int quantityOfDigit) {
    return (kValue + timesDigitWasFound) / (2*kValue + quantityOfDigit);
}


void Trainer::initializeTrainer() {
    trainingImages = setTrainingImages(userTrainingImagesFileName);
    trainingLabels = setTrainingLabels(userTrainingLabelsFileName);
    putStorageForOneDimensionalVector();
    numberOfTimesDigitOccurs = setNumberOfTimesDigitOccurs(trainingLabels);
    priors = setPriors();
    setModel(trainingLabels, trainingImages);
}
