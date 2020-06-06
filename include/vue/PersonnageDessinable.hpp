#ifndef __PERSONNAGEDESSINABLE_HPP__
#define __PERSONNAGEDESSINABLE_HPP__

#include <SFML/Graphics.hpp>
#include "per/IPersonnageVisiteur.hpp"
#include "vue/ADessinable.hpp"
#include "vue/TextureGest.hpp"

namespace vue
{
    class PersonnageDessinable : public vue::ADessinable<per::APersonnage>,
                                 public per::IPersonnageVisiteur
    {
    private:
        float m_margin;
        sf::Color m_couleur;
        sf::Sprite m_sprite;
        sf::RectangleShape m_barFond;
        sf::RectangleShape m_barValeur;
        Texture_S m_herosTex;
        Texture_S m_fantassinTex;

    public:
        /**
         * @brief Crée un dessinateur de Personnage.
         *
         * @param cote La longueur du côté des hexagones.
         */
        PersonnageDessinable(float cote = 50);
        /**
         * @brief Crée un dessinateur de Personnage.
         *
         * @param cote La longueur du côté des hexagones.
         * @param aPersonnage Un personnage à dessiner.
         */
        PersonnageDessinable(float cote, per::APersonnage_S aPersonnage);

        /**
         * @brief Obtient la couleur du personnage.
         *
         * @return La couleur du personnage.
         */
        sf::Color getCouleur() const { return m_couleur; }

        /**
         * @brief Définie la longueur du côté des hexagones.
         *
         * @param cote La longueur du côté des hexagones.
         */
        void setCote(float cote) override;

        /**
         * @brief Définit la couleur du personnage.
         *
         * @param couleur La couleur du personnage.
         */
        void setCouleur(const sf::Color& couleur);

        /* Implémentation de ADessinable */
        void setElement(per::APersonnage_S aPersonnage) override;
        /* Implémentation de Drawable */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        /* Implémentation de IPersonnageVisiteur */
        void visiter(const per::Heros& heros) override;
        void visiter(const per::Fantassin& fantassin) override;

    private:
        /**
         * @brief Prépare le dessinable à représenter le personnage.
         */
        void preparer();

        /**
         * @brief Actualise la barre de santé au personnage.
         *
         * @param personnage Le personnage dont on souhaite afficher la santé.
         */
        void preparerBarreSante(const per::APersonnage& personnage);
    };
} // namespace vue
#endif // __PERSONNAGEDESSINABLE_HPP__
