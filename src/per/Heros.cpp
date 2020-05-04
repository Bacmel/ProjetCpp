#include "per/Heros.hpp"
#include <algorithm>
#include <cmath>

namespace per
{
    void Heros::subitAttaque(size_t degat)
    {
	    if(degat>this->m_pv)
	    {
	        this->m_pv = 0;
	    }
	    else
	    {
	     	this->m_pv-=degat;
	    }
	}
    
    void Heros::rmObjet(obj::IObjet_S objet)
    {
        this->m_sac.erase(std::remove(this->m_sac.begin(), this->m_sac.end(), objet), this->m_sac.end());
    }
    
    void Heros::addSanteMax(int sante)
    {
        if(sante<0 and this->m_pvMax<=abs(sante)) // Degats
        {
            this->m_pvMax=0;
            this->m_pv=0;
        }
        else
        {
            this->m_pvMax+=sante;
            if(sante<0 and this->m_pv<=abs(sante)) //Degats
            {
                this->m_pv = 0;
            }
            else
            {
                this->m_pv+=sante;
            }
        }
    }
}; //namespace per
