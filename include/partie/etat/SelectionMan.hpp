#ifndef __SELECTIONMAN_HPP__
#define __SELECTIONMAN_HPP__

#include "hex/Coordonnees.hpp"
#include "obj/IObjet.hpp"
#include "partie/etat/IEtat.hpp"

namespace partie::etat
{
    class SelectionMan : public IEtat
    {
    protected:
        /** indice de L'Equipe en jeu. */
        size_t m_equipe;

    public:
        /**
         * @brief Construit un état SelectionAuto.
         *
         * @param equipe L'indice de l'équipe active.
         */
        SelectionMan(size_t indice);

        /* Constructeurs & operateurs de copie & destructeur */
        SelectionMan(const SelectionMan& autre) = default;
        SelectionMan(SelectionMan&& autre) = default;
        SelectionMan& operator=(const SelectionMan& autre) = default;
        SelectionMan& operator=(SelectionMan&& autre) = default;
        ~SelectionMan() = default;

        /* Méthodes IEtat. */
        std::string enTexte() const override;
        inline size_t getEquipeCourante() const override { return m_equipe; }
        inline per::APersonnage_S getPersoSelect() override;
        inline per::APersonnage_SC getPersoSelect() const override;
        inline obj::IObjet_S getObjetSelect() override;
        inline obj::IObjet_SC getObjetSelect() const override;
        void operation(Partie& partie, const hex::Coordonnees& coordonnees) override;
        void operation(Partie& partie, size_t indiceObjet) override;
        void operation(Partie& partie) override;
    };
} // namespace partie::etat

#endif //__SELECTIONMAN_HPP__
