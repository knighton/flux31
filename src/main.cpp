#include <string>

#include "image_classification_dataset.h"

using std::string;
using sunyata::ImageClassificationDataset;

int main() {
    string dataset_filename = "data/mnist.txt";
    ImageClassificationDataset data;
    data.Load(dataset_filename);
}
