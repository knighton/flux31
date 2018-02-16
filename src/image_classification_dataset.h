#pragma once

#include <string>
#include <utility>
#include <vector>

using std::pair;
using std::string;
using std::vector;

namespace sunyata {

class ImageClassificationDataset {
  public:
    size_t num_train() const { return num_train_; }
    size_t num_val() const { return num_val_; }

    size_t num_pixels() const { return channels_ * height_ * width_; }
    size_t channels() const { return channels_; }
    size_t height() const { return height_; }
    size_t width() const { return width_; }

    size_t num_labels() const { return num_labels_; }

    const vector<uint8_t>& x_train() const { return x_train_; }
    const vector<uint8_t>& y_train() const { return y_train_; }
    const vector<uint8_t>& x_val() const { return x_val_; }
    const vector<uint8_t>& y_val() const { return y_val_; }

    void Load(const string& filename);

    void SetUpEpoch(vector<pair<uint32_t, size_t>>* splits_indices) const;

    void Get(uint32_t split, size_t sample_index, vector<uint8_t>* image,
             uint32_t* label) const;

  private:
    size_t num_train_;
    size_t num_val_;

    size_t channels_;
    size_t height_;
    size_t width_;

    size_t num_labels_;

    vector<uint8_t> x_train_;
    vector<uint8_t> y_train_;
    vector<uint8_t> x_val_;
    vector<uint8_t> y_val_;
};

}  // namespace sunyata
