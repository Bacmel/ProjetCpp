#ifndef TASER_HPP
#define TASER_HPP

#include "obj/IObjet.hpp"

namespace obj
{
    class Taser : public IObjet
    {
    protected:
        /** Degat de l'arme. */
        size_t m_degat;

    public:
        Taser();

        bool estUtilisable() const override;

        void utiliser(donjon::IDonjon& donjon, const hex::Coordonnees& origine, const hex::Coordonnees& cible) override;

        virtual void accepter(IObjetVisiteur& visiteur) const override;

        virtual void actualiser() override;

        hex::Masque getPorte() const override;

    };
} // namespace obj

#endif // TASER_HPP
