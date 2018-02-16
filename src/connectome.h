#pragma once

#include <vector>

#include "id.h"

using std::vector;

namespace sunyata {

class Connectome {
  public:
    void Init(ID num_neurons, ID max_inputs_per_neuron, ID init_min_inputs);

  private:
    // Total number of neurons.
    ID num_neurons_;

    // Maximum number of input neurons per neuron.
    ID max_inputs_per_neuron_;

    // Matrix of neuron-neuron incoming connections.
    //
    // Shape: num_neurons_ * max_inputs_per_neuron_.
    vector<ID> feed_;

    // Current number of input neurons for each neuron.
    //
    // The first that number of cells will be in use.
    vector<ID> inputs_per_neuron_;
};

}  // namespace sunyata
