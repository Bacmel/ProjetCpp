#include "hex/Masque.hpp"
#include <stdexcept>

namespace hex
{
    Masque Masque::contour()
    {
        // Ajoute les coordonnées adjacentes au centre du repère.
        Masque contour;
        Direction directions[] = {Direction::Nord,
                                  Direction::NordEst,
                                  Direction::SudEst,
                                  Direction::Sud,
                                  Direction::SudOuest,
                                  Direction::NordOuest};
        for (Direction dir : directions)
        {
            contour.insert(Coordonnees::direction(dir));
        }
        return contour;
    }

    Masque::Masque() : std::set<Coordonnees>() {}

    Masque Masque::operator||(const Masque& autre) const
    {
        // Equivalent à une union.
        Masque ou(autre);
        for (auto itr = this->begin(); itr != this->end(); itr++)
        {
            ou.insert(*itr);
        }
        return ou;
    }

    Masque Masque::operator&&(const Masque& autre) const
    {
        // Equivalent à un inter.
        Masque et;
        for (auto itr = this->begin(); itr != this->end(); itr++)
        {
            if (autre(*itr)) { et.insert(*itr); }
        }
        return et;
    }

    Masque Masque::operator+(const Coordonnees& autre) const
    {
        // Ajout nouvelle case.
        Masque plus(*this);
        plus.insert(autre);
        return plus;
    }

    Masque Masque::operator-(const Coordonnees& autre) const
    {
        // Ajout nouvelle case.
        Masque moins(*this);
        moins.erase(moins.find(autre));
        return moins;
    }

    Masque Masque::deplacer(const Coordonnees& vecteur) const
    {
        // Déplace une à une les cases et les ajoute à un nouveau masque.
        Masque deplace;
        for (auto itr = this->begin(); itr != this->end(); itr++)
        {
            deplace.insert((*itr) + vecteur);
        }
        return deplace;
    }

    bool Masque::operator()(const Coordonnees& c) const
    {
        // Vérifie que la coordonnée est présente dans le set.
        if (this->find(c) != this->end()) { return true; }
        return false;
    }

    Masque Masque::tournerTrigonometrique(const Coordonnees& centre) const
    {
        // Tourne une à une les cases et les ajoute à un nouveau masque.
        Masque masqueTournee;
        for (auto itr = begin(); itr != end(); itr++)
        {
            Coordonnees tournee = (*itr).tournerTrigonometrique(centre);
            masqueTournee.insert(tournee);
        }
        return masqueTournee;
    }

    Masque Masque::tournerHoraire(const Coordonnees& centre) const
    {
        // Tourne une à une les cases et les ajoute à un nouveau masque.
        Masque masqueTournee;
        for (auto itr = begin(); itr != end(); itr++)
        {
            Coordonnees tournee = (*itr).tournerHoraire(centre);
            masqueTournee.insert(tournee);
        }
        return masqueTournee;
    }

    Masque Masque::tournerVers(const Coordonnees& centre, Direction cible, Direction initiale) const
    {
        // Tourne une à une les cases et les ajoute à un nouveau masque.
        Masque masqueTournee;
        for (auto itr = begin(); itr != end(); itr++)
        {
            Coordonnees tournee = (*itr).tournerVers(centre, cible, initiale);
            masqueTournee.insert(tournee);
        }
        return masqueTournee;
    }
} // namespace hex
