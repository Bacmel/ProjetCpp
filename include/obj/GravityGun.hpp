#ifndef GRAVITYGUN_HPP
#define GRAVITYGUN_HPP

#include "hex/Masque.hpp"
#include "obj/IObjet.hpp"
#include "utils/Jauge.hpp"

namespace obj
{
    class GravityGun : public IObjet
    {
    protected:
        /* Distance de projection du gravity gun en case*/
        size_t m_distance;
        /* Aire d'effet du gravity gun */
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
        virtual ~GravityGun() {}

        bool estUtilisable() const override;

        void utiliser(donjon::IDonjon& donjon, const hex::Coordonnees& origine, const hex::Coordonnees& cible) override;

        virtual void accepter(IObjetVisiteur& visiteur) const override;

        virtual void actualiser() override;
    };
} // namespace obj
#endif // GRAVITYGUN_HPP
