#ifndef __PERSONNAGEDESSINABLE_H__
#define __PERSONNAGEDESSINABLE_H__

#include <SFML/Graphics.hpp>
#include "per/IPersonnageVisiteur.hpp"
#include "utils/IObservateur.hpp"
#include "vue/TextureGest.hpp"

namespace vue
{
    class PersonnageDessinable : public sf::Drawable,
                                 public sf::Transformable,
                                 public per::IPersonnageVisiteur,
                                 public utils::IObservateur<per::APersonnage>
    {
    private:
        float m_cote;
        float m_margin;
        per::APersonnage* m_personnage;
        sf::Sprite m_sprite;
        sf::RectangleShape m_barFond;
        sf::RectangleShape m_barValeur;
        Texture_S m_herosTex;

    public:
        /**
         * @brief Crée un dessinateur de Personnage.
         *
         * @param cote La longueur du côté des hexagones.
         * @param aPersonnage Un personnage à dessiner.
         */
        PersonnageDessinable(float cote = 50, per::APersonnage* aPersonnage = nullptr);

        const per::APersonnage* getPersonnage() const { return m_personnage; }

        per::APersonnage* getPersonnage() { return m_personnage; }

        float getCote() const { return m_cote; }

        void setCote(float cote);

        void setPersonnage(per::APersonnage& personnage);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        virtual void visiter(const per::Heros& heros) override;

        virtual void visiter(const per::Fantassin& fantassin) override;

        virtual void actualiser(const per::APersonnage& info) override;

    private:
        void preparerBarreSante(const per::APersonnage& personnage);
    };
} // namespace vue
#endif // __PERSONNAGEDESSINABLE_H__
