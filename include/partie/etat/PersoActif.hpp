#ifndef __PERSOACTIF_HPP__
#define __PERSOACTIF_HPP__

#include "hex/Coordonnees.hpp"
#include "obj/IObjet.hpp"
#include "partie/etat/IEtat.hpp"
#include "per/APersonnage.hpp"

namespace partie::etat
{
    class PersoActif : public IEtat
    {
    protected:
        /** @brief Indice de l'equipe en jeu. */
        size_t m_equipe;
        /** @brief Personnage actif. */
        per::APersonnage_S m_personnage;

    public:
        /**
         * @brief Construit un état PersoActif.
         *
         * @param indice L'indice de l'équipe active.
         * @param personnage Le personnage actif.
         */
        PersoActif(size_t indice, per::APersonnage_S personnage);

        /* Constructeurs & operateurs de copie & destructeur */
        PersoActif(const PersoActif& autre) = default;
        PersoActif(PersoActif&& autre) = default;
        PersoActif& operator=(const PersoActif& autre) = default;
        PersoActif& operator=(PersoActif&& autre) = default;
        ~PersoActif() = default;

        /* Méthodes IEtat. */
        std::string enTexte() const override;
        inline size_t getEquipeCourante() const override { return m_equipe; }
        inline per::APersonnage_S getPersoSelect() override { return m_personnage; }
        inline per::APersonnage_SC getPersoSelect() const override { return m_personnage; }
        inline obj::IObjet_S getObjetSelect() override;
        inline obj::IObjet_SC getObjetSelect() const override;
        void operation(Partie& partie, const hex::Coordonnees& coordonnees) override;
        void operation(Partie& partie, size_t indiceObjet) override;
        void operation(Partie& partie) override;
    };
} // namespace partie::etat

#endif //__PERSOACTIF_HPP__
