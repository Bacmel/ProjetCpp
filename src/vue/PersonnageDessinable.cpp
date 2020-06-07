#include "vue/PersonnageDessinable.hpp"

using namespace sf;
using namespace per;

namespace vue
{
    PersonnageDessinable::PersonnageDessinable(float cote) :
        ADessinable(cote),
        m_margin(2),
        m_couleur(255, 255, 255),
        m_sprite(),
        m_barFond(),
        m_barValeur(),
        m_herosTex(),
        m_fantassinTex()
    {
        // Récupération des textures.
        TextureGest& gest = TextureGest::getInstance();
        m_herosTex = gest.obtenir("ressources/textures/per/heros.png");
        m_fantassinTex = gest.obtenir("ressources/textures/per/fantassin.png");
    }

    PersonnageDessinable::PersonnageDessinable(float cote, per::APersonnage_S aPersonnage) :
        ADessinable(cote, aPersonnage),
        m_margin(2),
        m_couleur(255, 255, 255),
        m_sprite(),
        m_barFond(),
        m_barValeur(),
        m_herosTex(),
        m_fantassinTex()
    {
        // Récupération des textures.
        TextureGest& gest = TextureGest::getInstance();
        m_herosTex = gest.obtenir("ressources/textures/per/heros.png");
        m_fantassinTex = gest.obtenir("ressources/textures/per/fantassin.png");
        // S'adapte au personnage.
        setElement(aPersonnage);
    }

    void PersonnageDessinable::setCote(float cote)
    {
        m_cote = cote;
        if (m_element != nullptr) { preparer(); }
    }

    void PersonnageDessinable::setCouleur(const sf::Color& couleur)
    {
        m_couleur = couleur;
        if (m_element != nullptr) { preparer(); }
    }

    void PersonnageDessinable::setElement(APersonnage_S personnage)
    {
        if (personnage == nullptr)
        { throw std::invalid_argument("PersonnageDessinable::setElement : personnage est null!"); }
        m_element = personnage;
        preparer();
    }

    void PersonnageDessinable::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // Applique la transformation et dessine les éléments.
        states.transform *= getTransform();
        target.draw(m_sprite, states);
        target.draw(m_barFond, states);
        target.draw(m_barValeur, states);
    }

    void PersonnageDessinable::preparer()
    {
        if (m_element == nullptr) { return; }
        // Adapte la barre de vie, la couleur du sprite la texture, etc.
        preparerBarreSante(*m_element);
        m_sprite.setColor(m_couleur);
        m_element->accepter(*this);
    }

    void PersonnageDessinable::visiter(const per::Heros&)
    {
        m_sprite.setTexture(*m_herosTex, true);
        // Met l'origine du sprite en son centre.
        Vector2u dim = m_herosTex->getSize();
        m_sprite.setOrigin(dim.x / 2., dim.y / 2.);
        // Rend la longueur du côté du sprite égale à celle d'une case.
        m_sprite.setScale(m_cote / dim.x, m_cote / dim.y);
    }

    void PersonnageDessinable::visiter(const per::Fantassin&)
    {
        m_sprite.setTexture(*m_fantassinTex, true);
        // Met l'origine du sprite en son centre.
        Vector2u dim = m_fantassinTex->getSize();
        m_sprite.setOrigin(dim.x / 2., dim.y / 2.);
        // Rend la longueur du côté du sprite égale à celle d'une case.
        m_sprite.setScale(m_cote / dim.x, m_cote / dim.y);
    }

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
        // Positionne la barre avec l'origine au centre de la case.
        Vector2f pos(m_cote / 2, m_cote / 2 + m_barFond.getSize().y * 1.25);
        m_barFond.setOrigin(pos);
        Vector2f posRelative(-m_margin / 2, -m_margin / 2);
        m_barValeur.setOrigin(pos + posRelative);
    }
} // namespace vue
