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

eo_params
	hind_flir,
	hind_llltv;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_hind_eo (void)
{
	eo_sensor							= TARGET_ACQUISITION_SYSTEM_FLIR;

	eo_azimuth							= rad (0.0);
	eo_min_azimuth						= rad (-30.0);
	eo_max_azimuth						= rad (30.0);
	eo_elevation						= rad (0.0);
	eo_min_elevation					= rad (-30.0);
	eo_max_elevation					= rad (10.0);
	eo_max_visual_range				= 5000.0,
	eo_ground_stabilised					= 0;

	hind_flir.field_of_view		= EO_FOV_WIDE;
	hind_flir.min_field_of_view	= EO_FOV_MEDIUM;
	hind_flir.max_field_of_view	= EO_FOV_WIDE;

	hind_llltv.field_of_view		= EO_FOV_WIDE;
	hind_llltv.min_field_of_view	= EO_FOV_MEDIUM;
	hind_llltv.max_field_of_view	= EO_FOV_WIDE;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_hind_eo (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_hind_eo_centred_viewpoint (viewpoint *vp)
{
	entity
		*source;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search;

	ASSERT (vp);

	source = get_gunship_entity ();

	inst3d = (object_3d_instance *) get_local_entity_ptr_value (source, PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	get_local_entity_vec3d (source, VEC3D_TYPE_POSITION, &inst3d->vp.position);

	get_local_entity_attitude_matrix (source, inst3d->vp.attitude);

	search.search_depth = 0;
	search.search_object = inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_OPTICS;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		get_3d_sub_object_world_viewpoint (search.result_sub_object, vp);
	}
	else
	{
		//
		// can happpen if the object is being destroyed
		//

		memcpy (&vp->position, &inst3d->vp.position, sizeof (vec3d));
	}

	memcpy (&vp->attitude, &inst3d->vp.attitude, sizeof (matrix3x3));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void inc_eo_field_of_view (eo_params *eo)
{
	ASSERT (eo);

	if (eo->field_of_view < eo->max_field_of_view)
	{
		eo->field_of_view++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void fast_inc_eo_field_of_view (eo_params *eo)
{
	ASSERT (eo);

	eo->field_of_view = eo->max_field_of_view;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void dec_eo_field_of_view (eo_params *eo)
{
	ASSERT (eo);

	if (eo->field_of_view > eo->min_field_of_view)
	{
		eo->field_of_view--;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void fast_dec_eo_field_of_view (eo_params *eo)
{
	ASSERT (eo);

	eo->field_of_view = eo->min_field_of_view;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_hind_eo (eo_params *eo)
{
	float
		fine_slew_rate,
		medium_slew_rate,
		mouse_slew_rate, // Jabberwock 030930
		coarse_slew_rate;

	ASSERT (eo);

	////////////////////////////////////////
	//
	// field of view
	//
	////////////////////////////////////////

	while (single_target_acquisition_system_inc_range_key)
	{
		dec_eo_field_of_view (eo);

		single_target_acquisition_system_inc_range_key--;
	}

	while (single_target_acquisition_system_inc_range_fast_key)
	{
		fast_dec_eo_field_of_view (eo);

		single_target_acquisition_system_inc_range_fast_key--;
	}

	////////////////////////////////////////

	while (single_target_acquisition_system_dec_range_key)
	{
		inc_eo_field_of_view (eo);

		single_target_acquisition_system_dec_range_key--;
	}

	while (single_target_acquisition_system_dec_range_fast_key)
	{
		fast_inc_eo_field_of_view (eo);

		single_target_acquisition_system_dec_range_fast_key--;
	}

	////////////////////////////////////////

	while (toggle_ground_stabilisation_key)
	{
		toggle_ground_stabilisation ();

		toggle_ground_stabilisation_key--;
	}

	////////////////////////////////////////

	////////////////////////////////////////
	//
	// slew optics
	//
	////////////////////////////////////////

	switch (eo->field_of_view)
	{
		////////////////////////////////////////
		case EO_FOV_NARROW:
		////////////////////////////////////////
		{
			fine_slew_rate = rad (0.05) * get_delta_time ();

			medium_slew_rate = rad (0.25) * get_delta_time ();

			mouse_slew_rate = rad (0.6) * get_delta_time ();	// Jabberwock 030930

			coarse_slew_rate = rad (1.0) * get_delta_time ();

			break;
		}
		////////////////////////////////////////
		case EO_FOV_MEDIUM:
		////////////////////////////////////////
		{
			fine_slew_rate = rad (0.5) * get_delta_time ();

			medium_slew_rate = rad (2.5) * get_delta_time ();

			mouse_slew_rate = rad (6) * get_delta_time ();	// Jabberwock 030930

			coarse_slew_rate = rad (10.0) * get_delta_time ();

			break;
		}
		////////////////////////////////////////
		case EO_FOV_WIDE:
		////////////////////////////////////////
		{
			fine_slew_rate = rad (4.0) * get_delta_time ();

			medium_slew_rate = rad (20.0) * get_delta_time ();

			mouse_slew_rate = rad (48) * get_delta_time ();	// Jabberwock 030930

			coarse_slew_rate = rad (80.0) * get_delta_time ();

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid field of view = %d", eo->field_of_view);

			break;
		}
	}

	////////////////////////////////////////

	keyboard_slew_eo_system(fine_slew_rate, medium_slew_rate, coarse_slew_rate);

	while (single_target_acquisition_system_select_next_target_key)
	{
		select_next_eo_target ();

		single_target_acquisition_system_select_next_target_key--;
	}

	////////////////////////////////////////

	while (single_target_acquisition_system_select_previous_target_key)
	{
		select_previous_eo_target ();

		single_target_acquisition_system_select_previous_target_key--;
	}

// Jabberwock 031107 Designated targets

	while (single_target_acquisition_system_select_next_designated_key)
	{
		select_next_designated_eo_target ();

		single_target_acquisition_system_select_next_designated_key--;
	}

	////////////////////////////////////////

	while (single_target_acquisition_system_select_previous_designated_key)
	{
		select_previous_designated_eo_target ();

		single_target_acquisition_system_select_previous_designated_key--;
	}

	 // POV flir control thealx 130215
		
		if ( (command_line_eo_pan_joystick_index == -1) && (command_line_mouse_look == MOUSELOOK_ON))
		{						
			float
				ROTATE_RATE;

			ROTATE_RATE = (float) command_line_mouse_look_speed / 5.0;

			if (joystick_pov_left)
			{
				eo_azimuth -= ROTATE_RATE * get_delta_time () * coarse_slew_rate * command_line_mouse_look_speed;

				eo_azimuth = max (eo_azimuth, eo_min_azimuth);
			}
			else if (joystick_pov_right)
			{
				eo_azimuth += ROTATE_RATE * get_delta_time () * coarse_slew_rate * command_line_mouse_look_speed;

				eo_azimuth = min (eo_azimuth, eo_max_azimuth);
			}

			if (joystick_pov_up)
			{
				eo_elevation += ROTATE_RATE * get_delta_time () * coarse_slew_rate * command_line_mouse_look_speed;

				eo_elevation = min (eo_elevation, eo_max_elevation);
			}
			else if (joystick_pov_down)
			{
				eo_elevation -= ROTATE_RATE * get_delta_time () * coarse_slew_rate * command_line_mouse_look_speed;

				eo_elevation = max (eo_elevation, eo_min_elevation);
			}
		}
  
		// Jabberwock 030930 - Mouse FLIR control functions
		// Improved mouse control thealx 130215

		else if ((command_line_eo_pan_joystick_index == -1)&&(command_line_mouse_look != MOUSELOOK_ON))
		{
			static int previous_mouse_update_flag = 1;
			float dh, dp;

			if (previous_mouse_update_flag != get_mouse_update_flag())
			{
				dh = get_mouse_move_delta_x() / 5000.0 * mouse_slew_rate * command_line_mouse_look_speed;
				dp = get_mouse_move_delta_y() / 5000.0 * mouse_slew_rate * command_line_mouse_look_speed;

				previous_mouse_update_flag = get_mouse_update_flag();

				eo_azimuth += dh;
				eo_azimuth = bound (eo_azimuth, eo_min_azimuth, eo_max_azimuth);
				eo_elevation -= dp;
				eo_elevation = bound (eo_elevation, eo_min_elevation, eo_max_elevation);
			}

		}

			// "Old EO" Zoom control by Joystick thealx 130215 

		if (command_line_eo_zoom_joystick_index != -1)
		{
			int pos = get_joystick_axis (command_line_eo_zoom_joystick_index, command_line_eo_zoom_joystick_axis);

			if (pos < -5500)
			{
				eo->field_of_view = eo->min_field_of_view;
			}
			else if ((pos > -5500) && (pos < 5000))
			{
				eo->field_of_view = eo->min_field_of_view + 1;
			}
			else if (pos > 5000)
			{
				eo->field_of_view = eo->max_field_of_view;
			}
		}
		else if ((command_line_mouse_look != MOUSELOOK_ON) || (command_line_field_of_view_joystick_index != -1))
		{
				while (mouse_wheel_down)
				{

								 if (eo->field_of_view < eo->max_field_of_view)
								{
										eo->field_of_view++;
								}

						 mouse_wheel_down--;
				}

				while (mouse_wheel_up)
				{
								 if (eo->field_of_view > eo->min_field_of_view)
								{
										eo->field_of_view--;
								}

						mouse_wheel_up--;
				}
		}

	// Jabberwock 030930 ends

	joystick_slew_eo_system(medium_slew_rate);

	////////////////////////////////////////
	// loke 030322
	// handle the ground stabilisation

	if (eo_ground_stabilised)
	{
		handle_ground_stabilisation();
	}

	////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void centre_hind_eo (void)
{
	eo_azimuth = rad (0.0);

	eo_elevation = rad (0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_hind_eo (object_3d_instance *inst3d)
{
	object_3d_sub_object_search_data
		search;

	ASSERT (inst3d);

	search.search_depth = 0;
	search.search_object = inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_OPTICS;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->relative_heading = eo_azimuth;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
