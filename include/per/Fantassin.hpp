#ifndef FANTASSIN_HPP
#define FANTASSIN_HPP

#include "pex/IPersonnage.hpp"
#include "hex/ICarte.hpp"
namespace per
{
    class Fantassin : public IPersonnage
    {
    protected :
        /** Santé du Fantassin et points de vie actuel */
        size_t m_pvMax;
        size_t m_pv;
        /** Arme du Fantassin : arme de CàC */
        size_t m_degat;
        ICarte_SC<bool> m_porte;
    public :
        explicit Fantassin();

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
    };
}; // namespace per

#endif // FANTASSIN_HPP

