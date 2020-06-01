#include "obj/GravityGun.hpp"
#include <map>
#include "donjon/IDonjon.hpp"
#include "hex/IterateurCarteHexagone.hpp"
#include "obj/IObjetVisiteur.hpp"

namespace obj
{
    /**
     * @brief Constructeur par defaut
     */
    GravityGun::GravityGun() : m_distance(1), m_porte(), m_aire(), m_timeMax(3), m_time(0)
    {
        m_porte = m_porte + hex::Coordonnees::direction(hex::Direction::NordOuest);
        m_porte = m_porte + hex::Coordonnees::direction(hex::Direction::Nord);
        m_porte = m_porte + hex::Coordonnees::direction(hex::Direction::NordEst);
        m_porte = m_porte + hex::Coordonnees::direction(hex::Direction::SudEst);
        m_porte = m_porte + hex::Coordonnees::direction(hex::Direction::Sud);
        m_porte = m_porte + hex::Coordonnees::direction(hex::Direction::SudOuest);
        m_aire = m_aire + hex::Coordonnees();
    }

    /**
     * @brief Constructeur pour la personnalisation
     *
     * Permet une personnalisation totale du gravity gun
     *
     * @param distance La distance de projection
     * @param porte La porte du coup
     * @param aire l'aire d'action du coup
     * @param timeMax le Temps de rechargement
     */
    GravityGun::GravityGun(size_t distance, hex::Masque porte, hex::Masque aire, size_t timeMax) :
        m_distance(distance),
        m_porte(porte),
        m_aire(aire),
        m_timeMax(timeMax),
        m_time(0)
    {
    }

    void GravityGun::utiliser(donjon::IDonjon& donjon, const hex::Coordonnees& origine, const hex::Coordonnees& cible)
    {
        std::map<hex::Coordonnees, hex::Direction> modele;
        hex::Coordonnees relative = cible - origine;
        if (m_porte(relative)) // Check si la cible est valide
        {
            for (auto itr = m_aire.begin(); itr != m_aire.end(); itr++)
            {
                if (*itr == hex::Coordonnees::direction(hex::Direction::Nord))
                {
                    modele.insert(
                        std::pair<hex::Coordonnees, hex::Direction>(*itr + relative, hex::Direction::Nord));
                }
                else if (*itr == hex::Coordonnees::direction(hex::Direction::NordEst))
                {
                    modele.insert(
                        std::pair<hex::Coordonnees, hex::Direction>(*itr + relative, hex::Direction::NordEst));
                }
                else if (*itr == hex::Coordonnees::direction(hex::Direction::SudEst))
                {
                    modele.insert(
                        std::pair<hex::Coordonnees, hex::Direction>(*itr + relative, hex::Direction::SudEst));
                }
                else if (*itr == hex::Coordonnees::direction(hex::Direction::Sud))
                {
                    modele.insert(
                        std::pair<hex::Coordonnees, hex::Direction>(*itr + relative, hex::Direction::Sud));
                }
                else if (*itr == hex::Coordonnees::direction(hex::Direction::SudOuest))
                {
                    modele.insert(
                        std::pair<hex::Coordonnees, hex::Direction>(*itr + relative, hex::Direction::SudOuest));
                }
                else if (*itr == hex::Coordonnees::direction(hex::Direction::NordOuest))
                {
                    modele.insert(
                        std::pair<hex::Coordonnees, hex::Direction>(*itr + relative, hex::Direction::NordOuest));
                }
                else
                {
                } // Autre (?)
            }
            donjon.pousse(modele, m_distance);
        }
    }

    void GravityGun::accepter(IObjetVisiteur& visiteur) const { visiteur.visiter(*this); }

    void GravityGun::actualiser()
    {
        if(m_time!= 0)
        {
            m_time--;
        }
    }

} // namespace obj
