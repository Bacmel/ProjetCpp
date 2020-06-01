#include "vue/PartieDessinable.hpp"
#include <iostream>
#include <stdexcept>
#include "vue/CaseDessinable.hpp"
#include "vue/PersonnageDessinable.hpp"

using namespace donjon;
using namespace donjon::cases;
using namespace hex;
using namespace per;
using namespace sf;

namespace vue
{
    PartieDessinable::PartieDessinable(float cote) : ADessinable(cote), m_font(), m_equipeText(), m_equipeIndicateur()
    {
        if (!m_font.loadFromFile("resources/font/joystix monospace.ttf"))
        { throw std::invalid_argument("Font n'a pas pu être chargée."); }
        m_equipeText.setFont(m_font);
        m_equipeText.setString("Equipe");
        m_equipeText.setCharacterSize(12);
        m_equipeText.setFillColor(Color::White);
        FloatRect bordures = m_equipeText.getLocalBounds();
        m_equipeIndicateur.setSize(Vector2f(bordures.height, bordures.height));
        m_equipeIndicateur.setPosition(bordures.left + bordures.width + 5, bordures.top);
    }

    PartieDessinable::PartieDessinable(float cote, partie::Partie& partie) : PartieDessinable(cote)
    {
        setElement(partie);
    }

    void PartieDessinable::setElement(partie::Partie& element) { m_element = &element; }

    void PartieDessinable::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        if (m_element == nullptr) { return; }
        IDonjon_S donjon = m_element->getDonjon();
        drawCarte(target, states, *donjon);
        drawPersonnages(target, states, *donjon);
        drawEquipe(target, states);
        drawInventaire(target, states);
    }

    sf::FloatRect PartieDessinable::getCaseInventaire(size_t indice) const
    {
        float cote = 50;
        FloatRect contours(cote * .1, cote * (indice + .5), cote, cote);
        return contours;
    }

    void PartieDessinable::drawCarte(sf::RenderTarget& target, sf::RenderStates& states, donjon::IDonjon& donjon) const
    {
        Vector2u dim = target.getSize();
        CaseDessinable caseDessinable(m_cote);
        ICarte_SC<ICase_S> carte = donjon.getCarte();
        auto itr = carte->iterateur();
        bool surligne(false);
        Coordonnees posPerso;
        try
        {
            auto perso = m_element->getPersoSelect();
            posPerso = perso->getPosition();
            surligne = true;
        }
        catch (const std::invalid_argument&)
        {
        }
        while (itr->aSuite())
        {
            Coordonnees pos = itr->suite();
            ICase_S iCase = (*carte)(pos);
            caseDessinable.setElement(*iCase);
            // Place la case dans le monde.
            Vector2f pixel = m_convertisseur(m_cote, pos);
            caseDessinable.setPosition(pixel.x + dim.x / 2., pixel.y + dim.y / 2.);
            if (surligne && pos == posPerso) { caseDessinable.surligner(); }
            // Dessine la case.
            target.draw(caseDessinable, states);
        }
    }

    void PartieDessinable::drawPersonnages(sf::RenderTarget& target,
                                           sf::RenderStates& states,
                                           donjon::IDonjon& donjon) const
    {
        PersonnageDessinable personnageDessinable(m_cote);
        Vector2u dim = target.getSize();
        size_t nbPerso = donjon.getNbPersonnages();
        for (size_t idcPerso = 0; idcPerso < nbPerso; idcPerso++)
        {
            APersonnage_S perso = donjon.getPersonnage(idcPerso);
            Vector2f pixel = m_convertisseur(m_cote, perso->getPosition());
            personnageDessinable.setElement(*perso);
            personnageDessinable.setPosition(pixel.x + dim.x / 2., pixel.y + dim.y / 2.);
            personnageDessinable.setCouleur(couleurEquipe(m_element->indiceEquipe(perso)));
            target.draw(personnageDessinable, states);
        }
    }

    void PartieDessinable::drawEquipe(sf::RenderTarget& target, sf::RenderStates& states) const
    {
        RectangleShape indicateur(m_equipeIndicateur);
        indicateur.setFillColor(couleurEquipe(m_element->getEquipeCourante()));
        target.draw(m_equipeText, states);
        target.draw(indicateur, states);
    }

    void PartieDessinable::drawInventaire(sf::RenderTarget& target, sf::RenderStates& states) const
    {
        per::APersonnage_SC personnage;
        try
        {
            personnage = m_element->getPersoSelect();
        }
        catch (const std::invalid_argument&)
        {
            return;
        }
        size_t nbObjet = personnage->tailleSac();
        ObjetDessinable objDessinable;
        for (size_t indiceObjet = 0; indiceObjet < nbObjet; indiceObjet++)
        {
            obj::IObjet_SC objet = personnage->getObjet(indiceObjet);
            FloatRect contours = getCaseInventaire(indiceObjet);
            objDessinable.setCote(contours.width);
            objDessinable.setPosition(contours.left + contours.width / 2, contours.top + contours.height / 2);
            objDessinable.setObjet(*objet);
            target.draw(objDessinable, states);
        }
    }

    sf::Color PartieDessinable::couleurEquipe(size_t equipe) const
    {

        if (equipe) { return sf::Color::Blue; }
        else
        {
            return sf::Color::Red;
        }
    }
} // namespace vue
