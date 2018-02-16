#pragma once

#include "connectome.h"
#include "consciousness.h"
#include "face.h"
#include "image_classification_dataset.h"

namespace sunyata {

class Mind {
  public:
    void Init(Face* face, Consciousness* hot, Connectome* net);

    void Run(const ImageClassificationDataset& data, size_t num_epochs);

  private:
    void Train(const vector<uint8_t>& image, ID label);
    void Evaluate(const vector<uint8_t>& image, ID label, bool* is_correct,
                  float* loss);

    // Image/label I/O.
    Face* face_{nullptr};

    // Currently activated neurons.
    Consciousness* hot_{nullptr};

    // Sparse neuron connectivity matrix.
    Connectome* net_{nullptr};
};

}  // namespace sunyata
