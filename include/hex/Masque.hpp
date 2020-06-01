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
         * @brief Genere un contour true.
         * 
         * @return Le contour true.
         */
        static Masque contour();
        
        explicit Masque();

        /* Constructeurs & operateurs de copie & destructeur */
        Masque(const Masque& autre);
        Masque(Masque&& autre);
        Masque& operator=(const Masque& autre);
        Masque& operator=(Masque&& autre);
        virtual ~Masque();

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
    };
} // namespace hex

#endif // __MASQUE_H__
