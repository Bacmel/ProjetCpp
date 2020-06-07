#include "vue/ObjetDessinable.hpp"
#include "utils/HexPixelConvertisseur.hpp"

using namespace sf;
using namespace obj;

namespace vue
{
    ObjetDessinable::ObjetDessinable(float cote) :
        ADessinable(cote),
        m_sprite(),
        m_textureGravityGun(),
        m_textureTaser()
    {
        // Récupère les textures.
        TextureGest& gest = TextureGest::getInstance();
        m_textureGravityGun = gest.obtenir("ressources/textures/obj/gravity_gun.png");
        m_textureTaser = gest.obtenir("ressources/textures/obj/taser.png");
    }

    ObjetDessinable::ObjetDessinable(float cote, obj::IObjet_S aObjet) : ObjetDessinable(cote)
    {
        if (aObjet == nullptr) { throw std::invalid_argument("ObjetDessinable::ObjetDessinable : aObjet est null!"); }
        setElement(aObjet);
    }

    void ObjetDessinable::surligner() { m_sprite.setColor(Color(255, 255, 50)); }

    void ObjetDessinable::setElement(IObjet_S iObjet)
    {
        if (iObjet == nullptr) { throw std::invalid_argument("ObjetDessinable::setElement : iObjet est null!"); }
        m_element = iObjet;
        m_sprite.setColor(Color::White);
        m_element->accepter(*this);
    }

    void ObjetDessinable::visiter(const obj::GravityGun&)
    {
        m_sprite.setTexture(*m_textureGravityGun, true);
        Vector2u dim = m_textureGravityGun->getSize();
        // Met l'origine du sprite en son centre.
        m_sprite.setOrigin(dim.x / 2., dim.y / 2.);
        // Rend la longueur du côté du sprite égale à celle d'une case.
        m_sprite.setScale(m_cote / dim.x, m_cote / dim.y);
    }

    void ObjetDessinable::visiter(const obj::Taser&)
    {
        m_sprite.setTexture(*m_textureTaser, true);
        Vector2u dim = m_textureTaser->getSize();
        // Met l'origine du sprite en son centre.
        m_sprite.setOrigin(dim.x / 2., dim.y / 2.);
        // Rend la longueur du côté du sprite égale à celle d'une case.
        m_sprite.setScale(m_cote / dim.x, m_cote / dim.y);
    }

    void ObjetDessinable::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_sprite, states);
    }

} // namespace vue
