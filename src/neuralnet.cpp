#include "neuralnet.h"
#include "supervised.h"

NeuralNet::NeuralNet(Rand r) : random(r)
{

}

NeuralNet::~NeuralNet()
{
  for(size_t i = 0; i < layers.size(); i++)
    		delete(layers[i]);
}

const char* NeuralNet::name()
{
  return "neural network";
}

Vec NeuralNet::getWeights()
{
  return weights;
}

void NeuralNet::train(const Matrix& features, const Matrix& labels)
{
  layers.clear();
  LayerLinear* l = new LayerLinear(features.cols(), labels.cols(), random);
  layers.push_back(l);

  for(size_t i = 0; i < layers.size(); ++i)
  {
    layers[i]->ordinary_least_squares(features, labels, weights);
  }
  delete l;

}


const Vec& NeuralNet::predict(const Vec& in)
{

  Vec layerInputs(in);
  size_t startWeight = 0;
  for(size_t i = 0; i < layers.size(); ++i)
  {
    VecWrapper layerWeights(weights, startWeight, layers[i]->getWeightCount());
    layers[i]->activate(layerWeights, layerInputs);

    layerInputs.copy(layers[i]->getActivation());
    startWeight += layers[i]->getWeightCount();
    activation.copy(layers[i]->getActivation());
  }

  return activation;
}

void NeuralNet::backprop(const Vec& targetVals)
{
  //calculating initial blame

  Vec finalActivation(layers[layers.size() -1]->getActivation());
  Vec initialBlame(finalActivation.size());


  for(size_t i = 0; i < initialBlame.size(); ++i)
  {
    initialBlame[i] = targetVals[i] - finalActivation[i];
  }
  // cout << endl;
  // cout << "computing output layer balem value: " << endl;
  // cout << "TARGET: ";
  // targetVals.print();
  // cout << endl;
  // cout << "prediction: ";
  // finalActivation.print();
  // cout << endl;
  // cout << "blame: ";
  // initialBlame.print();
  // cout << endl;
  layers[layers.size() -1]->setBlame(initialBlame);


  size_t startWeight = weights.size();
  Vec prevBlame(initialBlame);
  for(size_t i = layers.size() - 1; i > 0; --i)
  {

    //build the weights
    startWeight -= layers[i]->getWeightCount();
    VecWrapper layerWeights(weights, startWeight,layers[i]->getWeightCount());

    layers[i]->setBlame(prevBlame);
    layers[i]->backprop(layerWeights, prevBlame);
  }
  layers[0]->setBlame(prevBlame);

}

void NeuralNet::update_gradient(const Vec& x)
{
  //this is where uninitialized value was created
  //Conditional jump or move depends on uninitialised value(s)
  //that happens in tanh function aparently
  Vec in(x);
  size_t startGradient = 0;

  for(size_t i = 0; i < layers.size(); ++i)
  {

    Vec layerGradient(layers[i]->getWeightCount());
    layers[i]->update_gradient(in, layerGradient);

    //copying over the gradient
    for(size_t j = startGradient, k = 0; k < layerGradient.size(); ++j, ++k)
    {
      gradient[j] = layerGradient[k];
    }

    in.copy(layers[i]->getActivation());
    startGradient += layerGradient.size();
  }

}

void NeuralNet::init_weights()
{
  size_t startWeight = 0;

  for(size_t layerIndex = 0 ; layerIndex < layers.size(); ++layerIndex)
  {
   for(size_t i = startWeight; i < startWeight + layers[layerIndex]->getWeightCount(); ++i)
    {
      if(i >= weights.size()) throw Ex("Math error in init weights");
      if( layers[layerIndex]->getInputCount() <= 0) throw Ex("Math error in init weights (trying to divide by 0)");
      weights[i] = max(0.03, 1.0 / layers[layerIndex]->getInputCount()) * random.normal();
    }
    startWeight += layers[layerIndex]->getWeightCount();

  }
  if(startWeight != weights.size()) throw Ex("Error, not all weights initialized");
  //weights.copy({0.1, 0.2, 0.3, 0.4, 0.1, 0.2, 0.3});

}

void NeuralNet::refine_weights(const Vec& in, const Vec& targetVals, double learning_rate)
{

  gradient.fill(0.0);
  predict(in);
  backprop(targetVals);
  update_gradient(in);

  for(size_t i = 0; i < weights.size(); ++i)
  {
    weights[i] += gradient[i] * learning_rate;
  }
}

void NeuralNet::addLayerLinear(size_t in, size_t out)
{
  layers.push_back(new LayerLinear(in, out, random));
  weights.resize(weights.size() + layers[layers.size()-1]->getWeightCount());
  gradient.resize(weights.size());
}

void NeuralNet::addLayerTanh(size_t in)
{
  layers.push_back(new LayerTanh(in, random));

}

void NeuralNet::finite_difference(const Vec& in, const Vec& targetVals)
{

}
