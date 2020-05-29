#ifndef __CASEINTERDITE_H__
#define __CASEINTERDITE_H__

#include "donjon/cases/ICase.hpp"

namespace donjon::cases
{
    class Trou : public ICase
    {
    public:
        Trou();

        Trou(const Trou& autre) = default;
        Trou(Trou&& autre) = default;
        Trou& operator=(const Trou& autre) = default;
        Trou& operator=(Trou&& autre) = default;
        ~Trou() = default;

        virtual void deposer(obj::IObjet_S objet) override;

        virtual obj::IObjet_S ramasser() override;

        virtual const obj::IObjet& getObjet() const override;

        virtual void enEntree(per::APersonnage& personnage) override;

        virtual bool estPraticable() const override;

        virtual void enActivation(per::APersonnage& personnage) override;

        virtual bool estTransparent() const override;

        virtual void accepter(ICaseVisiteur& visiteur) const override;
    };
} // namespace donjon::cases
#endif // __CASEINTERDITE_H__
