#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include <memory>
#include "hex/Coordonnees.hpp"

namespace per
{

    class IPersonnage
    {
    public:
        typedef std::shared_ptr<IPersonnage> Ptr;
        typedef std::shared_ptr<const IPersonnage> ConstPtr;

        virtual ~IPersonnage() {}

        /**
         * @brief Prédicat sur la vie du personnage.
         *
         * @return true Si le joueur est vivant.
         * @return false sinon.
         */
        virtual bool estVivant() const = 0;

        /**
         * @brief Fait subir une attaque.
         *
         * La source n'est pas forcément un joueur jouable par un humain ou
         * l'ordinateur. Les dégats d'environnement sont associés à un joueur
         * qui représente l'environnement.
         *
         * @param source Le personnage qui émet les dégats.
         * @param degat La quantité de dégats (peut être différents de la santé
         *              retirée).
         */
        virtual void subitAttaque(IPersonnage& source, size_t degat) = 0;

        /**
         * @brief Obtient le nombre de points de vie.
         *
         * @return size_t Le nombre de points de vie.
         */
        virtual size_t getSante() const = 0;

        /**
         * @brief Obtient le nombre maximal de points de vie.
         *
         * @return size_t Le nombre maximal de points de vie.
         */
        virtual size_t getSanteMax() const = 0;
    };

}; // namespace per

#endif
