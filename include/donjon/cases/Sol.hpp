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

        Sol(const Sol& autre) = default;
        Sol(Sol&& autre) = default;
        Sol& operator=(const Sol& autre) = default;
        Sol& operator=(Sol&& autre) = default;
        virtual ~Sol() = default;

        void deposer(obj::IObjet_S objet) override;

        obj::IObjet_S ramasser() override;

        bool aObjet() const override;

        const obj::IObjet& getObjet() const override;

        void enEntree(per::APersonnage& personnage) override;

        bool estPraticable() const override;

        void enActivation(per::APersonnage& personnage) override;

        bool estTransparent() const override;

        void accepter(ICaseVisiteur& visiteur) const override;

        void actualiser() override;
    };
} // namespace donjon::cases
#endif // __SOL_HPP__
