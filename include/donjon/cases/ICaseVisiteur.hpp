#ifndef __ICASEVISITEUR_H__
#define __ICASEVISITEUR_H__

#include "donjon/cases/Sol.hpp"
#include "donjon/cases/Trou.hpp"
namespace donjon::cases
{
    class ICaseVisiteur
    {
    public:
        virtual void visite(const Sol& sol) = 0;
        virtual void visite(const Trou& trou) = 0;

        virtual ~ICaseVisiteur() = default;
    };
} // namespace donjon::cases
#endif // __ICASEVISITEUR_H__
