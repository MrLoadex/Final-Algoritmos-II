#include "Cubicle.h"

Cubicle::Cubicle(int cubicleId) : id(cubicleId) {}

void Cubicle::setId(int _id) {
    id = _id;
}

int Cubicle::getId() const {
    return id;
}
