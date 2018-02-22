#ifndef NEURALNET_H
#define NEURALNET_H

#include "vec.h"
#include "matrix.h"
#include "layer.h"
#include "layerlinear.h"
#include "layertanh.h"
#include <vector>
#include "supervised.h"
#include "rand.h"

using namespace std;

class NeuralNet : public SupervisedLearner
{

private:
  Vec weights;
  vector<Layer*> layers;
  Vec gradient;
  Rand random;

public:
  NeuralNet(Rand r);
  ~NeuralNet();
  virtual void train(const Matrix& features, const Matrix& labels);
	virtual const Vec& predict(const Vec& in);
  virtual const char* name();
  void backprop(const Vec& targetVals);
  void update_gradient(const Vec& in);
  void init_weights();
  void refine_weights(const Vec& in, const Vec& targetVals, double learning_rate);
  void addLayerLinear(size_t in, size_t out);
  void addLayerTanh(size_t in);
  Vec getWeights();
  void finite_difference(const Vec& in, const Vec& targetVals);


};



#endif
