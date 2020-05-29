#ifndef __PERSONNAGEDESSINATEUR_H__
#define __PERSONNAGEDESSINATEUR_H__

#include <SFML/Graphics.hpp>
#include "per/IPersonnageVisiteur.hpp"
#include "vue/ADessinateur.hpp"
#include "vue/TextureGest.hpp"

namespace vue
{
    class PersonnageDessinateur : public vue::ADessinateur, public per::IPersonnageVisiteur
    {
    private:
        sf::RenderTarget& m_cible;
        sf::Sprite m_sprite;
        sf::RectangleShape m_barFond;
        sf::RectangleShape m_barValeur;
        Texture_S m_herosTex;

    public:
        /**
         * @brief Crée un dessinateur de Personnage.
         *
         * @param m_cible
         */
        PersonnageDessinateur(sf::RenderTarget& cible);

        void dessiner(const per::APersonnage& personnage);

        virtual void visiter(const per::Heros& heros) override;

        virtual void visiter(const per::Fantassin& fantassin) override;

    private:
        void preparerBarreSante(const per::APersonnage& personnage);
    };
} // namespace vue
#endif // __PERSONNAGEDESSINATEUR_H__
