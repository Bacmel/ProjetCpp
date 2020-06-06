#ifndef __PERSONNAGEDESSINABLE_HPP__
#define __PERSONNAGEDESSINABLE_HPP__

#include <SFML/Graphics.hpp>
#include "per/IPersonnageVisiteur.hpp"
#include "utils/IObservateur.hpp"
#include "vue/ADessinable.hpp"
#include "vue/TextureGest.hpp"

namespace vue
{
    class PersonnageDessinable : public vue::ADessinable<per::APersonnage>,
                                 public per::IPersonnageVisiteur,
                                 public utils::IObservateur<per::APersonnage>
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
         * @param aPersonnage Un personnage à dessiner.
         */
        PersonnageDessinable(float cote = 50);
        PersonnageDessinable(float cote, per::APersonnage& aPersonnage);
        PersonnageDessinable(const PersonnageDessinable& autre);
        PersonnageDessinable& operator=(const PersonnageDessinable& autre);
        ~PersonnageDessinable();


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

        void setElement(per::APersonnage& aPersonnage) override;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        virtual void visiter(const per::Heros& heros) override;

        virtual void visiter(const per::Fantassin& fantassin) override;

        virtual void actualiser(const per::APersonnage& info) override;

    private:
        /**
         * @brief Actualise la barre de santé au personnage.
         *
         * @param personnage Le personnage dont on souhaite afficher la santé.
         */
        void preparerBarreSante(const per::APersonnage& personnage);
    };
} // namespace vue
#endif // __PERSONNAGEDESSINABLE_HPP__
