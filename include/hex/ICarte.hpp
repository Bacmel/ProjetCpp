#ifndef CARTE_HPP
#define CARTE_HPP

#include <memory>
#include <ostream>
#include "hex/Coordonnees.hpp"
#include "hex/IIterator.hpp"

namespace hex
{
    template <typename T>
    class ICarte
    {
    public:
        virtual ~ICarte() = default;

        virtual T& operator()(Coordonnees& c) = 0;

        virtual const T& operator()(Coordonnees& c) const = 0;

        virtual void remplir(const T& valeur) = 0;
        virtual void remplir(const ICarte& source, const Coordonnees& centre) = 0;

        virtual IIterator_S<Coordonnees> iterateur() const = 0;
    };

    template <class T>
    using ICarte_S = std::shared_ptr<ICarte<T>>;

    template <class T>
    using ICarte_SC = std::shared_ptr<const ICarte<T>>;

    template <class T>
    std::ostream& operator<<(std::ostream& os, const ICarte<T> carte)
    {
        auto itr = carte.iterateur();
        while (itr->aSuite())
        {
            hex::Coordonnees cItr = itr->suite();
            os << cItr << '\t' << carte(cItr) << std::endl;
        }
        return os;
    }

}; // namespace hex
#endif
