#include "face.h"

#include <cassert>

namespace sunyata  {

void Face::Init(ID num_neurons, ID num_image_repeats, ID pixels_per_image,
                float max_image_act, ID num_label_repeats, ID num_labels,
                float label_act) {
    num_neurons_ = num_neurons;

    total_image_slots_ = num_image_repeats * pixels_per_image;
    num_image_repeats_ = num_image_repeats;
    pixels_per_image_ = pixels_per_image;
    max_image_act_ = max_image_act;

    total_label_slots_ = num_label_repeats_ * num_labels;
    num_label_repeats_ = num_label_repeats;
    num_labels_ = num_labels;
    label_act_ = label_act;

    assert(total_image_slots_ + total_label_slots_ <= num_neurons_);
}

}  // namespace sunyata
