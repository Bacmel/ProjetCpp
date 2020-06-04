#include "partie/etat/Selection.hpp"
#include <iostream>
#include <stdexcept>
#include "partie/Partie.hpp"
#include "partie/etat/FinTour.hpp"
#include "partie/etat/Initial.hpp"
#include "partie/etat/PersoActif.hpp"

using namespace std;

namespace partie::etat
{
    Selection::Selection(size_t equipe) : m_equipe(equipe) {}

    void Selection::afficher() const { std::cout << "Selection{m_equipe : " << m_equipe << "}\n"; }

    per::APersonnage_SC Selection::getPersoSelect() const
    {
        throw std::invalid_argument("Selection::getPersoSelect : Pas de personnage sélectionné.");
    }

    obj::IObjet_SC Selection::getObjetSelect() const
    {
        throw std::invalid_argument("Selection::getPersoSelect : Pas d'objet sélectionné.");
    }

    void Selection::operation(Partie&, const hex::Coordonnees&)
    {
        throw logic_error("Selection::operation() : operation non supporte");
    }

    void Selection::operation(Partie&, size_t)
    {
        throw logic_error("Selection::operation() : operation non supporte");
    }

    void Selection::operation(Partie& partie)
    {
        vector<Equipe>& equipes = partie.getEquipes();
        Equipe& equipe = equipes.at(m_equipe);
        size_t nbMembres = equipe.compterMembres();
        if (nbMembres == 0) { partie.setEtat(IEtat_S(new FinTour(m_equipe))); }
        else if (nbMembres == 1)
        {
            per::APersonnage_S personnage = equipe.getMembre(0);
            partie.setEtat(IEtat_S(new PersoActif(m_equipe, personnage)));
        }
        else
        {
            partie.setEtat(IEtat_S(new Initial(m_equipe)));
        }
    }

} // namespace partie::etat
