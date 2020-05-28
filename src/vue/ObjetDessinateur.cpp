#include "vue/ObjetDessinateur.hpp"
#include <iostream>
#include <string>
#include "err/TextureESErreur.hpp"

using namespace sf;
namespace vue
{
    ObjetDessinateur::ObjetDessinateur(sf::RenderTarget& cible) :
        m_textureGravityGun(),
        m_cible(cible),
        m_rayon(100. / 3),
        m_sprite()
    {
        std::string chemin = "resources/textures/obj/gravity_gun.png";
        if (!m_textureGravityGun.loadFromFile(chemin))
        {
            throw err::TextureESErreur("ObjetDessinateur::ObjetDessinateur : Texture du gravity_gun introuvable!",
                                       chemin);
        }
    }

    void ObjetDessinateur::dessiner(const hex::Coordonnees& position, const obj::IObjet& iObjet)
    {
        m_sprite = Sprite();
        // Met le sprite au centre de sa case.
        float x = m_rayon / 2 * 3 * (float)position.getColonne();
        float y = m_rayon * sqrtf(3) * ((float)position.getColonne() / 2 + position.getLigne());
        Vector2u dim = m_cible.getSize();
        m_sprite.setPosition(dim.x / 2 + x, dim.y / 2 + y);
        // Adapte le sprite au type d'objet et le dessine.
        iObjet.accepter(*this);
        m_cible.draw(m_sprite);
    }

    void ObjetDessinateur::visiter(__attribute__((unused)) const obj::GravityGun& gravityGun)
    {
        m_sprite.setTexture(m_textureGravityGun);
        Vector2u dim = m_textureGravityGun.getSize();
        // Met l'origine du sprite en son centre.
        m_sprite.setOrigin(dim.x / 2., dim.y / 2.);
        // Rend la longueur du côté du sprite égale à celle d'une case.
        m_sprite.setScale(2 * (float)m_rayon / dim.x, 2 * (float)m_rayon / dim.y);
    }
} // namespace vue
