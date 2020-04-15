#ifndef __CASE_H__
#define __CASE_H__

#include <memory>
#include "obj/IObjet.hpp"
#include "per/IPersonnage.hpp"

namespace donjon
{
    class ICase
    {
    public:
        typedef std::shared_ptr<ICase> Ptr;
        typedef std::shared_ptr<const ICase> ConstPtr;

        virtual ~ICase() {}

        /**
         * @brief Dépose un objet sur une case.
         *
         * @param objet L'objet à déposer.
         *
         * @throw DepotError Quand le dépot est refusé (un objet est déjà
         *                   présent ou la case ne le permet pas).
         */
        virtual void deposer(obj::IObjet::Ptr objet) = 0;

        /**
         * @brief Donne l'objet et le retire.
         *
         * @return obj::IObjet::Ptr L'objet présent sur la case.
         *
         * @throw SansObjetError Quand la case n'a pas d'objet.
         */
        virtual obj::IObjet::Ptr ramasser() = 0;

        /**
         * @brief Obtient l'objet déposé.
         *
         * @return const obj::IObjet& L'objet déposé.
         *
         * @throw SansObjetError Quand la case n'a pas d'objet.
         */
        virtual const obj::IObjet& getObjet() const = 0;
    };
} // namespace donjon

#endif // __CASE_H__
