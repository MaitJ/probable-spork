#include "deltatime.hpp"


double const& DeltaTime::get() const {
    return this->dt;
}
void DeltaTime::set(double dt) {
    this->dt = dt;
}
