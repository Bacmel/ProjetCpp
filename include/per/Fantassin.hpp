#ifndef FANTASSIN_HPP
#define FANTASSIN_HPP

#include "per/APersonnage.hpp"
#include "hex/Masque.hpp"

namespace per
{
    class Fantassin : public APersonnage
    {
    protected:
        /** Arme du Fantassin : arme de CàC */

    public:
        Fantassin();

        Fantassin(const Fantassin& autre) = default;
        Fantassin(Fantassin&& autre) = default;
        Fantassin& operator=(const Fantassin& autre) = default;
        Fantassin& operator=(Fantassin&& autre) = default;
        ~Fantassin() {}

        void deplacer(Deplacement deplacement, hex::Coordonnees cible) override;
        void accepter(IPersonnageVisiteur& visiteur) const override;
        void actualiser() override;
    };
}; // namespace per

#endif // FANTASSIN_HPP
