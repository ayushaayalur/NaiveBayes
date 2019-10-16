//
//  ModelClassFile.hpp
//  naivebayes
//
//  Created by Ayusha Ayalur on 3/21/19.
//  Copyright © 2019 Ayusha Ayalur. All rights reserved.
//

#ifndef ModelClassFile_hpp
#define ModelClassFile_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>

class Trainer {
private:
    std::vector<std::vector<std::vector<char>>> trainingImages;
    std::vector<int> trainingLabels;
    std::vector<float> priors;
    std::vector<std::vector<std::vector<float>>> model;
    std::vector<int> numberOfTimesDigitOccurs;
public:
    Trainer (std::string userTrainingImagesInput, std::string userTrainingLabelsInput)
    {
        userTrainingImagesFileName = userTrainingImagesInput;
        userTrainingLabelsFileName = userTrainingLabelsInput;
    }
    std::string userTrainingLabelsFileName;
    std::string userTrainingImagesFileName;
    std::vector<std::vector<std::vector<char>>> getTrainingImages();
    std::vector<int> getTrainingLabels();
    std::vector<float> getPriorsVector();
    std::vector<std::vector<std::vector<float>>> getModel();
    std::vector<int> getNumberOfTimesVector();
    void putStorageForTrainingImages();
    void putStorageForOneDimensionalVector();
    void putStorageForModel();
    std::vector<std::vector<std::vector<char>>> setTrainingImages(std::string fileName);
    std::vector<int> setTrainingLabels(std::string fileName);
    std::vector<int> setNumberOfTimesDigitOccurs(std::vector<int> trainingLabels);
    std::vector<float> setPriors();
    void setModel(std::vector<int> trainingLabels, std::vector<std::vector<std::vector<char>>> trainingImages);
    std::vector<int> populateIndexesOfImages(std::vector<int> trainingLabels, int digit);
    void initializeTrainer();
    float findNaiveBayesResult(float kValue, int timesDigitWasFound, int quantityOfDigit);
};

#endif /* ModelClassFile_hpp */
