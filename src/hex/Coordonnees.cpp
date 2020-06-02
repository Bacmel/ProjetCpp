#include "hex/Coordonnees.hpp"
#include <cmath>
#include <sstream>
#include <stdexcept>
#include "utils/HexPixelConvertisseur.hpp"

namespace hex
{
    Coordonnees Coordonnees::direction(Direction direction)
    {
        if (direction == Direction::Nord)
        {
            Coordonnees nord(0, -1, 1);
            return nord;
        }
        if (direction == Direction::NordEst)
        {
            Coordonnees nordEst(1, -1, 0);
            return nordEst;
        }
        if (direction == Direction::SudEst)
        {
            Coordonnees sudEst(1, 0, -1);
            return sudEst;
        }
        if (direction == Direction::Sud)
        {
            Coordonnees sud(0, 1, -1);
            return sud;
        }
        if (direction == Direction::SudOuest)
        {
            Coordonnees sudOuest(-1, 1, 0);
            return sudOuest;
        }
        if (direction == Direction::NordOuest)
        {
            Coordonnees nordOuest(-1, 0, 1);
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

    float Coordonnees::angle(const Coordonnees& autre) const
    {
        utils::HexPixelConvertisseur convertisseur;
        sf::Vector2f pixel = convertisseur(1, autre - *this);
        // Calcul l'angle depuis l'axe du nord vers le point relatif.
        float angle = M_PI_2 + std::atan2(pixel.y, pixel.x);
        return angle;
    }

    Direction Coordonnees::direction(const Coordonnees& autre) const
    {
        // Récupère l'angle dans [0; M_PI[
        float angle = M_PI + this->angle(autre);
        float indiceDirectionf = 3.f * angle / M_PI;
        int indiceDirection = (int)indiceDirectionf;
        // Vérifie que l'indice est un entier.
        if (std::abs(indiceDirectionf - indiceDirection) > 1e-5)
        {
            throw std::invalid_argument(
                "Coordonnees::direction : L'angle avec l'autre case ne correspond pas à une direction.");
        }
        // Récupère la direction.
        Direction directions[] = {Direction::Sud,
                                  Direction::SudOuest,
                                  Direction::NordOuest,
                                  Direction::Nord,
                                  Direction::NordEst,
                                  Direction::SudEst};
        return directions[indiceDirection];
    }
    Coordonnees Coordonnees::tournerGauche(const Coordonnees& centre) const
    {
        Coordonnees relative = *this - centre;
        Coordonnees relativeTournee(-relative.getZ(), -relative.getX(), -relative.getY());
        Coordonnees tournee = relativeTournee + centre;
        return tournee;
    }

    Coordonnees Coordonnees::tournerDroite(const Coordonnees& centre) const
    {
        Coordonnees relative = *this - centre;
        Coordonnees relativeTournee(-relative.getY(), -relative.getZ(), -relative.getX());
        Coordonnees tournee = relativeTournee + centre;
        return tournee;
    }

    void Coordonnees::arrondir(float x, float y, float z)
    {
        float xRond = std::roundf(x);
        float yRond = std::roundf(y);
        float zRond = std::roundf(z);

        float xDiff = std::abs(x - xRond);
        float yDiff = std::abs(y - yRond);
        float zDiff = std::abs(z - zRond);

        if (xDiff > yDiff && xDiff > zDiff) { xRond = -yRond - zRond; }
        else if (yDiff > zDiff)
        {
            yRond = -xRond - zRond;
        }
        m_colonne = (int)xRond;
        m_ligne = (int)yRond;
    }

    void Coordonnees::arrondir(float ligne, float colonne) { arrondir(colonne, ligne, -colonne - ligne); }

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

    bool Coordonnees::operator>(const Coordonnees& autre) const
    {
        return (m_colonne == autre.m_colonne) ? (m_ligne > autre.m_ligne) : (m_colonne > autre.m_colonne);
    }
    bool Coordonnees::operator>=(const Coordonnees& autre) const { return (*this == autre || *this > autre); }
    bool Coordonnees::operator<(const Coordonnees& autre) const { return (autre > *this); }
    bool Coordonnees::operator<=(const Coordonnees& autre) const { return (*this == autre || *this < autre); }
    std::ostream& operator<<(std::ostream& os, const Coordonnees& c)
    {
        os << "Coordonnees(" << c.getLigne() << ", " << c.getColonne() << ")";
        return os;
    }
} // namespace hex
