#ifndef __DONJON_H__
#define __DONJON_H__

#include <vector>
#include "donjon/cases/ICase.hpp"
#include "donjon/IDonjon.hpp"
#include "hex/ICarte.hpp"
#include "per/APersonnage.hpp"

namespace donjon
{
    class Donjon : public IDonjon
    {
        std::vector<per::APersonnage_S>::iterator m_personnageActif;
        std::vector<per::APersonnage_S> m_personnages;
        hex::ICarte_S<ICase_S> m_carte;
        bool m_termine;
        per::APersonnage_S m_vainqueur;

    public:
        /**
         * @brief Construit un Donjon.
         *
         * @param carte Le terrain.
         */
        explicit Donjon(const hex::ICarte_S<ICase_S>& carte);

        /**
         * @brief Obtient la liste des personnages.
         *
         * @return std::vector<per::APersonnage_S>& La liste des personnages.
         */
        inline std::vector<per::APersonnage_S>& getPersonnages() { return m_personnages; }

        /**
         * @brief Obtient la carte du donjon.
         *
         * @return hex::ICarte_S<ICase_S> La carte du donjon.
         */
        inline hex::ICarte_S<ICase_S> getCarte() { return m_carte; }

        inline per::APersonnage_S getPersonnageActif() override { return *m_personnageActif; }

        inline per::APersonnage_SC getPersonnageActif() const override { return *m_personnageActif; }

        virtual void invoquer(per::APersonnage_S personnage, const hex::Coordonnees& position) override;

        virtual void deplace(const hex::Coordonnees& position) override;

        virtual void deplace(per::APersonnage& personnage, const hex::Coordonnees& position) override;

        virtual void degat(const hex::Coordonnees& centre, const hex::ICarte<bool>& zone, size_t degats) override;

        virtual void deposer(obj::IObjet_S objet, const hex::Coordonnees& position) override;

        virtual obj::IObjet_S ramasser(const hex::Coordonnees& position) override;

        virtual void finirTour() override;

        Donjon(Donjon&&) = default;
        Donjon(const Donjon&) = default;
        Donjon& operator=(Donjon&&) = default;
        Donjon& operator=(const Donjon&) = default;
        virtual ~Donjon() = default;
    };
} // namespace donjon

#endif // __DONJON_H__
