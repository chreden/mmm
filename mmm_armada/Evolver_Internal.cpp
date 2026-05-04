#include "Evolver_Internal.h"
#include "Type_Evolver.h"
#include "Type_EvolverClass.h"
#include "EvolverClass_Internal.h"

namespace mmm
{
    EvolverPtr Evolver::create(types::Entity* entity)
    {
        return EvolverPtr(new Evolver(static_cast<types::Evolver*>(entity)));
    }

    Evolver::Evolver(types::Evolver* evolver)
        : Producer(evolver)
    {

    }

    types::Evolver* Evolver::getEvolver() const
    {
        return static_cast<types::Evolver*>(getEntity());
    }

    float Evolver::getEvolutionProgress() const
    {
        return getEvolver()->m_buildFrac;
    }

    void Evolver::setEvolutionProgress(float value)
    {
        getEvolver()->m_buildFrac = value;
    }

    std::shared_ptr<GameObjectClass> Evolver::getClass() const
    {
        return std::shared_ptr<GameObjectClass>(new EvolverClass(static_cast<types::EvolverClass*>(getEvolver()->m_class)));
    }
}
