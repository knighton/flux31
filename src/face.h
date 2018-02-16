#pragma once

#include "id.h"

namespace sunyata {

class Face {
  public:
    void Init(ID num_neurons, ID num_image_repeats, ID pixels_per_image,
              float max_image_act, ID num_label_repeats, ID num_labels,
              float label_act);

  private:
    ID num_neurons_;

    ID total_image_slots_;
    ID num_image_repeats_;
    ID pixels_per_image_;
    float max_image_act_;

    ID total_label_slots_;
    ID num_label_repeats_;
    ID num_labels_;
    float label_act_;
};

}  // namespace sunyata
