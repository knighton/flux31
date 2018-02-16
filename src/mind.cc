#include "mind.h"

namespace sunyata {

void Mind::Init(Face* face, Consciousness* hot, Connectome* network) {
    face_ = face;
    hot_ = hot;
    network_ = network;
}

}  // namespace sunyata
