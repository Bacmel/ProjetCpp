#ifndef __IDONJON_H__
#define __IDONJON_H__

#include <memory>
#include "donjon/ICase.hpp"
#include "hex/ICarte.hpp"
#include "per/IPersonnage.hpp"

namespace donjon
{
    class IDonjon
    {
    public:
        typedef std::shared_ptr<IDonjon> Ptr;
        typedef std::shared_ptr<const IDonjon> ConstPtr;

        virtual ~IDonjon() {}

        /**
         * @brief Fait jouer à tour de rôles chaque personnage jusqu'à ce que l'un gagne.
         */
        virtual void jouer() = 0;

        /**
         * @brief Déplace un personnage aux cordonnées indiqué.
         *
         * @param personnage Le personnage à déplacer.
         * @param position La nouvelle position du personnage.
         *
         * @throw invalid_argument Quand le déplacement est impossible.
         */
        virtual void deplace(const per::IPersonnage& personnage, const hex::Coordonnees& position) = 0;

        /**
         * @brief Endommage tous les personnages présents dans la zone.
         *
         * @param centre Le centre de la zone de dégat.
         * @param zone La zone de dégat sous la forme d'un masque.
         * @param degats La quantité de dégats émise.
         */
        virtual void degat(const hex::Coordonnees& centre, const hex::ICarte<bool>& zone, size_t degats) = 0;

        /**
         * @brief Dépose un objet sur une case.
         *
         * @param objet L'objet à déposer.
         * @param position La position à laquelle déposer l'objet.
         *
         * @throw invalid_argument Quand un objet est déjà présent sur la case.
         */
        virtual void deposer(obj::IObjet::Ptr objet, const hex::Coordonnees& position) = 0;

        /**
         * @brief
         *
         * @param position
         * @return obj::IObjet::Ptr
         */
        virtual obj::IObjet::Ptr ramasser(const hex::Coordonnees& position) = 0;
    };
} // namespace donjon

#endif // __IDONJON_H__
