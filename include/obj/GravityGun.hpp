#ifndef GRAVITYGUN_HPP
#define GRAVITYGUN_HPP

#include "hex/Masque.hpp"
#include "obj/IObjet.hpp"

namespace obj
{
    class GravityGun : public IObjet
    {
    protected:
        /* Distance de projection du gravity gun en case*/
        size_t m_distance;
        /* Porte du gravity gun */
        hex::Masque m_porte;
        /* Aire d'effet du gravity gun */
        hex::Masque m_aire;
        /* Temps de rechargement apres utilisation et temps restant*/
        size_t m_timeMax;
        size_t m_time;

    public:
        /**
         * @brief Constructeur par defaut
         */
        GravityGun();

        /**
         * @brief Constructeur pour la personnalisation
         *
         * Permet une personnalisation totale du gravity gun
         *
         * @param distance La distance de projection
         * @param porte La porte du coup
         * @param aire l'aire d'action du coup
         * @param timeMax le Temps de rechargement
         */
        GravityGun(size_t distance, hex::Masque porte, hex::Masque aire, size_t timeMax);

        void utiliser(donjon::IDonjon& donjon, const hex::Coordonnees& origine, const hex::Coordonnees& cible);

        virtual void accepter(IObjetVisiteur& visiteur) const override;

        virtual void actualiser();
    };
} // namespace obj
#endif // GRAVITYGUN_HPP
