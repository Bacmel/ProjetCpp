#include "partie/Partie.hpp"
#include "donjon/Donjon.hpp"
#include "donjon/cases/ICase.hpp"
#include "donjon/cases/Sol.hpp"
#include "donjon/cases/Trou.hpp"
#include "err/CreationErreur.hpp"
#include "err/InfoErreur.hpp"
#include "hex/CarteHexagone.hpp"
#include "partie/etat/Decision.hpp"
#include "per/Heros.hpp"

using namespace donjon;
using namespace donjon::cases;
using namespace partie::etat;
using namespace hex;
using namespace per;
using namespace obj;
using namespace std;

namespace partie
{
    Partie::Partie(strat::IStrategie_S& strategie) : m_equipes()
    {
        // Crée la carte.
        genererCarte();
        size_t indice = genererEquipe(strategie);
        m_etat = IEtat_S(new Decision(indice));
    }

    Equipe& Partie::getEquipe(size_t indice) { return m_equipes.at(indice); }

    const Equipe& Partie::getEquipe(size_t indice) const { return m_equipes.at(indice); }

    void Partie::setEtat(etat::IEtat_S etat)
    {
        m_etatP = m_etat;
        m_etat = etat;
    }

    size_t Partie::genererEquipe(strat::IStrategie_S& strategie)
    {
        Equipe equipe(strategie);
        m_equipes.push_back(equipe);
        return m_equipes.size() - 1;
    }

    void Partie::genererPersonnage(APersonnage_S personnage, size_t indice)
    {
        // Récupère une case libre et l'équipe souhaitée.
        Coordonnees c = coordonneesLibre();
        Equipe& equipe = m_equipes.at(indice);
        // Ajoute le joueur dans l'équipe et dans le donjon.
        equipe.ajouterMembre(personnage);
        m_donjon->invoquer(personnage, c);
    }

    void Partie::genererCarte()
    {
        // A changer
        ICarte_S<ICase_S> carte(new CarteHexagone<ICase_S>(5));
        function<ICase_S()> fournisseurSol = []() { return make_shared<Sol>(); };
        carte->remplir(fournisseurSol);
        Coordonnees positionTrou = Coordonnees().translater(Direction::Nord);
        (*carte)(positionTrou) = ICase_S(new Trou());
        m_donjon = IDonjon_S(new Donjon(carte));
    }

    void Partie::genererObjet(IObjet_S objet)
    {
        Coordonnees c = coordonneesLibre();
        m_donjon->deposer(objet, c);
    }

    void Partie::demande(Coordonnees coordonnees) { m_etat->operation(*this, coordonnees); }

    void Partie::demande(size_t indiceObjet) { m_etat->operation(*this, indiceObjet); }

    void Partie::demande() { m_etat->operation(*this); }

    int Partie::indiceGagnant() const
    {
        int precedent = -1;
        int gagnant = -1;
        for (size_t i = 0; i < m_donjon->getNbPersonnages(); i++)
        {
            APersonnage_SC personnage = m_donjon->getPersonnage(i);
            if (personnage->estVivant())
            {
                precedent = gagnant;
                gagnant = indiceEquipe(personnage);
            }
            if (precedent != -1 && precedent != gagnant)
            { throw err::InfoErreur("Partie::indiceGagnant : Information non disponible."); }
        }
        return gagnant;
    }

    size_t Partie::indiceEquipe(APersonnage_SC personnage) const
    {
        for (size_t i = 0; i < m_equipes.size(); i++)
        {
            const Equipe& equipe = m_equipes.at(i);
            if (equipe.estMembre(*personnage)) { return i; }
        }
        throw err::InfoErreur("Partie::indiceEquipe : Information non disponible.");
    }

    hex::Coordonnees Partie::coordonneesLibre()
    {
        vector<Coordonnees> coordonnees = m_donjon->getCaseVide();
        size_t size = coordonnees.size();
        if (size == 0) { throw err::CreationErreur("Partie::coordonneesLibre : Plus de case disponible."); }
        auto c = coordonnees.begin();
        c += rand() % coordonnees.size();
        return *c;
    }

} // namespace partie
