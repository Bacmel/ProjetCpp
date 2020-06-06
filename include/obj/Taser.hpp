#ifndef __TASER_HPP__
#define __TASER_HPP__

#include "obj/IObjet.hpp"

namespace obj
{
    class Taser : public IObjet
    {
    protected:
        /** Degat de l'arme. */
        size_t m_degat;

    public:
        /**
         * @brief Constructeur par defaut
         */
        Taser();

        /* Constructeurs & operateurs de copie & destructeur */
        Taser(const Taser& autre) = default;
        Taser(Taser&& autre) = default;
        Taser& operator=(const Taser& autre) = default;
        Taser& operator=(Taser&& autre) = default;
        ~Taser() = default;

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

#endif // __TASER_HPP__