#include "image_classification_dataset.h"

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <random>
#include <utility>

using std::ifstream;
using std::make_pair;

namespace sunyata {

void ImageClassificationDataset::Load(const string& filename) {
    x_train_.clear();
    y_train_.clear();
    x_val_.clear();
    y_val_.clear();

    size_t train_samples;
    size_t train_channels;
    size_t train_height;
    size_t train_width;
    size_t val_samples;
    size_t val_channels;
    size_t val_height;
    size_t val_width;

    ifstream in(filename);
    assert(in.good());
    in >> train_samples >> train_channels >> train_height >> train_width;
    in >> val_samples >> val_channels >> val_height >> val_width;
    assert(train_channels == val_channels);
    assert(train_height == val_height);
    assert(train_width == val_width);
    size_t pixels_per_image = train_channels * train_height * train_width;

    num_train_ = train_samples;
    num_val_ = val_samples;
    channels_ = train_channels;
    height_ = train_height;
    width_ = train_width;

    x_train_.reserve(train_samples);
    y_train_.reserve(train_samples);
    x_val_.reserve(val_samples);
    y_val_.reserve(val_samples);

    num_labels_ = 0;
    for (size_t i = 0; i < train_samples; ++i) {
        for (size_t j = 0; j < pixels_per_image; ++j) {
            uint32_t byte;
            in >> byte;
            x_train_.emplace_back(byte);
        }
        uint32_t byte;
        in >> byte;
        y_train_.emplace_back(byte);
        if (num_labels_ <= byte) {
            num_labels_ = byte + 1;
        }
    }

    for (size_t i = 0; i < val_samples; ++i) {
        for (size_t j = 0; j < pixels_per_image; ++j) {
            uint32_t byte;
            in >> byte;
            x_val_.emplace_back(byte);
        }
        uint32_t byte;
        in >> byte;
        y_val_.emplace_back(byte);
    }
}

void ImageClassificationDataset::SetUpEpoch(
        vector<pair<uint32_t, size_t>>* splits_indices) const {
    if (splits_indices->size() != num_train_ + num_val_) {
        splits_indices->resize(num_train_ + num_val_);
    }
    for (size_t i = 0; i < num_train_; ++i) {
        (*splits_indices)[i] = make_pair(0, i);
    }
    for (size_t i = 0; i < num_val_; ++i) {
        (*splits_indices)[num_train_ + i] = make_pair(1, i);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(splits_indices->begin(), splits_indices->end(), g);
}

void ImageClassificationDataset::Get(
        uint32_t split, size_t sample_index, vector<uint8_t>* image,
        uint32_t* klass) const {
    const vector<uint8_t>* x_bytes;
    const vector<uint8_t>* y_bytes;
    if (!split) {
        x_bytes = &x_train_;
        y_bytes = &y_train_;
    } else if (split == 1) {
        x_bytes = &x_val_;
        y_bytes = &y_val_;
    } else {
        assert(false);
    }
    size_t bytes_in_image = channels_ * height_ * width_;
    if (image->size() != bytes_in_image) {
        image->resize(bytes_in_image);
    }
    size_t x_begin = sample_index * bytes_in_image;
    size_t x_end = (sample_index + 1) * bytes_in_image;
    assert(x_end <= x_bytes->size());
    for (size_t i = 0; i < bytes_in_image; ++i) {
        (*image)[i] = (*x_bytes)[x_begin + i];
    }
    size_t y_index = sample_index;
    assert(y_index < y_bytes->size());
    *klass = (*y_bytes)[y_index];
}

}  // namespace sunyata
