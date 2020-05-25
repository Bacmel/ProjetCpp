#ifndef __CASE_H__
#define __CASE_H__

#include <memory>
#include "obj/IObjet.hpp"
#include "per/APersonnage.hpp"

namespace donjon::cases
{
    class ICase
    {
    public:
        virtual ~ICase() {}

        /**
         * @brief Dépose un objet sur une case.
         *
         * @param objet L'objet à déposer.
         *
         * @throw DepotError Quand le dépot est refusé (un objet est déjà
         *                   présent ou la case ne le permet pas).
         */
        virtual void deposer(obj::IObjet_S objet) = 0;

        /**
         * @brief Donne l'objet et le retire.
         *
         * @return obj::IObjet_S L'objet présent sur la case.
         *
         * @throw SansObjetError Quand la case n'a pas d'objet.
         */
        virtual obj::IObjet_S ramasser() = 0;

        /**
         * @brief Obtient l'objet déposé.
         *
         * @return const obj::IObjet& L'objet déposé.
         *
         * @throw SansObjetError Quand la case n'a pas d'objet.
         */
        virtual const obj::IObjet& getObjet() const = 0;

        /**
         * @brief Notifie qu'un personnage est arrivé.
         *
         * @param personnage Le personnage arrivé.
         */
        virtual void enEntree(per::APersonnage& personnage) = 0;

        /**
         * @brief Notifie qu'un personnage a activé la case.
         *
         * @param personnage Le personnage qui active la case.
         */
        virtual void enActivation(per::APersonnage& personnage) = 0;

        /**
         * @brief Indique si un personnage peut marcher sur la case.
         *
         * @return true Un personnage peut être déplace sur la case.
         * @return false Un personnage ne peut pas être déplacé sur la case.
         */
        virtual bool estPraticable() const = 0;

        /**
         * @brief Indique si un personnage peut voir au travers de la case.
         *
         * @return true Si la vue n'est pas bloquée sinon false.
         */
        virtual bool estTransparent() const = 0;
    };

    using ICase_S = std::shared_ptr<ICase>;
    using ICase_SC = std::shared_ptr<const ICase>;
} // namespace donjon

#endif // __CASE_H__