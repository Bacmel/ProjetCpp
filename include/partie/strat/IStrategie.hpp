#ifndef __ISTRATEGIE_HPP__
#define __ISTRATEGIE_HPP__

#include <memory>

namespace partie
{
    class Equipe;
    class Partie;
} // namespace partie

namespace partie::strat
{
    class IStrategie
    {
    public:
        virtual ~IStrategie() = default;

        /**
         * @brief Demande à la stratégie de prendre un décision.
         *
         * @param partie La partie pour laquelle on joue.
         * @param equipe L'équipe pour laquelle on joue.
         */
        virtual void mettreEnOeuvre(partie::Partie& partie, partie::Equipe& equipe) = 0;
    };
    using IStrategie_S = std::shared_ptr<IStrategie>;
} // namespace partie::strat
#endif // __ISTRATEGIE_HPP__
