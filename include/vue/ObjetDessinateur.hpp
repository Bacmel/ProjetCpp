#ifndef __OBJETDESSINATEUR_H__
#define __OBJETDESSINATEUR_H__

#include <SFML/Graphics.hpp>
#include "hex/Coordonnees.hpp"
#include "obj/IObjetVisiteur.hpp"

namespace vue
{
    class ObjetDessinateur : public obj::IObjetVisiteur
    {
    private:
        sf::Texture m_textureGravityGun;
        sf::RenderTarget& m_cible;
        size_t m_rayon;
        sf::Sprite m_sprite;

    public:
        /**
         * @brief Construit un dessinateur d'objet.
         *
         * @param cible La toile sur laquelle dessiner.
         */
        ObjetDessinateur(sf::RenderTarget& cible);

        /**
         * @brief Dessine un objet aux coordonnées indiquées.
         *
         * @param position Les coordonnées auxquelles se trouve l'objet.
         * @param iObjet L'objet à dessiner.
         */
        void dessiner(const hex::Coordonnees& position, const obj::IObjet& iObjet);

        virtual void visiter(const obj::GravityGun& gravityGun) override;
    };
} // namespace vue
#endif // __OBJETDESSINATEUR_H__
