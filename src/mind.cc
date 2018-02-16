#include "mind.h"

namespace sunyata {

void Mind::Init(Face* face, Consciousness* hot, Connectome* net) {
    face_ = face;
    hot_ = hot;
    net_ = net;
}

}  // namespace sunyata
