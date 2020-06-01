#ifndef COORDONNEES_HPP
#define COORDONNEES_HPP

#include <ostream>
namespace hex
{

    enum class Direction
    {
        NordOuest,
        Nord,
        NordEst,
        SudEst,
        Sud,
        SudOuest
    };

    class Coordonnees
    {
    protected:
        int m_ligne;
        int m_colonne;

    public:

        static Coordonnees direction(Direction direction);

        Coordonnees();
        Coordonnees(int ligne, int colonne);
        Coordonnees(int x, int y, int z);

        Coordonnees(const Coordonnees& autre) = default; // Constructeur par copie
        Coordonnees(Coordonnees&& autre) = default; // Constructeur par déplacement
        Coordonnees& operator=(const Coordonnees& autre) = default; // Assignation par copie
        Coordonnees& operator=(Coordonnees&& autre) = default; // Assignation par déplacement
        virtual ~Coordonnees() = default;

        inline int getColonne() const { return m_colonne; }
        inline int getLigne() const { return m_ligne; }

        inline int getX() const { return m_colonne; }
        inline int getY() const { return m_ligne; };
        inline int getZ() const { return -m_colonne - m_ligne; }

        Coordonnees translate(Direction dir, int distance = 1) const;
        int longueur() const;
        int distance(const Coordonnees& autre) const;

        Coordonnees tournerGauche(const Coordonnees& centre) const;
        Coordonnees tournerDroite(const Coordonnees& centre) const;

        void arrondir(float x, float y, float z);
        void arrondir(float ligne, float colonne);

        Coordonnees operator+(const Coordonnees& autre) const;
        Coordonnees operator-() const;
        Coordonnees operator-(const Coordonnees& autre) const;
        Coordonnees operator*(int scalaire) const;

        bool operator==(const Coordonnees& autre) const;
        bool operator!=(const Coordonnees& autre) const;
        bool operator>(const Coordonnees& autre) const;
        bool operator>=(const Coordonnees& autre) const;
        bool operator<(const Coordonnees& autre) const;
        bool operator<=(const Coordonnees& autre) const;
        friend std::ostream& operator<<(std::ostream& os, const Coordonnees& c);
    };

}; // namespace hex
#endif
