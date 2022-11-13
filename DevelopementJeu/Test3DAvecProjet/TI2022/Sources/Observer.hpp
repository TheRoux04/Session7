/// @file Observer.hpp
/// @brief Patron de conception observateur.
/// @author Patrick Singcaster (singcaster\@clogik.io)

#pragma once

#include <list>

using namespace std;

/// @class Observer
/// @brief Observateur.
class Observer {
public:
    virtual void notification() = 0;
};
