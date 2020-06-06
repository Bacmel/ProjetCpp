#ifndef __SELECTIONAUTO_HPP__
#define __SELECTIONAUTO_HPP__

#include "partie/etat/IEtat.hpp"

namespace partie::etat
{
    class SelectionAuto: public IEtat
    {
    private:
        /** @brief L'indice de l'équipe active. */
        size_t m_equipe;

    public:
        /**
         * @brief Construit un état SelectionAuto.
         *
         * @param equipe L'indice de l'équipe active.
         */
        explicit SelectionAuto(size_t equipe);

        void afficher() const override;

        size_t getEquipeCourante() const override { return m_equipe; }

        per::APersonnage_SC getPersoSelect() const override;

        obj::IObjet_SC getObjetSelect() const override;

        void operation(Partie& partie, const hex::Coordonnees& coordonnees) override;

        void operation(Partie& partie, size_t indiceObjet) override;

        void operation(Partie& partie) override;
    };
} // namespace partie::etat
#endif // __SELECTIONAUTO_HPP__
