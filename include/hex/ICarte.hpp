#ifndef CARTE_HPP
#define CARTE_HPP

#include "hex/Coordonnees.hpp"
namespace hex
{

template <typename T>
class ICarte
{
public:
    virtual ~ICarte() = default;
    virtual T &operator()(Coordonnees &c) = 0;
    virtual const T &operator()(Coordonnees &c) const = 0;
};

};
#endif
