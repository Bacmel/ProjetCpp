#include "partie/etat/SelectionAuto.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "partie/Partie.hpp"
#include "partie/etat/FinTour.hpp"
#include "partie/etat/PersoActif.hpp"
#include "partie/etat/SelectionMan.hpp"

using namespace std;

namespace partie::etat
{
    SelectionAuto::SelectionAuto(size_t equipe) : m_equipe(equipe) {}

    string SelectionAuto::enTexte() const
    {
        stringstream ss;
        ss << "<Etat SelectionAuto>" << endl;
        ss << "equipe : " << m_equipe << endl;
        return ss.str();
    }

    per::APersonnage_S SelectionAuto::getPersoSelect()
    {
        throw std::logic_error("SelectionAuto::getPersoSelect : Pas de personnage sélectionné.");
    }

    per::APersonnage_SC SelectionAuto::getPersoSelect() const
    {
        throw std::logic_error("SelectionAuto::getPersoSelect : Pas de personnage sélectionné.");
    }

    obj::IObjet_S SelectionAuto::getObjetSelect()
    {
        throw std::logic_error("SelectionAuto::getPersoSelect : Pas d'objet sélectionné.");
    }

    obj::IObjet_SC SelectionAuto::getObjetSelect() const
    {
        throw std::logic_error("SelectionAuto::getPersoSelect : Pas d'objet sélectionné.");
    }

    void SelectionAuto::operation(Partie&, const hex::Coordonnees&)
    {
        throw logic_error("SelectionAuto::operation : operation non supporte");
    }

    void SelectionAuto::operation(Partie&, size_t)
    {
        throw logic_error("SelectionAuto::operation : operation non supporte");
    }

    void SelectionAuto::operation(Partie& partie)
    {

        Equipe& equipe = partie.getEquipe(m_equipe);
        size_t nbMembres = equipe.compterMembres();

        if (nbMembres == 0)
        {
            // L'équipe n'a plus de membre, on met fin à son tour.
            partie.setEtat(IEtat_S(new FinTour(m_equipe)));
        }
        else if (nbMembres == 1)
        {
            // L'équipe n'a qu'un seul membre, on le sélectionne.
            per::APersonnage_S personnage = equipe.getMembre(0);
            partie.setEtat(IEtat_S(new PersoActif(m_equipe, personnage)));
        }
        else
        {
            // L'équipe à plusieurs membres, on laise le joueur choisir.
            partie.setEtat(IEtat_S(new SelectionMan(m_equipe)));
        }
    }

} // namespace partie::etat
