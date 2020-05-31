#ifndef __CASENEUTRE_H__
#define __CASENEUTRE_H__

#include "donjon/cases/ICase.hpp"

namespace donjon::cases
{
    class Sol : public ICase
    {
        obj::IObjet_S m_objet;

    public:
        Sol();

        virtual void deposer(obj::IObjet_S objet) override;

        virtual obj::IObjet_S ramasser() override;

        virtual bool aObjet() const override;

        virtual const obj::IObjet& getObjet() const override;

        virtual void enEntree(per::APersonnage& personnage) override;

        virtual bool estPraticable() const override;

        virtual void enActivation(per::APersonnage& personnage) override;

        virtual bool estTransparent() const override;

        virtual void accepter(ICaseVisiteur& visiteur) const override;

        virtual void actualiser() override;
        
        Sol(const Sol& autre) = default;
        Sol(Sol&& autre) = default;
        Sol& operator=(const Sol& autre) = default;
        Sol& operator=(Sol&& autre) = default;
        virtual ~Sol() = default;
    };

} // namespace donjon::cases

#endif // __CASENEUTRE_H__
