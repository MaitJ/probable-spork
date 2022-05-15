#ifndef DELTATIME_H
#define DELTATIME_H

class DeltaTime {
    //Time between frames in seconds
    double dt = 0.f;

public:
    double const& get() const;
    void set(double dt);
};


#endif
