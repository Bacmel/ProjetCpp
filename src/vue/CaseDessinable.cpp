#include "vue/CaseDessinable.hpp"
#include <SFML/Graphics.hpp>
#include "err/SansObjetErreur.hpp"
#include "utils/HexPixelConvertisseur.hpp"
#include "vue/TextureGest.hpp"

using namespace sf;
using namespace donjon::cases;
using namespace obj;

namespace vue
{
    CaseDessinable::CaseDessinable(float cote) :
        ADessinable(cote),
        m_case(nullptr),
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

    CaseDessinable::CaseDessinable(float cote, ICase& iCase) : CaseDessinable(cote) { setElement(iCase); }

    void CaseDessinable::setElement(ICase& iCase)
    {
        // On se détache de la précédente case et on s'attache à la nouvelle.
        if (m_case != nullptr) { m_case->detacher(this); }
        m_hexagone.setFillColor(Color::White);
        iCase.attacher(this);
        // On met à jour les champs.
        actualiser(iCase);
        m_case = &iCase;
    }

    void CaseDessinable::surligner()
    {
        m_hexagone.setOutlineThickness(-2);
        m_hexagone.setFillColor(Color(255, 255, 50));
        m_hexagone.setOutlineColor(sf::Color::Yellow);
    }

    void CaseDessinable::setCote(float cote)
    {
        ADessinable::setCote(cote);
        m_hexagone.setRadius(cote);
        m_hexagone.setOrigin(cote, cote);
    }

    void CaseDessinable::visite(const Sol&)
    {
        m_hexagone.setOutlineThickness(-0.5);
        m_hexagone.setOutlineColor(sf::Color::Black);
        m_hexagone.setTexture(m_textureSol.get());
    }

    void CaseDessinable::visite(const Trou&)
    {
        m_hexagone.setOutlineThickness(0);
        m_hexagone.setTexture(m_textureTrou.get());
    }

    void CaseDessinable::draw(RenderTarget& target, RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_hexagone, states);
        if (m_case->aObjet()) { target.draw(m_objDessinable, states); }
    }

    void CaseDessinable::actualiser(const donjon::cases::ICase& iCase)
    {
        iCase.accepter(*this);
        if (iCase.aObjet())
        {
            const IObjet& iObjet = iCase.getObjet();
            m_objDessinable.setObjet(iObjet);
        }
    }
} // namespace vue
