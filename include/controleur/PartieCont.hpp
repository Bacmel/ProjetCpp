#ifndef __PARTIECONT_HPP__
#define __PARTIECONT_HPP__

#include <memory>
#include "controleur/IControleur.hpp"
#include "partie/Partie.hpp"
#include "utils/HexPixelConvertisseur.hpp"
#include "vue/PartieDessinable.hpp"

namespace controleur
{
    class PartieCont : public IControleur
    {
    private:
        /** @brief Accès à la vue. */
        std::shared_ptr<const vue::PartieDessinable> m_dessinable;
        /** @brief Accès au modèle. */
        std::shared_ptr<partie::Partie> m_partie;
        /** @brief Functor de conversion grille hexagonale vers l'écran */
        utils::HexPixelConvertisseur m_convertisseur;

    public:
        /**
         * @brief Construit un contrôleur pour la partie.
         *
         * @param dessinable La partie dessinable à contrôler.
         * @param partie Le modèle avec lequel intéragir.
         * @throw std::invalid_argument Quand dessinable ou partie sont nuls ou
         * si le dessinable ne représente pas la partie.
         */
        PartieCont(std::shared_ptr<const vue::PartieDessinable> dessinable, std::shared_ptr<partie::Partie> partie);

        /* Implémentation de IControleur */
        void enEvenement(const vue::Fenetre& source, sf::Event& even) override;

    protected:
        /**
         * @brief Vérifie que le clic est sur un objet et en informe le modèle.
         *
         * @param coordonneesClic La coordonnée du clic.
         * @return true si l'évènement a été traité.
         */
        bool clicObjet(const sf::Vector2f& coordonneesClic);

        /**
         * @brief Convertie la coordonnée du clique en coordonnée hexagonale et
         * en informe le modèle.
         *
         * @param coordonneesClic La coordonnée du clique dans le repère "monde".
         * @param source La fenêtre qui a créé l'évènement.
         */
        void clicCase(const sf::Vector2f& coordonneesClic, const vue::Fenetre& source);
    };
} // namespace controleur
#endif // __PARTIECONT_HPP__
