#include "partie/Partie.hpp"
#include "donjon/Donjon.hpp"
#include "donjon/cases/ICase.hpp"
#include "donjon/cases/Sol.hpp"
#include "donjon/cases/Trou.hpp"
#include "err/InfoErreur.hpp"
#include "hex/CarteHexagone.hpp"
#include "per/Heros.hpp"

using namespace donjon;
using namespace donjon::cases;
using namespace hex;
using namespace per;
using namespace std;

namespace partie
{
    Partie::Partie(size_t joueurs) :
        m_equipes(joueurs),
        m_personnages(),
        m_carte(new CarteHexagone<ICase_S>(5)),
        m_objets(),
        m_donjon(new Donjon(m_carte))
    {
    }

    void Partie::genererEquipe()
    {
        for (size_t i = 0; i < m_equipes.size(); i++)
        {
            genererPersonnage(i); // Generation Heros
        }
    }

    void Partie::genererPersonnage(size_t indice)
    {
        APersonnage_S h(new Heros(3));
        m_personnages.push_back(h);
        m_equipes.at(indice).insert(h->getId());
    }

    void Partie::genererCarte()
    {
        function<ICase_S()> fournisseurSol = []() { return make_shared<Sol>(); };
        m_carte->remplir(fournisseurSol);
        Coordonnees positionTrou = Coordonnees().translate(Direction::Nord);
        (*m_carte)(positionTrou) = ICase_S(new Trou());
    }

    void Partie::genererObjet()
    {
        // Pas encore.
    }

    void Partie::initialiserDonjon()
    {
        vector<APersonnage_S>::iterator itr;
        for (itr = m_personnages.begin(); itr != m_personnages.end(); itr++)
        {
            do
            {
                int ligne = (rand() % 10) - 5;
                int colonne = (rand() % 10) - 5;
                Coordonnees c(colonne, ligne);
                try
                {
                    m_donjon->invoquer(*itr, c);
                    break;
                }
                catch (std::invalid_argument)
                {
                }
            } while (true);
        }
    }

    void Partie::gererEquipe(size_t indice)
    {
        set<size_t>::iterator itr = m_equipes.at(indice).begin();
        for (itr; itr != m_equipes.at(indice).end(); itr++)
        {
            gererPersonnage(indicePersonnage((*itr)));
        }
    }

    void Partie::gererPersonnage(size_t indice)
    {
        do
        {
            int choix = rand()%6;
            Direction direction;
            switch(choix)
            {
                case 0:
                    direction = Direction::Nord;
                    break;
                case 1:
                    direction = Direction::NordEst;
                    break;
                case 2:
                    direction = Direction::SudEst;
                    break;
                case 3:
                    direction = Direction::Sud;
                    break;
                case 4:
                    direction = Direction::SudOuest;
                    break;
                case 5:
                    direction = Direction::NordOuest;
                    break;
            }
            Coordonnees c = m_personnages.at(indice)->getPosition().translate(direction);
            try
            {
                m_donjon->deplace(*(m_personnages.at(indice)), Deplacement::Marcher, c);
                break;
            }
            catch (std::invalid_argument)
            {
            }
        } while (true);
    }

    void Partie::gererObjet(size_t indice)
    {
        // Pas encore
    }

    int Partie::indiceGagnant()
    {
        int precedent = -1;
        int gagnant = -1;
        vector<APersonnage_S>::iterator itr;
        for (itr = m_personnages.begin(); itr != m_personnages.end(); itr++)
        {
            if ((*itr)->estVivant())
            {
                precedent = gagnant;
                gagnant = indiceEquipe((*itr));
            }
            if (precedent != -1 && precedent != gagnant)
            { throw err::InfoErreur("Partie::indiceGagnant : Information non disponible."); }
        }
        return gagnant;
    }

    size_t Partie::indiceEquipe(APersonnage_S personnage)
    {
        size_t indice = personnage->getId();
        for (size_t i = 0; i < m_equipes.size(); i++)
        {
            if (m_equipes.at(i).find(indice) != m_equipes.at(i).end()) { return i; }
        }
        throw err::InfoErreur("Partie::indiceEquipe : Information non disponible.");
    }

    size_t Partie::indicePersonnage(size_t id)
    {
        for (size_t i = 0; i < m_personnages.size(); i++)
        {
            if (id == m_personnages.at(i)->getId()) { return i; }
        }
        throw err::InfoErreur("Partie::indicePersonnage : Information non disponible.");
    }

} // namespace partie