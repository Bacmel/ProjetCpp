#include "partie/Partie.hpp"
#include "donjon/Donjon.hpp"
#include "donjon/cases/ICase.hpp"
#include "donjon/cases/Sol.hpp"
#include "donjon/cases/Trou.hpp"
#include "err/CreationErreur.hpp"
#include "err/InfoErreur.hpp"
#include "hex/CarteHexagone.hpp"
#include "per/Heros.hpp"

using namespace donjon;
using namespace donjon::cases;
using namespace hex;
using namespace per;
using namespace obj;
using namespace std;

namespace partie
{
    Partie::Partie(size_t joueurs) : m_equipes(joueurs) { genererCarte(); }

    void Partie::genererPersonnage(APersonnage_S personnage, size_t indice)
    {
        Coordonnees c = coordonneesLibre();
        m_equipes.at(indice).insert(personnage->getId());
        m_donjon->invoquer(personnage, c);
    }

    void Partie::genererCarte()
    {
        // A changer
        ICarte_S<ICase_S> carte(new CarteHexagone<ICase_S>(1));
        function<ICase_S()> fournisseurSol = []() { return make_shared<Sol>(); };
        carte->remplir(fournisseurSol);
        Coordonnees positionTrou = Coordonnees().translate(Direction::Nord);
        (*carte)(positionTrou) = ICase_S(new Trou());
        m_donjon = IDonjon_S(new Donjon(carte));
    }

    void Partie::genererObjet(IObjet_S objet)
    {
        Coordonnees c = coordonneesLibre();
        m_donjon->deposer(objet, c);
    }

    void Partie::deplacerPersonnage(size_t indice, per::APersonnage_S personnage, Deplacement deplacement, Coordonnees cible)
    {
        if (indice != indiceEquipe(personnage))
        { /** throw (Partie::deplacerPersonnage : le personnage n'appartient pas a l'equipe.) */
        }
        m_donjon->deplace(*personnage, deplacement, cible);
    }

    void Partie::finTourJoueur(size_t indice)
    {
        // A faire
    }

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
        size_t indice = personnage->getId();
        for (size_t i = 0; i < m_equipes.size(); i++)
        {
            if (m_equipes.at(i).find(indice) != m_equipes.at(i).end()) { return i; }
        }
        throw err::InfoErreur("Partie::indiceEquipe : Information non disponible.");
    }

    hex::Coordonnees Partie::coordonneesLibre()
    {
        vector<Coordonnees> coordonnees = m_donjon->getCaseVide();
        size_t size = coordonnees.size();
        cout << size << endl;
        if (size == 0) { throw err::CreationErreur("Partie::coordonneesLibre : Plus de case disponible."); }
        auto c = coordonnees.begin();
        c += rand() % coordonnees.size();
        cout << *c << endl;
        return *c;
    }

} // namespace partie
