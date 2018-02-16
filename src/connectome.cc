#include "connectome.h"

#include <cassert>
#include <cmath>
#include <cstdlib>

namespace sunyata {

void Connectome::Init(ID num_neurons, ID max_inputs_per_neuron,
                      ID init_min_inputs) {
    num_neurons_ = num_neurons;
    max_inputs_per_neuron_ = max_inputs_per_neuron;

    // See rand() div/mod reusage in Tick().
    assert(max_inputs_per_neuron_ * max_inputs_per_neuron_ *
           max_inputs_per_neuron_ <= UINT32_MAX);

    feed_.clear();
    feed_.resize(num_neurons * max_inputs_per_neuron);
    inputs_per_neuron_.clear();
    inputs_per_neuron_.reserve(num_neurons);
    for (ID i = 0; i < num_neurons; ++i) {
        auto x = static_cast<double>(rand()) / RAND_MAX;
        x = pow(x, 3);
        x *= (max_inputs_per_neuron - init_min_inputs);
        x += init_min_inputs;
        auto num_inputs = static_cast<ID>(x);
        inputs_per_neuron_.emplace_back(num_inputs);
        for (ID j = 0; j < num_inputs; ++j) {
            auto index = i * max_inputs_per_neuron +j;
            feed_[index] = static_cast<ID>(rand()) % num_neurons;
        }
    }
}

void Connectome::Tick(const vector<float>& act, vector<float>* new_act) {
    // Process each neuron's inputs, resulting in new activations.
    for (ID i = 0; i < num_neurons_; ++i) {
        float x = 0;
        auto& num_inputs = inputs_per_neuron_[i];
        for (ID j = 0; j < num_inputs; ++j) {
            auto index = i * max_inputs_per_neuron_ + j;
            auto& id = feed_[index];
            x += act[id];
        }
        x /= num_inputs;
        (*new_act)[i] = x;
    }

    // Wire feeder neurons closer together.
    for (ID i = 0; i < num_neurons_; ++i) {
        uint32_t bits = static_cast<uint32_t>(rand());
        auto offset = i * max_inputs_per_neuron_;
        auto& num_inputs = inputs_per_neuron_[i];
        ID from_index = offset + bits % num_inputs;
        bits /= num_inputs;
        ID to_index = offset + bits % num_inputs;
        bits /= num_inputs;
        auto& from_id = feed_[from_index];
        auto& to_id = feed_[to_index];
        auto& num_inputs_of_from = inputs_per_neuron_[from_id];
        ID replace_index = from_id * num_inputs_of_from + bits % num_inputs;
        auto& id = feed_[replace_index];
        id = to_id;
    }
}

}  // namespace sunyata
