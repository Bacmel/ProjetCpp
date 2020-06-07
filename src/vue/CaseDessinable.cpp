#include "vue/CaseDessinable.hpp"
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include "err/SansObjetErreur.hpp"
#include "utils/HexPixelConvertisseur.hpp"
#include "vue/TextureGest.hpp"

using namespace donjon::cases;
using namespace obj;
using namespace sf;

namespace vue
{
    CaseDessinable::CaseDessinable(float cote) :
        ADessinable(cote),
        m_hexagone(cote, 6),
        m_textureSol(),
        m_textureTrou(),
        m_objDessinable(cote)
    {
        // Récupère les textures.
        TextureGest& gest = TextureGest::getInstance();
        m_textureSol = gest.obtenir("resources/textures/cases/sol.png");
        m_textureTrou = gest.obtenir("resources/textures/cases/trou.png");
        // Prépare un hexagone.
        m_hexagone.setOrigin(cote, cote);
        m_hexagone.setRotation(90);
        m_hexagone.setOutlineThickness(-1);
        m_hexagone.setOutlineColor(Color::Black);
    }

    CaseDessinable::CaseDessinable(float cote, ACase_S aCase) : CaseDessinable(cote)
    {
        if (aCase == nullptr) { throw std::invalid_argument("CaseDessinable::CaseDessinable : La case est nulle!"); }
        setElement(aCase);
    }

    void CaseDessinable::setElement(ACase_S aCase)
    {
        if (aCase == nullptr) { throw std::invalid_argument("CaseDessinable::setElement : La case est nulle!"); }
        // On met à jour les champs.
        m_hexagone.setFillColor(Color::White);
        m_element = aCase;
        preparer();
    }

    void CaseDessinable::surligner()
    {
        // Met les contours en surbrillance.
        m_hexagone.setOutlineThickness(-2);
        m_hexagone.setFillColor(Color(255, 255, 50));
        // Teinte le fond.
        m_hexagone.setOutlineColor(sf::Color::Yellow);
    }

    void CaseDessinable::setCote(float cote)
    {
        // Adapte la taille de l'hexagone.
        ADessinable::setCote(cote);
        m_hexagone.setRadius(cote);
        m_hexagone.setOrigin(cote, cote);
    }

    void CaseDessinable::visite(const Sol&)
    {
        // Met des contours fin et noir.
        m_hexagone.setOutlineThickness(-0.5);
        m_hexagone.setOutlineColor(sf::Color::Black);
        // Adapte la texture.
        m_hexagone.setTexture(m_textureSol.get(), true);
    }

    void CaseDessinable::visite(const Trou&)
    {
        // Retire les contours.
        m_hexagone.setOutlineThickness(0);
        // Adapte la texture.
        m_hexagone.setTexture(m_textureTrou.get(), true);
    }

    void CaseDessinable::draw(RenderTarget& target, RenderStates states) const
    {
        // Applique la transformation.
        states.transform *= getTransform();
        // Dessine la case puis son objet.
        target.draw(m_hexagone, states);
        if (m_element->aObjet()) { target.draw(m_objDessinable, states); }
    }

    void CaseDessinable::preparer()
    {
        // S'adapte au type exacte.
        m_element->accepter(*this);
        if (m_element->aObjet())
        {
            // Adapte l'objet dessinable.
            IObjet_S iObjet = m_element->getObjet();
            m_objDessinable.setElement(iObjet);
        }
    }
} // namespace vue
