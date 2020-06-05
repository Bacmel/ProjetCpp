#ifndef __FANTASSIN_HPP__
#define __FANTASSIN_HPP__

#include "hex/Masque.hpp"
#include "obj/Taser.hpp"
#include "per/APersonnage.hpp"

namespace per
{
    class Fantassin : public APersonnage
    {
    protected:
        /** Arme du Fantassin : arme de CàC. */
        obj::IObjet_S m_arme;

    public:
        Fantassin();

        Fantassin(const Fantassin& autre) = default;
        Fantassin(Fantassin&& autre) = default;
        Fantassin& operator=(const Fantassin& autre) = default;
        Fantassin& operator=(Fantassin&& autre) = default;
        ~Fantassin() = default;

        /* Méthodes APersonnage. */
        void accepter(IPersonnageVisiteur& visiteur) const override;
        obj::IObjet_SC getObjet(size_t indice) const override;
        obj::IObjet_S getObjet(size_t indice) override;
        size_t tailleSac() const override;

        /* Méthode IAtualisable. */
        void actualiser() override;

        /* Méthodes IPorte. */
        hex::Masque getPorte() const override;
        hex::Masque getZoneDegat(hex::Coordonnees cible) const override;
    };
}; // namespace per

#endif // __FANTASSIN_HPP__