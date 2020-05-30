#include "vue/PersonnageDessinable.hpp"

using namespace sf;

namespace vue
{
    PersonnageDessinable::PersonnageDessinable(float cote, per::APersonnage* aPersonnage) :
        m_cote(cote),
        m_margin(2),
        m_personnage(nullptr),
        m_sprite(),
        m_barFond(),
        m_barValeur(),
        m_herosTex()
    {
        // Récupération des textures.
        TextureGest& gest = TextureGest::getInstance();
        m_herosTex = gest.obtenir("resources/textures/per/heros.png");

        if (aPersonnage != nullptr) { setPersonnage(*aPersonnage); }
    }

    void PersonnageDessinable::setCote(float cote)
    {
        m_cote = cote;
        if (m_personnage != nullptr) { actualiser(*m_personnage); }
    }

    void PersonnageDessinable::setPersonnage(per::APersonnage& personnage)
    {
        m_personnage = &personnage;
        actualiser(personnage);
    }

    void PersonnageDessinable::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_sprite, states);
        target.draw(m_barFond, states);
        target.draw(m_barValeur, states);
    }

    void PersonnageDessinable::visiter(__attribute__((unused)) const per::Heros& heros)
    {
        m_sprite.setTexture(*m_herosTex);
        Vector2u dim = m_herosTex->getSize();
        // Met l'origine du sprite en son centre.
        m_sprite.setOrigin(dim.x / 2., dim.y / 2.);
        // Rend la longueur du côté du sprite égale à celle d'une case.
        m_sprite.setScale(m_cote / dim.x, m_cote / dim.y);
    }

    void PersonnageDessinable::actualiser(const per::APersonnage& personnage)
    {
        preparerBarreSante(personnage);

        m_barFond.setPosition(-m_cote / 2, -m_cote / 2 - m_barFond.getSize().y * 1.25);
        m_barValeur.setPosition(-m_cote / 2, -m_cote / 2 - m_barFond.getSize().y * 1.25);
        personnage.accepter(*this);
    }
    void PersonnageDessinable::visiter(__attribute__((unused)) const per::Fantassin& fantassin) {}

    void PersonnageDessinable::preparerBarreSante(const per::APersonnage& personnage)
    {
        // Prépare une nouvelle barre de fond.
        Vector2f taille(m_cote, m_cote / 5.);
        m_barFond = RectangleShape(taille);
        m_barFond.setFillColor(Color(150, 150, 150));
        // Prépare une nouvelle barre de valeur.
        size_t santeMax = personnage.getSanteMax();
        size_t sante = personnage.getSante();
        Vector2f tailleValeur((m_cote - m_margin) * sante / santeMax, taille.y - m_margin);
        m_barValeur = RectangleShape(tailleValeur);
        m_barValeur.setFillColor(Color::Red);
        m_barValeur.setOrigin(-Vector2f(m_margin / 2, m_margin / 2));
    }

} // namespace vue
