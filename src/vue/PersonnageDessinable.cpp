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
        m_herosTex = gest.obtenir("resources/textures/per/heros.png");
        m_fantassinTex = gest.obtenir("resources/textures/per/fantassin.png");
    }

    PersonnageDessinable::PersonnageDessinable(float cote, per::APersonnage& aPersonnage) :
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
        m_herosTex = gest.obtenir("resources/textures/per/heros.png");
        m_fantassinTex = gest.obtenir("resources/textures/per/fantassin.png");
        // S'adapte au personnage.
        setElement(aPersonnage);
    }

    PersonnageDessinable::PersonnageDessinable(const PersonnageDessinable& autre) : ADessinable(0) { *this = autre; }

    PersonnageDessinable::~PersonnageDessinable()
    {
        // Se détache du personnage observé.
        if (m_element != nullptr) { m_element->detacher(this); }
    }

    PersonnageDessinable& PersonnageDessinable::operator=(const PersonnageDessinable& autre)
    {
        // Copie les valeurs.
        m_cote = autre.m_cote;
        m_margin = autre.m_margin;
        m_couleur = autre.m_couleur;
        m_sprite = autre.m_sprite;
        m_barFond = autre.m_barFond;
        m_barValeur = autre.m_barValeur;
        m_herosTex = autre.m_herosTex;
        m_fantassinTex = autre.m_fantassinTex;
        // Se détache du précédent personnage et s'adapte au nouveau.
        if (m_element != nullptr) { m_element->detacher(this); }
        if (autre.m_element != nullptr) { setElement(*(autre.m_element)); }
        return *this;
    }

    void PersonnageDessinable::setCote(float cote)
    {
        m_cote = cote;
        if (m_element != nullptr) { actualiser(*m_element); }
    }

    void PersonnageDessinable::setCouleur(const sf::Color& couleur)
    {
        m_couleur = couleur;
        if (m_element != nullptr) { actualiser(*m_element); }
    }

    void PersonnageDessinable::setElement(APersonnage& personnage)
    {
        if (m_element != nullptr) { m_element->detacher(this); }
        m_element = &personnage;
        m_element->attacher(this);
        m_element = &personnage;
        actualiser(personnage);
    }

    void PersonnageDessinable::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // Applique la transformation et dessine les éléments.
        states.transform *= getTransform();
        target.draw(m_sprite, states);
        target.draw(m_barFond, states);
        target.draw(m_barValeur, states);
    }

    void PersonnageDessinable::visiter(__attribute__((unused)) const per::Heros& heros)
    {
        m_sprite.setTexture(*m_herosTex);
        // Met l'origine du sprite en son centre.
        Vector2u dim = m_herosTex->getSize();
        m_sprite.setOrigin(dim.x / 2., dim.y / 2.);
        // Rend la longueur du côté du sprite égale à celle d'une case.
        m_sprite.setScale(m_cote / dim.x, m_cote / dim.y);
    }

    void PersonnageDessinable::actualiser(const per::APersonnage& personnage)
    {
        preparerBarreSante(personnage);
        m_sprite.setColor(m_couleur);
        personnage.accepter(*this);
    }
    void PersonnageDessinable::visiter(__attribute__((unused)) const per::Fantassin& fantassin)
    {
        m_sprite.setTexture(*m_fantassinTex);
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
