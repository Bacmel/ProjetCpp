#ifndef __DONJON_HPP__
#define __DONJON_HPP__

#include <vector>
#include "donjon/IDonjon.hpp"
#include "donjon/cases/ACase.hpp"
#include "hex/ICarte.hpp"
#include "per/APersonnage.hpp"

namespace donjon
{
    class Donjon : public IDonjon
    {
    private:
        std::vector<per::APersonnage_S> m_personnages;
        hex::ICarte_S<cases::ACase_S> m_carte;

    public:
        /**
         * @brief Construit un Donjon.
         *
         * @param carte Le terrain.
         */
        explicit Donjon(const hex::ICarte_S<cases::ACase_S>& carte);

        Donjon(Donjon&&) = default;
        Donjon(const Donjon&) = default;
        Donjon& operator=(Donjon&&) = default;
        Donjon& operator=(const Donjon&) = default;
        ~Donjon() = default;

        /**
         * @brief Obtient la liste des personnages.
         *
         * @return std::vector<per::APersonnage_S>& La liste des personnages.
         */
        std::vector<per::APersonnage_SC> getPersonnages() const;

        /**
         * @brief Obtient la carte du donjon.
         *
         * @return hex::ICarte_S<cases::ACase_S> La carte du donjon.
         */
        inline hex::ICarte_S<cases::ACase_S> getCarte() { return m_carte; }

        /* Implémentation de IDonjon */
        virtual void invoquer(per::APersonnage_S personnage, const hex::Coordonnees& position) override;
        virtual void deplacer(per::APersonnage& personnage,
                              per::Deplacement type,
                              const hex::Coordonnees& position) override;
        virtual void pousser(const std::map<hex::Coordonnees, hex::Direction>& aoe, size_t distance) override;
        virtual void degat(const std::map<hex::Coordonnees, size_t>& aoe) override;
        virtual void deposer(obj::IObjet_S objet, const hex::Coordonnees& position) override;
        virtual obj::IObjet_S ramasser(const hex::Coordonnees& position) override;
        std::vector<hex::Coordonnees> getCaseVide() const override;
        size_t getNbPersonnages() const override;
        per::APersonnage_SC getPersonnage(size_t indice) const override;
        per::APersonnage_S getPersonnage(size_t indice) override;
        per::APersonnage_SC getPersonnageParId(size_t id) const override;
        per::APersonnage_S getPersonnageParId(size_t id) override;
        per::APersonnage_SC trouver(const hex::Coordonnees& position) const override;
        per::APersonnage_S trouver(const hex::Coordonnees& position) override;
        bool estOccupee(const hex::Coordonnees& position) const override;

        /* Implémentation de IActualisable */
        void actualiser() override;

    private:
        /**
         * @brief Pousse un personnage.
         *
         * Le personnage s'arrête sur une case non praticable. Il s'arrête s'il
         * collisionne un autre personnage. Il s'arrête s'il heurte un mur ou
         * sort de la carte. Dans ce cas, il prend 1 pt de dégat.
         *
         * @param personnage Le personnage à pousser.
         * @param direction La direction dans laquelle il est poussé.
         * @param distance La distance maximale parcourue.
         */
        void pousse(const per::APersonnage_S& personnage, hex::Direction direction, size_t distance);
    };
} // namespace donjon
#endif // __DONJON_HPP__
