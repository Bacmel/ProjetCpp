#include "partie/strat/JoueurHumain.hpp"
#include "partie/etat/SelectionAuto.hpp"
#include "partie/Partie.hpp"
#include <memory>

namespace partie::strat
{
    JoueurHumain::JoueurHumain() {}

    void JoueurHumain::mettreEnOeuvre(partie::Partie& partie, partie::Equipe&)
    {
        size_t id = partie.getEquipeCourante();
        partie.setEtat(std::make_shared<etat::SelectionAuto>(id));
        partie.demander();
    }
} // namespace partie::strat
