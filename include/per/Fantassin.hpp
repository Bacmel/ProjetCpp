#ifndef FANTASSIN_HPP
#define FANTASSIN_HPP

#include "per/APersonnage.hpp"
#include "hex/Masque.hpp"
#include "obj/Taser.hpp"

namespace per
{
    class Fantassin : public APersonnage
    {
    protected:
        /** Arme du Fantassin : arme de CàC */
        obj::IObjet_S m_arme;
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
        obj::IObjet_SC getObjet(size_t indice) const override;
        obj::IObjet_S getObjet(size_t indice) override;
        size_t tailleSac() const override;

        hex::Masque getPorte() const override;


    };
}; // namespace per

#endif // FANTASSIN_HPP
