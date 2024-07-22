#pragma once

#include "FileReader.h"
#include "Types.h"

#define ccon __stdcall

typedef unsigned char (ccon *PFUNC)();

#define _MMM_FLEETOPS_GRC_FIX

namespace mmm
{
	//This is what gets passed in to the dll from Armada 2.
	struct ScriptInterface
	{
		virtual hot_int* ScriptCreate_hot_int(const char *) = 0;
		virtual void ScriptDestroy_hot_int(class hot_int *) = 0;
		virtual void ScriptCreate_dirty_int(char *) = 0;
		virtual void ScriptDestroy_dirty_int(class dirty_int *) = 0;
		virtual void ScriptCreate_timer_int(char *) = 0;
		virtual void ScriptDestroy_timer_int(class timer_int *) = 0;
		virtual void ScriptCreate_hot_float(char *) = 0;
		virtual void ScriptDestroy_hot_float(class hot_float *) = 0;
			virtual int* ScriptGet_WORLD(void) = 0;
		virtual void ScriptGet_ALWAYS_EVALUATE(void) = 0;
			virtual hot_int* ScriptGet_isCineractiveCancel() = 0;
			virtual hot_int* ScriptGet_isCineractiveDone() = 0;
		virtual void ScriptGet_moons_team_1(void) = 0;
		virtual void ScriptGet_moons_team_2(void) = 0;
		virtual void ScriptGet_moons_team_3(void) = 0;
		virtual void ScriptGet_moons_team_4(void) = 0;
		virtual void ScriptGet_moons_team_5(void) = 0;
		virtual void ScriptGet_moons_team_6(void) = 0;
		virtual void ScriptGet_moons_team_7(void) = 0;
		virtual void ScriptGet_moons_team_8(void) = 0;
		virtual void ScriptGet_strength_team_1(void) = 0;
		virtual void ScriptGet_strength_team_2(void) = 0;
		virtual void ScriptGet_strength_team_3(void) = 0;
		virtual void ScriptGet_strength_team_4(void) = 0;
		virtual void ScriptGet_strength_team_5(void) = 0;
		virtual void ScriptGet_strength_team_6(void) = 0;
		virtual void ScriptGet_strength_team_7(void) = 0;
		virtual void ScriptGet_strength_team_8(void) = 0;
		virtual void ScriptGet_tried_warp_team_1(void) = 0;
		virtual void ScriptGet_tried_warp_team_2(void) = 0;
		virtual void ScriptGet_tried_warp_team_3(void) = 0;
		virtual void ScriptGet_tried_warp_team_4(void) = 0;
		virtual void ScriptGet_tried_warp_team_5(void) = 0;
		virtual void ScriptGet_tried_warp_team_6(void) = 0;
		virtual void ScriptGet_tried_warp_team_7(void) = 0;
		virtual void ScriptGet_tried_warp_team_8(void) = 0;
				
			//Get the time that elapsed since the start of the mission.
			virtual float GetTime( ) = 0;
			//Determines if the specified team is an AI player
			virtual bool IsAITeam( int teamNumber ) = 0;

		virtual void IsEnabled(int) = 0;
		virtual void ResetStrategyCycle(void) = 0;
				
			//Returns true if the specified craft is at red alert
			virtual bool IsRedAlert( int craftId ) = 0;
			//Returns true if the specified craft is at yellow alert
			virtual bool IsYellowAlert( int craftId ) = 0;
			//Returns true if the specified craft is at green alert
			virtual bool IsGreenAlert( int craftId ) = 0;

		virtual void HideObject(int, unsigned char) = 0;
				
			virtual bool IsOdf(int, char *) = 0;

		virtual void IsVisibleToTeam(int, int) = 0;
			//Clear the shroud on the map for the player
			virtual void ClearShroud(void) = 0;
			//Clear the fog on the map for the player
			virtual void ClearFog(void) = 0;

		virtual void GetRealTeam(int) = 0;
		virtual void GetPerceivedTeam(int) = 0;
		virtual void SetWormholeTeam(int, int) = 0;
		virtual void StuffIntoWormhole(int, int) = 0;
			virtual void EnableWormholeTravel(int teamId, unsigned char enabled) = 0;
		virtual void SetWormholeDeleteOnTransport(int, unsigned char) = 0;
		virtual void SetWormholeExpireOnClose(int, unsigned char) = 0;
		virtual void GetAllyShipAttacks(int, int) = 0;
		virtual void GetAllyStationAttacks(int, int) = 0;
		virtual void IsRace(int, char *) = 0;
		virtual void CountUnits(int, char *) = 0;
		virtual void AllStationsDestroyed(int) = 0;

			//Get the number of stations that a team has.
			virtual int CountStations(int) = 0;

		virtual void AllCapitalShipsDestroyed(int) = 0;
				
		virtual void CountCapitalShips(int) = 0;

		virtual void CountVisibleUnits(int, int, unsigned char, char *) = 0;
		virtual void CountUnitsNearObject(int, float, int, char *) = 0;
		virtual void CountUnitsNearPoint(char *, float, int, char *, int) = 0;
		virtual void CountVisibleUnitsNearPoint(int, char *, float, int, unsigned char, char *, int) = 0;
		virtual void CountVisibleUnitsNearObject(int, float, int, unsigned char, char *) = 0;
		virtual void GetNearestObjectNearPosition(const Vector3 &, float, int, char *, int, unsigned char, int) = 0;
		virtual void GetNearestObjectNearMe(int, float, int, char *, int, unsigned char) = 0;
		virtual void GetNearestObjectNearPath(char *, float, int, char *, int, unsigned char) = 0;
		virtual void CountUnitsInRectangle(char *, int, char *, int, int) = 0;
		virtual void CountUnitsInRectangle2(char *, int, char *, int, int) = 0;
		virtual void GetDistance(int &, char *, int) = 0;
		virtual void GetDistance(int &, int &) = 0;
		virtual void GetShieldPercent(int) = 0;
		virtual void GetRealShieldPercent(int) = 0;
		virtual void Exists(int) = 0;
		virtual void DoesNotExist(int) = 0;
			virtual unsigned char IsAlive(int) = 0;
				
			virtual bool IsExploding( int craftId ) = 0;

		virtual void IsDerelict(int) = 0;
		virtual void IsCompromised(int, int) = 0;
			virtual float GetCrew(int) = 0;
		virtual void GetPlanetCivPop(int) = 0;
		virtual void SetPlanetCivPop(int, int) = 0;
		virtual void GetSpecialEnergy(int) = 0;
		virtual void GetDilithiumOnFreighter(int) = 0;
		virtual void IsThereARomulanSpyOnShip(int) = 0;
		virtual void GetTranswarpExitWormhole(int) = 0;
		virtual void EnginesActive(int) = 0;
		virtual void SensorsActive(int) = 0;
		virtual void ShieldGeneratorActive(int) = 0;
		virtual void LifeSupportActive(int) = 0;
		virtual void WeaponsActive(int) = 0;
		virtual void EnginesDisabled(int) = 0;
		virtual void SensorsDisabled(int) = 0;
		virtual void ShieldGeneratorDisabled(int) = 0;
		virtual void LifeSupportDisabled(int) = 0;
		virtual void WeaponsDisabled(int) = 0;
		virtual void EnginesDestroyed(int) = 0;
		virtual void SensorsDestroyed(int) = 0;
		virtual void ShieldGeneratorDestroyed(int) = 0;
		virtual void LifeSupportDestroyed(int) = 0;
		virtual void WeaponsDestroyed(int) = 0;
			virtual int GetFirstCraft(void) = 0;
			virtual int GetNextCraft(void) = 0;
		virtual void GetLocationOfFlag(int) = 0;
		virtual void GetRealTeamOfFlag(int) = 0;
		virtual void GetPercievedTeamOfFlag(int) = 0;
		virtual void IsRaceOfFlag(int, char *) = 0;
		virtual void IsUnconfirmedAlly(int, int) = 0;
		virtual void IsUnconfirmedNeutral(int, int) = 0;
		virtual void IsUnconfirmedEnemy(int, int) = 0;
		virtual void IsConfirmedAlly(int, int) = 0;
		virtual void IsConfirmedNeutral(int, int) = 0;
		virtual void IsConfirmedEnemy(int, int) = 0;
				
			//Loads a specified AIP file for the given team
			virtual void AI_Team_Load_AIP(int teamNumber, char * aipName ) = 0;
			//Sets whether the AI should control the specified team.
			virtual void SetIsAITeam(const int & teamNumber, const bool & isAi) = 0;
			//Enable AI for the specified team
			virtual void EnableTeam( int teamNumber ) = 0;
			//I assume this turns off the AI for this team number
			virtual void DisableTeam( int teamNumber ) = 0;

		virtual void EnableAllAITeams(void) = 0;
		virtual void DisableAllAITeams(void) = 0;

		virtual void SetSpecialForcesFlag(int, unsigned char) = 0;
		virtual void RecruitSpecialForces(int, int &) = 0;
		virtual void RecruitSpecialForces(char *, int, int &) = 0;
			
			//Set the specified ship to red alert
			virtual void SetRedAlert( int craftId ) = 0;
			//Set the specified ship to yellow alert
			virtual void SetYellowAlert( int craftId ) = 0;
			//Set the specified ship to green alert.
			virtual void SetGreenAlert( int craftId ) = 0;

		virtual void SetPathType(char *, int PathType) = 0;

			virtual void GetRepair(int) = 0;

		virtual void Scout(int) = 0;
		virtual void SearchAndDestroy(int) = 0;
		virtual void InQueue(int) = 0;

			virtual void UnderAttack(int, float) = 0;

		virtual void InAttackMode(int) = 0;
		virtual void OutOfSpecialAttackMode(int) = 0;
		virtual void InStopMode(int) = 0;
		virtual void CommandAllShips( AiCommand, int, const char *, unsigned char, unsigned char) = 0;
			
					
			//Now, im unsure what to do with this one.
			virtual void SetCommandWhatWhoParamVO(int craftId, AiCommand command, int target, long unknown, bool playVoice ) = 0;
			//Give the specified ship a command with another craft as the target.
			//Optionally plays the voiceover.
			virtual void SetCommandWhatWhoVO( int craftId, AiCommand command, int target, bool playVoice ) = 0;
			//Give the specified ship a command that takes a string parameter
			//Used for building things. Optionally play a voiceover file.
			virtual void SetCommandWhatWhoWhereVO( int craftId, AiCommand command, char* param, Vector3 pos, bool playVoice ) = 0;
				
			virtual void SetCommandMoveAutonomyLow(int) = 0;
				
			//Get the current order for this craft
			virtual int GetCurrentCommand( int craftId ) = 0;

		virtual void IsCargoShipReadyToLoad(int) = 0;
		virtual void IsCargoShipFullAndReadyToSend(int) = 0;
		virtual void StopAllShips(int, const char *, unsigned char, unsigned char) = 0;
		virtual void Mine(int, int) = 0;
		virtual void Attack(int, Vector3) = 0;
		virtual void Attack(int, int, int) = 0;
		virtual void Colonize(int, int) = 0;
		virtual void Special_Attack(int, Vector3, const char *) = 0;
		virtual void Special_Attack(int, const char *) = 0;
		virtual void Special_Attack(int, int, const char *) = 0;
		virtual void SetSpecialWeaponAttackInterval(int, float) = 0;
		virtual void AllowMultipleSpecialWeaponFire(int, unsigned char) = 0;
		virtual void AI_Attack(int, Vector3) = 0;
		virtual void AI_Attack(int) = 0;
		virtual void AI_Attack(int, int) = 0;
		virtual void GetMainEnemyBaseLocation(int) = 0;
		virtual void AttackMainEnemyBase(int, unsigned char) = 0;
				
			virtual void Cloak(int) = 0;

			virtual void ImmediateCloak(int) = 0;

			virtual void Decloak(int) = 0;

		virtual void Goto(int, int, unsigned char, int) = 0;
		virtual void Goto(int, char *, unsigned char, int) = 0;
		virtual void Stop(int, int) = 0;
		virtual void Patrol(int, char *) = 0;
		virtual void Build(int, char *) = 0;
				
			//Add a billboard effect to the specified craft. Dont know any effects yet.
			virtual void AddBillboardEffect( int craftId, char* name ) = 0;
			//Add the transporter effect to the specified craft
			virtual void AddTransporterEffect( int craftId ) = 0;
			//Remove the billboard effect on the specifid craft (includes transporter)
			virtual void RemoveBillboardEffect( int craftId ) = 0;

		virtual void PauseSimulation(void) = 0;
		virtual void UnpauseSimulation(void) = 0;

		virtual void GridVisible( bool visible ) = 0;

		virtual void Starfield_Load_Background_Geometry(char *) = 0;
			//Center the camera on a path.
			virtual void CenterCamera( const char* pathName, int index ) = 0;
			//Center the camera on the specified position
			virtual void CenterCamera( Vector3 position ) = 0;
			//Center the camera on a craft 
			virtual void CenterCamera( int craftId ) = 0;
			//Set the zoom level of the camera. 0 is fully zoomed in and 1 is fully zoomed out.
			virtual void SetCameraZoom(float percentage) = 0;

		virtual void PlayCinematicMovie(class script *, char *, int, unsigned char) = 0;
		virtual void StopMovie(void) = 0;
		virtual void IsMoviePlaying(void) = 0;
		virtual void FindGameEvent(const char *) = 0;
		virtual void TriggerGameEvent(int, int) = 0;

			virtual void MinimapMessage(int, int, float) = 0;

			//Unknown
			//Radius
			//Grow Rate
			//Unknown
			virtual void MinimapMessage(char *, int, float, int) = 0;

			virtual int ShowTitle(int x, int y, const char * text, unsigned char unk) = 0;
			virtual void RemoveTitle(int id, unsigned char unk) = 0;
				
			//Player, color, text, , as a guess.
			//??,  ???, Text, isFade
			virtual int ShowSubtitle(int x, int y, const char * text, unsigned char unk) = 0;
			virtual void RemoveSubtitle(int id, unsigned char unk) = 0;

		virtual void GetHandle(char *) = 0;
				
			virtual bool IsValid(int) = 0;

			virtual Vector3* GetLocation(char *, int) = 0;
				
			virtual Vector3* GetLocation(int) = 0;

		virtual void GetAttackLocation(int, int) = 0;
		virtual void BuildObject(char *, int, char *, int) = 0;
		virtual void BuildObject(char *, int, int, float, float, float) = 0;
				
			virtual int ReplaceObject(int, char *) = 0;
		virtual void RemoveObject(int) = 0;
		virtual void RemoveAllObjects(void) = 0;
		virtual void RemoveAllCraft(unsigned char, int) = 0;
		virtual void SetRealTeam(int, int) = 0;
		virtual void SetPerceivedTeam(int, int) = 0;
		virtual void SetRace(int, const char *) = 0;
			virtual int GetRace(int) = 0;
		virtual void GetOriginalRace(int) = 0;
		virtual void LoadCargoShip(int, int) = 0;
		virtual void SetPosition(int, char *, int) = 0;
		virtual void SetPosition(int, char *) = 0;
		virtual void SetVelocity(int, const Vector3 &) = 0;
				
			//Set the angular velocity of the specified craft (x, y, z)
			virtual void SetAngularVelocity( int craftId, const Vector3 & angularVelocity ) = 0;

		virtual void PointAt(int, int) = 0;
		virtual void PointAt(int, char *) = 0;
		virtual void ObstacleAvoidance(unsigned char) = 0;
		virtual void PathPlanning(unsigned char) = 0;
		virtual void CollisionPrevention(unsigned char) = 0;
				
			virtual float GetCombatSpeed(int) = 0;

			virtual void SetCombatSpeed(int, float) = 0;

			//Get how fast the ship will move under impulse
			virtual float GetImpulseSpeed( int craftId ) = 0;
			//Set how fast the ship will move under impulse.
			virtual void SetImpulseSpeed( int craftId, float speed ) = 0;
			//Reset the impulse speed of the ship
			virtual void ResetImpulseSpeed( int craftId ) = 0;

			virtual void AllowWarp(int) = 0;

			virtual void SetShieldPercent(int, float) = 0;
			virtual void SetMaxShields(int, float) = 0;

		virtual void SetCrew(int, float) = 0;
		virtual void SetSpecialEnergy(int, float) = 0;
		virtual void AllowAsTarget(int, int, unsigned char) = 0;
		virtual void SetForceOntoMap(int, unsigned char) = 0;
		virtual void DisableEngines(int, unsigned char) = 0;
		virtual void DisableSensors(int, unsigned char) = 0;
		virtual void DisableShieldGenerator(int, unsigned char) = 0;
		virtual void DisableLifeSupport(int, unsigned char) = 0;
		virtual void DisableWeapons(int, unsigned char) = 0;
		virtual void DestroyCritical(int) = 0;
		virtual void DamageEngines(int, float) = 0;
		virtual void DamageSensors(int, float) = 0;
		virtual void DamageShieldGenerator(int, float) = 0;
		virtual void DamageLifeSupport(int, float) = 0;
		virtual void DamageWeapons(int, float) = 0;
				
			//Explodes the ship with the specified ID.
			virtual void ExplodeNow( int craftId ) = 0;

		virtual void SetCurrentHealth(int, float) = 0;
			virtual float GetCurrentHealth(int) = 0;
			virtual float GetMaxHealth(int) = 0;
			
				
		virtual void CraftCanRepair( int craftHandle, bool canRepair ) = 0;
		virtual void CraftCanRecrew(int, unsigned char) = 0;
			
			//Set if the specified craft is invincible. Will then have minimum
			//of 10 health, and will be recrewed atuomatically.
			virtual void CraftCannotDie( int craftHandle, bool cantDie ) = 0;
			//Can be used to allow an invincible craft to become derelict
			virtual void ButItCanBeDerelicted( int craftHandle, bool canBeDerelict ) = 0;

		virtual void GetNearestStarbase(int, int) = 0;
		virtual void GetNearestShipyard(int, int, unsigned char) = 0;
		virtual int GetNearestRepairFacility(int, int) = 0;
		virtual void GetNearestObject(int) = 0;
		virtual void GetNearestTranswarpGate(int) = 0;
		virtual void GetNearestVehicle(char *, int) = 0;
		virtual void GetNearestVehicle(int) = 0;
		virtual void GetNearestEnemy(int, float) = 0;
		virtual void LinkWormholes(int, int) = 0;
		virtual void CreateSpecialFlag(int, char *) = 0;
		virtual void RestrictSpecialFlag(int, /*SpecialFlag::Restriction*/int, int) = 0;
		virtual void RestrictSpecialFlag(int, /*SpecialFlag::Restriction*/int, char *) = 0;
		virtual void RestrictSpecialFlag(int, /*SpecialFlag::Restriction*/int) = 0;
		virtual void ClearRestrictions(int) = 0;
		virtual void TransferFlag(int, int) = 0;
		virtual void ObjectHasFlag(int) = 0;

			virtual void FailMission(float, const char *) = 0;


			virtual void SucceedMission(float, const char *) = 0;

		virtual void MonitorInputControls(PFUNC) = 0;
		virtual void GetInputControlPointer(const char *) = 0;
			virtual int GetDilithium(int) = 0;
			virtual int GetMaxDilithium(int) = 0;
		virtual void AddDilithium(int, int) = 0;
		virtual void SetDilithium(int, int) = 0;
			virtual int GetMetal(int) = 0;
			virtual int GetMaxMetal(int) = 0;
		virtual void AddMetal(int, int) = 0;
		virtual void SetMetal(int, int) = 0;
			virtual int GetBiomatter(int) = 0;
		virtual void AddBiomatter(int, int) = 0;
		virtual void SetBiomatter(int, int) = 0;
			virtual int GetLatinum(int) = 0;
			virtual int GetMaxLatinum(int) = 0;
		virtual void AddLatinum(int, int) = 0;
		virtual void SetLatinum(int, int) = 0;
			virtual float GetTeamCrew(int) = 0;
			virtual float GetMaxCrew(int) = 0;
		virtual void AddCrew(int, float) = 0;
		virtual void SetTeamCrew(int, float) = 0;
			virtual float GetOfficers(int) = 0;
			virtual float GetOfficerCapacity(int) = 0;
		virtual void AddOfficers(int, float) = 0;
		virtual void SetOfficers(int, float) = 0;

			//Set the relation frome team1 to team2
			virtual void SetRelation(int sourceTeam, int targetTeam, eTeamRelation relaton ) = 0;
			
			//Shows data on how much you have sent to a team (like in the mission with
			//the other station). Can only show one at a time.
			virtual void ShowTradesTo( int teamNumber ) = 0;

			//Set whether the ferengi will trade with your trading stations.
			virtual void FerengiCanTrade( bool value ) = 0;

			//Set whether the ferengi will steal derelict vessels.
			virtual void FerengiCanSteal( bool value ) = 0;

			//Set the objectives to be visible or invisible.
			virtual void ObjectivesDisplay_Set_Visibility( bool value ) = 0;

			//Load the objectives from a file.
			virtual void ObjectivesDisplay_Set_Text_From_File( const char * filename, unsigned char unknown ) = 0;

			//Set an objective to complete or incomplete.
			virtual void ObjectivesDisplaySetObjectiveComplete( int objectiveNumber, unsigned char value ) = 0;
			
			//Display a message with the text from a file. This file must have 
			//been loaded by the game already.
			virtual void MessageDisplay_Set_Text_From_File(char *) = 0;

		virtual void FadeOut(class script *, float time, float delay, float type, unsigned char dontWait) = 0;
		virtual void FadeIn(class script *, float time, float delay, float type, unsigned char dontWait) = 0;
		virtual void FadeRemove(void) = 0;
		virtual void EnableLight(int, unsigned char) = 0;
			//Starts playing the credits
			virtual void StartCredits(void) = 0;
			//Stops playing the credits
			virtual void EndCredits(void) = 0;
		virtual void SetClippingDistance(float) = 0;
		virtual void SetObjectCullingDistance(float) = 0;
		virtual void RestoreObjectCullingDistance(void) = 0;
			
			//Plays a sound file as a voiceover (at the voiceover volume)
			//Returns a messageid.
			virtual int AudioMessage(class script * unknown, const char* filename, bool dontWaitForMessageToFinish ) = 0;
			//Plays a sound file as music (at the music volume)
			virtual int PlayMusic(class script * unknown, const char * filename, bool dontWaitForMessageToFinish ) = 0;

		virtual void WaitForEnterKey(class script *) = 0;

			//Find out if the message that was started has finished yet.
			//returns a bool (unsigned char) - 0 is still playing.
			virtual unsigned char IsAudioMessageDone( int messageId ) = 0;

			//Stop the message with specified id.
			virtual void StopAudioMessage( int messageId ) = 0;

		virtual void CineractiveStart(class script *, unsigned char) = 0;
		virtual void CineractiveCameraOffset(char *, float, unsigned char) = 0;
		virtual void CineractiveCameraOffset(float, float, float, unsigned char) = 0;
		virtual void CineractiveTargetOffset(char *, float, unsigned char) = 0;
		virtual void CineractiveTargetOffset(float, float, float, unsigned char) = 0;
		virtual void CineractiveShot(char *, float, char *, float) = 0;
		virtual void CineractiveShot(char *, float, int) = 0;
		virtual void CineractiveShot(char *, float, char *, int) = 0;
		virtual void CineractiveShot(char *, float, unsigned char) = 0;
		virtual void CineractiveShot(int, char *, float) = 0;
		virtual void CineractiveShot(int, int) = 0;
		virtual void CineractiveShot(int, char *, int) = 0;
		virtual void CineractiveShot(int, unsigned char) = 0;
		virtual void CineractiveShot(char *, int, char *, float) = 0;
		virtual void CineractiveShot(char *, int, int) = 0;
		virtual void CineractiveShot(char *, int, char *, int) = 0;
		virtual void CineractiveShot(char *, int, unsigned char) = 0;
		virtual void CineractiveShotTrackLeft(char *, int, char *, int, int) = 0;
		virtual void CineractiveConstantSpeed(unsigned char) = 0;
		virtual void SetPathSegmentSpeedModifier(int, float) = 0;
			virtual void CineractiveEnd(void) = 0;
		virtual void AddToLoad(void *) = 0;
		virtual void RemoveFromLoad(void *) = 0;
		virtual void AddToSave(void *) = 0;
		virtual void RemoveFromSave(void *) = 0;
		virtual void out(class FileWriter &, float *, unsigned int, char *) = 0;
		virtual void out(class FileWriter &, Vector3 *, unsigned int, char *) = 0;
		virtual void out(class FileWriter &, class timer_int *, char *) = 0;
		virtual void out(class FileWriter &, class hot_int *, char *) = 0;
		virtual void out(class FileWriter &, int *, unsigned int, char *) = 0;
		virtual void in(FileReader &, float *, unsigned int) = 0;
		virtual void in(FileReader &, Vector3 *, unsigned int) = 0;
		virtual void in(FileReader &, class timer_int *) = 0;
		virtual void in(FileReader &, class hot_int *) = 0;
		virtual void in(FileReader &, int *, unsigned int) = 0;
				
			//Set the text that appears above the minimap.
			virtual void SetTeamText(char *) = 0;

		virtual void SetStarbaseUpgrades(int, int) = 0;
		virtual void CreateNewSiegeFleet(void) = 0;
		virtual void CreateNewMoveFleet(void) = 0;
		virtual void CreateNewAttackFleet(void) = 0;
		virtual void CreateNewDefendFleet(void) = 0;
		virtual void RandomGetUnsigned(unsigned int) = 0;
			virtual unsigned char IsShipAliveAndOffMap(int) = 0;
		virtual void Starfield_Load_New_Background_Geometry(char *, char *) = 0;
			//Find out if the craft with the specified craftid
			//is a station. Returns true if it is.
			virtual bool IsStation( int craftId ) = 0;
		virtual void RemoveFromAdLog(int) = 0;
		virtual void AddToAdLog(int) = 0;
		virtual void HasTimeElapsed(float) = 0;
		virtual void SetCanBeDecommissioned(int, unsigned char) = 0;
			//0 to enable chat, 1 to disable.	
			virtual void DisableChat( bool value ) = 0;
		virtual void MuteSounds(float) = 0;
				
			//Set the name of the craft with the specified id to the name
			//given.
			virtual const char* SetName( int craftId, const char* name) = 0;

			//Disables saving of the game.
			virtual void DisableSave(void) = 0;
			//Enables saving of the game
			virtual void EnableSave(void) = 0;

		virtual void TeamKamikaze(int) = 0;
		virtual void TeamAttackAll(int) = 0;
		virtual void GetLatinumTraded(int, int) = 0;
		virtual void SetTeamDistressCallRange(int, float) = 0;
#ifdef _MMM_FLEETOPS_GRC_FIX
		virtual int GetReplacementChild(int handle) = 0;
#endif
	};

	ScriptInterface* getScriptInterface( );
	void			 setScriptInterface( ScriptInterface* sInterface );
}