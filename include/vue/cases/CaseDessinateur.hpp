#ifndef __CASEDESSINATEUR_H__
#define __CASEDESSINATEUR_H__

#include <SFML/Graphics.hpp>
#include "donjon/cases/ICaseVisiteur.hpp"
#include "donjon/cases/Sol.hpp"
#include "hex/Coordonnees.hpp"
#include "vue/ADessinateur.hpp"
#include "vue/TextureGest.hpp"

namespace vue::cases
{
    class CaseDessinateur : public ADessinateur, public donjon::cases::ICaseVisiteur
    {
    private:
        Texture_S m_textureSol;
        Texture_S m_textureTrou;
        sf::RenderTarget& m_cible;
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
        inline Texture_S getTextureSol() const { return m_textureSol; }

        /**
         * @brief Obtient la cible des dessins.
         *
         * @return La cible des dessins.
         */
        inline const sf::RenderTarget& getCible() const { return m_cible; }

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
