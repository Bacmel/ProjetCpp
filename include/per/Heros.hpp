#ifndef __HEROS_HPP__
#define __HEROS_HPP__

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

        Heros(const Heros& autre) = default;
        Heros(Heros&& autre) = default;
        Heros& operator=(const Heros& autre) = default;
        Heros& operator=(Heros&& autre) = default;
        ~Heros() = default;

        /* Méthodes APersonnage. */
        void accepter(IPersonnageVisiteur& visiteur) const override;
        void ajouterObjet(obj::IObjet_S objet) override;
        void retirerObjet(obj::IObjet_S objet) override;
        obj::IObjet_SC getObjet(size_t indice) const override;
        obj::IObjet_S getObjet(size_t indice) override;
        size_t tailleSac() const override;

        /* Méthode IAtualisable. */
        void actualiser() override;

        /* Méthodes IPorte. */
        hex::Masque getPorte() const override;
        hex::Masque getZoneDegat(const hex::Coordonnees& cible) const override;
    };
}; // namespace per

#endif // __HEROS_HPP__
