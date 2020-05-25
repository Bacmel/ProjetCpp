#include "per/Boss.hpp"
#include <stdexcept>

namespace per
{
    Boss::Boss(size_t pvMax, hex::Coordonnees coor, std::vector<obj::IObjet_S> sac) :
        APersonnage::APersonnage(pvMax, coor),
        m_sac(sac)
    {
    }

    void Boss::prendre(obj::IObjet_S objet)
    {
        if (objet != nullptr) { m_sac.push_back(objet); }
    }

    obj::IObjet_S Boss::lacher(size_t indice)
    {
        obj::IObjet_S objet(nullptr);
        try
        {
            objet = m_sac.at(indice);
        }
        catch (const std::out_of_range& ex)
        {
            throw std::out_of_range("per::Boss::lacher : Pas d'objet à cette position");
        }
        auto itr = m_sac.begin() + indice;
        m_sac.erase(itr);
        return objet;
    }
} // namespace per
