#include "per/Heros.hpp"

namespace per
{
    void Heros::subitAttaque(IPersonnage& source, size_t degat)
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
    
    void Heros::rmObjet(IObjet_S objet)
    {
        auto it = std::find(this->m_sac.begin(), this->m_sac.end(), objet);
        if(it != this->m_sac.end())
        {
            this->m_sac.erase(it);
        }
    }
    
    void Heros::addSanteMax(int sante)
    {
        if(this->m_pvMax+sante<0)
        {
            this->m_pvMax=0;
            this->m_pv=0;
        }
        else
        {
            this->m_pvMax+=sante;
            if(this->m_pv+sante<0)
            {
                this->m_pv = 0;
            }
            else
            {
                this->m_pv+=sante;
            }
        }
    }
}; //namespace
