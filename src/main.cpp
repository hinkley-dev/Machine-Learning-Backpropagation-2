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



void testLearner(SupervisedLearner& learner)
{


}


size_t convertToDecimal(const Vec& oneHot)
{
	return oneHot.indexOfMax();
}

void testMNIST(Rand random)
{
	cout << "start loading data" << endl;
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
			testFeats[row][col] = (testFeats[row][col] / 256.0);
		}
	}

	for(size_t row = 0; row < trainFeats.rows(); ++row)
	{
		for(size_t col = 0 ; col < trainFeats.cols(); ++col)
		{
			trainFeats[row][col] = (trainFeats[row][col] / 256.0);
		}
	}

	if(trainLabs.rows() != trainFeats.rows() || testLabs.rows() != testFeats.rows())
		throw Ex("invalid data in MNIST upload");

	NeuralNet nn(random);
	nn.addLayerLinear(784,80);
	nn.addLayerTanh(80);
	nn.addLayerLinear(80,30);

	nn.addLayerTanh(30);
	nn.addLayerLinear(30,10);
	nn.addLayerTanh(10);

	nn.init_weights();

	double learning_rate = 0.03;
	size_t itr = 7;

	size_t trainingDataCount = trainFeats.rows();

	//to shuffle the data
	size_t *randomIndicies= new size_t[trainingDataCount];
	for(size_t j = 0; j < trainingDataCount; ++j)
	{
		randomIndicies[j] = j;
	}



	Vec onehot(10);
	onehot.fill(0.0);
	//epochs
	for(size_t i = 0 ; i < itr; ++i)
	{
		//create random indexes
		random_shuffle(&randomIndicies[0],&randomIndicies[trainingDataCount]);


		cout << "itr: " << i << " is starting refinement." << endl;

			for(size_t j = 0; j < trainingDataCount*3; ++j)
			{
				size_t trainRow = random.next(trainingDataCount);
				size_t digit = trainLabs.row(trainRow)[0];
				onehot[digit] = 1.0;
				nn.refine_weights(trainFeats.row(trainRow), onehot , learning_rate);
				onehot[digit] = 0.0;
			}


		cout << "itr: " << i << " has completed refining." << endl;

		//test after an epoch
		size_t testingDataCount = testFeats.rows();
		size_t misclassifications = 0;
		for(size_t j = 0; j < testingDataCount; ++j)
		{
			const Vec& oneHotPrediction = nn.predict(testFeats.row(j));
			size_t prediction = convertToDecimal(oneHotPrediction);
			if(prediction != (size_t)testLabs.row(j)[0])
				misclassifications++;
		}
		cout << misclassifications <<" / " << testingDataCount << endl;
		// if(misclassifications < 350)
		// 	return;
	}

	delete[] randomIndicies;


}


int main(int argc, char *argv[])
{
	Rand random(12);
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
		//cout << 325 << endl;
		testMNIST(random);
		// NeuralNet nn(random);
		// nn.addLayerLinear(1,2);
		// nn.addLayerTanh(2);
		// nn.addLayerLinear(2,1);
		// nn.init_weights();
		// Vec in(1);
		// Vec target(1);
		// in[0] = 0.3;
		// target[0] = 0.7;
		// for(size_t i = 0; i < 3; ++i)
		// {
		// 	nn.refine_weights(in, target, 0.1);
		// }
		// nn.getWeights().print();
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
