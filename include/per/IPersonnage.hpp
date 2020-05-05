#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include <memory>
#include "hex/Coordonnees.hpp"

namespace per
{

    class APersonnage
    {
    protected:
        /** Nombre de Personnages*/
        static size_t id_suivante = 0;
        
        /** Santé du Personnage et points de vie actuel */
        size_t m_pvMax;
        size_t m_pv;
        
        /** Identifiant Personnage */
        size_t const m_id;
    public:
        APersonnage(size_t pvMax) : m_pvMax(pvMax), m_pv(pvMax), m_id(id_suivante)
        {
            id_suivante++;
        }

        virtual ~APersonnage() {}

        /**
         * @brief Prédicat sur la vie du personnage.
         *
         * @return true Si le joueur est vivant.
         * @return false sinon.
         */
        virtual bool estVivant() const;

       /**
        * @brief Fait subir une attaque.
        *
        * La source n'est pas forcément un joueur jouable par un humain ou
        * l'ordinateur. Les dégats d'environnement sont associés à un joueur
        * qui représente l'environnement.
        *
        * @param degat La quantité de dégats (peut être différents de la santé
        *              retirée).
        */
       virtual void subitAttaque(size_t degat);

       /**
        * @brief Obtient le nombre de points de vie.
        *
        * @return size_t Le nombre de points de vie.
        */
       virtual size_t getSante() const
       {
           return m_pv;
       }

       /**
        * @brief Obtient le nombre maximal de points de vie.
        *
        * @return size_t Le nombre maximal de points de vie.
        */
       virtual size_t getSanteMax() const
       {
           return m_pvMax;
       }

       /**
        * @brief Obtient l'identifiant.
        *
        * @return size_t l'identifiant
        */
       virtual size_t getId() const
       {
           return m_id;
       }

       /**
        * @brief Redefinit le nombre de point de vie.
        *
        * @param pv le nouveau nombre de point de vie.
        */
       virtual void setSante(size_t pv)
       {
          m_pv = pv>=m_pvMax ? m_pvMax : pv;
       }

   };

   using APersonnage_S = std::shared_ptr<APersonnage>;
   using APersonnage_SC = std::shared_ptr<const APersonnage>;

}; // namespace per

#endif
