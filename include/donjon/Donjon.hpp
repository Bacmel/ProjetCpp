#ifndef __DONJON_H__
#define __DONJON_H__

#include "donjon/IDonjon.hpp"
#include <vector>
#include "donjon/Entite.hpp"
#include "hex/ICarte.hpp"
#include "donjon/ICase.hpp"

namespace donjon
{
    class Donjon : public IDonjon
    {
        std::vector<Entite> m_entites;
        hex::ICarte_S<ICase_S> m_carte;

    public:
        Donjon(const hex::ICarte_S<ICase_S>& carte);

        virtual void jouer() override;
        virtual void deplace(const per::IPersonnage& personnage, const hex::Coordonnees& position) override;
        virtual void degat(const hex::Coordonnees& centre, const hex::ICarte<bool>& zone, size_t degats) override;
        virtual void deposer(obj::IObjet_S objet, const hex::Coordonnees& position) override;
        virtual obj::IObjet_S ramasser(const hex::Coordonnees& position) override;

        Donjon(Donjon&&) = default;
        Donjon(const Donjon&) = default;
        Donjon& operator=(Donjon&&) = default;
        Donjon& operator=(const Donjon&) = default;
        virtual ~Donjon() = default;
    };
} // namespace donjon

#endif // __DONJON_H__
