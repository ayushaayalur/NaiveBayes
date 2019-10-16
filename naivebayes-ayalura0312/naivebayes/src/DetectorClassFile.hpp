//
//  DetectorClassFile.hpp
//  naivebayes
//
//  Created by Ayusha Ayalur on 3/22/19.
//  Copyright © 2019 Ayusha Ayalur. All rights reserved.
//

#ifndef DetectorClassFile_hpp
#define DetectorClassFile_hpp

#include <stdio.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>

class Detector {
private:
    std::vector<std::vector<std::vector<char>>> testImages;
    std::vector<int> testLabels;
    std::vector<std::vector<float>> posteriors;
    std::vector<int> results;
    std::vector<std::vector<float>> confusionMatrix;
    std::vector<std::vector<std::vector<float>>> model;
    std::vector<float> priors;
public:
    Detector (std::string userTestImagesInput, std::string userTestLabelsInput, std::vector<std::vector<std::vector<float>>> probabilityVectorFromModel, std::vector<float> priorsVectorFromModel)
    {
        userTestImagesFileName = userTestImagesInput;
        userTestLabelsFileName = userTestLabelsInput;
        model = probabilityVectorFromModel;
        priors = priorsVectorFromModel;
    }
    std::string userTestImagesFileName;
    std::string userTestLabelsFileName;
    std::vector<std::vector<std::vector<char>>> getTestImages();
    std::vector<int> getResults();
    std::vector<int> getTestLabels();
    std::vector<float> getPriors();
    std::vector<std::vector<std::vector<float>>> getProbabilityVector();
    std::vector<std::vector<float>> getPosteriors();
    std::vector<std::vector<float>> getConfusionMatrix();
    void setPosteriorsStorage();
    void putStorageForTrainingImages();
    void putStorageForConfusionMatrix();
    std::vector<std::vector<std::vector<char>>> setTestImages(std::string userInput);
    std::vector<int> setTestLabels(std::string userInput);
    std::vector<std::vector<float>> setPosteriors(std::vector<std::vector<std::vector<char>>> testImagesVector);
    std::vector<int> setResults(std::vector<std::vector<float>> posteriors);
    std::vector<std::vector<float>> setConfusionMatrix(std::vector<int> testLabels, std::vector<int> results);
    void generateResults();
};

#endif /* DetectorClassFile_hpp */
