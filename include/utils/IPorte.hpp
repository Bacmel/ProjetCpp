#ifndef __IPORTE_HPP__
#define __IPORTE_HPP__

#include "hex/Masque.hpp"

namespace utils
{
    class IPorte
    {
    public:
        virtual ~IPorte() = default; 

        /**
         * @brief Obtient le masque de la porte des actions.
         * 
         * @return porte le masque de la porte.
         */
        virtual hex::Masque getPorte() const = 0;

        /**
         * @brief Obtient le masque des degats.
         * 
         * @param cible la coordonnees cible.
         * @return le masque de degat.
         */
        virtual hex::Masque getZoneDegat(const hex::Coordonnees& cible) const = 0;
    };
} // namespace utils

#endif // __IPORTE_HPP__