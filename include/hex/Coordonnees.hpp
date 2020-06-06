#ifndef __COORDONNEES_HPP__
#define __COORDONNEES_HPP__

#include <ostream>
namespace hex
{

    /**
     * @brief Directions normales aux côtés d'un hexagone.
     *
     * Le nord ouest est en haut à gauche.
     */
    enum class Direction
    {
        NordOuest,
        Nord,
        NordEst,
        SudEst,
        Sud,
        SudOuest
    };

    /**
     * @brief Classe simplifiant les opérations géométrique sur une grille
     * hexagonale.
     */
    class Coordonnees
    {
    protected:
        /** @brief La ligne en coordonnées axiales. */
        int m_ligne;
        /** @brief La colonne en coordonnées axiales. */
        int m_colonne;

    public:
        /**
         * @brief Arrondit la coordonnée décimale à la coordonnée entière la
         * plus proche.
         *
         * @param ligne La ligne (en cases).
         * @param colonne La colonne (en cases).
         * @return Coordonnees La coordonnee au valeur arrondi.
         */
        static Coordonnees arrondir(float ligne, float colonne);

        /**
         * @brief Arrondit la coordonnée décimale à la coordonnée entière la
         * plus proche.
         *
         * @param x Distance selon l'axe X.
         * @param y Distance selon l'axe Y.
         * @param z Distance selon l'axe Z.
         * @return Coordonnees La coordonnee au valeur arrondi.
         */
        static Coordonnees arrondir(float x, float y, float z);

        /**
         * @brief Crée une coordonnées selon la direction donnée.
         *
         * La coordonnées est adjacente à l'origine (0, 0).
         *
         * @param direction Direction de la case par rapport à l'origine.
         * @return Une coordonnées selon la direction donnée.
         *
         * @throw std::invalid_argument Quand la direction n'est pas supportée.
         */
        static Coordonnees direction(Direction direction);

        /**
         * @brief Crée une coordonnées à l'origine (0, 0).
         */
        Coordonnees();

        /**
         * @brief Crée une coordonnées axiale.
         *
         * @param ligne La ligne (en cases).
         * @param colonne La colonne (en cases).
         */
        Coordonnees(int ligne, int colonne);

        /**
         * @brief Crée une coordonnées cubique.
         *
         * Le point doit appartenir au plan d'équation x + y + z = 0.
         * @param x Distance selon l'axe X.
         * @param y Distance selon l'axe Y.
         * @param z Distance selon l'axe Z.
         *
         * @throw std::invalid_argument Quand les coordonnées ne sont pas valides.
         */
        Coordonnees(int x, int y, int z);

        Coordonnees(const Coordonnees& autre) = default;
        Coordonnees(Coordonnees&& autre) = default;
        Coordonnees& operator=(const Coordonnees& autre) = default;
        Coordonnees& operator=(Coordonnees&& autre) = default;
        ~Coordonnees() = default;

        /**
         * @brief Obtient la colonne en coordonnées axiales.
         *
         * @return La colonne en coordonnées axiales.
         */
        inline int getColonne() const { return m_colonne; }

        /**
         * @brief Obtient la ligne en coordonnées axiales.
         *
         * @return La ligne en coordonnées axiales.
         */
        inline int getLigne() const { return m_ligne; }

        /**
         * @brief Obtient la coordonnées selon l'axe X en coordonnées cubiques.
         *
         * @return La coordonnées selon l'axe X en coordonnées cubiques.
         */
        inline int getX() const { return m_colonne; }

        /**
         * @brief Obtient la coordonnées selon l'axe Y en coordonnées cubiques.
         *
         * @return La coordonnées selon l'axe Y en coordonnées cubiques.
         */
        inline int getY() const { return m_ligne; }

        /**
         * @brief Obtient la coordonnées selon l'axe Z en coordonnées cubiques.
         *
         * @return La coordonnées selon l'axe Z en coordonnées cubiques.
         */
        inline int getZ() const { return -m_colonne - m_ligne; }

        /**
         * @brief Translate la coordonnées dans la direction et sur la distance
         * donnée.
         *
         * @param dir Direction de la translation.
         * @param distance Longueur de la translation.
         * @return La coordonnées translaté dans la direction à la distance donnée.
         */
        Coordonnees translater(Direction dir, int distance = 1) const;

        /**
         * @brief Calcule la longueur jusqu'à l'origine du repère.
         *
         * @return La longueur jusqu'à l'origine du repère.
         */
        int longueur() const;

        /**
         * @brief Calcule la distance jusqu'à la coordonnées donnée.
         *
         * @param autre La coordonnées dont on disire connaitre la distance.
         * @return La distance jusqu'à la coordonnées donnée.
         */
        int distance(const Coordonnees& autre) const;

        /**
         * @brief Calcule l'angle entre deux cases.
         *
         * L'angle est mesuré depuis l'axe vertical ascendant et dans le sens
         * horaire. L'angle est dans ]-M_PI; M_PI].
         *
         * @param autre La case avec laquelle on désire connaitre l'angle.
         * @return L'angle entre la case courrante et celle sélectionnée.
         */
        float angle(const Coordonnees& autre) const;

        /**
         * @brief Donne la direction entre deux cases.
         *
         * @param autre La case avec laquelle on désire connaitre la direction.
         * @return La direction entre la case courrante et celle sélectionnée.
         *
         * @throw std::invalid_argument Quand les deux cases ne sont pas
         * alignées.
         */
        Direction direction(const Coordonnees& autre) const;

        /**
         * @brief Tourne de 60° dans le sens trigonométrique.
         *
         * @param centre Le centre de la rotation.
         * @return La coordonnée tournée de 60° dans le sens trigonométrique.
         */
        Coordonnees tournerTrigonometrique(const Coordonnees& centre) const;

        /**
         * @brief Tourne de 60° dans le sens horaire.
         *
         * @param centre Le centre de la rotation.
         * @return La coordonnée tournée de 60° dans le sens horaire.
         */
        Coordonnees tournerHoraire(const Coordonnees& centre) const;

        /**
         * @brief Tourne d'une direction vers une autre.
         *
         * @param centre Le centre de la rotation.
         * @param cible L'orientation voulue.
         * @param initiale L'orientation initiale.
         * @return La coordonnée tournée jusqu'à la direction ciblée.
         */
        Coordonnees tournerVers(const Coordonnees& centre, Direction cible, Direction initiale = Direction::Nord) const;

        /**
         * @brief Additionne avec la coordonnée.
         *
         * @param autre La coordonnée à additionner.
         * @return Le somme des coordonnées.
         */
        Coordonnees operator+(const Coordonnees& autre) const;

        /**
         * @brief Donne l'opposée.
         *
         * @return L'opposée de la coordonnée.
         */
        Coordonnees operator-() const;

        /**
         * @brief Soustrait la coordonnée.
         *
         * @param autre La coordonnée à soustraire.
         * @return La différence des coordonnées.
         */
        Coordonnees operator-(const Coordonnees& autre) const;

        /**
         * @brief Multiple avec un scalaire.
         *
         * @param scalaire Le scalaire par lequel multiplié.
         * @return La coordonnée multipliée par le scalaire.
         */
        Coordonnees operator*(int scalaire) const;

        /**
         * @brief Test l'égalité avec une coordonnée.
         *
         * @param autre La coordonnée à tester.
         * @return true Si la coordonnée est équivalente.
         */
        bool operator==(const Coordonnees& autre) const;

        /**
         * @brief Test l'inégalité avec une coordonnée.
         *
         * @param autre La coordonnée à tester.
         * @return true Si la coordonnée est équivalente.
         */
        bool operator!=(const Coordonnees& autre) const;

        /**
         * @brief Test la supériorité stricte par rapport à la coordonnée.
         *
         * Une coordonnée est supérieure si sa colonne est la plus grande. En
         * cas d'égalité des colonnes, elle est supérieure si sa colonne est la
         * plus grande.
         *
         * @param autre La coordonnée à tester.
         * @return true Si la coordonnée est plus petite.
         */
        bool operator>(const Coordonnees& autre) const;

        /**
         * @brief Test la supériorité par rapport à la coordonnée.
         *
         * Une coordonnée est supérieure si sa colonne est la plus grande. En
         * cas d'égalité des colonnes, elle est supérieure si sa colonne est la
         * plus grande.
         *
         * @param autre La coordonnée à tester.
         * @return true Si la coordonnée est plus petite.
         */
        bool operator>=(const Coordonnees& autre) const;

        /**
         * @brief Test l'infériorité stricte par rapport à la coordonnée.
         *
         * Une coordonnée est supérieure si sa colonne est la plus grande. En
         * cas d'égalité des colonnes, elle est supérieure si sa colonne est la
         * plus grande.
         *
         * @param autre La coordonnée à tester.
         * @return true Si la coordonnée est plus petite.
         */
        bool operator<(const Coordonnees& autre) const;

        /**
         * @brief Test l'infériorité par rapport à la coordonnée.
         *
         * Une coordonnée est supérieure si sa colonne est la plus grande. En
         * cas d'égalité des colonnes, elle est supérieure si sa colonne est la
         * plus grande.
         *
         * @param autre La coordonnée à tester.
         * @return true Si la coordonnée est plus petite.
         */
        bool operator<=(const Coordonnees& autre) const;

        /**
         * @brief Ecrit la coordonnée axiale.
         *
         * @param os Le flux dans lequel écrire.
         * @param c La coordonnée à écrire.
         * @return Le flux fourni.
         */
        friend std::ostream& operator<<(std::ostream& os, const Coordonnees& c);
    };
}; // namespace hex
#endif // __COORDONNEES_HPP__
