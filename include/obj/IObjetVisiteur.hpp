#ifndef __IOBJETVISITEUR_HPP__
    #define __IOBJETVISITEUR_H__

    #include "obj/GravityGun.hpp"
    #include "obj/Taser.hpp"

namespace obj
{
    class IObjetVisiteur
    {
    public:
        virtual ~IObjetVisiteur() = default;

        /**
         * @brief Permet au visiteur d'adapter son action au GravityGun.
         *
         * @param gravityGun Le gravity gun à visiter.
         */
        virtual void visiter(const obj::GravityGun& gravityGun) = 0;

        /**
         * @brief Permet au visiteur d'adapter son action au Taser.
         *
         * @param taser Le taser à visiter.
         */
        virtual void visiter(const obj::Taser& taser) = 0;
    };
} // namespace obj
#endif // __IOBJETVISITEUR_HPP__
