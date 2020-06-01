#ifndef __FINTOUR_H__
#define __FINTOUR_H__

#include "hex/Coordonnees.hpp"
#include "obj/IObjet.hpp"
#include "partie/etat/IEtat.hpp"

namespace partie::etat
{
    class FinTour : public IEtat
    {
    protected:
        /* indice de l'equipe en jeu. */
        size_t m_indiceEquipe;

    public:
        FinTour(size_t indice);

        /**
         * @brief Operation de l'etat courant sur la partie.
         *
         * @param partie la Partie.
         * @param coordonnees les coordonnees selectionnees.
         * @param objet l'objet selectionne.
         */
        void operation(Partie& partie, const hex::Coordonnees& coordonnees);
        void operation(Partie& partie, obj::IObjet_S objet);
        void operation(Partie& partie);

        /**
         * @brief Affiche l'état courant.
         */
        void afficher() const;

                /**
         * @brief Obtient l'equipe courante.
         *
         * @return size_t l'equipe courante.
         */
        inline size_t getEquipeCourante() const {return m_indiceEquipe;}

        /**
         * @brief Obtient le personnage selectionne.
         *
         * @throw std::invalide_argument ne possede pas d'information.
         * @return per::APersonnage_SC le personnage selestionne.
         */
        inline per::APersonnage_SC getPersoSelect() const;

        /**
         * @brief Obtient l'objet selectionne.
         * 
         * @throw std::invalide_argument ne possede pas d'information.
         * @return obj::IObjet_SC l'objet selectionne.
         */
        inline obj::IObjet_SC getObjetSelect() const;
    };
} // namespace partie::etat

#endif //__FINTOUR_H__