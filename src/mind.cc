#include "mind.h"

#include <cstdio>

#include "util.h"

namespace sunyata {

void Mind::Init(Face* face, Consciousness* hot, Connectome* net) {
    face_ = face;
    hot_ = hot;
    net_ = net;
}

void Mind::Tick(const vector<float>& in, vector<float>* out) {
    UNUSED(in);  // XXX
    UNUSED(out);  // XXX
}

void Mind::Train(const vector<uint8_t>& image, ID label) {
    vector<float> act;
    face_->SetUpActivations(&act);
    face_->AddImage(image, &act);
    face_->AddLabel(label, &act);

    vector<float> new_act;
    face_->SetUpActivations(&new_act);

    for (ID i = 0; i < 5; ++i) {
        Tick(act, &new_act);
        Tick(new_act, &act);
    }
}

void Mind::Evaluate(const vector<uint8_t>& image, ID label, bool* is_correct,
                    float* loss) {
    UNUSED(image);  // XXX
    UNUSED(label);  // XXX
    UNUSED(is_correct);  // XXX
    UNUSED(loss);  // XXX
}

void Mind::Run(const ImageClassificationDataset& data, size_t num_epochs) {
    vector<pair<uint32_t, size_t>> splits_indices;
    vector<uint8_t> image;
    ID label;
    size_t count = 0;
    for (size_t epoch = 0; epoch < num_epochs; ++epoch) {
        data.SetUpEpoch(&splits_indices);
        for (size_t i = 0; i < splits_indices.size(); ++i) {
            printf("TICK %zu\n", count);
            auto& it = splits_indices[i];
            auto& split = it.first;
            auto& sample = it.second;
            data.Get(split, sample, &image, &label);
            if (!split) {
                Train(image, label);
            } else {
                bool is_correct;
                float loss;
                Evaluate(image, label, &is_correct, &loss);
            }
            ++count;
            printf("%s\n", string(20, '\n').c_str());
        }
    }
}

}  // namespace sunyata
