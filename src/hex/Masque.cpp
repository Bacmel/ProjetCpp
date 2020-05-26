#include "hex/Masque.hpp"
#include <stdexcept>

namespace hex
{
    Masque::Masque(size_t m_rayon) : hex::CarteHexagone<bool>(m_rayon) {}

    Masque::Masque(const Masque& autre) : CarteHexagone<bool>(autre) {}

    Masque::Masque(Masque&& autre) : CarteHexagone<bool>(autre) {}

    Masque& Masque::operator=(const Masque& autre)
    {
        CarteHexagone<bool>::operator=(autre);
        return *this;
    }

    Masque& Masque::operator=(Masque&& autre)
    {
        CarteHexagone<bool>::operator=(autre);
        return *this;
    }

    Masque::~Masque() {}

    Masque Masque::operator||(const Masque& autre) const
    {
        if (autre.m_rayon != m_rayon) { throw std::invalid_argument("Masques de tailles différentes"); }
        Masque ou(m_rayon);
        // Applique un OU sur chaque élément avec celui de autre au même coordonnees.
        auto itr = ou.iterateur();
        while (itr->aSuite())
        {
            Coordonnees c = itr->suite();
            ou(c) = (*this)(c) || autre(c);
        }
        return ou;
    }

    Masque Masque::operator&&(const Masque& autre) const
    {
        if (autre.m_rayon != m_rayon) { throw std::invalid_argument("Masques de tailles différentes"); }
        Masque et(m_rayon);
        // Applique un ET sur chaque élément avec celui de autre au même coordonnees.
        auto itr = et.iterateur();
        while (itr->aSuite())
        {
            Coordonnees c = itr->suite();
            et(c) = (*this)(c) && autre(c);
        }
        return et;
    }

    Masque Masque::operator!() const
    {
        Masque inverse(*this);
        // Applique un NON sur chaque élément.
        auto itr = inverse.iterateur();
        while (itr->aSuite())
        {
            Coordonnees c = itr->suite();
            inverse(c) = !(*this)(c);
        }
        return inverse;
    }

} // namespace hex
