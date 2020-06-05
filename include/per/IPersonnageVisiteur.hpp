#ifndef __IPERSONNAGEVISITEUR_HPP__
#define __IPERSONNAGEVISITEUR_HPP__

#include "per/Fantassin.hpp"
#include "per/Heros.hpp"

namespace per
{
    class IPersonnageVisiteur
    {
    public:
        virtual ~IPersonnageVisiteur() {}

        /**
         * @brief Permet d'obtenir l'instance précise d'un APersonnage_S.
         *
         * @param heros l'instance a visiter.
         */
        virtual void visiter(const Heros& heros) = 0;

        /**
         * @brief Permet d'obtenir l'instance précise d'un APersonnage_S.
         *
         * @param fantassin l'instance a visiter.
         */
        virtual void visiter(const Fantassin& fantassin) = 0;
    };
} // namespace per
#endif // __IPERSONNAGEVISITEUR_HPP__