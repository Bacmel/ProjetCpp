#ifndef __IPERSONNAGEVISITEUR_H__
#define __IPERSONNAGEVISITEUR_H__

#include "per/Fantassin.hpp"
#include "per/Heros.hpp"

namespace per
{
    class IPersonnageVisiteur
    {
    public:
        virtual ~IPersonnageVisiteur() {}

        virtual void visiter(const per::Heros& heros) = 0;
        virtual void visiter(const per::Fantassin& fantassin) = 0;
    };
} // namespace per
#endif // __IPERSONNAGEVISITEUR_H__
