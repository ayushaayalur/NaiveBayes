//
//  test.cpp
//  naivebayes
//
//  Created by Ayusha Ayalur on 3/23/19.
//  Copyright © 2019 Ayusha Ayalur. All rights reserved.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "TrainerClassFile.hpp"
#include "DetectorClassFile.hpp"

std::vector<int> trainingLabels;
void populateTrainingLabels(){
    trainingLabels.push_back(2);
    trainingLabels.push_back(2);
    trainingLabels.push_back(5);
    trainingLabels.push_back(8);
    trainingLabels.push_back(0);
}


Trainer trainer("trainingimages.txt", "traininglabels.txt");
Detector detector("testimages.txt", "testlabels.txt", trainer.getModel(), trainer.getPriorsVector());


TEST_CASE("populate indexOfImages for multiple indexes") {
    populateTrainingLabels();
    std::vector<int> toCheck;
    toCheck.push_back(0);
    toCheck.push_back(1);
    REQUIRE(trainer.populateIndexesOfImages(trainingLabels, 2) == toCheck);
}

TEST_CASE("populate indexOfImages for one index") {
    std::vector<int> toCheck;
    toCheck.push_back(3);
    REQUIRE(trainer.populateIndexesOfImages(trainingLabels, 8) == toCheck);
}

TEST_CASE("populate indexOfImages for no index") {
    std::vector<int> toCheck;
    REQUIRE(trainer.populateIndexesOfImages(trainingLabels, 3) == toCheck);
}

TEST_CASE("find NaiveBayesResult") {
    double naiveBayesResult = trainer.findNaiveBayesResult(0.1, 10, 10);
    int dummy = (int)(naiveBayesResult *1000.0);
    naiveBayesResult = ((double)dummy) / 1000.0;
    REQUIRE(naiveBayesResult == 0.99);
}

TEST_CASE("find NaiveBayesResult greater than 0") {
    double naiveBayesResult = trainer.findNaiveBayesResult(0.1, 20, 10);
    int dummy = (int)(naiveBayesResult *1000.0);
    naiveBayesResult = ((double)dummy) / 1000.0;
    REQUIRE(naiveBayesResult == 1.97);}

TEST_CASE("test putStorageForTrainingImages first level") {
    trainer.putStorageForTrainingImages();
    REQUIRE(trainer.getTrainingImages().size() == 5000);
}

TEST_CASE("test putStorageForTrainingImages second level") {
    REQUIRE(trainer.getTrainingImages()[0].size() == 28);
}

TEST_CASE("test putStorageForTrainingImages third level") {
    REQUIRE(trainer.getTrainingImages()[0][0].size() == 28);
}

TEST_CASE("test putStorageForModel first level") {
    trainer.putStorageForModel();
    REQUIRE(trainer.getModel().size() == 10);
}

TEST_CASE("test putStorageForModel second level") {
    REQUIRE(trainer.getModel()[0].size() == 28);
}

TEST_CASE("test putStorageForModel third level") {
    REQUIRE(trainer.getModel()[0][0].size() == 28);
}

TEST_CASE("test priors storage") {
    trainer.putStorageForOneDimensionalVector();
    REQUIRE(trainer.getPriorsVector().size() == 10);
}

TEST_CASE("test numberOfTimesDigitOccurs storage") {
    REQUIRE(trainer.getNumberOfTimesVector().size() == 10);
}

TEST_CASE("test confusion matrix storage") {
    detector.putStorageForConfusionMatrix();
    REQUIRE(detector.getConfusionMatrix().size() == 10);
}

