/// @file Drawable2d.hpp
/// @brief Contrôles visuels.
/// @author Thomas Laporte

#pragma once

#include "../../Observer.hpp"

/// @class Drawable2d
/// @brief Contrôles visuels.
class Drawable2d : public Observer {
public:
    Vector3d position;
    Anchor anchor;

    virtual ~Drawable2d() {}

    virtual void notification() = 0;
    virtual void draw() = 0;

    virtual void setPosition(const Vector3d& position) {
        this->position = position;
    }

    virtual void setAnchor(Anchor anchor) {
        this->anchor = anchor;
    }
};
