#ifndef __FENETRE_HPP__
#define __FENETRE_HPP__

#include <SFML/Graphics.hpp>
#include <list>
#include <map>
#include "controlleur/IControlleur.hpp"

namespace vue
{
    class Fenetre
    {
    private:
        sf::RenderWindow m_fenetre;
        std::map<sf::Event::EventType, std::list<controlleur::IControlleur_S>> m_gestEven;
        std::shared_ptr<sf::Drawable> m_dessinable;

    public:
        /**
         * @brief Construit une Fenêtre.
         *
         * @param videoMode Le mode vidéo de la fenêtre.
         * @param titre Le titre de la fenêtre.
         */
        Fenetre(sf::VideoMode& videoMode, std::string titre);

        /**
         * @brief Obtient le RenderWindow.
         *
         * @return Le RenderWindow.
         */
        sf::RenderWindow& getRenderWindow() { return m_fenetre; }

        /**
         * @brief Obtient le RenderWindow.
         *
         * @return Le RenderWindow.
         */
        const sf::RenderWindow& getRenderWindow() const { return m_fenetre; }

        /**
         * @brief Actualiser la fenêtre en boucle.
         *
         * NOTE: Cette méthode contient la boucle infini pour cette fenêtre. La
         * méthode ne termine qu'après la fermeture de celle-ci.
         */
        void actualiser();

        /**
         * @brief Acutalise la fenêtre une seule fois.
         */
        void actualiserUneFois();

        /**
         * @brief Attacher un gestionnaire d'évènement à un type d'évènement.
         *
         * @param evenGest Le gestionnaire d'évènement.
         * @param type Le type suivit.
         */
        void attacher(sf::Event::EventType type, controlleur::IControlleur_S evenGest);

        /**
         * @brief Detache un gestionnaire d'évènement d'un type d'évènement.
         *
         * @param evenGest Le gestionnaire d'évènement.
         * @param type Le type suivit.
         */
        void detacher(sf::Event::EventType type, controlleur::IControlleur_S evenGest);

        /**
         * @brief Définie l'objet dessiné
         *
         * @param dessinable L'objet dessiné.
         */
        void setDessinable(std::shared_ptr<sf::Drawable> dessinable) { m_dessinable = dessinable; }

    protected:
        /**
         * @brief Notifie les gestionnaires d'évènements correspondant à l'évènement.
         *
         * @param even L'évènement.
         */
        void notifier(sf::Event& even);
    };
} // namespace vue
#endif // __FENETRE_HPP__
