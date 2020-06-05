#ifndef __MASQUE_H__
#define __MASQUE_H__

#include <set>
#include "hex/Coordonnees.hpp"

namespace hex
{
    class Masque : public std::set<Coordonnees>
    {
    public:
        /**
         * @brief Genere un anneau de rayon 1.
         *
         * @return Le anneau de rayon 1.
         */
        static Masque contour();

        /**
         * @brief Crée un masque vide.
         */
        Masque();

        /* Constructeurs & operateurs de copie & destructeur */
        Masque(const Masque& autre) = default;
        Masque(Masque&& autre) = default;
        Masque& operator=(const Masque& autre) = default;
        Masque& operator=(Masque&& autre) = default;
        ~Masque() = default;

        /**
         * @brief Deplace l'ensemble des cases.
         *
         * @param vecteur le vecteur de deplacement.
         * @return Le masque deplace.
         */
        virtual Masque deplacer(const Coordonnees& vecteur) const;

        /**
         * @brief Indique la valeur booleenne de la case.
         *
         * @param coordonnees la case a etudier.
         * @return bool la valeur de la case
         */
        virtual bool operator()(const Coordonnees& c) const;

        /**
         * @brief Tourne le masque vers la gauche.
         *
         * @param centre Le centre de la rotation.
         * @return Le masque tourné vers la gauche.
         */
        virtual Masque tournerTrigonometrique(const Coordonnees& centre) const;

        /**
         * @brief Tourne le masque vers la droite.
         *
         * @param centre Le centre de la rotation.
         * @return Le masque tourné vers la droite.
         */
        virtual Masque tournerHoraire(const Coordonnees& centre) const;

        /**
         * @brief Tourne d'une direction vers une autre.
         *
         * @param centre Le centre de la rotation.
         * @param cible L'orientation voulue.
         * @param initiale L'orientation initiale.
         * @return Le masque tourné jusqu'à la direction ciblée.
         */
        virtual Masque tournerVers(const Coordonnees& centre, Direction cible, Direction initiale) const;

        /**
         * @brief Applique un OU case par case entre les deux masques.
         *
         * @param autre Un autre masque. Il doit être de la même taille que
         * l'instance.
         * @return Le masque résultant du OU case par case.
         */
        virtual Masque operator||(const Masque& autre) const;

        /**
         * @brief Applique un ET case par case entre les deux masques.
         *
         * @param autre Un autre masque. Il doit être de la même taille que
         * l'instance.
         * @return Le masque résultant du ET case par case.
         */
        virtual Masque operator&&(const Masque& autre) const;

        /**
         * @brief Ajoute une case au masque.
         *
         * @param autre une autre case.
         * @return Le masque résultant plus une case.
         */
        virtual Masque operator+(const Coordonnees& autre) const;

        /**
         * @brief Retire une case au masque.
         *
         * @param autre une autre case.
         * @return Le masque résultant plus une case.
         */
        virtual Masque operator-(const Coordonnees& autre) const;
    };
} // namespace hex

#endif // __MASQUE_H__
