#include "layer.h"

Layer::Layer(size_t inputs, size_t outputs, Rand r) :
  activation(outputs), blame(outputs), random(r)
{

}

Layer::Layer(size_t inputs, Rand r) :
  activation(inputs), blame(inputs), random(r)
{
}

Layer::~Layer()
{

}

Vec Layer::getActivation()
{
  return activation;
}

void Layer::setBlame(Vec& _blame)
{
  blame.copy(_blame);
}

size_t Layer::getWeightCount()
{
  return weightCount;
}
