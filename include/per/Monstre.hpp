#ifndef MONSTRE_HPP
#define MONSTRE_HPP

#include <memory>
#include <vector>
#include "per/IPersonnage.hpp"
#include "obj/IObjet.hpp"
#include "hex/Coordonnees.hpp"

namespace per
{

    class Monstre : public IPersonnage
    {
    protected:
	/** Santé du Montre et points de vie actuel */
        size_t pvMax;
	size_t pv;
	/** Arme du monstre */
	obj::ConstPtr arme;
	/** Position du Montre dans le donjon */
	hex::Coordonnee coor;
    public:
	explicit Monstre(size_t pvMax, hex::Coordonnees coor, obj::ConstPtr arme) : pvMax(pvMax), pv(pvMax), coor(coor), arme(arme) {}

	/** Fonctions de l'Interface */
	bool estVivant() const
	{
	    return (bool) this->pv;
	}

        void subitAttaque(IPersonnage& source, size_t degat)
	{
	    if(degat>this->pv)
	    {
	        this->pv = 0;
	    }
	    else
	    {
		this->pv-=degat;
	    }
	}

	size_t getSante() const
	{
	    return this->pv;
	}

	size_t getSanteMax() const
	{
	    return this->pvMax;
	}

    };
}; // namespace per

#endif // MONSTRE_HPP
