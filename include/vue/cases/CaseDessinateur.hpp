#ifndef __CASEDESSINATEUR_H__
#define __CASEDESSINATEUR_H__

#include <SFML/Graphics.hpp>
#include "donjon/cases/ICaseVisiteur.hpp"
#include "donjon/cases/Sol.hpp"
#include "hex/Coordonnees.hpp"

namespace vue::cases
{
    class CaseDessinateur : public donjon::cases::ICaseVisiteur
    {
    private:
        sf::Texture m_textureSol;
        sf::Texture m_textureTrou;
        sf::RenderTarget& m_cible;
        size_t m_rayon;
        sf::CircleShape m_hexagone;

    public:
        /**
         * @brief Construit un dessinateur de case dédié à la cible.
         *
         * @param cible La toile du dessin.
         */
        CaseDessinateur(sf::RenderTarget& cible);

        /**
         * @brief Obtient la texture utilisée pour les cases Sol.
         *
         * @return La texture utilisée pour les cases Sol.
         */
        inline const sf::Texture& getTextureSol() const { return m_textureSol; }

        /**
         * @brief Obtient la cible des dessins.
         *
         * @return La cible des dessins.
         */
        inline const sf::RenderTarget& getCible() const { return m_cible; }

        /**
         * @brief Obtient le rayon du cercle circonscrit à l'hexagone.
         *
         * @return Le rayon du cercle circonscrit à l'hexagone (en pixels).
         *
         * @see getCote()
         */
        inline size_t getRayon() const { return m_rayon; }

        /**
         * @brief Défini le rayon du cercle circonscrit à l'hexagone.
         *
         * @param rayon Le rayon du cercle circonscrit à l'hexagone (en pixels).
         *
         * @see setCote()
         */
        inline void setRayon(size_t rayon) { m_rayon = rayon; }

        /**
         * @brief Obtient la longueur du côté de l'hexagone.
         *
         * @return La longueur du côté de l'hexagone.
         *
         * @see getRayon()
         */
        size_t getCote() const;

        /**
         * @brief Défini la longueur du côté de l'hexagone.
         *
         * @param rayon La longueur du côté de l'hexagone.
         *
         * @see setRayon()
         */
        void setCote(size_t rayon);

        /**
         * @brief Dessine la case sur la cible.
         *
         * @param iCase La case à dessiner.
         */
        void dessine(const hex::Coordonnees& position, donjon::cases::ICase& iCase);

        void visite(const donjon::cases::Sol& sol) override;

        void visite(const donjon::cases::Trou& trou) override;
    };

} // namespace vue::cases
#endif // __CASEDESSINATEUR_H__
