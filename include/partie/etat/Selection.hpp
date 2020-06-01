#ifndef __SELECTION_H__
#define __SELECTION_H__

#include "partie/etat/IEtat.hpp"

namespace partie::etat
{
    class Selection: public IEtat
    {
    private:
        size_t m_equipe;

    public:
        explicit Selection(size_t equipe);
        ~Selection() {}

        void afficher() const override;

        size_t getEquipeCourante() const override { return m_equipe; }

        per::APersonnage_SC getPersoSelect() const override;

        obj::IObjet_SC getObjetSelect() const override;

        void operation(Partie& partie, const hex::Coordonnees& coordonnees) override;

        void operation(Partie& partie, size_t indiceObjet) override;
    };
} // namespace partie::etat
#endif // __SELECTION_H__
