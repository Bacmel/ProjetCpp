#ifndef HEROS_HPP
#define HEROS_HPP

#include <memory>
#include <vector>
#include "per/IPersonnage.hpp"
#include "obj/IObjet.hpp"
#include "hex/Coordonnees.hpp"

namespace per
{

    class Heros : public IPersonnage
    {
    protected:
	/** Santé du Heros et points de vie actuel */
        size_t pvMax;
	size_t pv;
	/** Liste des objets detenue par le Heros */
	vector<obj::Ptr> sac;
	/** Position du Heros dans le donjon */
	hex::Coordonnees coor;
    public:
	explicit Heros(size_t pvMax, hex::Coordonnees coor) : pvMax(pvMax), pv(pvMax), coor(coor)
	{
	    this->sac = vector<obj::Ptr>(0);
	}

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

	/**
	 * @brief Recupère un objet.
	 *
	 * @param objet l'objet.
	 */
	void addObjet(obj::Ptr objet)
	{
	    this->sac.push_back(objet);
	}

	/**
	 * @brief Perd un objet de son inventaire.
	 *
	 * @param objet l'objet perdu.
	 */
	void rmObjet(obj::Ptr objet)
	{
	    auto it = std::find(this->sac.begin(), this->sac.end(), objet);
            if(it != this->sac.end())
	    {
	        this->sac.erase(it);
	    }
    	}

	/**
	 * @brief Autorise l'objet à interagir avec le Heros.
	 *
	 * Certains item nécessite d'avoir accès aux attributs du Heros.
	 *
	 * @param heros le Heros
	 */
	friend void obj::IObjet::interaction(Heros heros);
    };
}; // namespace per

#endif // HEROS_HPP
