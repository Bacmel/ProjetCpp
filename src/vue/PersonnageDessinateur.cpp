#include "vue/PersonnageDessinateur.hpp"

using namespace sf;

namespace vue
{
    PersonnageDessinateur::PersonnageDessinateur(sf::RenderTarget& cible) :
        ADessinateur(50),
        m_cible(cible),
        m_sprite(),
        m_herosTex()
    {
        TextureGest& gest = TextureGest::getInstance();
        m_herosTex = gest.obtenir("resources/textures/per/heros.png");
    }

    void PersonnageDessinateur::dessiner(const per::APersonnage& personnage)
    {
        Vector2u dim = m_cible.getSize();
        m_sprite = Sprite();
        // Déplace le sprite au coordonnées.
        Vector2f pixel = hexVersPixel(personnage.getPosition());
        Vector2f posSprite(dim.x / 2. + pixel.x, dim.y / 2. + pixel.y);
        m_sprite.setPosition(posSprite);
        // Adapte le sprite puis le dessine.
        preparerBarreSante(personnage);
        float cote = getRayon();

        m_barFond.setPosition(posSprite.x - cote / 2, posSprite.y - cote / 2 - m_barFond.getSize().y * 1.25);
        m_barValeur.setPosition(posSprite.x - cote / 2, posSprite.y - cote / 2 - m_barFond.getSize().y * 1.25);
        personnage.accepter(*this);
        m_cible.draw(m_sprite);
        m_cible.draw(m_barFond);
        m_cible.draw(m_barValeur);
    }

    void PersonnageDessinateur::visiter(__attribute__((unused)) const per::Heros& heros)
    {
        m_sprite.setTexture(*m_herosTex);
        Vector2u dim = m_herosTex->getSize();
        // Met l'origine du sprite en son centre.
        m_sprite.setOrigin(dim.x / 2., dim.y / 2.);
        // Rend la longueur du côté du sprite égale à celle d'une case.
        float cote = getRayon();
        m_sprite.setScale(cote / dim.x, cote / dim.y);
    }

    void PersonnageDessinateur::visiter(__attribute__((unused)) const per::Fantassin& fantassin) {}

    void PersonnageDessinateur::preparerBarreSante(const per::APersonnage& personnage)
    {
        float cote = getRayon();
        // Prépare une nouvelle barre de fond.
        Vector2f taille(cote, cote / 5.);
        m_barFond = RectangleShape(taille);
        m_barFond.setFillColor(Color(150, 150, 150));
        // Prépare une nouvelle barre de valeur.
        size_t santeMax = personnage.getSanteMax();
        size_t sante = personnage.getSante();
        Vector2f tailleValeur((cote-5) * sante / santeMax, taille.y -5);
        m_barValeur = RectangleShape(tailleValeur);
        m_barValeur.setFillColor(Color::Red);
        m_barValeur.setOrigin(-Vector2f(2.5, 2.5));
    }

} // namespace vue
