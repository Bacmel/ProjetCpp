#ifndef IOBJET_HPP
#define IOBJET_HPP

#include "per/Personnage.hpp"

namespace obj
{

class IObjet
{
public:
    void utiliser(per::Personnage &p);
};

}; // namespace obj

#endif
