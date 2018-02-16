#pragma once

#include <vector>

#include "id.h"

using std::vector;

namespace sunyata {

// A short-term cache of spiking neurons.
class Consciousness {
  public:
    // Setup.
    void Init(ID num_slots, ID num_neurons);

    // Perform a round of spikes given a list of neuron activations.
    void Update(const vector<float>& act);

  private:
    // Get the "heat" of a slot count.
    float GetHeat(ID count);

    // Spike one neuron.
    void Spike(ID id);

    // Shape parameters.
    ID num_slots_;
    ID num_neurons_;

    // The list of neurons that spiked recently.
    //
    // Shape: num_slots_.
    vector<ID> slots_;

    // The number of mentions in slots_ per neuron.
    //
    // Shape: num_neurons_.
    vector<ID> counts_;

    // Precomputed mapping of slot count -> score approaching 1.
    //
    // Values range from 0 (cold) to approaching 1 (hot).  Currently computed by
    // tanh(x) ** 2.
    //
    // Shape: grows as needed.
    vector<float> heat_scale_;

    // How "hot" each neuron is (see heat_scale_).
    //
    // Shape: num_neurons_.
    vector<float> heats_;
};

}  // namespace sunyata
