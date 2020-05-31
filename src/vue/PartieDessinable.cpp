#include "vue/PartieDessinable.hpp"
#include <iostream>
#include "vue/CaseDessinable.hpp"
#include "vue/PersonnageDessinable.hpp"

using namespace donjon;
using namespace donjon::cases;
using namespace hex;
using namespace per;
using namespace sf;

namespace vue
{
    PartieDessinable::PartieDessinable(float cote) : ADessinable(cote) {}

    PartieDessinable::PartieDessinable(float cote, partie::Partie& partie) : ADessinable(cote, partie) {}

    void PartieDessinable::setElement(partie::Partie& element) { m_element = &element; }

    void PartieDessinable::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        if (m_element == nullptr) { return; }
        IDonjon_S donjon = m_element->getDonjon();
        drawCarte(target, states, *donjon);
        drawPersonnages(target, states, *donjon);
    }

    void PartieDessinable::drawCarte(sf::RenderTarget& target, sf::RenderStates& states, donjon::IDonjon& donjon) const
    {
        Vector2u dim = target.getSize();
        CaseDessinable caseDessinable(m_cote);
        ICarte_SC<ICase_S> carte = donjon.getCarte();
        auto itr = carte->iterateur();
        while (itr->aSuite())
        {
            Coordonnees pos = itr->suite();
            ICase_S iCase = (*carte)(pos);
            caseDessinable.setElement(*iCase);
            // Place la case dans le monde.
            Vector2f pixel = m_convertisseur(m_cote, pos);
            caseDessinable.setPosition(pixel.x + dim.x / 2., pixel.y + dim.y / 2.);
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
            target.draw(personnageDessinable, states);
        }
    }
} // namespace vue
