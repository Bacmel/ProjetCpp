#include "partie/Partie.hpp"
#include "donjon/Donjon.hpp"
#include "donjon/cases/ACase.hpp"
#include "donjon/cases/Sol.hpp"
#include "donjon/cases/Trou.hpp"
#include "err/CreationErreur.hpp"
#include "err/InfoErreur.hpp"
#include "hex/CarteHexagone.hpp"
#include "partie/etat/Decision.hpp"

using namespace hex;
using namespace donjon;
using namespace donjon::cases;
using namespace obj;
using namespace partie::etat;
using namespace per;
using namespace std;

namespace partie
{
    Partie::Partie(strat::IStrategie_S& strategie) : m_equipes()
    {
        // Crée la carte.
        genererCarte();
        // Crée un 1ere équipe pour initialiser la machine à état.
        size_t indice = genererEquipe(strategie);
        m_etat = IEtat_S(new Decision(indice));
    }

    Equipe& Partie::getEquipe(size_t indice) { return m_equipes.at(indice); }

    const Equipe& Partie::getEquipe(size_t indice) const { return m_equipes.at(indice); }

    void Partie::setEtat(etat::IEtat_S etat)
    {
        // Conserve l'état précédent pour qu'il puisse terminer ses actions
        // avant d'être libéré.
        m_etatP = m_etat;
        m_etat = etat;
    }

    size_t Partie::genererEquipe(strat::IStrategie_S& strategie)
    {
        // Crée une nouvelle équipe vide, la conserve et donne son indice.
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
        // Crée une carte et la remplie de Sol.
        ICarte_S<ACase_S> carte(new CarteHexagone<ACase_S>(5));
        function<ACase_S()> fournisseurSol = []() { return make_shared<Sol>(); };
        carte->remplir(fournisseurSol);
        // Place un trou.
        Coordonnees positionTrou = Coordonnees().translater(Direction::Nord);
        (*carte)(positionTrou) = ACase_S(new Trou());
        // Crée le donjon.
        m_donjon = IDonjon_S(new Donjon(carte));
    }

    void Partie::genererObjet(IObjet_S objet)
    {
        // Trouve une coordonnées sans objet et y dépose l'objet.
        Coordonnees c = coordonneesLibre();
        m_donjon->deposer(objet, c);
    }

    void Partie::demander() { m_etat->operation(*this); }

    void Partie::demander(size_t indiceObjet) { m_etat->operation(*this, indiceObjet); }

    void Partie::demander(Coordonnees coordonnees) { m_etat->operation(*this, coordonnees); }

    int Partie::indiceGagnant() const
    {
        int gagnant(-1);
        // Pour chaque équipe, on regarde s'il y a au moins 1 survivant.
        for (int indice = 0; indice < (int)m_equipes.size(); indice++)
        {
            const Equipe& equipe = m_equipes.at(indice);
            if (equipe.compterSurvivant() > 0)
            {
                // Si on a déjà un gagnant, la partie n'est pas terminée.
                if (gagnant != -1) { throw err::InfoErreur("Partie::indiceGagnant : Information non disponible."); }
                // On stock le gagnant.
                gagnant = indice;
            }
        }
        return gagnant;
    }

    size_t Partie::indiceEquipe(APersonnage_SC personnage) const
    {
        // On interroge chaque équipe.
        for (size_t i = 0; i < m_equipes.size(); i++)
        {
            const Equipe& equipe = m_equipes.at(i);
            if (equipe.estMembre(*personnage)) { return i; }
        }
        // Aucune équipe ne connais ce personnage.
        throw err::InfoErreur("Partie::indiceEquipe : Le personnage ne fait pas partie d'une équipe.");
    }

    hex::Coordonnees Partie::coordonneesLibre()
    {
        // Vérifie qu'il existe une case vide.
        vector<Coordonnees> coordonnees = m_donjon->getCaseVide();
        size_t size = coordonnees.size();
        if (size == 0) { throw err::CreationErreur("Partie::coordonneesLibre : Plus de case disponible."); }
        // Tire au sort une case parmis celles libres.
        auto c = coordonnees.begin();
        c += rand() % coordonnees.size();
        return *c;
    }

} // namespace partie
