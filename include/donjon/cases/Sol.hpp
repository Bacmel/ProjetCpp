#ifndef __SOL_HPP__
#define __SOL_HPP__

#include "donjon/cases/ACase.hpp"

namespace donjon::cases
{
    class Sol : public ACase
    {
    private:
        /**
         * @brief Un objet présent sur la case.
         */
        obj::IObjet_S m_objet;

    public:
        /**
         * @brief Construit un sol.
         *
         * Le sol ne possêde pas d'objet.
         */
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
#endif // __SOL_HPP__
