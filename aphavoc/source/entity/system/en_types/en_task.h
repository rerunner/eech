// 
// 	 Enemy Engaged RAH-66 Comanche Versus KA-52 Hokum
// 	 Copyright (C) 2000 Empire Interactive (Europe) Ltd,
// 	 677 High Road, North Finchley, London N12 0DA
// 
// 	 Please see the document LICENSE.TXT for the full licence agreement
// 
// 2. LICENCE
//  2.1 	
//  	Subject to the provisions of this Agreement we now grant to you the 
//  	following rights in respect of the Source Code:
//   2.1.1 
//   	the non-exclusive right to Exploit  the Source Code and Executable 
//   	Code on any medium; and 
//   2.1.2 
//   	the non-exclusive right to create and distribute Derivative Works.
//  2.2 	
//  	Subject to the provisions of this Agreement we now grant you the
// 	following rights in respect of the Object Code:
//   2.2.1 
// 	the non-exclusive right to Exploit the Object Code on the same
// 	terms and conditions set out in clause 3, provided that any
// 	distribution is done so on the terms of this Agreement and is
// 	accompanied by the Source Code and Executable Code (as
// 	applicable).
// 
// 3. GENERAL OBLIGATIONS
//  3.1 
//  	In consideration of the licence granted in clause 2.1 you now agree:
//   3.1.1 
// 	that when you distribute the Source Code or Executable Code or
// 	any Derivative Works to Recipients you will also include the
// 	terms of this Agreement;
//   3.1.2 
// 	that when you make the Source Code, Executable Code or any
// 	Derivative Works ("Materials") available to download, you will
// 	ensure that Recipients must accept the terms of this Agreement
// 	before being allowed to download such Materials;
//   3.1.3 
// 	that by Exploiting the Source Code or Executable Code you may
// 	not impose any further restrictions on a Recipient's subsequent
// 	Exploitation of the Source Code or Executable Code other than
// 	those contained in the terms and conditions of this Agreement;
//   3.1.4 
// 	not (and not to allow any third party) to profit or make any
// 	charge for the Source Code, or Executable Code, any
// 	Exploitation of the Source Code or Executable Code, or for any
// 	Derivative Works;
//   3.1.5 
// 	not to place any restrictions on the operability of the Source 
// 	Code;
//   3.1.6 
// 	to attach prominent notices to any Derivative Works stating
// 	that you have changed the Source Code or Executable Code and to
// 	include the details anddate of such change; and
//   3.1.7 
//   	not to Exploit the Source Code or Executable Code otherwise than
// 	as expressly permitted by  this Agreement.
// 



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum TASK_CATEGORY_TYPES
{
	TASK_CATEGORY_RECON,
	TASK_CATEGORY_STRIKE,
	TASK_CATEGORY_SUPPORT,
	TASK_CATEGORY_MISC,

	NUM_TASK_CATEGORY_TYPES
};

typedef enum TASK_CATEGORY_TYPES task_category_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum TASK_STATE_TYPES
{
	TASK_STATE_UNASSIGNED,
	TASK_STATE_ASSIGNED,
	TASK_STATE_COMPLETED,

	NUM_TASK_STATE_TYPES
};

typedef enum TASK_STATE_TYPES task_state_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum TASK_COMPLETED_TYPES
{

	TASK_INCOMPLETE,
	TASK_COMPLETED_FAILURE,
	TASK_COMPLETED_PARTIAL,
	TASK_COMPLETED_SUCCESS,

	NUM_TASK_COMPLETED_TYPES
};

typedef enum TASK_COMPLETED_TYPES task_completed_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum TASK_TERMINATED_TYPES
{

	TASK_TERMINATED_IN_PROGRESS,
	TASK_TERMINATED_EXPIRE_TIME_REACHED,
	TASK_TERMINATED_ABORTED,
	TASK_TERMINATED_GROUP_DESTROYED,
	TASK_TERMINATED_OBJECTIVE_MESSAGE,
	TASK_TERMINATED_STOP_TIME_REACHED,
	TASK_TERMINATED_WAYPOINT_ROUTE_COMPLETE,

	NUM_TASK_TERMINATED_TYPES
};

typedef enum TASK_TERMINATED_TYPES task_terminated_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum TASK_TARGET_SOURCE_TYPES
{

	TASK_TARGET_SOURCE_SCAN_AIR,
	TASK_TARGET_SOURCE_SCAN_ALL,
	TASK_TARGET_SOURCE_SCAN_GROUND,
	TASK_TARGET_SOURCE_OBJECTIVE_NOMINATED,
	TASK_TARGET_SOURCE_TASK_OBJECTIVE,
	TASK_TARGET_SOURCE_NONE,

	NUM_TASK_TARGET_SOURCE_TYPES
};

typedef enum TASK_TARGET_SOURCE_TYPES task_target_source_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum TASK_TARGET_TYPES
{

	TASK_TARGET_TYPE_NONE					= (0),
	TASK_TARGET_TYPE_AIRBORNE_AIRCRAFT	= (1 << 0),
	TASK_TARGET_TYPE_ANTI_AIRCRAFT		= (1 << 1),
	TASK_TARGET_TYPE_ANY						= (1 << 2),
	TASK_TARGET_TYPE_BUILDING				= (1 << 3),
	TASK_TARGET_TYPE_BRIDGE					= (1 << 4),
	TASK_TARGET_TYPE_CARGO					= (1 << 5),
	TASK_TARGET_TYPE_COMMS					= (1 << 6),
	TASK_TARGET_TYPE_FACTORY				= (1 << 7),
	TASK_TARGET_TYPE_FIXED_WING			= (1 << 8),
	TASK_TARGET_TYPE_GROUNDED_AIRCRAFT	= (1 << 9),
	TASK_TARGET_TYPE_HELICOPTER			= (1 << 10),
	TASK_TARGET_TYPE_MOBILE					= (1 << 11),
	TASK_TARGET_TYPE_PEOPLE					= (1 << 12),
	TASK_TARGET_TYPE_POWER					= (1 << 13),
	TASK_TARGET_TYPE_ROUTED					= (1 << 14),
	TASK_TARGET_TYPE_SHIP					= (1 << 15),
	TASK_TARGET_TYPE_VEHICLE				= (1 << 16),

	NUM_TASK_TARGET_TYPES
};

typedef enum TASK_TARGET_TYPES task_target_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum TASK_TARGET_CLASS_TYPES
{

	TASK_TARGET_CLASS_ALL,
	TASK_TARGET_CLASS_AIR,
	TASK_TARGET_CLASS_GROUND,

	NUM_TASK_TARGET_CLASS_TYPES
};

typedef enum TASK_TARGET_CLASS_TYPES task_target_class_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum TASK_OBJECTIVE_PREVIEW_TYPES
{

	TASK_OBJECTIVE_PREVIEW_NONE,
	TASK_OBJECTIVE_PREVIEW_STILL,
	TASK_OBJECTIVE_PREVIEW_LIVE,

	NUM_TASK_OBJECTIVE_PREVIEW_TYPES
};

typedef enum TASK_OBJECTIVE_PREVIEW_TYPES task_objective_preview_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum TASK_ROE_TYPES
{
	TASK_ROE_NONE,
	TASK_ROE_OBJECTIVE,
	TASK_ROE_ALL,

	NUM_TASK_ROE_TYPES
};

typedef enum TASK_ROE_TYPES task_roe_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum TASK_OBJECTIVE_INFO_TYPES
{
	TASK_OBJECTIVE_INFO_NONE,
	TASK_OBJECTIVE_INFO_ALWAYS_UNKNOWN,
	TASK_OBJECTIVE_INFO_FOG_OF_WAR_KNOWN,
	TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,

	NUM_TASK_OBJECTIVE_INFO_TYPES
};

typedef enum TASK_OBJECTIVE_INFO_TYPES task_objective_info_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern const char
	*task_status_names [],
	*task_debrief_result_names [],
	*task_terminated_names [],
	*task_target_source_names [];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
