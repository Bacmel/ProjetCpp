#ifndef __APERSONNAGE_HPP__
#define __APERSONNAGE_HPP__

#include <map>
#include <memory>
#include <vector>
#include "hex/Coordonnees.hpp"
#include "obj/IObjet.hpp"
#include "utils/IActualisable.hpp"
#include "utils/IPorte.hpp"
#include "utils/Jauge.hpp"

namespace per
{
    // Forward decleration. (Evite les includes cycliques)
    class IPersonnageVisiteur;

    /** @brief Enumeration des deplacements possibles. */
    enum class Deplacement
    {
        Marcher,
        Sauter,
        Forcer
    };

    class APersonnage : public utils::IActualisable, public utils::IPorte
    {
    protected:
        /** @brief Identifiant pour le personnage suivant. */
        static size_t idSuivante;

        /** @brief Sante du personnage et points de vie actuel. */
        utils::Jauge m_pv;

        /** @brief Position du personnage. */
        hex::Coordonnees m_position;

        /** Identifiant du personnage. */
        size_t const m_id;

        /** Carte des degats infliges. */
        std::map<hex::Coordonnees, size_t> m_zoneEffet;

    public:
        APersonnage(size_t pvMax, hex::Coordonnees position);

        virtual ~APersonnage() = default;

        /**
         * @brief Prédicat sur la vie du personnage.
         *
         * @return true Si le personnage est vivant.
         * @return false sinon.
         */
        virtual bool estVivant() const;

        /**
         * @brief Fait subir une attaque.
         *
         * NOTE: La source n'est pas forcément un joueur jouable par un humain
         * ou l'ordinateur. Les dégats d'environnement sont associés à un joueur
         * qui représente l'environnement.
         *
         * @param degat La quantité de dégats (peut être différents de la santé
         *              retirée).
         */
        virtual void subirAttaque(size_t degat);

        /**
         * @brief Obtient le nombre de points de vie.
         *
         * @return size_t Le nombre de points de vie.
         */
        virtual size_t getSante() const { return m_pv.getVal(); }

        /**
         * @brief Obtient le nombre maximal de points de vie.
         *
         * @return size_t Le nombre maximal de points de vie.
         */
        virtual size_t getSanteMax() const { return m_pv.getValMax(); }

        /**
         * @brief Obtient l'identifiant.
         *
         * @return size_t l'identifiant.
         */
        virtual size_t getId() const { return m_id; }

        /**
         * @brief Obtient la position.
         *
         * @return Coordonnees la position.
         */
        virtual const hex::Coordonnees& getPosition() const { return m_position; }

        /**
         * @brief Obtient la zone d'effet.
         *
         * @return std::map<hex::Coordonnees, size_t> la zone d'effet.
         */
        virtual const std::map<hex::Coordonnees, size_t>& getZoneEffet() const { return m_zoneEffet; }

        /**
         * @brief Modifie la santé.
         *
         * NOTE: Elle peut être négative.
         *
         * @param sante La santé à ajouter.
         */
        void ajouterSante(int sante);

        /**
         * @brief Modifie la santé maximale
         *
         * NOTE: Elle peut être négative.
         *
         * @param sante La santé à ajouter. Elle peut être négative.
         */
        void ajouterSanteMax(int sante);

        /**
         * @brief Tue le personnage.
         */
        virtual void tuer();

        /**
         * @brief Redefinit la position.
         *
         * @param deplacement le type de deplacement.
         * @param cible la nouvelle position.
         * @throw err::DeplacementErreur
         * Quand le deplacement demande n'est pas disponible
         */
        virtual void deplacer(Deplacement deplacement, hex::Coordonnees cible);

        /**
         * @brief Accepte un visiteur.
         *
         * @param visiteur Le visiteur à accepter.
         */
        virtual void accepter(IPersonnageVisiteur& visiteur) const = 0;

        /**
         * @brief Confie un objet.
         *
         * @param objet L'objet à confier.
         *
         * @throw std::logic_error Quand la classe concrète ne le permet pas.
         */
        virtual void ajouterObjet(obj::IObjet_S objet);

        /**
         * @brief Perd un objet de son inventaire.
         *
         * @param objet L'objet perdu.
         *
         * @throw std::logic_error Quand la classe concrète ne le permet pas.
         */
        virtual void retirerObjet(obj::IObjet_S objet);

        /**
         * @brief Donne la taille du sac (aka. le nombre d'IObjet qu'il contient)
         *
         * @return La taille du sac.
         */
        virtual size_t tailleSac() const;

        /**
         * @brief Obtient l'objet à l'indice indiqué.
         *
         * @param indice L'indice de l'objet dans le sac.
         * @return L'objet à cet indice.
         *
         * @throw std::out_of_range Quand il n'y a pas d'objet à l'indice donné.
         */
        virtual obj::IObjet_SC getObjet(size_t indice) const;

        /**
         * @brief Obtient l'objet à l'indice indiqué.
         *
         * @param indice L'indice de l'objet dans le sac.
         * @return L'objet à cet indice.
         *
         * @throw std::out_of_range Quand il n'y a pas d'objet à l'indice donné.
         */
        virtual obj::IObjet_S getObjet(size_t indice);
    };

    using APersonnage_S = std::shared_ptr<APersonnage>;
    using APersonnage_SC = std::shared_ptr<const APersonnage>;
}; // namespace per

#endif // __APERSONNAGE_HPP__
