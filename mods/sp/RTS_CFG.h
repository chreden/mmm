///////////////////////////////////////////////////////////////////////////////
//
// RTS_CFG.h
//
// Runtime configuration file for real-time topdown strategy elements added
// to the engine.
//
// By the Mad Dr. I.  4/98.
//
///////////////////////////////////////////////////////////////////////////////

//
// Include the ART only parameters
//
#include "ART_CFG.h"

// include the parameters for the Admiral's Log
#include "ADLOG_CFG.h"

// include the network configuration
//#include "Network_CFG.h"

///////////////////////////////////////////////////////////////////////////////
// Interface Settings
///////////////////////////////////////////////////////////////////////////////

// INTRO MOVIE
#define cfgINTRO_MOVIE_NAME "Intro.bik"

// CAMERA CONTROL

// Where do we start the cinematic zoom?
float cfg_DEFAULT_TACTICAL_ZOOM = 10.0;

float OVERVIEW_PARABOLA_FOCUS = 200.0;
float OVERVIEW_MAX_HEIGHT  = 1850.0;
float OVERVIEW_INIT_HEIGHT = 1000.0;
float OVERVIEW_MIN_HEIGHT  =  10.0;
float OVERVIEW_INIT_ROTATION = 0.0;
int SCROLL_BORDER_WIDTH = 8;
float SCROLL_COEFFICIENT = 90000.0;
float FASTSCROLL_COEFFICIENT = 0.005;
float ZOOM_SCROLL_COEFFICIENT = 0.01;
float ROTATION_SCROLL_COEFFICIENT = 0.01;
float CINEMATIC_ROTATION_COEFFECIENT = 0.035;
float KEYBOARD_SCROLL_RATE =  20.0;
float cfgMOUSE_HOLD_LEVEL	= 0.28;		// how long the mouse button needs to be held before it's considered a hold
int SCROLL_ACCELERATION = 3;				// Multiplier for each "step"
float MAX_SCROLL_SPEED = 2.0;				// The max speed we want to scroll
float INITIAL_SCROLL_SPEED = 0.5;			    // Initial speed
int cfgTACTICAL_WHERE_MODE = 1;				// use last selected end path or what you get from shift

// SHIP SELECTION
int SELECTION_RECTANGLE_COMMIT_AREA = 100;	// Define the area of the rectangle we need to form for the selection
											// rectangle to become the current action.

float STATION_PLACEMENT_GRID_SIZE = 50.0;	// The size of the grid squares in the placement map.

float cfgPATH_POINT_SELECTION_DISTANCE=15;	// How far from a path point we
											// can click and select it

int SNAP_TO_DISTANCE = 10;					// Distance where the panels snap to another panel or the edge.
int UNHIDE_DISTANCE = 15;					// Distance at which the interface auto-hide pops up.

// GRID ACTION FX
float GRID_FX_GROWTH_RATE = 0.83;
float GRID_FX_MAX_SIZE = 0.01;
float GRID_FX_MIN_SIZE = 0.005;
float GRID_FX_GROWTH_INTERVAL = 0.01;		// In seconds. Time to pass between growth.
float GRID_FX_ROTATION_SPEED = 2.0;

// DEBUG DISPLAY
int SHOW_QUADTREE = 0;						// Should we show the quadtree decompsition?
int SHOW_FOOTPRINTS_IN_EDIT_MODE = 1;		// Should we show footprints in edit mode?
int DEBUG_VECTORS_3D = 0;
int DEBUG_SHOW_AI_PATHS = 0;
int DEBUG_SHOW_AI_PATHS_RUNNING = 0;
int DEBUG_SHOW_CURVES = 1;
int DEBUG_SHOW_OBJ_POSTS = 1;
int DEBUG_SHOW_LOCAL_BOUNDING_BOX = 0;
int DEBUG_SHOW_OBJECT_BOUNDING_BOX = 0;
int DEBUG_SHOW_OBJECT_BOUNDING_SPHERE = 0;
int DEBUG_SHOW_BOUNDING_SQUARE = 0;
// DEBUG_DRAW can  be 0 - 3
//	0 means draw nothing, 
//	1 means draw just coords 
//	2 means draw everything but AI, 
//	3 means AI state only
int DEBUG_DRAW = 0;

///////////////////////////////////////////////////////////////////////////////
// Other...
///////////////////////////////////////////////////////////////////////////////

//
// DEFAULT MISSION START STARDATE (if not specified in the mission itself)
//

float cfgINITIAL_STARDATE = 0.0;	// stardate at mission start if not specified, orig: 56123.1
float cfgSTARDATE_PER_SECOND = 1.0;		// for every "game second (more or less real time second), this many stardate intervals pass

//
// PARAMETERS FOR MULTIPLAYER MISSION TYPES
//

float cfgDEFEND_TIME = 60.0 * 60.0;		// how long does a defender need to hold out (if unspecified) in seconds -- 1 hour
float cfgLATINUM_COLLECT = 15000.0;		// how much latinum to collect to win a latinum collection game

//
// DIFFICULTY SETTINGS
//

// Damage coefficients for incoming damage for user in single player
float EASY_DAMAGE = 1.0;
float HARD_DAMAGE = 1.0;

// Mining rate cooefficients for user in single player
float EASY_MINING_MODIFIER = 1.0;
float HARD_MINING_MODIFIER = 1.0;

// AI special weapon fire rate
float EASY_SPECIAL_WEAPON_FIRE_MODIFIER = 1.0;
float DEFAULT_SPECIAL_WEAPON_FIRE_MODIFIER = 1.0;
float HARD_SPECIAL_WEAPON_FIRE_MODIFIER = 1.0;

// Build cost multiplier handicap for hard AI
float HARD_AI_COST_HANDICAP = 0.1;
float HARD_AI_SPEED_HANDICAP = 0.6;

float MEDIUM_AI_COST_HANDICAP = 0.2;
float MEDIUM_AI_SPEED_HANDICAP = 0.7;

float EASY_AI_COST_HANDICAP = 0.75;
float EASY_AI_SPEED_HANDICAP = 0.8;

// Percent chance that AI fleets will cloak for long moves in Instant Action
// and Multiplayer AI (provided they can!)
float HARD_AI_CLOAK_PERCENT = 100;
float MEDIUM_AI_CLOAK_PERCENT = 100;
float EASY_AI_CLOAK_PERCENT = 100;

// how far away must latinum resource bases be? (to keep them from building
// clusters of mining stations around clusters of nebulas
float cfgRESOURCE_LATINUM_SPACING = 5.0;

// how far should the transmuters park from the resource
float cfg8472_RESOURCE_DISTANCE = 400.0;

// what is too close to the resource?
float cfg8472_RESOURCE_INSIDE_DISTANCE = 300.0;

// how many freighters can we have around each resource?
int cfgFREIGHTERS_PER_MOON = 5;
int cfgFREIGHTERS_PER_NEBULA = 5;
int cfgFREIGHTERS_PER_PLANET = 5;

// Threat multiplier penalty for getting resources
float cfgRESOURCE_THREAT_PENALTY_COEFFICIENT = 1.0;

// if we start a planet base, build this far above the surface
float cfgPLANET_BASE_BUILD_BUFFER = 400.0;

// At what range of a move command will AI cloak in Instant Action and MP?
float cfg_MIN_MOVE_DISTANCE_FOR_CLOAK = 2000.0;

// At what range will the AI try to warp?
float cfg_MIN_MOVE_WARP_DISTANCE = 999999.0;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// CLEAN TO HERE.
// I've eliminated unused parameters above this spot.
// Please clean more, and move this down as appropriate.
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//
// DAMAGE MODEL
//

// Are we using the hitpoint system for damage allocation?
int USE_SYSTEM_HITPOINTS = 1;
int SYSTEM_HITPOINTS_BONUS = 0;
float SHIELD_DAMAGE_PROTECTION = 1.0;
// determines how important it is that a hardpoint be close to the targeting hardpoint
// increase to make distance less important
int cfgFACING_CONSTANT = 3;
// number between 0 and 1 inclusive determining how much to weigh the facing probabilities versus the
// predetermined probabilities
float cfgFACING_WEIGHT	= 0.2;

// The default for pre-loading is off for debug, on for release.
// If you want it different, uncomment these two.

// Should we demand load all ODFs?
int cfgDEMAND_LOAD_ODFS = 1;

// Reload object classes on editor instance creation?
// NOTE: When placing objects with this flag on, ALL OBJECTS of the same type
//		actually end up with different Object Classes, because they ALWAYS get reloaded.
//		Only turn this on if you're actually making changes to the odfs, not when building a mission.
int cfgRELOAD_OBJECT_CLASSES = 0;

// Should we go to windowed mode when we hit an assert?  Very useful for single monitor machines.
int cfgFLIP_TO_WINDOWED_ON_ASSERT = 1;

// What's our default grid rendering state in tactical mode? 0=grid only, 1=grid+height bars, 2=none
int cfgTACTICAL_GRID_RENDER = 2;

// What's our default grid rendering state in strategic mode? 0=grid only, 1=grid+height bars, 2=none
int cfgSTRATEGIC_GRID_RENDER = 2;

// Should we show the framerate in the upper left corner?
int  FRAMERATE_DISPLAY = 0;

// At what size should we start scaling objects in strategic view?
float cfgMIN_STRATEGIC_VIEW_OBJECT_RADIUS = 25.0; // 1/4 grid square size

// What's the maximum strategic view scale factor?
float cfgMAX_STRATEGIC_VIEW_OBJECT_SCALE = 1.75;  // Grow by at most 75%

//       A    AAAAA
//      A A     A
//     A   A    A
//     AAAAA    A
//     A   A    A
//     A   A  AAAAA

// STRATEGIC AI

// Show this many goals in the minimap display
int cfg_AI_SHOW_GOALS_COUNT = 12;

// COMBAT

// Instead of standing perfectly still, should we circle in place near our
// weapon range?
int CIRCLE_IN_PLACE_DURING_COMBAT = 0;
float CIRCLE_RADIUS_DIVISOR = 6.0;

// PATHING

// How quickly do we rotate away from collision (1.57 is very quick)
float MAX_PREVENTION_ROTATION = 0.6;

// Cost of OFF-MAP pathing
int OFF_MAP_PATHING_COST = 90000;

// Path Planning
float HIGHEST_QUADTREE_GRID_RESOLUTION = 50.0;

// BUFFER FOR WARP FOOTPRINTS
float cfg_WARP_INHIBITION_BUFFER = 160.0;

// Should we use the full on path planning?
int USE_PATH_PLANNING = 1;

// A value for terrain impassability
int IMPASSABLE_TERRAIN = -1;

// Default value for terrain cost
int DEFAULT_TERRAIN_VALUE = 100;

// Warp inhibition cost
int cfg_WARP_INHIBITION_COST = DEFAULT_TERRAIN_VALUE * 4;

// Almost, but not quite impassable
int cfg_ALMOST_INTRAVERSIBLE = 99999; //300

// Do we want the extra special rubber banding effect to make paths nicer?
int PERFORM_RUBBER_BANDING = 1;

// In certain combat modes, we go extra slow
float COMBAT_SLOWDOWN = 1.0;

// The leader of a formation should slow down
float FORMATION_LEADER_SLOWDOWN = 1.0;

// Pathing cost for nebulae
float NEBULAE_PATHING_COST = 300.0;

// Extra distance for pathing around nebulae
float NEBULAE_PATHING_SAFETY_COEFFICIENT = 1.8;

// Pathing cost for asteroid belts
float ASTEROID_BELT_PATHING_COST = 400.0;

// Pathing cost for blackholes
float BLACKHOLE_PATHING_COST = IMPASSABLE_TERRAIN;

// Extra distance for pathing around blackholes
float BLACKHOLE_PATHING_SAFETY_COEFFICIENT = 1.5;

// Do we default to formation move, or non-formation group move
int cfgDEFAULT_TO_FORMATION_MOVE = 0;

// How do we scale the planet radius for the gravity induced dewarping zone.
float cfgPLANET_DEWARP_RADIUS_MULTIPLIER = 0;
// Radius multiplier for black holes, since hey, they got gravity
float cfgBLACKHOLE_DEWARP_RADIUS_MULTIPLIER = 0;

// how far away from the outside of a planet should borg freighters mine?
float PLANET_MINING_RADIUS_OFFSET = 150;

// STRATEGIC AI PARAMETERS
float AI_GRID_SIZE = 400.0;
#define EASY_AI "AI_Easy_Script.dsl"
#define MEDIUM_AI "AI_Medium_Script.dsl"
#define HARD_AI "AI_Hard_Script.dsl"

// Ship combat configuration
float SKINNY_SHIP_COMBAT_FLOOR = -250.0;
float SKINNY_SHIP_COMBAT_CEILING = 250.0;
float SHIP_COMBAT_FLOOR = -250.0;
float SHIP_COMBAT_CEILING = 250.0;
float DEEP_SPACE_SHIP_COMBAT_FLOOR = -250.0;
float DEEP_SPACE_SHIP_COMBAT_CEILING = 250.0;
float ANCHOR_PURSUIT_POINT_ANGLE = (3.14159/6);
float ANCHOR_RADIUS = 4.0;
float ANCHOR_PURSUIT_FORCE = 10.0;
float CENTER_OF_COMBAT_PERSISTENCE_CUTOFF = 6 * ANCHOR_RADIUS;
float DOGFIGHT_RANGE = 70.0;

// multiply times target radius to get radius for circling, cloverleaf
float cfgDOGFIGHT_RADIUS_MODIFIER = 3.0;
float cfgCLOVERLEAF_RADIUS_MODIFIER = 1.2;

//
// COLLISION AVOIDANCE & PATH FOLLOWING STUFF
//

// How far apart should ships be when moving in formation
float FORMATION_SPACING = 100.0;

// How much the last cycle's collision avoidance force should factor into
// this cycle's.  Must be less than 1.0, and should likely not be very close
// to 1.0.
float OLD_AVOIDANCE_FORCE_WEIGHT = 0.7;

//Obstacle avoidance is off by default
int OBSTACLE_AVOIDANCE = 0;

// How far ahead to project a collision
float COLLISION_LOOK_AHEAD_TIME = 1.4;

// How much wider than reality to pretend objects are for collision avoidance
float COLLISION_SAFETY_MARGIN = 1.2;

// We're adding a special repulsion on the y-axis for collision avoidance.
float Y_REPULSION = 0.5;

// When we're following a scripted 3D path, we know to advance to the next
// point when we're within this radius of the current point
float PATH_POINT_RADIUS = 35.0;
float PATH_POINT_RADIUS_SQUARED = PATH_POINT_RADIUS * PATH_POINT_RADIUS;

// We need an epsilon value for sending units to the right or bottom of the map
// to keep our position strictly LESS than the edge value
float MAP_EDGE_EPSILON = 0.1;

// We actually start keeping ships from the edge this many meters out
float MAP_EDGE_BUFFER = 100.0;

//
//     GAMEPLAY
//

// Transporter parameters.
float TRANSPORTER_RANGE = 1000.0;
float TRANSPORTER_DELAY = 1.0;
float TRANSPORTER_ACTION_DELAY = 1.0;
int   TRANSPORTER_MAX = 3;

//fraction of the the build time it takes to decommission
float DECONSTRUCT_PERCENT_TIME = 0.75;

// Weapon parameters.
float BEAM_MISS_LIFETIME = 0.5;

// Use team color for normal weapons?
int NORMAL_WEAPON_TEAM_COLOR = 0;

// UI Limits for each resource
int MAX_DILITHIUM =	99999;
int MAX_CREW =		9999999;
int MAX_LATINUM =	99999;
int MAX_METAL =		99999;
int MAX_OFFICERS =	999;
int MAX_BIOMATTER =	99999;

int STARTING_DILITHIUM =		4000;
int STARTING_CREW =			9999999;
int STARTING_CREW_CAPACITY =		1000;
int STARTING_LATINUM =			2000;
int STARTING_METAL =			500;
int STARTING_BIOMATTER =		100;
int SINGLE_PLAYER_OFFICER_LIMIT =	20;

struct MP_Resource_Class
{
	char m_key[80];
};

int MP_RESOURCE_MODES = 3;
MP_Resource_Class MP_STARTING_RESOURCE[MP_RESOURCE_MODES] = 
{
	"sr_normal",
	"sr_lots",
	"sr_unlimited",
};

struct MP_Officer_Limit_Class
{
	char m_key[80];
	int m_officer_limit;
};

int MP_OFFICER_LIST_SIZE = 12;
MP_Officer_Limit_Class MP_OFFICER_LIMIT[MP_OFFICER_LIST_SIZE] = 
{
	"credits_20",			20,
	"credits_22",			22,
	"credits_24",			24,
	"credits_26",			26,
	"credits_28",			28,
	"credits_30",			30,
	"credits_00",			 0,
	"credits_10",			10,
	"credits_12",			12,
	"credits_14",			14,
	"credits_16",			16,
	"credits_18",			18
};



int DRAW_PIZZA_BOX = 0;

float cfgSCREEN_WIDTH =	1600.0;
float cfgSCREEN_HEIGHT = 1200.0;

int cfgRESIZEABLE_WINDOW = 1;

// How far away should we look for ships to snap to in Tactical View?
float cfgTACTICAL_SNAP_DISTANCE = 800.0;

// should we fade out craft that get too close to the camera?
int cfgFADE_OUT_ENABLED = 0;
// ratio of radius/distance at which fade out begins
float cfgFADE_OUT_MIN_FOV = 0.9;
// ratio of radius/distance at which fade out is maximum
float cfgFADE_OUT_MAX_FOV = 0.99;
// maximum degree of fade-out (1.0 = invisible, 0.0 = opaque)
float cfgFADE_OUT_MAX = 0.9;

// How far you have to be from your anchor to try warping at all
float cfgTOO_CLOSE_TO_WARP = 800.0;

// Bonus points to be added to winner(s) game score
float cfgWINNERS_BONUS = 5000;

//
// PLANET CONSTANTS
//
int cfgPOP_SPARSE	= 1000;
int cfgPOP_LIGHT	= 2000;
int cfgPOP_MEDIUM	= 3000;
int cfgPOP_HEAVY	= 5000;
float cfgPLANET_CIVILIAN_RATE_MODIFIER = 0.20;

// PLANET CONSTANTS

// How often should we take snapshots of strength for the timeline?
// in seconds
// this is just the initial sample rate, it decreases as the game plays
float cfgTIMELINE_FREQ = 0.5;


// How much time should there be between 2 ferengi traders going to one trading station?
float cfgTSTATION_TIME_BETWEEN_FERENGI = 60;
// extra time added per ferengi trader that a team has killed
float cfgKILL_FERENGI_TIME_ADD = 5;

float cfgBIOMATTER_RECYCLE_FRACTION = 0;

#define cfgSOUND_VOICE_SAMPLE "borg_transmit1.ogg"
#define cfgSOUND_EFFECTS_SAMPLE "federation_phaser_small.wav"
#define cfgSOUND_BUTTON_SAMPLE "federation_click.wav"
#define cfgSOUND_SHELL_BUTTON_HOVER "Beep1.ogg"
#define cfgSOUND_SHELL_BUTTON_CLICK "Beep2.ogg"
#define cfgSOUND_INGAME_CHAT_SEND "Chatsend.ogg"
#define cfgSOUND_INGAME_CHAT_RECEIVE "Chatreceive.ogg"
#define cfgSOUND_SHELL_MUSIC "shell.ogg"
#define cfgSOUND_LOADING_MUSIC "loading.mp3"
#define cfgSOUND_INGAME_CHEAT "cheater.ogg"

#define SYSTEM_REPAIR_SPARK_SPRITE "xempty"

#define cfgBUTTON_COLOR "ffffff";
#define cfgTEXT_COLOR "ffffff";

int GAME_OPTIONS_RANDOM_MAP = 0;
int GAME_OPTIONS_MOTHERSHIP = 0;
int GAME_OPTIONS_OFFICERS = 0;
int GAME_OPTIONS_WARP = 0;
int GAME_OPTIONS_MAP_DEPTH = 0;

int cfgCINEMATIC_WINDOW_ENABLED = 0;

int cfgSINGLE_PLAYER_ENABLED = 1;
int DISABLE_HEIGHT_CHANGE = 1;

float REPAIR_SHIP_DISTANCE = 350;

#define cfgDEFAULT_MAP "first.bzn";
#define cfgDEFAULT_MAP_TITLE "The Very First Map";
