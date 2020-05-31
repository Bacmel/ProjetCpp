#ifndef __PARTIEDESSINABLE_H__
#define __PARTIEDESSINABLE_H__

#include "partie/Partie.hpp"
#include "utils/HexPixelConvertisseur.hpp"
#include "utils/IObservateur.hpp"
#include "vue/ADessinable.hpp"

namespace vue
{
    class PartieDessinable : public ADessinable<partie::Partie>
    {
    private:
        utils::HexPixelConvertisseur m_convertisseur;

    public:
        PartieDessinable(float cote);
        PartieDessinable(float cote, partie::Partie& partie);
        ~PartieDessinable() {}

        void setElement(partie::Partie& element) override;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        void drawCarte(sf::RenderTarget& target, sf::RenderStates& states, donjon::IDonjon& donjon) const;
        void drawPersonnages(sf::RenderTarget& target, sf::RenderStates& states, donjon::IDonjon& donjon) const;
    };
} // namespace vue
#endif // __PARTIEDESSINABLE_H__
