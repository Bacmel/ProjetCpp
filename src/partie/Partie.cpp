#include "partie/Partie.hpp"
#include <algorithm>
#include "donjon/Donjon.hpp"
#include "donjon/cases/ICase.hpp"
#include "donjon/cases/Sol.hpp"
#include "donjon/cases/Trou.hpp"
#include "err/CreationErreur.hpp"
#include "err/InfoErreur.hpp"
#include "hex/CarteHexagone.hpp"
#include "partie/etat/Initial.hpp"
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
    Partie::Partie(std::vector<Equipe>& equipes) : m_equipes(equipes) {
        
        genererCarte(); }

    void Partie::genererPersonnage(APersonnage_S personnage, size_t indice)
    {
        Coordonnees c = coordonneesLibre();
        m_equipes.at(indice).insert(personnage->getId());
        m_donjon->invoquer(personnage, c);
    }

    void Partie::genererCarte()
    {
        // A changer
        ICarte_S<ICase_S> carte(new CarteHexagone<ICase_S>(5));
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
        if (size == 0) { throw err::CreationErreur("Partie::coordonneesLibre : Plus de case disponible."); }
        auto c = coordonnees.begin();
        c += rand() % coordonnees.size();
        return *c;
    }

} // namespace partie
