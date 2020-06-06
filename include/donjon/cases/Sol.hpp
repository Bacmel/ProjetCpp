#ifndef __CASENEUTRE_HPP__
#define __CASENEUTRE_HPP__

#include "donjon/cases/ICase.hpp"

namespace donjon::cases
{
    class Sol : public ICase
    {
        obj::IObjet_S m_objet;

    public:
        Sol();

        /* Constructeurs & operateurs de copie & destructeur */
        Sol(const Sol& autre) = default;
        Sol(Sol&& autre) = default;
        Sol& operator=(const Sol& autre) = default;
        Sol& operator=(Sol&& autre) = default;
        virtual ~Sol() = default;

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

#endif // __CASENEUTRE_HPP__
