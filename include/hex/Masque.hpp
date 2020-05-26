#ifndef __IMASQUE_H__
#define __IMASQUE_H__

#include "hex/CarteHexagone.hpp"

namespace hex
{
    class Masque : public CarteHexagone<bool>
    {
    public:
        /**
         * @brief Construit un nouveau masque hexagonale.
         *
         * Le rayon ne tient pas compte de la case centrale. Un masque de rayon
         * 0 est de diamètre 1. Un masque de rayon 2 est de diamètre 5.
         *
         * @param rayon Le rayon de l'hexagone (ne compte pas le centre).
         */
        explicit Masque(size_t rayon);

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
         * @brief Applique un NON sur chaque case.
         *
         * @return Le masque inverse de l'instance.
         */
        virtual Masque operator!() const;
    };
} // namespace hex

#endif // __IMASQUE_H__
