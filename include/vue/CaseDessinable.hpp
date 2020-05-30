#ifndef __CASEDESSINABLE_H__
#define __CASEDESSINABLE_H__

#include <SFML/Graphics.hpp>
#include "donjon/cases/ICaseVisiteur.hpp"
#include "utils/IObservateur.hpp"
#include "vue/ObjetDessinable.hpp"
#include "vue/TextureGest.hpp"

namespace vue
{
    class CaseDessinable : public sf::Drawable,
                           public sf::Transformable,
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
        /**
         * @brief Construit un dessinateur de case dédié à la cible.
         *
         * @param cible La toile du dessin.
         */
        CaseDessinable(float cote = 50.f, donjon::cases::ICase* iCase = nullptr);
        virtual ~CaseDessinable() {}

        float getCote() const { return m_hexagone.getRadius(); }

        void setCase(donjon::cases::ICase& iCase);

        void setCote(float cote);

        virtual void visite(const donjon::cases::Sol& sol) override;

        virtual void visite(const donjon::cases::Trou& trou) override;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        virtual void actualiser(const donjon::cases::ICase& iCase) override;
    };
} // namespace vue
#endif // __CASEDESSINABLE_H__
