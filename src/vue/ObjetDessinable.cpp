#include "vue/ObjetDessinable.hpp"
#include "utils/HexPixelConvertisseur.hpp"

using namespace sf;
using namespace obj;

namespace vue
{
    ObjetDessinable::ObjetDessinable(float cote, const obj::IObjet* iObjet) :
        m_cote(cote),
        m_objet(nullptr),
        m_sprite(),
        m_textureGravityGun(),
        m_textureTaser()
    {
        // Récupère les textures.
        TextureGest& gest = TextureGest::getInstance();
        m_textureGravityGun = gest.obtenir("resources/textures/obj/gravity_gun.png");
        m_textureTaser = gest.obtenir("resources/textures/obj/taser.png");
        if (iObjet != nullptr) { setObjet(*iObjet); }
    }

    void ObjetDessinable::setObjet(const obj::IObjet& iObjet)
    {
        m_objet = &iObjet;
        iObjet.accepter(*this);
    }

    void ObjetDessinable::visiter(const obj::GravityGun&)
    {
        m_sprite.setTexture(*m_textureGravityGun);
        Vector2u dim = m_textureGravityGun->getSize();
        // Met l'origine du sprite en son centre.
        m_sprite.setOrigin(dim.x / 2., dim.y / 2.);
        // Rend la longueur du côté du sprite égale à celle d'une case.
        m_sprite.setScale(m_cote / dim.x, m_cote / dim.y);
    }

    void ObjetDessinable::visiter(const obj::Taser&)
    {
        m_sprite.setTexture(*m_textureTaser);
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
