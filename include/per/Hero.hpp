#ifndef HERO_HPP
#define HERO_HPP

#include <vector>
#include "obj/IObjet.hpp"
#include "per/APersonnage.hpp"

namespace per
{

    class Hero : public APersonnage
    {
    protected:
        /** Liste des objets detenue par le Hero */
        std::vector<obj::IObjet_S> m_sac;

    public:
		/**
		 * @brief Construit un nouveau Hero
		 *
		 * @param pvMax
		 */
        explicit Hero(size_t pvMax);

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
    };
}; // namespace per

#endif // HERO_HPP
