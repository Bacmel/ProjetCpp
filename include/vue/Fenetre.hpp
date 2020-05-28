#ifndef __FENETRE_H__
#define __FENETRE_H__

#include <SFML/Graphics.hpp>
#include <functional>
#include <list>
#include <map>
#include "controlleur/IControlleur.hpp"

namespace vue
{
    using Dessinateur = std::function<void(sf::RenderWindow&)>;

    class Fenetre
    {
    private:
        sf::RenderWindow m_fenetre;
        std::map<sf::Event::EventType, std::list<controlleur::IControlleur*>> m_gestEven;
        Dessinateur m_dessinateur;

    public:
        Fenetre(sf::VideoMode& videoMode, std::string titre);
        ~Fenetre() {}

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
        void attacher(sf::Event::EventType type, controlleur::IControlleur* evenGest);

        /**
         * @brief Detache un gestionnaire d'évènement d'un type d'évènement.
         *
         * @param evenGest Le gestionnaire d'évènement.
         * @param type Le type suivit.
         */
        void detacher(sf::Event::EventType type, controlleur::IControlleur* evenGest);

        void setDessinateur(Dessinateur dessinateur) { m_dessinateur = dessinateur; }

    protected:
        /**
         * @brief Notifie les gestionnaires d'évènements correspondant à l'évènement.
         *
         * @param even L'évènement.
         */
        void notifier(sf::Event& even);
    };
} // namespace vue
#endif // __FENETRE_H__
