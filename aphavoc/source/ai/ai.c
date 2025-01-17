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

#include "project.h"

#include "ai_misc/ai_misc.h"
#include "taskgen/taskgen.h"
#include "faction/faction.h"
#include "highlevl/highlevl.h"
#include "parser/parsgen.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	ai_memory_counter;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void reinitialise_ai_debug ();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ai_system (void)
{

	#if AI_DEBUG

	debug_log ("Initialise AI system");

	ai_memory_counter = 0;

	#endif

	initialise_ai_database ();

	initialise_route_data ();

	initialise_object_3d_regeneration_database ();

	initialise_high_level_ai ();

	initialise_speech_buffers ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void start_ai_system (void)
{
	start_high_level_ai ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stop_ai_system (void)
{
	stop_high_level_ai ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_ai_system (void)
{

	deinitialise_briefing_parser ();

	deinitialise_ai_database ();

	deinitialise_route_data ();

	deinitialise_formation_database ();

	deinitialise_formation_component_database ();

	deinitialise_high_level_ai ();

	deinitialise_speech_buffers ();

	reinitialise_ai_debug ();

	#if AI_DEBUG

	debug_log ("Deinitialise AI system");

	debug_log ("AI Memory count = %d", ai_memory_counter);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reinitialise_client_ai_system (void)
{

	comms_model_types
		temp_comms_model;

	comms_data_flow_types
		temp_comms_data_flow;

	temp_comms_model = get_comms_model ();

	temp_comms_data_flow = get_comms_data_flow ();

	//
	// set comms model and data flow to SERVER/TX
	//

	set_comms_model (COMMS_MODEL_SERVER);

	set_comms_data_flow (COMMS_DATA_FLOW_TX);

	if (population_placement_filename)
	{

		read_population_placement_file (population_placement_filename);
	}

	set_comms_model (temp_comms_model);

	set_comms_data_flow (temp_comms_data_flow);

	initialise_keysite_farp_enable (get_local_force_entity (ENTITY_SIDE_BLUE_FORCE));

	initialise_keysite_farp_enable (get_local_force_entity (ENTITY_SIDE_RED_FORCE));

	initialise_briefing_parser ();

	set_assign_create_waypoint_route (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reinitialise_ai_system (void)
{

	ASSERT (get_current_game_session ());

	initialise_briefing_parser ();

	reinitialise_ai_debug ();

	clear_road_route_data ();

	deinitialise_formation_database ();

	initialise_formation_database ();

	deinitialise_formation_component_database ();

	initialise_formation_component_database ();

	deinitialise_speech_buffers ();

	initialise_speech_buffers ();

	set_assign_create_waypoint_route (TRUE);

	#if AI_DEBUG

	debug_log ("Reinitialise AI system");

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reinitialise_ai_debug (void)
{

	#if LANDING_ROUTE_CHECK

	destroy_debug_landing_route_check ();

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
