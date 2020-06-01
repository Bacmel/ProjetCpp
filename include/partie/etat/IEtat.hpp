#ifndef __IETAT_H__
#define __IETAT_H__

#include <memory>
#include "hex/Coordonnees.hpp"
#include "per/APersonnage.hpp"
#include "obj/IObjet.hpp"

namespace partie
{
    class Partie;
    namespace etat
    {
        class IEtat
        {
        public:
            virtual ~IEtat() {}

            /**
             * @brief Operation de l'etat courant sur la partie.
             *
             * @param partie la Partie.
             * @param coordonnees les coordonnees selectionnees.
             * @param objet l'objet selectionne.
             */
            virtual void operation(Partie& partie, const hex::Coordonnees& coordonnees) = 0;
            virtual void operation(Partie& partie, obj::IObjet_S objet) = 0;

            /**
             * @brief Affiche l'état courant.
             */
            virtual void afficher() const = 0;

            /**
             * @brief Obtient l'equipe courante.
             *
             * @return size_t l'equipe courante.
             */
            virtual size_t getEquipeCourante() const = 0;

            /**
             * @brief Obtient le personnage selectionne.
             *
             * @throw std::invalide_argument ne possede pas d'information.
             * @return per::APersonnage_SC le personnage selestionne.
             */
            virtual per::APersonnage_SC getPersoSelect() const = 0;

            /**
             * @brief Obtient l'objet selectionne.

            * @throw std::invalide_argument ne possede pas d'information.
            * @return obj::IObjet_SC l'objet selectionne.
            */
            virtual obj::IObjet_SC getObjetSelect() const = 0;

        };

        using IEtat_S = std::shared_ptr<IEtat>;
        using IEtat_SC = std::shared_ptr<const IEtat>;
    } // namespace etat
} // namespace partie

#endif //__IETAT_H__
