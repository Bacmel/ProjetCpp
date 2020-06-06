#ifndef __OBJETDESSINABLE_HPP__
#define __OBJETDESSINABLE_HPP__

#include <SFML/Graphics.hpp>
#include "obj/IObjetVisiteur.hpp"
#include "vue/TextureGest.hpp"

namespace vue
{
    class ObjetDessinable : public sf::Drawable, public sf::Transformable, public obj::IObjetVisiteur
    {
    private:
        float m_cote;
        const obj::IObjet* m_objet;
        sf::Sprite m_sprite;
        Texture_S m_textureGravityGun;
        Texture_S m_textureTaser;

    public:
        /**
         * @brief Construit un dessinateur d'objet.
         *
         * @param cote La longueur du coté de l'hexagone.
         */
        ObjetDessinable(float cote = 50, const obj::IObjet* iObjet = nullptr);

        /**
         * @brief Mets en surbriance l'objet dessiné.
         */
        void surligner();

        /**
         * @brief Obtient la longueur du côté de l'hexagone utilisé.
         *
         * @return La longueur du côté de l'hexagone
         */
        float getCote() const { return m_cote; }

        /**
         * @brief Obtient un pointeur vers l'objet dessiné.
         *
         * ATTENTION: Ce pointeur ne doit être libéré, en aucun cas.
         *
         * @return Un pointeur vers l'objet dessiné (peut être null).
         */
        const obj::IObjet* getObjet() const { return m_objet; }

        /**
         * @brief Définit la longueur du côté de l'hexagone à utiliser.
         *
         * @param cote La longueur du côté de l'hexagone à utiliser.
         */
        void setCote(float cote) { m_cote = cote; }

        /**
         * @brief Définit l'objet à dessiner.
         *
         * @param iObjet L'objet à dessiner.
         */
        void setObjet(const obj::IObjet& iObjet);

        virtual void visiter(const obj::GravityGun& gravityGun) override;

        virtual void visiter(const obj::Taser& taser) override;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
} // namespace vue
#endif // __OBJETDESSINABLE_HPP__
