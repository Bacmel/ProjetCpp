#include "vue/ObjetDessinateur.hpp"
#include "utils/HexPixelConvertisseur.hpp"

using namespace sf;

namespace vue
{
    ObjetDessinateur::ObjetDessinateur(sf::RenderTarget& cible) :
        ADessinateur(50),
        m_textureGravityGun(),
        m_cible(cible),
        m_sprite()
    {
        TextureGest& gest = TextureGest::getInstance();
        m_textureGravityGun = gest.obtenir("resources/textures/obj/gravity_gun.png");
    }

    void ObjetDessinateur::dessine(const hex::Coordonnees& position, const obj::IObjet& iObjet)
    {
        m_sprite = Sprite();
        // Met le sprite au centre de sa case.
        utils::HexPixelConvertisseur hexVersPixel;
        Vector2f pixel = hexVersPixel(getRayon(), position);
        Vector2u dim = m_cible.getSize();
        m_sprite.setPosition(dim.x / 2 + pixel.x, dim.y / 2 + pixel.y);
        // Adapte le sprite au type d'objet et le dessine.
        iObjet.accepter(*this);
        m_cible.draw(m_sprite);
    }

    void ObjetDessinateur::visiter(__attribute__((unused)) const obj::GravityGun& gravityGun)
    {
        m_sprite.setTexture(*m_textureGravityGun);
        Vector2u dim = m_textureGravityGun->getSize();
        // Met l'origine du sprite en son centre.
        m_sprite.setOrigin(dim.x / 2., dim.y / 2.);
        // Rend la longueur du côté du sprite égale à celle d'une case.
        float cote = getRayon();
        m_sprite.setScale(cote / dim.x, cote / dim.y);
    }
} // namespace vue
