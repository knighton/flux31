#include "mind.h"

#include <cstdio>

#include "util.h"

namespace sunyata {

void Mind::Init(Face* face, Consciousness* hot, Connectome* net) {
    face_ = face;
    hot_ = hot;
    net_ = net;
}

void Mind::Train(const vector<uint8_t>& image, ID label) {
    vector<float> act;
    face_->SetUpActivations(&act);
    face_->AddImage(image, &act);
    face_->AddLabel(label, &act);

    vector<float> new_act;
    face_->SetUpActivations(&new_act);

    for (ID i = 0; i < 5; ++i) {
        net_->Tick(act, &new_act);
        net_->Tick(new_act, &act);
    }
}

void Mind::Evaluate(const vector<uint8_t>& image, ID label, bool* is_correct,
                    float* loss) {
    vector<float> act;
    face_->SetUpActivations(&act);
    face_->AddImage(image, &act);

    vector<float> new_act;
    face_->SetUpActivations(&new_act);

    auto num_labels = face_->num_labels();
    vector<float> preds;
    preds.resize(10 * num_labels);

    for (ID i = 0; i < 5; ++i) {
        net_->Tick(act, &new_act);
        face_->PredictLabel(new_act, &preds[i * 2 * num_labels]);

        net_->Tick(new_act, &act);
        face_->PredictLabel(act, &preds[(i * 2 + 1) * num_labels]);
    }

    printf("\n");
    printf("   ");
    for (ID i = 0; i < 10; ++i) {
        printf("%7u", i);
    }
    printf("\n");
    vector<float> sums;
    sums.resize(num_labels);
    for (ID i = 0; i < 10; ++i) {
        printf("%2u:", i);
        for (ID j = 0; j < num_labels; ++j) {
            auto& pred = preds[i * num_labels + j];
            sums[j] += pred;
            printf(" %6.3f", pred);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
    printf("   ");
    ID max_index = 0;
    float max_sum = -1;
    for (ID i = 0; i < 10; ++i) {
        auto& sum = sums[i];
        printf(" %6.3f", sum);
        if (max_sum < sum) {
            max_sum = sum;
            max_index = i;
        }
    }
    printf("\n");
    printf("\n");
    printf("    true %u pred %u acc %u\n", label, max_index,
           label == max_index);
    *is_correct = label == max_index;
    printf("\n");
    printf("\n");

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
