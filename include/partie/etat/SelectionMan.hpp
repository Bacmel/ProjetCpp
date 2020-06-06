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
        size_t m_indiceEquipe;

    public:
        SelectionMan(size_t indice);

        inline void afficher() const override;

        inline size_t getEquipeCourante() const override { return m_indiceEquipe; }

        inline per::APersonnage_SC getPersoSelect() const override;

        inline obj::IObjet_SC getObjetSelect() const override;

        void operation(Partie& partie, const hex::Coordonnees& coordonnees) override;

        void operation(Partie& partie, size_t indiceObjet) override;

        void operation(Partie& partie) override;

    };
} // namespace partie::etat

#endif //__SELECTIONMAN_HPP__
