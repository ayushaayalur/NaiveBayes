//
//  DetectorClassFile.cpp
//  naivebayes
//
//  Created by Ayusha Ayalur on 3/22/19.
//  Copyright © 2019 Ayusha Ayalur. All rights reserved.
//

#include "DetectorClassFile.hpp"

std::vector<std::vector<std::vector<char>>> Detector::getTestImages() {
    return testImages;
}

std::vector<int> Detector::getTestLabels() {
    return testLabels;
}

std::vector<std::vector<std::vector<float>>> Detector::getProbabilityVector() {
    return model;
}

std::vector<float> Detector::getPriors() {
    return priors;
}

std::vector<std::vector<float>> Detector::getPosteriors() {
    return posteriors;
}

std::vector<int> Detector::getResults() {
    return results;
}

std::vector<std::vector<float>> Detector::getConfusionMatrix() {
    return confusionMatrix;
}

void Detector::setPosteriorsStorage() {
    for (int i = 0; i < 1000; i++) {
        posteriors.push_back(std::vector<float>());
        for (int j = 0; j < 10; j++) {
            posteriors[i].push_back(log10(priors[j]));
        }
    }
}

void Detector::putStorageForTrainingImages() {
    for(int i = 0; i < 1000; i++) {
        testImages.push_back(std::vector<std::vector<char>>());
        for (int j = 0; j < 28; j++) {
            testImages[i].push_back(std::vector<char>());
            for (int k = 0; k < 28; k++) {
                testImages[i][j].push_back(0);
            }
        }
    }
}

void Detector::putStorageForConfusionMatrix() {
    for (int i = 0; i < 10; i++) {
        confusionMatrix.push_back(std::vector<float>());
        for (int j = 0; j < 10; j++) {
            confusionMatrix[i].push_back(0.0);
        }
    }
}

std::vector<std::vector<std::vector<char>>> Detector::setTestImages(std::string userInput) {
    std::ifstream infile(userInput);
    putStorageForTrainingImages();
    int i = 0;
    int j = 0;
    std::string line;
    if (infile.good()) {
        while (getline(infile, line)) {
            std::vector<char> data(line.begin(), line.end());
            testImages[i][j] = data;
            j++;
            if (j % 28 == 0) {
                i++;
                j = 0;
            }
        }
    }
    return testImages;
}

std::vector<int> Detector::setTestLabels(std::string userInput) {
    std::ifstream infile(userInput);
    
    int tempData;
    if (infile.good()) {
        while (!infile.eof()) {
            infile >> tempData;
            testLabels.push_back(tempData);
        }
    }
    infile.close();
    return testLabels;
}

std::vector<std::vector<float>> Detector::setPosteriors(std::vector<std::vector<std::vector<char> > > testImagesVector) {
    for (int page = 0; page < 1000; page++) {
        for (int digit = 0; digit < 10; digit++) {
            for (int i = 0; i < 28; i++) {
                for (int j = 0; j < 28; j++) {
                    if (testImagesVector[page][i][j] == ' ') {
                        posteriors[page][digit] += log10(1 - model[digit][i][j]);
                    } else {
                        posteriors[page][digit] += log10(model[digit][i][j]);
                    }
                }
            }
        }
    }
    return posteriors;
}

std::vector<int> Detector::setResults(std::vector<std::vector<float> > posteriors) {
    for (int i = 0; i < 1000; i++) {
        results.push_back(0);
    }
    for (int i = 0; i < 1000; i++) {
        int indexOfMaxValue = 0;
        float maxValue = posteriors[i][0];
        for (int j = 1; j < 10; j++) {
            if (posteriors[i][j] > maxValue) {
                indexOfMaxValue = j;
                maxValue = posteriors[i][j];
            }
        }
        results[i] = indexOfMaxValue;
    }
    return results;
}

std::vector<std::vector<float>> Detector::setConfusionMatrix(std::vector<int> testLabels, std::vector<int> results) {
    putStorageForConfusionMatrix();
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::vector<int> indexesOfLabels;
            float valueCounter = 0.0;
            for (int testLabelIndex = 0; testLabelIndex < 1000; testLabelIndex++) {
                if (testLabels[testLabelIndex] == i) {
                    indexesOfLabels.push_back(testLabelIndex);
                }
            }
            for (int iOfLabels = 0; iOfLabels < indexesOfLabels.size(); iOfLabels++) {
                if (results[indexesOfLabels[iOfLabels]] == j) {
                    valueCounter++;
                }
            }
            confusionMatrix[i][j] = (float) 100*(valueCounter / indexesOfLabels.size());
        }
    }
    return confusionMatrix;
}

void Detector::generateResults() {
    testImages = setTestImages(userTestImagesFileName);
    testLabels = setTestLabels(userTestLabelsFileName);
    setPosteriorsStorage();
    posteriors = setPosteriors(testImages);
    results = setResults(posteriors);
    confusionMatrix = setConfusionMatrix(testLabels, results);
}

