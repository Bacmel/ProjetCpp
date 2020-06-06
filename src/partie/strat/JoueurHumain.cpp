#include "partie/strat/JoueurHumain.hpp"
#include "partie/etat/Selection.hpp"
#include "partie/Partie.hpp"
#include <memory>

namespace partie::strat
{
    JoueurHumain::JoueurHumain() {}

    void JoueurHumain::mettreEnOeuvre(partie::Partie& partie, partie::Equipe&)
    {
        size_t id = partie.getEquipeCourante();
        partie.setEtat(std::make_shared<etat::Selection>(id));
        partie.demande();
    }
} // namespace partie::strat