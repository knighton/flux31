#include "consciousness.h"

#include <algorithm>
#include <cassert>
#include <random>

namespace sunyata {

void Consciousness::Init(ID num_slots, ID num_neurons) {
    assert(num_slots);
    assert(num_neurons);

    num_slots_ = num_slots;
    num_neurons_ = num_neurons;
    slots_.clear();
    slots_.reserve(num_slots);
    counts_.clear();
    counts_.resize(num_neurons);
    heat_scale_.clear();
    heats_.clear();
    heats_.resize(num_neurons);

    for (ID i = 0; i < num_slots; ++i) {
        auto id = static_cast<ID>(rand()) % num_neurons_;
        slots_.emplace_back(id);
        auto& count = counts_[id];
        ++count;
        heats_[id] = GetHeat(count);
    }
}

float Consciousness::GetHeat(ID count) {
    heat_scale_.reserve(count + 1);
    for (ID i = static_cast<ID>(heat_scale_.size()); i < count + 1; ++i) {
        auto x = static_cast<float>(tanh(i));
        heat_scale_.emplace_back(x * x);
    }
    return heat_scale_[count];
}

void Consciousness::Spike(ID id) {
    if (slots_.size() < num_slots_) {
        slots_.emplace_back(id);
        auto& count = counts_[id];
        ++count;
        heats_[id] = GetHeat(count);
        return;
    }

    auto old_index = static_cast<ID>(rand()) % slots_.size();
    auto& old_id = slots_[old_index];
    if (old_id == id) {
        return;
    }

    auto& old_count = counts_[old_id];
    --old_count;
    heats_[old_id] = GetHeat(old_count);
    auto& count = counts_[id];
    ++count;
    heats_[id] = GetHeat(count);
    old_id = id;
}

void Consciousness::Update(const vector<float>& act) {
    assert(act.size() == num_neurons_);
    vector<ID> ids;
    for (ID i = 0; i < num_neurons_; ++i) {
        if (static_cast<float>(rand()) / RAND_MAX < act[i]) {
            ids.emplace_back(i);
        }
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(ids.begin(), ids.end(), g);
    for (auto& id : ids) {
        Spike(id);
    }
}

}  // namespace sunyata
