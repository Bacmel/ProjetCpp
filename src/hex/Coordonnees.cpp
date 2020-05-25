#include "hex/Coordonnees.hpp"
#include <cmath>
#include <sstream>
#include <stdexcept>

namespace hex
{
    Coordonnees Coordonnees::direction(Direction direction)
    {
        if (direction == Direction::Nord)
        {
            Coordonnees nord(0, 1, -1);
            return nord;
        }
        if (direction == Direction::NordEst)
        {
            Coordonnees nordEst(1, 0, -1);
            return nordEst;
        }
        if (direction == Direction::SudEst)
        {
            Coordonnees sudEst(1, -1, 0);
            return sudEst;
        }
        if (direction == Direction::Sud)
        {
            Coordonnees sud(0, -1, 1);
            return sud;
        }
        if (direction == Direction::SudOuest)
        {
            Coordonnees sudOuest(-1, 0, 1);
            return sudOuest;
        }
        if (direction == Direction::NordOuest)
        {
            Coordonnees nordOuest(-1, 1, 0);
            return nordOuest;
        }
        std::stringstream ss;
        ss << "Direction : " << (int)direction << " non supportée.";
        throw std::invalid_argument(ss.str());
    }

    Coordonnees::Coordonnees() : m_ligne(0), m_colonne(0) {}

    Coordonnees::Coordonnees(int ligne, int colonne) : m_ligne(ligne), m_colonne(colonne) {}

    Coordonnees::Coordonnees(int x, int y, int z) : m_ligne(y), m_colonne(x)
    {
        if (x + y + z != 0) { throw std::invalid_argument("La somme des coordonnees n'est pas nulle."); }
    }

    Coordonnees Coordonnees::translate(Direction dir, int distance) const
    {
        Coordonnees relative = Coordonnees::direction(dir) * distance;
        Coordonnees absolue = *this + relative;
        return absolue;
    }

    int Coordonnees::longueur() const
    {
        float x(getX()), y(getY()), z(getZ());
        return int((fabsf(x) + fabsf(y) + fabsf(z)) / 2);
    }

    int Coordonnees::distance(const Coordonnees& autre) const
    {
        Coordonnees relative = autre - *this;
        return relative.longueur();
    }

    Coordonnees Coordonnees::operator+(const Coordonnees& autre) const
    {
        Coordonnees somme(m_ligne + autre.m_ligne, m_colonne + autre.m_colonne);
        return somme;
    }

    Coordonnees Coordonnees::operator-() const
    {
        Coordonnees oppose(-m_ligne, -m_colonne);
        return oppose;
    }

    Coordonnees Coordonnees::operator-(const Coordonnees& autre) const
    {
        Coordonnees difference(m_ligne - autre.m_ligne, m_colonne - autre.m_colonne);
        return difference;
    }

    Coordonnees Coordonnees::operator*(int scalaire) const
    {
        Coordonnees produit(scalaire * m_ligne, scalaire * m_colonne);
        return produit;
    }

    bool Coordonnees::operator==(const Coordonnees& autre) const
    {
        return m_ligne == autre.m_ligne && m_colonne == autre.m_colonne;
    }

    bool Coordonnees::operator!=(const Coordonnees& autre) const { return !(*this == autre); }

    std::ostream& operator<<(std::ostream& os, const Coordonnees& c)
    {
        os << "Coordonnees(" << c.getLigne() << ", " << c.getColonne() << ")";
        return os;
    }
} // namespace hex
