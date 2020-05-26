#ifndef __CASEINTERDITE_H__
#define __CASEINTERDITE_H__

#include "donjon/cases/ICase.hpp"

namespace donjon::cases
{
    class CaseInterdite : public ICase
    {
    public:
        CaseInterdite();

        CaseInterdite(const CaseInterdite& autre) = default;
        CaseInterdite(CaseInterdite&& autre) = default;
        CaseInterdite& operator=(const CaseInterdite& autre) = default;
        CaseInterdite& operator=(CaseInterdite&& autre) = default;
        ~CaseInterdite() = default;

        virtual void deposer(obj::IObjet_S objet) override;

        virtual obj::IObjet_S ramasser() override;

        virtual const obj::IObjet& getObjet() const override;

        virtual void enEntree(per::APersonnage& personnage) override;

        virtual bool estPraticable() const override;

        virtual void enActivation(per::APersonnage& personnage) override;

        virtual bool estTransparent() const override;
    };
} // namespace donjon::cases
#endif // __CASEINTERDITE_H__
