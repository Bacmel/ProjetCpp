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
        void deposer(obj::IObjet_S objet) override;
        obj::IObjet_S ramasser() override;
        bool aObjet() const override;
        const obj::IObjet_SC getObjet() const override;
        const obj::IObjet_S getObjet() override;
        void enEntree(per::APersonnage& personnage) override;
        bool estPraticable() const override;
        void enActivation(per::APersonnage& personnage) override;
        bool estTransparent() const override;
        void accepter(ICaseVisiteur& visiteur) const override;
        /* Méthode IActualisable. */
        void actualiser() override;
    };
} // namespace donjon::cases
#endif // __TROU_HPP__
