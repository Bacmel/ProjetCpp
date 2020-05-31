#include "vue/Fenetre.hpp"

using namespace sf;
using namespace std;
using namespace controlleur;
namespace vue
{
    Fenetre::Fenetre(sf::VideoMode& videoMode, std::string titre) : m_fenetre(), m_gestEven(), m_dessinateur(nullptr)
    {
        ContextSettings cs;
        cs.antialiasingLevel = 5;
        m_fenetre.create(videoMode, titre, Style::Default, cs);
    }

    void Fenetre::actualiser()
    {
        while (m_fenetre.isOpen())
        {
            actualiserUneFois();
        }
    }

    void Fenetre::actualiserUneFois()
    {
        if (m_fenetre.isOpen())
        {
            // Gestion des évènements.
            Event event;
            while (m_fenetre.pollEvent(event))
            {
                if (event.type == Event::Closed) { m_fenetre.close(); }
                if (event.type == Event::Resized)
                {
                    // on met à jour la vue, avec la nouvelle taille de la fenêtre
                    sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                    View vue = sf::View(visibleArea);
                    float facteurZoom = 500. / std::min(event.size.height, event.size.width);
                    vue.zoom(facteurZoom);
                    m_fenetre.setView(vue);
                }
                notifier(event);
            }
            // Dessin de la fenêtre actualisée.
            m_fenetre.clear();
            m_dessinateur(m_fenetre);
            m_fenetre.display();
        }
    }

    void Fenetre::attacher(sf::Event::EventType type, IControlleur* evenGest)
    {
        // Crée une liste si il n'y en a pas déjà.
        auto itr = m_gestEven.find(type);
        if (itr == m_gestEven.end())
        {
            auto res = m_gestEven.insert(pair<Event::EventType, list<IControlleur*>>(type, list<IControlleur*>()));
            itr = res.first;
        }
        // Ajoute le gestionnaire à la liste.
        itr->second.push_back(evenGest);
    }

    void Fenetre::detacher(sf::Event::EventType type, IControlleur* evenGest)
    {
        // Vérifie que le type d'évènements a des gestionnaires et supprime celui donné.
        auto itr = m_gestEven.find(type);
        if (itr != m_gestEven.end()) { itr->second.remove(evenGest); }
    }

    void Fenetre::notifier(sf::Event& even)
    {
        // Vérifie qu'il y a des gestionnaires adaptés.
        auto itr = m_gestEven.find(even.type);
        if (itr != m_gestEven.end())
        {
            // Appelle chaque gestionnaire.
            pair<Event::EventType, list<IControlleur*>> elem = *itr;
            for (IControlleur*& gest : elem.second)
            {
                if (gest != nullptr) { gest->enEvenement(even); }
            }
        }
    }
} // namespace vue
