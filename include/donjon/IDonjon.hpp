#ifndef __IDONJON_H__
#define __IDONJON_H__

#include <memory>
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
         * @brief Obtient le personnage actif (aka. personnage qui peut réaliser
         * une action).
         *
         * @return APersonnage_S Le personnage actif.
         */
        virtual per::APersonnage_S getPersonnageActif() = 0;
        /**
         * @brief Obtient le personnage actif (aka. personnage qui peut réaliser
         * une action).
         *
         * @return APersonnage_SC Le personnage actif.
         */
        virtual per::APersonnage_SC getPersonnageActif() const = 0;

        /**
         * @brief Déplace le personnage actif aux cordonnées indiquées et met
         * fin à son tour.
         *
         * @param position La nouvelle position du personnage.
         *
         * @throw invalid_argument Quand le déplacement est impossible.
         * @see donjon::Donjon::finirTour()
         */
        virtual void deplace(const hex::Coordonnees& position) = 0;

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

        /**
         * @brief Met fin au tour du joueur actif.
         *
         * Un nouveau joueur actif est sélectionné.
         *
         * @throw std::runtime_exception S'il n'y a plus de personnage en vie.
         * @see donjon::IDonjon::getPersonnageActif
         */
        virtual void finirTour() = 0;
    };

    using IDonjon_S = std::shared_ptr<IDonjon>;
    using IDonjon_SC = std::shared_ptr<const IDonjon>;
} // namespace donjon

#endif // __IDONJON_H__
