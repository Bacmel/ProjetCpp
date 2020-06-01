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
    GravityGun::GravityGun() : m_distance(1), m_porte(1), m_aire(0), m_timeMax(3), m_time(0)
    {
        m_porte.remplir(true);
        m_porte(hex::Coordonnees()) = false;
        m_aire.remplir(true);
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
            hex::IIterator_S<hex::Coordonnees> itr = m_aire.iterateur();
            for (hex::Coordonnees coordonnees; itr->aSuite(); coordonnees = itr->suite())
            {
                if (coordonnees == hex::Coordonnees::direction(hex::Direction::Nord))
                {
                    modele.insert(
                        std::pair<hex::Coordonnees, hex::Direction>(coordonnees + relative, hex::Direction::Nord));
                }
                else if (coordonnees == hex::Coordonnees::direction(hex::Direction::NordEst))
                {
                    modele.insert(
                        std::pair<hex::Coordonnees, hex::Direction>(coordonnees + relative, hex::Direction::NordEst));
                }
                else if (coordonnees == hex::Coordonnees::direction(hex::Direction::SudEst))
                {
                    modele.insert(
                        std::pair<hex::Coordonnees, hex::Direction>(coordonnees + relative, hex::Direction::SudEst));
                }
                else if (coordonnees == hex::Coordonnees::direction(hex::Direction::Sud))
                {
                    modele.insert(
                        std::pair<hex::Coordonnees, hex::Direction>(coordonnees + relative, hex::Direction::Sud));
                }
                else if (coordonnees == hex::Coordonnees::direction(hex::Direction::SudOuest))
                {
                    modele.insert(
                        std::pair<hex::Coordonnees, hex::Direction>(coordonnees + relative, hex::Direction::SudOuest));
                }
                else if (coordonnees == hex::Coordonnees::direction(hex::Direction::NordOuest))
                {
                    modele.insert(
                        std::pair<hex::Coordonnees, hex::Direction>(coordonnees + relative, hex::Direction::NordOuest));
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
