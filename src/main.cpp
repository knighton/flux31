#include <string>

#include "connectome.h"
#include "consciousness.h"
#include "face.h"
#include "id.h"
#include "image_classification_dataset.h"
#include "mind.h"

using std::string;
using sunyata::Connectome;
using sunyata::Consciousness;
using sunyata::Face;
using sunyata::ID;
using sunyata::ImageClassificationDataset;
using sunyata::Mind;

int main() {
    // Dataset.
    size_t num_epochs = 1000;
    string dataset_filename = "data/mnist.txt";
    ImageClassificationDataset data;
    data.Load(dataset_filename);

    // Number of neurons in your brain.
    ID num_neurons = 1024;

    // The size of your consciousness.
    ID num_hot_slots = 512;

    // Neuron connectivity params.
    ID init_min_inputs = 2;
    ID max_inputs_per_neuron = 32;

    // Image params.
    ID num_image_repeats = 1;
    ID pixels_per_image = static_cast<ID>(data.num_pixels());
    float max_image_act = 1.f;

    // Label params.
    ID num_label_repeats = 10;
    ID num_labels = static_cast<ID>(data.num_labels());
    float label_act = 1.f;

    // I/O.
    Face face;
    face.Init(num_neurons, num_image_repeats, pixels_per_image, max_image_act,
              num_label_repeats, num_labels, label_act);

    // Short-term memory.
    Consciousness hot;
    hot.Init(num_hot_slots, num_neurons);

    // Long-term memory.
    Connectome net;
    net.Init(num_neurons, max_inputs_per_neuron, init_min_inputs);

    // Together.
    Mind mind;
    mind.Init(&face, &hot, &net);
    mind.Run(data, num_epochs);
}
