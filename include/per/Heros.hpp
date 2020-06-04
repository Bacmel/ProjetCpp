#ifndef HEROS_HPP
#define HEROS_HPP

#include <vector>
#include "obj/IObjet.hpp"
#include "per/APersonnage.hpp"

namespace per
{

    class Heros : public APersonnage
    {
    protected:
        /** Liste des objets detenue par le Hero */
        std::vector<obj::IObjet_S> m_sac;

    public:
        /**
         * @brief Construit un nouveau Hero.
         *
         * @param pvMax la sante maximale.
         */
        explicit Heros(size_t pvMax);

        void deplacer(Deplacement deplacement, hex::Coordonnees cible) override;

        void accepter(IPersonnageVisiteur& visiteur) const override;

        void ajouterObjet(obj::IObjet_S objet) override;

        void retirerObjet(obj::IObjet_S objet) override;

        size_t tailleSac() const override;

        obj::IObjet_SC getObjet(size_t indice) const override;

        obj::IObjet_S getObjet(size_t indice) override;

        void actualiser() override;

        hex::Masque getPorte() const override;
        hex::Masque getZoneDegat(hex::Coordonnees cible) const override;
    };
}; // namespace per

#endif // HEROS_HPP
