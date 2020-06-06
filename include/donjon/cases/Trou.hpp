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

        Trou(const Trou& autre) = default;
        Trou(Trou&& autre) = default;
        Trou& operator=(const Trou& autre) = default;
        Trou& operator=(Trou&& autre) = default;
        ~Trou() = default;

        void deposer(obj::IObjet_S objet) override;

        obj::IObjet_S ramasser() override;

        bool aObjet() const override;

        const obj::IObjet& getObjet() const override;

        void enEntree(per::APersonnage& personnage) override;

        bool estPraticable() const override;

        void enActivation(per::APersonnage& personnage) override;

        bool estTransparent() const override;

        void accepter(ICaseVisiteur& visiteur) const override;
    };
} // namespace donjon::cases
#endif // __TROU_HPP__
