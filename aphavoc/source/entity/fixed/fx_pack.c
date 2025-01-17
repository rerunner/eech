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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_fixed_data (entity *en, fixed *raw, pack_modes mode)
{
	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			pack_vec3d (en, VEC3D_TYPE_POSITION, &raw->position);

			/////////////////////////////////////////////////////////////////
			if (mode == PACK_MODE_SERVER_SESSION)
			{

				if (raw->task_dependent_root.first_child)
				{

					pack_int_value (en, INT_TYPE_VALID, TRUE);

					pack_list_root (en, LIST_TYPE_TASK_DEPENDENT, &raw->task_dependent_root);
				}
				else
				{

					pack_int_value (en, INT_TYPE_VALID, FALSE);
				}
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (raw->target_root.first_child)
			{

				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_root (en, LIST_TYPE_TARGET, &raw->target_root);
			}
			else
			{

				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			// gunship_target_link

			// sector_link

			pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, raw->sub_type);

			pack_int_value (en, INT_TYPE_OBJECT_3D_SHAPE, raw->object_3d_shape);

			pack_int_value (en, INT_TYPE_ALIVE, raw->alive);

			pack_int_value (en, INT_TYPE_SIDE, raw->side);

			// gunship_radar_los_clear

			// object_drawn_once_this_frame

			pack_float_value (en, FLOAT_TYPE_HEADING, raw->heading);

			if (raw->heading == 0.0)
			{

				debug_log ("FX_PACK: heading = zero");
			}

			break;
		}
		////////////////////////////////////////
		case PACK_MODE_BROWSE_SESSION:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case PACK_MODE_UPDATE_ENTITY:
		////////////////////////////////////////
		{
			//
			// cannot update entity at this level as the update may not apply to all entity types below
			//

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_fixed_data (entity *en, fixed *raw, pack_modes mode)
{
	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			unpack_vec3d (en, VEC3D_TYPE_POSITION, &raw->position);

			/////////////////////////////////////////////////////////////////
			if (mode == PACK_MODE_SERVER_SESSION)
			{
				if (unpack_int_value (en, INT_TYPE_VALID))
				{

					unpack_list_root (en, LIST_TYPE_TASK_DEPENDENT, &raw->task_dependent_root);
				}
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_root (en, LIST_TYPE_TARGET, &raw->target_root);
			}
			/////////////////////////////////////////////////////////////////

			// gunship_target_link

			// sector_link

			raw->sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

			raw->object_3d_shape = unpack_int_value (en, INT_TYPE_OBJECT_3D_SHAPE);

			raw->alive = unpack_int_value (en, INT_TYPE_ALIVE);

			raw->side = unpack_int_value (en, INT_TYPE_SIDE);

			// gunship_radar_los_clear

			// object_drawn_once_this_frame

			raw->heading = unpack_float_value (en, FLOAT_TYPE_HEADING);

			break;
		}
		////////////////////////////////////////
		case PACK_MODE_BROWSE_SESSION:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case PACK_MODE_UPDATE_ENTITY:
		////////////////////////////////////////
		{
			//
			// cannot update entity at this level as the update may not apply to all entity types below
			//

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
