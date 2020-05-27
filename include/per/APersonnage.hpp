#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include <memory>
#include "hex/Coordonnees.hpp"
#include "utils/Jauge.hpp"

namespace per
{
    enum class Deplacement
    {
        Marcher,
        Sauter,
        Forcer
    };

    class APersonnage
    {
    protected:
        /** Nombre de Personnages*/
        static size_t idSuivante;

        /** Santé du Personnage et points de vie actuel */
        utils::Jauge m_pv;
        /** Coordonnée du Personnage */
        hex::Coordonnees m_position;
        /** Identifiant Personnage */
        size_t const m_id;

    public:
        APersonnage(size_t pvMax, hex::Coordonnees position);

        virtual ~APersonnage() = 0;

        /**
         * @brief Prédicat sur la vie du personnage.
         *
         * @return true Si le joueur est vivant.
         * @return false sinon.
         */
        virtual bool estVivant() const;

        /**
         * @brief Fait subir une attaque.
         *
         * La source n'est pas forcément un joueur jouable par un humain ou
         * l'ordinateur. Les dégats d'environnement sont associés à un joueur
         * qui représente l'environnement.
         *
         * @param degat La quantité de dégats (peut être différents de la santé
         *              retirée).
         */
        virtual void subitAttaque(size_t degat);

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
        virtual hex::Coordonnees getPosition() const { return m_position; }

        /**
         * @brief Modifie la santé.
         *
         * @param sante La santé à ajouter. Elle peut être négative.
         */
        void ajouterSante(int sante);

        /**
         * @brief Modifie la santé maximale
         *
         * @param sante La santé à ajouter. Elle peut être négative.
         */
        void ajouterSanteMax(int sante);

        /**
         * @brief Redefinit la position.
         *
         * @param deplacement le type de deplacement.
         * @param cible la nouvelle position.
         * @throw DeplacementError Quand le deplacement
         * demande n'est pas disponible
         */
        virtual void deplacer(Deplacement deplacement, hex::Coordonnees cible) = 0;

        /**
         * @brief Tue le personnage.
         */
        virtual void tuer();
    };

    using APersonnage_S = std::shared_ptr<APersonnage>;
    using APersonnage_SC = std::shared_ptr<const APersonnage>;

}; // namespace per

#endif
