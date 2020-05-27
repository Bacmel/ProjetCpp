#ifndef __PERSONNAGECOMPARATEUR_H__
#define __PERSONNAGECOMPARATEUR_H__

#include "per/APersonnage.hpp"
namespace donjon
{
    struct PersonnageComparateur
    {
        /**
         * @brief Compare les deux personnage.
         *
         * @param p1 Le 1er personnage à comparer.
         * @param p2 Le 2eme personnage à comparer.
         * @return true si p1 est inférieur à p2 sinon false.
         */
        bool operator()(const per::APersonnage_S& p1, const per::APersonnage_S& p2);
    };

} // namespace donjon
#endif // __PERSONNAGECOMPARATEUR_H__
