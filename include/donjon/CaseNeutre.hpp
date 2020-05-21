#ifndef __CASENEUTRE_H__
#define __CASENEUTRE_H__

#include "donjon/ICase.hpp"

namespace donjon
{
    class CaseNeutre : public ICase
    {
        obj::IObjet_S m_objet;

    public:
        CaseNeutre();

        virtual void deposer(obj::IObjet_S objet) override;
        virtual obj::IObjet_S ramasser() override;
        virtual const obj::IObjet& getObjet() const override;

        CaseNeutre(const CaseNeutre& autre) = default;
        CaseNeutre(CaseNeutre&& autre) = default;
        CaseNeutre& operator=(const CaseNeutre& autre) = default;
        CaseNeutre& operator=(CaseNeutre&& autre) = default;
        virtual ~CaseNeutre() = default;
    };

} // namespace donjon

#endif // __CASENEUTRE_H__
