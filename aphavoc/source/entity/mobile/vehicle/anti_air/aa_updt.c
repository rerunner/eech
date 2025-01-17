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

#include "entity/tacview/tacview.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_server (entity *en)
{

	anti_aircraft
		*raw;

	raw = (anti_aircraft *) get_local_entity_data (en);

	update_local_entity_view_interest_level (en);

	raw->vh.sleep -= get_delta_time ();

	raw->vh.sleep = max (raw->vh.sleep, 0.0f);

	if (raw->vh.mob.alive)
	{

		////////////////////////////////////////

		update_vehicle_loading_doors (en);

		update_vehicle_radar (en);

		////////////////////////////////////////
		//
		// ORDER IS CRITICAL
		//

		update_vehicle_target_scan (en);

		update_vehicle_weapon_system_ready (en);

		update_entity_weapon_systems (en);

		update_entity_weapon_system_weapon_and_target_vectors (en);

		update_vehicle_weapon_fire (en);

		update_vehicle_decoy_release (en);

		//
		////////////////////////////////////////

		if (tacview_is_logging() && raw->vh.mob.alive)
		{
			int
				moved = get_local_entity_int_value(en, INT_TYPE_MOBILE_MOVING),
				rotated = get_local_entity_int_value(en, INT_TYPE_ROTATED);

			// TODO.  Actually recorde rotation, so we can use it
			rotated = moved;

			if (moved || rotated || command_line_tacview_logging < 3)
				write_tacview_unit_update(en, moved, rotated, FALSE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_client (entity *en)
{
	anti_aircraft
		*raw;

	raw = (anti_aircraft *) get_local_entity_data (en);

	update_local_entity_view_interest_level (en);

	raw->vh.sleep -= get_delta_time ();

	raw->vh.sleep = max (raw->vh.sleep, 0.0f);

	if (raw->vh.mob.alive)
	{

		////////////////////////////////////////

		update_vehicle_loading_doors (en);

		update_vehicle_radar (en);

		////////////////////////////////////////
		//
		// ORDER IS CRITICAL
		//

		update_vehicle_weapon_system_ready (en);

		update_entity_weapon_systems (en);

		update_entity_weapon_system_weapon_and_target_vectors (en);

		//
		////////////////////////////////////////


		if (tacview_is_logging() && raw->vh.mob.alive)
		{
			int
				moved = get_local_entity_int_value(en, INT_TYPE_MOBILE_MOVING),
				rotated = get_local_entity_int_value(en, INT_TYPE_ROTATED);

			rotated = moved;

			if (moved || rotated || command_line_tacview_logging < 3)
				write_tacview_unit_update(en, moved, rotated, FALSE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_anti_aircraft_update_functions (void)
{
	fn_update_client_server_entity[ENTITY_TYPE_ANTI_AIRCRAFT][COMMS_MODEL_SERVER]	= update_server;

	fn_update_client_server_entity[ENTITY_TYPE_ANTI_AIRCRAFT][COMMS_MODEL_CLIENT]	= update_client;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
