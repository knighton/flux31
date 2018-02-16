#include "face.h"

#include <cassert>
#include <cstdio>

namespace sunyata  {

void Face::Init(ID num_neurons, ID num_image_repeats, ID pixels_per_image,
                float max_image_act, ID num_label_repeats, ID num_labels,
                float label_act) {
    printf("[Face] There are %u neurons.\n", num_neurons);
    num_neurons_ = num_neurons;

    total_image_slots_ = num_image_repeats * pixels_per_image;
    num_image_repeats_ = num_image_repeats;
    pixels_per_image_ = pixels_per_image;
    max_image_act_ = max_image_act;
    auto image_pct = total_image_slots_ * 100.0f / num_neurons;
    printf("[Face] We write images to %u neurons (%u copies x %u pixels) "
           "(%.3f%% of them), with maximum activation %.3f.\n",
           total_image_slots_, num_image_repeats_, pixels_per_image_, image_pct,
           max_image_act_);

    total_label_slots_ = num_label_repeats * num_labels;
    num_label_repeats_ = num_label_repeats;
    num_labels_ = num_labels;
    label_act_ = label_act;
    auto label_pct = total_label_slots_ * 100.0f / num_neurons;
    printf("[Face] We write labels to %u neurons (%u copies x %u labels) "
           "(%.3f%% of them), with selected label activation %.3f.\n",
           total_label_slots_, num_label_repeats, num_labels_, label_pct,
           label_act_);

    assert(total_image_slots_ + total_label_slots_ <= num_neurons_);
}

}  // namespace sunyata
