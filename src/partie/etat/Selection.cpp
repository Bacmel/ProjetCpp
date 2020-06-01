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

    void Selection::operation(Partie& partie, const hex::Coordonnees& coordonnees)
    {
        vector<set<size_t>>& equipes = partie.getEquipes();
        set<size_t>& membres = equipes.at(m_equipe);

        if (membres.size() == 0) { partie.setEtat(IEtat_S(new FinTour(m_equipe))); }
        else if (membres.size() == 1)
        {
            auto itr = membres.begin();
            size_t idPerso = *itr;
            donjon::IDonjon_S donjon = partie.getDonjon();
            per::APersonnage_S personnage = donjon->getPersonnageParId(idPerso);
            partie.setEtat(IEtat_S(new PersoActif(m_equipe, personnage)));
        }
        else
        {
            partie.setEtat(IEtat_S(new Initial(m_equipe)));
        }
    }

} // namespace partie::etat
