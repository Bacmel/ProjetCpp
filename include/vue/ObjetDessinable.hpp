#ifndef __OBJETDESSINABLE_HPP__
#define __OBJETDESSINABLE_HPP__

#include <SFML/Graphics.hpp>
#include "obj/IObjetVisiteur.hpp"
#include "vue/ADessinable.hpp"
#include "vue/TextureGest.hpp"

namespace vue
{
    class ObjetDessinable : public ADessinable<obj::IObjet>, public obj::IObjetVisiteur
    {
    private:
        sf::Sprite m_sprite;
        Texture_S m_textureGravityGun;
        Texture_S m_textureTaser;

    public:
        /**
         * @brief Construit un dessinateur d'objet.
         *
         * @param cote La longueur du coté de l'hexagone.
         */
        ObjetDessinable(float cote);

        /**
         * @brief Construit un nouveau dessinateur.
         *
         * @param cote Le cote de l'hexagone (en pixels).
         * @param aObjet L'objet a dessiner.
         *
         * @throw std::invalid_argument Quand aObjet est null.
         */
        ObjetDessinable(float cote, obj::IObjet_S aObjet);

        /**
         * @brief Mets en surbriance l'objet dessiné.
         *
         * @param La couleur de surbriance.
         */
        void setColor(const sf::Color& couleur);

        /**
         * @brief Obtient la longueur du côté de l'hexagone utilisé.
         *
         * @return La longueur du côté de l'hexagone
         */
        float getCote() const { return m_cote; }

        /**
         * @brief Définit la longueur du côté de l'hexagone à utiliser.
         *
         * @param cote La longueur du côté de l'hexagone à utiliser.
         */
        void setCote(float cote) { m_cote = cote; }

        /* Implémentation de ADessinable */
        void setElement(obj::IObjet_S iObjet) override;
        /* Implémentation de IObjetVisiteur */
        void visiter(const obj::GravityGun& gravityGun) override;
        void visiter(const obj::Taser& taser) override;
        /* Implémentation de Drawable */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
} // namespace vue
#endif // __OBJETDESSINABLE_HPP__
