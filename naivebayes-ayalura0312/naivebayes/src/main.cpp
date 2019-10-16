//
//  main.cpp
//  naivebayes
//
//  Created by Ayusha Ayalur on 3/19/19.
//  Copyright © 2019 Ayusha Ayalur. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <math.h>
#include "TrainerClassFile.hpp"
#include "DetectorClassFile.hpp"

std::vector<std::vector<std::vector<float>>> readFile(std::string fileName) {
    std::ifstream source(fileName);
    std::vector<std::vector<std::vector<float>>> readVector;
    for(int i = 0; i < 10; i++) {
        readVector.push_back(std::vector<std::vector<float>>());
        for (int j = 0; j < 28; j++) {
            readVector[i].push_back(std::vector<float>());
            for (int k = 0; k < 28; k++) {
                readVector[i][j].push_back(0);
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 28; j++) {
            for (int k = 0; k < 28; k++) {
                source >> readVector[i][j][k];
            }
        }
    }
    return readVector;
}

void writeFile(std::string fileName, std::vector<std::vector<std::vector<float>>> probabilityArray){
    std::ofstream outfile(fileName);
    if (outfile.good()) {
        for (int i=0; i < probabilityArray.size(); i++) {
            for (int j = 0; j < probabilityArray[i].size(); j++) {
                for (int k = 0; k < probabilityArray[i][j].size(); k++) {
                    outfile << probabilityArray[i][j][k] << " ";
                }
                outfile << "\n";
            }
        }
    }
    outfile.close();
}

void prettyPrint(std::vector<std::vector<float>> confusionMatrix) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::cout << std::fixed << std::setprecision(2) << confusionMatrix[i][j] << " | ";
        }
        std::cout << "\n";
    }
}

int main(int argc, const char * argv[]) {
    std::cout << "Please enter name of file you want to read training images from: " << std::endl;
    std::string userTrainingImagesInput;
    std::getline(std::cin, userTrainingImagesInput);
    
    std::cout << "Please enter name of file you want to read training labels from: "<< std::endl;
    std::string userTrainingLabelsInput;
    std::getline(std::cin, userTrainingLabelsInput);
    
    Trainer trainer(userTrainingImagesInput, userTrainingLabelsInput);
    trainer.initializeTrainer();
    
    std::cout << "Finished Training! Please enter where you want to save your model: " << std::endl;
    std::string userSaveModelInput;
    std::getline(std::cin, userSaveModelInput);
    
    writeFile(userSaveModelInput, trainer.getModel());
    
    std::cout << "Saved! Please enter what file you want to classify images from: " << std::endl;
    std::string userTestImagesInput;
    std::getline(std::cin, userTestImagesInput);
    
    std::vector<std::vector<std::vector<float>>> detectorProbability = readFile(userSaveModelInput);
    
    std::cout << "Saved! Please enter what file your test labels are in: " << std::endl;
    std::string userTestLabelsInput;
    std::getline(std::cin, userTestLabelsInput);
    
    Detector detector(userTestImagesInput, userTestLabelsInput, detectorProbability, trainer.getPriorsVector());
    detector.generateResults();
    
    std::cout << "Here is your generated confusion matrix: " << std::endl;
    prettyPrint(detector.getConfusionMatrix());
    return 0;
}
