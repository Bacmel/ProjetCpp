#ifndef __ICASEVISITEUR_HPP__
#define __ICASEVISITEUR_HPP__

#include "donjon/cases/Sol.hpp"
#include "donjon/cases/Trou.hpp"
namespace donjon::cases
{
    class ICaseVisiteur
    {
    public:
        virtual ~ICaseVisiteur() = default;

        /**
         * @brief Visite le type concret Sol.
         *
         * @param sol Le Sol visité.
         */
        virtual void visite(const Sol& sol) = 0;

        /**
         * @brief Visite le type concret Trou.
         *
         * @param trou Le Trou visité.
         */
        virtual void visite(const Trou& trou) = 0;
    };
} // namespace donjon::cases
#endif // __ICASEVISITEUR_HPP__
