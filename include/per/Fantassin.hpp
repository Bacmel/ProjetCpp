#ifndef FANTASSIN_HPP
#define FANTASSIN_HPP

#include "hex/ICarte.hpp"
#include "per/APersonnage.hpp"

namespace per
{
    class Fantassin : public APersonnage
    {
    protected:
        /** Arme du Fantassin : arme de CàC */
        size_t m_degat;
        hex::ICarte_SC<bool> m_porte;

    public:
        Fantassin();

        Fantassin(const Fantassin& autre) = default;
        Fantassin(Fantassin&& autre) = default;
        Fantassin& operator=(const Fantassin& autre) = default;
        Fantassin& operator=(Fantassin&& autre) = default;
        ~Fantassin() {}

    };
}; // namespace per

#endif // FANTASSIN_HPP
