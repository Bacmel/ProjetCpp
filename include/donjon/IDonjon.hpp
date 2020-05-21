#ifndef __IDONJON_H__
#define __IDONJON_H__

#include <memory>
#include "donjon/ICase.hpp"
#include "hex/ICarte.hpp"
#include "per/APersonnage.hpp"

namespace donjon
{
    class IDonjon
    {
    public:
        virtual ~IDonjon() {}

        /**
         * @brief Invoque le personnage à la position spécifiée.
         *
         * @param personnage Le personnage à invoquer.
         * @param position La position où se trouvera le joueur
         */
        virtual void invoquer(per::APersonnage_S personnage, const hex::Coordonnees& position) = 0;

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
        virtual void deplace(const per::APersonnage& personnage, const hex::Coordonnees& position) = 0;

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
        virtual void deposer(obj::IObjet_S objet, const hex::Coordonnees& position) = 0;

        /**
         * @brief
         *
         * @param position
         * @return obj::IObjet_S
         */
        virtual obj::IObjet_S ramasser(const hex::Coordonnees& position) = 0;
    };

    using IDonjon_S = std::shared_ptr<IDonjon>;
    using IDonjon_SC = std::shared_ptr<const IDonjon>;
} // namespace donjon

#endif // __IDONJON_H__
