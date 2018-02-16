#include "connectome.h"

#include <cmath>
#include <cstdlib>

namespace sunyata {

void Connectome::Init(ID num_neurons, ID max_inputs_per_neuron,
                      ID init_min_inputs) {
    num_neurons_ = num_neurons;
    max_inputs_per_neuron_ = max_inputs_per_neuron;

    feed_.clear();
    feed_.resize(num_neurons * max_inputs_per_neuron);
    inputs_per_neuron_.clear();
    inputs_per_neuron_.reserve(num_neurons);
    for (ID i = 0; i < num_neurons; ++i) {
        auto x = static_cast<double>(rand()) / RAND_MAX;
        x = pow(x, 3);
        x += init_min_inputs;
        x *= (max_inputs_per_neuron - init_min_inputs);
        auto num_inputs = static_cast<ID>(x);
        inputs_per_neuron_.emplace_back(num_inputs);
        for (ID j = 0; j < num_inputs; ++j) {
            auto index = i * max_inputs_per_neuron +j;
            feed_[index] = static_cast<ID>(rand()) % num_neurons;
        }
    }
}

}  // namespace sunyata
