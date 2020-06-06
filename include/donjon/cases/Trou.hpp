#ifndef __TROU_HPP__
#define __TROU_HPP__

#include "donjon/cases/ACase.hpp"

namespace donjon::cases
{
    class Trou : public ACase
    {
    public:
        /**
         * @brief Construit un Trou.
         */
        Trou();

        /* Constructeurs & operateurs de copie & destructeur */
        Trou(const Trou& autre) = default;
        Trou(Trou&& autre) = default;
        Trou& operator=(const Trou& autre) = default;
        Trou& operator=(Trou&& autre) = default;
        ~Trou() = default;

        /* Méthodes ICase. */
        virtual void deposer(obj::IObjet_S objet) override;
        virtual obj::IObjet_S ramasser() override;
        virtual bool aObjet() const override;
        virtual const obj::IObjet& getObjet() const override;
        virtual void enEntree(per::APersonnage& personnage) override;
        virtual bool estPraticable() const override;
        virtual void enActivation(per::APersonnage& personnage) override;
        virtual bool estTransparent() const override;
        virtual void accepter(ICaseVisiteur& visiteur) const override;

        /* Méthode IActualisable. */
        virtual void actualiser() override;
    };
} // namespace donjon::cases
#endif // __TROU_HPP__
