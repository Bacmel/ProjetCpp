#ifndef __CASEDESSINABLE_HPP__
#define __CASEDESSINABLE_HPP__

#include "donjon/cases/ICaseVisiteur.hpp"
#include "vue/ADessinable.hpp"
#include "vue/ObjetDessinable.hpp"

namespace vue
{
    class CaseDessinable : public vue::ADessinable<donjon::cases::ACase>, public donjon::cases::ICaseVisiteur
    {
    private:
        sf::CircleShape m_hexagone;
        Texture_S m_textureSol;
        Texture_S m_textureTrou;
        ObjetDessinable m_objDessinable;

    public:
        /**
         * @brief Construit une CaseDessinable.
         *
         * @param cote La longueur du côté de l'hexagone (en px).
         */
        CaseDessinable(float cote);

        /**
         * @brief Construit une CaseDessinable.
         *
         * @param cote La longueur du côté de l'hexagone (en px).
         * @param aCase La case à dessiner.
         *
         * @throw std::invalid_argument Quand aCase est null.
         */
        CaseDessinable(float cote, donjon::cases::ACase_S aCase);

        /**
         * @brief Surligne la case.
         *
         * Quand elle est surlignée, ses bordures sont plus épaisses et jaune.
         * Le fond est jaunie.
         */
        void surligner();

        /* Implémentation de ADessinable */
        void setCote(float cote) override;
        void setElement(donjon::cases::ACase_S aCase) override;
        void visiter(const donjon::cases::Sol& sol) override;
        void visiter(const donjon::cases::Trou& trou) override;
        /* Implémentation de Drawable */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        /**
         * @brief Préparer le dessinable pour représenter la case.
         */
        void preparer();
    };
} // namespace vue
#endif // __CASEDESSINABLE_HPP__
