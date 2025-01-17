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

static void set_local_attitude_matrix (entity *en, matrix3x3 attitude)
{
	camera
		*raw;

	ASSERT (attitude);

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_ATTITUDE_MATRIX, en, attitude);

	#endif

	raw = (camera *) get_local_entity_data (en);

	memcpy (raw->attitude, attitude, sizeof (matrix3x3));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_local_attitude_matrix (entity *en, matrix3x3 attitude)
{
	camera
		*raw;

	ASSERT (attitude);

	raw = (camera *) get_local_entity_data (en);

	memcpy (attitude, raw->attitude, sizeof (matrix3x3));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static matrix3x3 *get_local_attitude_matrix_ptr (entity *en)
{
	camera
		*raw;

	raw = (camera *) get_local_entity_data (en);

	return (&raw->attitude);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_local_attitude_angles (entity *en, float heading, float pitch, float roll)
{
	camera
		*raw;

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_ATTITUDE_ANGLES, en, heading, pitch, roll);

	#endif

	raw = (camera *) get_local_entity_data (en);

	get_3d_transformation_matrix (raw->attitude, heading, pitch, roll);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_local_attitude_angles (entity *en, float *heading, float *pitch, float *roll)
{
	camera
		*raw;

	ASSERT (heading);

	ASSERT (pitch);

	ASSERT (roll);

	raw = (camera *) get_local_entity_data (en);

	*heading = get_heading_from_attitude_matrix (raw->attitude);

	*pitch = get_pitch_from_attitude_matrix (raw->attitude);

	*roll = get_roll_from_attitude_matrix (raw->attitude);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_local_float_value (entity *en, float_types type)
{
	camera
		*raw;

	float
		value;

	raw = (camera *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case FLOAT_TYPE_HEADING:
		////////////////////////////////////////
		{
			value = get_heading_from_attitude_matrix (raw->attitude);

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_PITCH:
		////////////////////////////////////////
		{
			value = get_pitch_from_attitude_matrix (raw->attitude);

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_ROLL:
		////////////////////////////////////////
		{
			value = get_roll_from_attitude_matrix (raw->attitude);

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal_invalid_float_type (en, type);

			break;
		}
	}

	return (value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_camera_attitude_functions (void)
{
	fn_set_local_entity_raw_attitude_matrix	[ENTITY_TYPE_CAMERA]								= set_local_attitude_matrix;
	fn_set_local_entity_attitude_matrix			[ENTITY_TYPE_CAMERA]								= set_local_attitude_matrix;
	fn_get_local_entity_attitude_matrix			[ENTITY_TYPE_CAMERA]								= get_local_attitude_matrix;
	fn_get_local_entity_attitude_matrix_ptr	[ENTITY_TYPE_CAMERA]								= get_local_attitude_matrix_ptr;

	fn_set_local_entity_raw_attitude_angles	[ENTITY_TYPE_CAMERA]	  			  		  		= set_local_attitude_angles;
	fn_set_local_entity_attitude_angles			[ENTITY_TYPE_CAMERA]		  				  		= set_local_attitude_angles;
	fn_get_local_entity_attitude_angles			[ENTITY_TYPE_CAMERA]							 	= get_local_attitude_angles;
	fn_get_local_entity_float_value				[ENTITY_TYPE_CAMERA][FLOAT_TYPE_HEADING]	= get_local_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_CAMERA][FLOAT_TYPE_PITCH]		= get_local_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_CAMERA][FLOAT_TYPE_ROLL]		= get_local_float_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
