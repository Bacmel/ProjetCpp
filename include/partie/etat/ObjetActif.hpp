#ifndef __OBJETACTIF_HPP__
#define __OBJETACTIF_HPP__

#include "obj/IObjet.hpp"
#include "partie/etat/IEtat.hpp"
#include "per/APersonnage.hpp"

namespace partie::etat
{
    class ObjetActif : public IEtat
    {
    private:
        size_t m_equipe;
        per::APersonnage_S m_personnage;
        obj::IObjet_S m_objet;

    public:
        /**
         * @brief Construit un état ObjetActif.
         *
         * @param equipe L'indice de l'équipe active.
         * @param personnage Le personnage actif.
         * @param objet L'objet sélectionné.
         */
        ObjetActif(size_t equipe, per::APersonnage_S personnage, obj::IObjet_S objet);

        void afficher() const override;

        inline size_t getEquipeCourante() const override { return m_equipe; }

        inline per::APersonnage_SC getPersoSelect() const override { return m_personnage; };

        inline obj::IObjet_SC getObjetSelect() const override { return m_objet; }

        void operation(Partie& partie, const hex::Coordonnees& coordonnees) override;

        void operation(Partie& partie, size_t indiceObjet) override;

        void operation(Partie& partie) override;
    };

} // namespace partie::etat
#endif // __OBJETACTIF_HPP__
