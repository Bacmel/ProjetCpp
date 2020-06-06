#ifndef __IETAT_HPP__
#define __IETAT_HPP__

#include <memory>
#include "hex/Coordonnees.hpp"
#include "obj/IObjet.hpp"
#include "per/APersonnage.hpp"

namespace partie
{
    class Partie;

    namespace etat
    {
        class IEtat
        {
        public:
            virtual ~IEtat() = default;

            /**
             * @brief Obtient l'equipe courante.
             *
             * @return size_t l'equipe courante.
             */
            virtual size_t getEquipeCourante() const = 0;

            /**
             * @brief Obtient le personnage selectionne.
             *
             * @throw std::logic_error ne possede pas d'information.
             * @return per::APersonnage_SC le personnage selestionne.
             */
            virtual per::APersonnage_SC getPersoSelect() const = 0;

            /**
             * @brief Obtient l'objet selectionne.

            * @throw std::logic_error ne possede pas d'information.
            * @return obj::IObjet_SC l'objet selectionne.
            */
            virtual obj::IObjet_SC getObjetSelect() const = 0;

            /**
             * @brief Affiche l'état courant.
             */
            virtual void afficher() const = 0;

            /**
             * @brief Operation de l'état courant sur la partie.
             *
             * Permet de communiquer la case selectionne a l'etat.
             *
             * @param partie La partie.
             * @param coordonnees Les coordonnees selectionnees.
             */
            virtual void operation(Partie& partie, const hex::Coordonnees& coordonnees) = 0;

            /**
             * @brief Operation de l'état courant sur la partie.
             *
             * Permet de communiquer l'objet selectionne a l'etat.
             *
             * @param partie La partie.
             * @param indiceObjet L'indice de l'objet selectionné.
             */
            virtual void operation(Partie& partie, size_t indiceObjet) = 0;

            /**
             * @brief Operation de l'état courant sur la partie.
             *
             * Lance l'etat seul.
             *
             * @param partie La partie.
             * @param indiceObjet L'indice de l'objet selectionné.
             */
            virtual void operation(Partie& partie) = 0;
        };

        using IEtat_S = std::shared_ptr<IEtat>;
        using IEtat_SC = std::shared_ptr<const IEtat>;
    } // namespace etat
} // namespace partie

#endif //__IETAT_HPP__
