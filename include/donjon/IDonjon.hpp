#ifndef __IDONJON_HPP__
#define __IDONJON_HPP__

#include <map>
#include <memory>
#include <vector>
#include "donjon/cases/ACase.hpp"
#include "hex/ICarte.hpp"
#include "per/APersonnage.hpp"

namespace donjon
{
    class IDonjon : public utils::IActualisable
    {
    public:
        virtual ~IDonjon() = default;

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
         * @param type Le type de déplacement.
         * @param position La nouvelle position du personnage.
         *
         * @throw invalid_argument Quand le déplacement est impossible.
         */
        virtual void deplace(per::APersonnage& personnage, per::Deplacement type, const hex::Coordonnees& position) = 0;

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
         * @brief Donne l'objet (s'il y en a) et le retire.
         *
         * @param position La position à laquelle on ramasse.
         * @return obj::IObjet_S L'objet présent sur la case.
         *
         * @throw err::SansObjetErreur Quand la case n'a pas d'objet.
         */
        virtual obj::IObjet_S ramasser(const hex::Coordonnees& position) = 0;

        /**
         * @brief Retourne la liste des cases disponibles.
         *
         * @return set<hex::Coordonnees> la liste des cases disponibles.
         */
        virtual std::vector<hex::Coordonnees> getCaseVide() const = 0;

        /**
         * @brief Obtient le nombre de personnage.
         *
         * @return Le nombre de personnages.
         */
        virtual size_t getNbPersonnages() const = 0;

        /**
         * @brief Obtient le i ème personnage.
         *
         * @param indice L'indice du personnage.
         * @return Un pointeur partagé vers le personnage.
         * @throw std::out_of_range Quand le personnage n'existe pas.
         */
        virtual per::APersonnage_SC getPersonnage(size_t indice) const = 0;

        /**
         * @brief Obtient le i ème personnage.
         *
         * @param indice L'indice du personnage.
         * @return Un pointeur partagé vers le personnage.
         * @throw std::out_of_range Quand le personnage n'existe pas.
         */
        virtual per::APersonnage_S getPersonnage(size_t indice) = 0;

        /**
         * @brief Obtient le personnage avec l'id précisiée.
         *
         * @param id L'identifiant du personnage.
         * @return Un pointeur partagé vers le personnage.
         */
        virtual per::APersonnage_SC getPersonnageParId(size_t id) const = 0;

        /**
         * @brief Obtient le personnage avec l'id précisiée.
         *
         * @param id L'identifiant du personnage.
         * @return Un pointeur partagé vers le personnage.
         */
        virtual per::APersonnage_S getPersonnageParId(size_t id) = 0;

        /**
         * @brief Obtient la carte du donjon.
         *
         * @return hex::ICarte_S<cases::ICase_S> La carte du donjon.
         */
        virtual hex::ICarte_S<cases::ACase_S> getCarte() = 0;

        /**
         * @brief Donne le personnage présent aux coordonnées indiquées.
         *
         * @param position La position du personnage.
         * @return Le personnage à cette position.
         * @throw std::runtime_exception Quand il n'y a pas de personnage à
         * l'endroit indiqué.
         */
        virtual per::APersonnage_S trouver(const hex::Coordonnees& position) = 0;

        /**
         * @brief Donne le personnage présent aux coordonnées indiquées.
         *
         * @param position La position du personnage.
         * @return Le personnage à cette position.
         * @throw std::runtime_exception Quand il n'y a pas de personnage à
         * l'endroit indiqué.
         */
        virtual per::APersonnage_SC trouver(const hex::Coordonnees& position) const = 0;

        /**
         * @brief Indique si un personnage se trouve sur la case.
         * @return true Si un personnage occupe la case, sinon false.
         */
        virtual bool estOccupee(const hex::Coordonnees& position) const = 0;
    };

    using IDonjon_S = std::shared_ptr<IDonjon>;
    using IDonjon_SC = std::shared_ptr<const IDonjon>;
} // namespace donjon

#endif // __IDONJON_H__
