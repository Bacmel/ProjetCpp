#ifndef BOSS_PP
#define BOSS_HPP

#include <memory>
#include <vector>
#include "per/IPersonnage.hpp"
#include "obj/IObjet.hpp"
#include "hex/Coordonnees.hpp"

namespace per
{

    class Boss : public IPersonnage
    {
    protected:
	/** Santé du Boss et points de vie actuel */
        size_t pvMax;
	size_t pv;
	/** Liste des objets detenue par le Boss */
	vector<obj::ConstPtr> sac;
	/** Position du Boss dans le donjon */
	hex::Coordonnees coor;
    public:
	explicit Boss(size_t pvMax, hex::Coordonnees coor, vector<obj::ConstPtr> sac) : pvMax(pvMax), pv(pvMax), coor(coor), sac(sac) {}

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

#endif // BOSS_HPP
