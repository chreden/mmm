#pragma once

#include <memory>

namespace mmm
{

#ifndef _MMM_DEFINESHAREDPTR
#define _MMM_DEFINESHAREDPTR(x) class x; typedef std::shared_ptr<x> x##Ptr;
#endif

    _MMM_DEFINESHAREDPTR(GameObject);
    _MMM_DEFINESHAREDPTR(Craft);
    _MMM_DEFINESHAREDPTR(IonStorm);
    _MMM_DEFINESHAREDPTR(BlackHole);
    _MMM_DEFINESHAREDPTR(AreaEffectObject);
    _MMM_DEFINESHAREDPTR(UtritiumBall);
    _MMM_DEFINESHAREDPTR(BackgroundPlanet);
    _MMM_DEFINESHAREDPTR(BackgroundObject);
    _MMM_DEFINESHAREDPTR(LatinumNebula);
    _MMM_DEFINESHAREDPTR(TerrainObject);
    _MMM_DEFINESHAREDPTR(Planet);
    _MMM_DEFINESHAREDPTR(TradingStation);
    _MMM_DEFINESHAREDPTR(MiningStation);
    _MMM_DEFINESHAREDPTR(Starbase);
    _MMM_DEFINESHAREDPTR(Evolver);
    _MMM_DEFINESHAREDPTR(ConstructionRig);
    _MMM_DEFINESHAREDPTR(ResearchStation);
    _MMM_DEFINESHAREDPTR(CraftSystem);
    _MMM_DEFINESHAREDPTR(Producer);
    _MMM_DEFINESHAREDPTR(RepairShip);
    _MMM_DEFINESHAREDPTR(Colony);
    _MMM_DEFINESHAREDPTR(ResearchPod);
    _MMM_DEFINESHAREDPTR(CargoShip);
    _MMM_DEFINESHAREDPTR(PhotonTorpedo);
    _MMM_DEFINESHAREDPTR(Missile);
    _MMM_DEFINESHAREDPTR(AntimatterMine);
    _MMM_DEFINESHAREDPTR(GravityMine);
    _MMM_DEFINESHAREDPTR(Mine);
    _MMM_DEFINESHAREDPTR(Bullet);
    _MMM_DEFINESHAREDPTR(PulsePhaser);
    _MMM_DEFINESHAREDPTR(AsteroidField);
    _MMM_DEFINESHAREDPTR(Scavenger);
    _MMM_DEFINESHAREDPTR(PlanetMiningBase);
    _MMM_DEFINESHAREDPTR(SensorArray);
    _MMM_DEFINESHAREDPTR(OrdnanceDamage);

    _MMM_DEFINESHAREDPTR(CraftClass);
    _MMM_DEFINESHAREDPTR(ColonyClass);
    _MMM_DEFINESHAREDPTR(RepairShipClass);
    _MMM_DEFINESHAREDPTR(ProducerClass);

    _MMM_DEFINESHAREDPTR(Queue);
    _MMM_DEFINESHAREDPTR(SplineQueue);

    _MMM_DEFINESHAREDPTR(BuildQueue);

    _MMM_DEFINESHAREDPTR(TimerHook);

    _MMM_DEFINESHAREDPTR(EntityFinderFilter);

    class NoCopy
    {
    protected:
        NoCopy() { };
    private:
        NoCopy( const NoCopy& ){ };
        NoCopy& operator=( const NoCopy& ) { };
    };
}
