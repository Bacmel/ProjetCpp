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
        sf::Font m_font;
        sf::Text m_equipeText;
        sf::RectangleShape m_equipeIndicateur;

    public:
        PartieDessinable(float cote);
        PartieDessinable(float cote, partie::Partie& partie);
        ~PartieDessinable() {}

        void setElement(partie::Partie& element) override;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::FloatRect getCaseInventaire(size_t indice) const;

    private:
        void drawCarte(sf::RenderTarget& target, sf::RenderStates& states, donjon::IDonjon& donjon) const;
        void drawPersonnages(sf::RenderTarget& target, sf::RenderStates& states, donjon::IDonjon& donjon) const;
        void drawEquipe(sf::RenderTarget& target, sf::RenderStates& states) const;
        void drawInventaire(sf::RenderTarget& target, sf::RenderStates& states) const;
        sf::Color couleurEquipe(size_t equipe) const;
    };
} // namespace vue
#endif // __PARTIEDESSINABLE_H__
