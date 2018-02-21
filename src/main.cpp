// ----------------------------------------------------------------
// The contents of this file are distributed under the CC0 license.
// See http://creativecommons.org/publicdomain/zero/1.0/
// ----------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <string>
#include <memory>
#include "error.h"
#include "string.h"
#include "rand.h"
#include "matrix.h"
#include "supervised.h"
#include "baseline.h"
#include "layer.h"
#include "layerlinear.h"
#include "neuralnet.h"
#include <algorithm>

using std::cout;
using std::cerr;
using std::string;
using std::auto_ptr;

void test(SupervisedLearner& learner, const char* challenge)
{
	// Load the training data
	// string fn = "data/";
	// fn += challenge;
	// Matrix trainFeatures;
	// trainFeatures.loadARFF(fn + "_train_feat.arff");
	// Matrix trainLabels;
	// trainLabels.loadARFF(fn + "_train_lab.arff");
	//
	// // Train the model
	// learner.train(trainFeatures, trainLabels);
	//
	// // Load the test data
	// Matrix testFeatures;
	// testFeatures.loadARFF(fn + "_test_feat.arff");
	// Matrix testLabels;
	// testLabels.loadARFF(fn + "_test_lab.arff");

	// Measure and report accuracy
	// size_t misclassifications = learner.countMisclassifications(testFeatures, testLabels);
	// cout << "Misclassifications by " << learner.name() << " at " << challenge << " = " << to_str(misclassifications) << "/" << to_str(testFeatures.rows()) << "\n";
}

void testHousingData(SupervisedLearner& learner)
{
	// Load the training data
	string fn = "data/";
	Matrix features;
	features.loadARFF(fn + "housing_features.arff");
	Matrix labels;
	labels.loadARFF(fn + "housing_labels.arff");



	learner.crossValidation(features, labels,5,10);

	// Load the test data

}

void testNeuralNetWithOLS(Rand random)
{
	NeuralNet nn(random);

	double learning_rate = 0.1;
	size_t itr = 3;
	nn.addLayerLinear(1,2);
	nn.addLayerTanh(2);
	nn.addLayerLinear(2,1);
	nn.init_weights();
	// double prevErr = 0;
	// size_t good = 0;



	// size_t *randomIndicies= new size_t[dataCount];
	// for(size_t j = 0; j < dataCount; ++j)
	// {
	// 	randomIndicies[j] = j;
	// }

	for(size_t i = 0 ; i < itr; ++i)
	{
		//double totalErr = 0;

		//create random indexes
		//random_shuffle(&randomIndicies[0], &randomIndicies[dataCount-1]);




			Vec in(1);
			in[0] = 0.3;
			Vec target(1);
			target[0] = 0.7;
			nn.refine_weights(in, target, learning_rate);


	}




}

void testLearner(SupervisedLearner& learner)
{


}

Vec convertToOneHot(size_t in)
{
	Vec oneHot(10);
	oneHot.fill(0);
	oneHot[in] = 1;
	return oneHot;
}

size_t convertToDecimal(Vec& oneHot)
{
	return oneHot.indexOfMax();
}

void testMNIST(Rand random)
{
	cout << "loading data" << endl;
	//load data
	string fn = "data/";
	Matrix testFeats;
	testFeats.loadARFF(fn + "test_feat.arff");
	Matrix testLabs;
	testLabs.loadARFF(fn + "test_lab.arff");


	Matrix trainFeats;
	trainFeats.loadARFF(fn + "train_feat.arff");
	Matrix trainLabs;
	trainLabs.loadARFF(fn + "train_lab.arff");
	cout << "done loading data" << endl;

	//scale features
	for(size_t row = 0; row < testFeats.rows(); ++row)
	{
		for(size_t col = 0 ; col < testFeats.cols(); ++col)
		{
			testFeats[row][col] = double(testFeats[row][col] / 256.0);
		}
	}

	for(size_t row = 0; row < trainFeats.rows(); ++row)
	{
		for(size_t col = 0 ; col < trainFeats.cols(); ++col)
		{
			trainFeats[row][col] = double(trainFeats[row][col] / 256.0);
		}
	}

	NeuralNet nn(random);
	nn.addLayerLinear(784,80);
	nn.addLayerTanh(80);
	nn.addLayerLinear(80,30);
	nn.addLayerTanh(30);
	nn.addLayerLinear(30,10);
	nn.addLayerTanh(10);

	nn.init_weights();


	//training NeuralNet
	double learning_rate = 0.003;
	size_t itr = 7;

	size_t trainingDataCount = trainFeats.rows();

	size_t *randomIndicies= new size_t[trainingDataCount]();
	for(size_t j = 0; j < trainingDataCount; ++j)
	{
		randomIndicies[j] = j;
	}

	//epochs
	for(size_t i = 0 ; i < itr; ++i)
	{
		//create random indexes
		random_shuffle(&randomIndicies[0], &randomIndicies[trainingDataCount-1]);
		cout << "itr: " << i << " is starting refinement." << endl;
		for(size_t j = 0; j < trainingDataCount; ++j)
		{
			size_t testRow = randomIndicies[j];
			Vec oneHotLabel = convertToOneHot(trainLabs.row(testRow)[0]);
			nn.refine_weights(trainFeats.row(testRow), oneHotLabel , learning_rate);
		}
		cout << "itr: " << i << " has completed refining." << endl;

		//test after an epoch
		size_t testingDataCount = testFeats.rows();
		size_t misclassifications = 0;
		for(size_t j = 0; j < testingDataCount; ++j)
		{
			Vec oneHotPrediction = nn.predict(testFeats.row(j));
			size_t prediction = convertToDecimal(oneHotPrediction);
			if(prediction != testLabs.row(j)[0])
				misclassifications++;
		}
		cout << misclassifications <<" / " << testingDataCount << endl;
	}

	delete[] randomIndicies;

}




int main(int argc, char *argv[])
{
	Rand random(123);
	enableFloatingPointExceptions();
	int ret = 1;
	try
	{
		BaselineLearner bl;
		testLearner(bl);
		ret = 0;
	}
	catch(const std::exception& e)
	{
		cerr << "An error occurred: " << e.what() << "\n";
	}
	try
	{
		//NeuralNet nn(random);
		//testHousingData(nn);
		//testNeuralNetWithOLS(random);

		testMNIST(random);
		ret = 0;
	}
	catch(const std::exception& e)
	{
		cerr << "An error occurred: " << e.what() << "\n";
	}
	cout.flush();
	cerr.flush();
	return ret;
}
