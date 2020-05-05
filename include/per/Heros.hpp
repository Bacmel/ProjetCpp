#ifndef HEROS_HPP
#define HEROS_HPP

#include <vector>
#include "per/IPersonnage.hpp"
#include "obj/IObjet.hpp"

namespace per
{

    class Heros : public IPersonnage
    {
    protected:
	    /** Santé du Heros et points de vie actuel */
        size_t m_pvMax;
	    size_t m_pv;
	    /** Liste des objets detenue par le Heros */
	    std::vector<obj::IObjet_S> m_sac;

    public:
	    explicit Heros(size_t pvMax) : m_pvMax(pvMax), m_pv(pvMax)
        {
	        this->m_sac = std::vector<obj::IObjet_S>(0);
	    }

	    inline bool estVivant() const
	    {
	        return (bool) this->m_pv;
	    }

        void subitAttaque(size_t degat); 

    	inline size_t getSante() const
	    {
	        return this->m_pv;
	    }

    	inline size_t getSanteMax() const
	    {
	        return this->m_pvMax;
	    }

	    /**
	    * @brief Recupère un objet.
	    *
	    * @param objet l'objet.
	    */
	    inline void addObjet(obj::IObjet_S objet)
	    {
	        this->m_sac.push_back(objet);
	    }

	    /**
	    * @brief Perd un objet de son inventaire.
	    *
	    * @param objet l'objet perdu.
	    */
	    void rmObjet(obj::IObjet_S objet);

        /**
        * @brief Autorise la modification de la santé max
        *
        * @param sante la santé à rajouter (ou à soustraire)
        */
        void addSanteMax(int sante);
    };
}; // namespace per

#endif // HEROS_HPP
