#ifndef CARTE_HPP
#define CARTE_HPP

#include "hex/Coordonnees.hpp"
#include <memory>

namespace hex
{

template <typename T>
class ICarte
{
public:
    typedef std::shared_ptr<ICarte> Ptr;
    typedef std::shared_ptr<const ICarte> ConstPtr;

    virtual ~ICarte() = default;
    virtual T &operator()(Coordonnees &c) = 0;
    virtual const T &operator()(Coordonnees &c) const = 0;
};

};
#endif
