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
         * @param position la position.
         */
        explicit Heros(size_t pvMax);

        /**
         * @brief Recupère un objet.
         *
         * @param objet l'objet.
         */
        void addObjet(obj::IObjet_S objet);

        /**
         * @brief Perd un objet de son inventaire.
         *
         * @param objet l'objet perdu.
         */
        void rmObjet(obj::IObjet_S objet);

        /**
         * @brief Modifie la santé maximale
         *
         * @param sante La santé à ajouter. Elle peut être négative.
         */
        void addSanteMax(int sante);

        virtual void deplacer(Deplacement deplacement, hex::Coordonnees cible) override;

        virtual void accepter(IPersonnageVisiteur& visiteur) const override;
    };
}; // namespace per

#endif // HEROS_HPP
