#include "vue/PartieDessinable.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "err/InfoErreur.hpp"
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
        drawGagnant(target, states);
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
        ICarte_S<ACase_S> carte = donjon.getCarte();
        auto itr = carte->iterateur();
        bool surligne(false);
        Coordonnees posPerso;
        try
        {
            auto perso = m_element->getPersoSelect();
            posPerso = perso->getPosition();
            surligne = true;
        }
        catch (const std::logic_error&)
        {
        }
        while (itr->aSuite())
        {
            Coordonnees pos = itr->suite();
            ACase_S iCase = (*carte)(pos);
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
        catch (const std::logic_error&)
        {
            return;
        }
        size_t nbObjet = personnage->tailleSac();
        ObjetDessinable objDessinable;
        obj::IObjet_SC objSel;
        try
        {
            objSel = m_element->getObjetSelect();
        }
        catch (const std::logic_error&)
        {
        }
        for (size_t indiceObjet = 0; indiceObjet < nbObjet; indiceObjet++)
        {
            obj::IObjet_SC objet = personnage->getObjet(indiceObjet);
            FloatRect contours = getCaseInventaire(indiceObjet);
            objDessinable.setCote(contours.width);
            objDessinable.setPosition(contours.left + contours.width / 2, contours.top + contours.height / 2);
            objDessinable.setObjet(*objet);
            if (objSel == objet) { objDessinable.surligner(); }
            target.draw(objDessinable, states);
        }
    }

    void PartieDessinable::drawGagnant(sf::RenderTarget& target, sf::RenderStates& states) const
    {
        try
        {
            // Récupère le vainqueur et construit un sf::Text
            int indiceGagnant = m_element->indiceGagnant();
            std::stringstream ss;
            ss << "L'equipe " << (indiceGagnant + 1) << " remporte\n\tla victoire!";
            Text victoire(ss.str(), m_font);
            // Met le sf::Text au centre de l'écran.
            FloatRect contours = victoire.getLocalBounds();
            victoire.setOrigin(contours.width / 2, contours.height / 2);
            victoire.setFillColor(couleurEquipe(indiceGagnant));
            Vector2u dimensions = target.getSize();
            victoire.setPosition(dimensions.x / 2.f, dimensions.y / 2.f);
            target.draw(victoire, states);
        }
        catch (const err::InfoErreur&)
        {
        }
    }

    sf::Color PartieDessinable::couleurEquipe(size_t equipe) const
    {
        size_t nbEquipe = m_element->getEquipes().size();
        int hue = (int)(((float)equipe / nbEquipe) * 360);
        Color couleur = depuisHSV(hue, 1, 1);
        return couleur;
    }

    sf::Color PartieDessinable::depuisHSV(int hue, float saturation, float value) const
    {
        // Basé sur: https://www.rapidtables.com/convert/color/hsv-to-rgb.html
        float c = value * saturation;
        float x = c * (1 - std::abs((hue / 60) % 2 - 1));
        float m = value - c;
        float r, g, b;
        if (0 <= hue && hue < 60)
        {
            r = c;
            g = x;
            b = 0;
        }
        else if (hue < 120)
        {
            r = x;
            g = c;
            b = 0;
        }
        else if (hue < 180)
        {
            r = 0;
            g = c;
            b = x;
        }
        else if (hue < 240)
        {
            r = 0;
            g = x;
            b = c;
        }
        else if (hue < 300)
        {
            r = x;
            g = 0;
            b = c;
        }
        else
        {
            r = c;
            g = 0;
            b = x;
        }
        return Color((r + m) * 255, (g + m) * 255, (b + m) * 255);
    }
} // namespace vue
