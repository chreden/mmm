#pragma once

#include "Producer.h"

namespace mmm
{
    namespace types
    {
        struct Evolver;
    }

    class Evolver : public Producer
    {
    public:
        static EvolverPtr create(types::Entity* entity);
        virtual std::shared_ptr<GameObjectClass> getClass() const;
        float getEvolutionProgress() const;
        void setEvolutionProgress(float value);
    protected:
        explicit Evolver(types::Evolver* evolver);
    private:
        types::Evolver* getEvolver() const;
    };
}
