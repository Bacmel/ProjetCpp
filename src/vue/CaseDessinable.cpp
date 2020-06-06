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

    CaseDessinable::CaseDessinable(const CaseDessinable& autre) :
        ADessinable(autre.m_cote),
        m_objDessinable(autre.m_cote)
    {
        *this = autre;
    }

    CaseDessinable& CaseDessinable::operator=(const CaseDessinable& autre)
    {
        // Copie les valeurs
        m_hexagone = autre.m_hexagone;
        m_textureSol = autre.m_textureSol;
        m_textureTrou = autre.m_textureTrou;
        m_objDessinable = autre.m_objDessinable;
        // Se détache du précédent personnage et s'adapte au nouveau.
        if (m_element != nullptr) { m_element->detacher(this); }
        if (autre.m_element != nullptr) { setElement(autre.m_element); }
        return *this;
    }

    CaseDessinable::~CaseDessinable()
    {
        // Se détache du personnage observé.
        if (m_element != nullptr) { m_element->detacher(this); }
    }

    CaseDessinable::CaseDessinable(float cote, ACase_S aCase) : CaseDessinable(cote)
    {
        if (aCase == nullptr) { throw std::invalid_argument("CaseDessinable::CaseDessinable : La case est nulle!"); }
        setElement(aCase);
    }

    void CaseDessinable::setElement(ACase_S aCase)
    {
        if (aCase == nullptr) { throw std::invalid_argument("CaseDessinable::setElement : La case est nulle!"); }
        // On se détache de la précédente case et on s'attache à la nouvelle.
        if (m_element != nullptr) { m_element->detacher(this); }
        aCase->attacher(this);
        // On met à jour les champs.
        m_hexagone.setFillColor(Color::White);
        m_element = aCase;
        actualiser(*aCase);
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
        // Applique la transformation.
        states.transform *= getTransform();
        // Dessine la case puis son objet.
        target.draw(m_hexagone, states);
        if (m_element->aObjet()) { target.draw(m_objDessinable, states); }
    }

    void CaseDessinable::actualiser(const donjon::cases::ACase&)
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
