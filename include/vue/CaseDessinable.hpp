#ifndef __CASEDESSINABLE_H__
#define __CASEDESSINABLE_H__

#include "vue/ADessinable.hpp"
#include "donjon/cases/ICaseVisiteur.hpp"
#include "utils/IObservateur.hpp"
#include "vue/ObjetDessinable.hpp"
#include "vue/TextureGest.hpp"

namespace vue
{
    class CaseDessinable : public vue::ADessinable<donjon::cases::ICase>,
                           public donjon::cases::ICaseVisiteur,
                           public utils::IObservateur<donjon::cases::ICase>
    {
    private:
        donjon::cases::ICase* m_case;
        sf::CircleShape m_hexagone;
        Texture_S m_textureSol;
        Texture_S m_textureTrou;
        ObjetDessinable m_objDessinable;

    public:
        CaseDessinable(float cote);
        CaseDessinable(float cote, donjon::cases::ICase& iCase);
        virtual ~CaseDessinable() {}

        void setCote(float cote) override;

        void setElement(donjon::cases::ICase& iCase) override;

        virtual void visite(const donjon::cases::Sol& sol) override;

        virtual void visite(const donjon::cases::Trou& trou) override;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        virtual void actualiser(const donjon::cases::ICase& iCase) override;
    };
} // namespace vue
#endif // __CASEDESSINABLE_H__
