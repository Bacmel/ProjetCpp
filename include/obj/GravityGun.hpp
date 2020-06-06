#ifndef __GRAVITYGUN_HPP__
#define __GRAVITYGUN_HPP__

#include "hex/Masque.hpp"
#include "obj/IObjet.hpp"
#include "utils/Jauge.hpp"

namespace obj
{
    class GravityGun : public IObjet
    {
    private:
        /** @brief Distance de projection du gravity gun en case*/
        size_t m_distance;
        /** @brief Aire d'effet du gravity gun */
        hex::Masque m_aire;
        /** @brief La charge de l'objet. */
        utils::Jauge m_charge;

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
         * @param aire L'aire d'action du coup quand le personnage est face au
         * Nord.
         * @param timeMax le Temps de rechargement
         */
        GravityGun(size_t distance, hex::Masque aire, size_t timeMax);

        GravityGun(const GravityGun& autre) = default;
        GravityGun(GravityGun&& autre) = default;
        GravityGun& operator=(const GravityGun& autre) = default;
        GravityGun& operator=(GravityGun&& autre) = default;
        ~GravityGun() = default;

        /* Méthodes IObjet. */
        bool estUtilisable() const override;
        void utiliser(donjon::IDonjon& donjon, const hex::Coordonnees& origine, const hex::Coordonnees& cible) override;
        virtual void accepter(IObjetVisiteur& visiteur) const override;

        /* Méthode IAtualisable. */
        virtual void actualiser() override;

        /* Méthodes IPorte. */
        hex::Masque getPorte() const override;
        hex::Masque getZoneDegat(const hex::Coordonnees& cible) const override;
    };
} // namespace obj
#endif // __GRAVITYGUN_HPP__
