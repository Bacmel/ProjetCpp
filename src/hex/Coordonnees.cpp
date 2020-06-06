#include "hex/Coordonnees.hpp"
#include <cmath>
#include <sstream>
#include <stdexcept>
#include "utils/HexPixelConvertisseur.hpp"

namespace hex
{
    Coordonnees Coordonnees::arrondir(float ligne, float colonne)
    {
        return arrondir( colonne, ligne, -colonne - ligne);
    }

    Coordonnees Coordonnees::arrondir(float x, float y, float z)
    {
        if (std::abs(x + y + z) > 1e-5)
        { throw std::invalid_argument("Coordonnees::Coordonnees : La somme des composantes n'est pas nulle."); }
        // Arrondie les coordonnées.
        float xRond = std::round(x);
        float yRond = std::round(y);
        float zRond = std::round(z);
        // S'assure que la somme des composantes soit nulle. On recalcule la
        // composante arrondie qui maximise l'erreur en fonction des 2 autres.
        float xDiff = std::abs(x - xRond);
        float yDiff = std::abs(y - yRond);
        float zDiff = std::abs(z - zRond);

        if (xDiff > yDiff && xDiff > zDiff) { xRond = -yRond - zRond; }
        else if (yDiff > zDiff)
        {
            yRond = -xRond - zRond;
        }
        // On initialise l'objet.
        return Coordonnees((int)yRond, (int)xRond);
    }

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

    Coordonnees Coordonnees::translater(Direction dir, int distance) const
    {
        // Calcul le déplacement relatif.
        Coordonnees relative = Coordonnees::direction(dir) * distance;
        // Ajoute l'origine à la coordonnées relative pour avoir la position absolue.
        Coordonnees absolue = *this + relative;
        return absolue;
    }

    int Coordonnees::longueur() const { return int((std::abs(getX()) + std::abs(getY()) + std::abs(getZ())) / 2.0F); }

    int Coordonnees::distance(const Coordonnees& autre) const
    {
        // Calcule la longueur de la position relative.
        Coordonnees relative = autre - *this;
        return relative.longueur();
    }

    float Coordonnees::angle(const Coordonnees& autre) const
    {
        utils::HexPixelConvertisseur convertisseur;
        // Passage dans le repère orthogonale (repère de l'écran).
        sf::Vector2f pixel = convertisseur(1, autre - *this);
        // Puis calcul de l'angle depuis l'axe du nord vers le point relatif.
        float angle = M_PI_2 + std::atan2(pixel.y, pixel.x);
        return angle;
    }

    Direction Coordonnees::direction(const Coordonnees& autre) const
    {
        // Récupère l'angle dans [0; 2 * M_PI[
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
        return directions[indiceDirection % 6];
    }
    Coordonnees Coordonnees::tournerTrigonometrique(const Coordonnees& centre) const
    {
        // Fait tourner la coordonnée relative pour l'ajoute au centre de la rotation.
        Coordonnees relative = *this - centre;
        Coordonnees relativeTournee(-relative.getZ(), -relative.getX(), -relative.getY());
        Coordonnees tournee = relativeTournee + centre;
        return tournee;
    }

    Coordonnees Coordonnees::tournerHoraire(const Coordonnees& centre) const
    {
        // Fait tourner la coordonnée relative pour l'ajoute au centre de la rotation.
        Coordonnees relative = *this - centre;
        Coordonnees relativeTournee(-relative.getY(), -relative.getZ(), -relative.getX());
        Coordonnees tournee = relativeTournee + centre;
        return tournee;
    }

    Coordonnees Coordonnees::tournerVers(const Coordonnees& centre, Direction cible, Direction initiale) const
    {
        Coordonnees origine;
        Coordonnees repere = Coordonnees::direction(initiale);
        Coordonnees tournee = *this;
        // Fait tourner la coordonnées voulue avec la coordonnées qui sert
        // d'indicateur, jusqu'à ce que l'indicateur soit dans la direction
        // ciblée.
        for (size_t i = 0; i < 6; i++)
        {
            if (origine.direction(repere) == cible) { break; }
            tournee = tournee.tournerTrigonometrique(centre);
            repere = repere.tournerTrigonometrique(origine);
        }
        return tournee;
    }

    Coordonnees Coordonnees::operator+(const Coordonnees& autre) const
    {
        // Somme chaque composante.
        Coordonnees somme(m_ligne + autre.m_ligne, m_colonne + autre.m_colonne);
        return somme;
    }

    Coordonnees Coordonnees::operator-() const
    {
        // Inverse chaque composante.
        Coordonnees oppose(-m_ligne, -m_colonne);
        return oppose;
    }

    Coordonnees Coordonnees::operator-(const Coordonnees& autre) const
    {
        // Fait la différence avec chaque composante.
        Coordonnees difference(m_ligne - autre.m_ligne, m_colonne - autre.m_colonne);
        return difference;
    }

    Coordonnees Coordonnees::operator*(int scalaire) const
    {
        // Multiplie les coordonnees par le scalaire.
        Coordonnees produit(scalaire * m_ligne, scalaire * m_colonne);
        return produit;
    }

    bool Coordonnees::operator==(const Coordonnees& autre) const
    {
        // Vérifie l'égalité des 2 composantes.
        return m_ligne == autre.m_ligne && m_colonne == autre.m_colonne;
    }

    bool Coordonnees::operator!=(const Coordonnees& autre) const { return !(*this == autre); }

    bool Coordonnees::operator>(const Coordonnees& autre) const
    {
        // On tri par colonne puis par ligne.
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
