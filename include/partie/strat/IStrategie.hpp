#ifndef __ISTRATEGIE_H__
#define __ISTRATEGIE_H__

#include "partie/Partie.hpp"
#include <memory>

namespace partie
{
    class Equipe;
}

namespace partie::strat
{
    class IStrategie
    {
    public:
        virtual ~IStrategie() {}

        virtual void mettreEnOeuvre(partie::Partie& partie, partie::Equipe& equipe) = 0;
    };

    using IStrategie_S = std::shared_ptr<IStrategie>;
    using IStrategie_U = std::unique_ptr<IStrategie>;
}
#endif // __ISTRATEGIE_H__
