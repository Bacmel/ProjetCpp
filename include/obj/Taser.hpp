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

        void utiliser(donjon::IDonjon& donjon, const hex::Coordonnees& origine, const hex::Coordonnees& cible) override;
        virtual void accepter(IObjetVisiteur& visiteur) const override;

    };
} // namespace obj

#endif // TASER_HPP