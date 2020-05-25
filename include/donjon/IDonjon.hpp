#ifndef __IDONJON_H__
#define __IDONJON_H__

#include <memory>
#include <map>
#include "donjon/cases/ICase.hpp"
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
         * @brief Déplace un personnage aux cordonnées indiqué.
         *
         * @param personnage Le personnage à déplacer.
         * @param position La nouvelle position du personnage.
         *
         * @throw invalid_argument Quand le déplacement est impossible.
         */
        virtual void deplace(per::APersonnage& personnage, const hex::Coordonnees& position) = 0;

        /**
         * @brief Pousse les personnages dans la zone d'effet.
         *
         * Un personnage poussé s'arrête sur une case non praticable. Il
         * s'arrête s'il collisionne un autre personnage. Il s'arrête s'il
         * heurte un mur ou sort de la carte. Dans ce cas, il prend 1 pt de
         * dégat.
         *
         * @param aoe Area Of Effects - Cases sur lesquels on pousse les
         * personnages présents dans la direction indiquée.
         * @param distance La distance à laquelle un personnage est poussé.
         */
        virtual void pousse(const std::map<hex::Coordonnees, hex::Direction>& aoe, size_t distance) = 0;

        /**
         * @brief Endommage tous les personnages présents dans la zone.
         *
         * @param aoe Area Of Effects - Cases sur lesquels on applique des dégats.
         */
        virtual void degat(const std::map<hex::Coordonnees, size_t>& aoe) = 0;

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
