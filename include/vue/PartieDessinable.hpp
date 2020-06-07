#ifndef __PARTIEDESSINABLE_HPP__
#define __PARTIEDESSINABLE_HPP__

#include <memory>
#include "partie/Partie.hpp"
#include "utils/HexPixelConvertisseur.hpp"
#include "vue/ADessinable.hpp"

namespace vue
{
    class PartieDessinable : public ADessinable<partie::Partie>
    {
    private:
        utils::HexPixelConvertisseur m_convertisseur;
        sf::Font m_font;
        sf::Text m_equipeText;
        sf::RectangleShape m_equipeIndicateur;

    public:
        /**
         * @brief Construit un dessinateur de partie.
         *
         * @param cote La longueur du coté de l'hexagone.
         */
        PartieDessinable(float cote);

        /**
         * @brief Construit un nouveau dessinateur.
         *
         * @param cote Le cote de l'hexagone (en pixels).
         * @param partie L'objet a dessiner.
         *
         * @throw std::invalid_argument Quand partie est null.
         */
        PartieDessinable(float cote, std::shared_ptr<partie::Partie> partie);

        /**
         * @brief Obtient les contours de la ième case de l'inventaire.
         *
         * @param i L'indice de l'inventaire.
         * @return Les contours de la ième case de l'inventaire.
         */
        sf::FloatRect getCaseInventaire(size_t indice) const;

        /* Implémentation de ADessinable */
        void setElement(std::shared_ptr<partie::Partie> element) override;
        /* Implémentation de Drawable */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        /**
         * @brief Dessine la carte.
         *
         * @param target La cible sur laquelle dessiner.
         * @param states L'état de la cible.
         * @param donjon Le donjon à dessiner.
         */
        void drawDonjon(sf::RenderTarget& target, sf::RenderStates& states, donjon::IDonjon& donjon) const;

        /**
         * @brief Dessine les personnages.
         *
         * @param target La cible sur laquelle dessiner.
         * @param states L'état de la cible.
         * @param donjon Le donjon à dessiner.
         */
        void drawPersonnages(sf::RenderTarget& target, sf::RenderStates& states, donjon::IDonjon& donjon) const;

        /**
         * @brief Dessine l'indicateur d'équipe active.
         *
         * @param target La cible sur laquelle dessiner.
         * @param states L'état de la cible.
         */
        void drawEquipe(sf::RenderTarget& target, sf::RenderStates& states) const;

        /**
         * @brief Dessine l'inventaire du personnage sélectionné.
         *
         * @param target La cible sur laquelle dessiner.
         * @param states L'état de la cible.
         */
        void drawInventaire(sf::RenderTarget& target, sf::RenderStates& states) const;

        /**
         * @brief Dessine un text pour indiquer le vainqueur.
         *
         * @param target La cible sur laquelle dessiner.
         * @param states L'état de la cible.
         */
        void drawGagnant(sf::RenderTarget& target, sf::RenderStates& states) const;

        /**
         * @brief Génère la couleur pour l'équipe donnée.
         *
         * @param equipe L'indice de l'équipe.
         * @return Une couleur propre à l'équipe.
         */
        sf::Color couleurEquipe(size_t equipe) const;

        /**
         * @brief Convertie une couleur HSV en RGB.
         *
         * @param hue La teinte (entre 0 et 360)
         * @param saturation La saturation (entre 0 et 1)
         * @param value La valeur (entre 0 et 1)
         * @return La couleur équivalente en RGB.
         */
        sf::Color depuisHSV(int hue, float saturation, float value) const;
    };
} // namespace vue
#endif // __PARTIEDESSINABLE_HPP__
