#ifndef __ENTITE_H__
#define __ENTITE_H__

#include <ostream>
#include "hex/Coordonnees.hpp"
#include "per/APersonnage.hpp"

namespace donjon
{
    class Entite
    {
        static size_t idSuivante;

        const size_t m_id;
        hex::Coordonnees m_position;
        per::APersonnage_S m_personnage;

    public:
        explicit Entite(per::APersonnage_S personnage);

        size_t getId() const { return m_id; }

        const hex::Coordonnees& getPosition() const { return m_position; }
        void setPosition(const hex::Coordonnees& position) { m_position = position; }

        per::APersonnage_SC getPersonnage() const { return m_personnage; }
        per::APersonnage_S getPersonnage() { return m_personnage; }

        bool operator<(const Entite& autre) const;
        bool operator>(const Entite& autre) const;

        Entite(const Entite& autre) = default;
        Entite(Entite&& autre) = default;
        Entite& operator=(const Entite& autre) = default;
        Entite& operator=(Entite&& autre) = default;
        ~Entite() = default;
    };

    std::ostream& operator<<(std::ostream& os, const Entite& entite);
} // namespace donjon
#endif // __ENTITE_H__
