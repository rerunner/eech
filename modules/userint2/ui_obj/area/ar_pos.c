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

#include "userint2.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_x (ui_object *obj, float x)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	//if (area->x != x)
	{
	
		area->x_end = x;
		area->x_start = x;
	
		set_ui_object_redraw (obj, TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_area_ui_object_x (ui_object *obj)
{
	
	area_ui_object
		*area;

	float
		x,
		px = 0;

	ui_object
		*parent;

	parent = get_ui_object_parent (obj);

	if (parent)
	{

		px = get_ui_object_x (parent);
	}

	area = (area_ui_object *) obj->data;

	x = area->x_start + ( get_ui_object_bounded_t_value (obj) * ( area->x_end - area->x_start ) );

	if (area->virtual_coords)
	{

		if (parent)
		{

			x *= get_ui_object_x_size (parent);
		}
		else
		{

			x *= get_screen_width (video_screen);
		}
	}

	return x + px;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_y (ui_object *obj, float y)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	//if (area->y != y)
	{
		
		area->y_end = y;
		area->y_start = y;
	
		set_ui_object_redraw (obj, TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_area_ui_object_y (ui_object *obj)
{
	
	area_ui_object
		*area;

	float
		y,
		py = 0;

	ui_object
		*parent;

	parent = get_ui_object_parent (obj);

	if (parent)
	{

		py = get_ui_object_y (parent);
	}

	area = (area_ui_object *) obj->data;

	y = area->y_start + (get_ui_object_bounded_t_value (obj) * (area->y_end - area->y_start));
						
	if (area->virtual_coords)
	{

		if (parent)
		{

			y *= get_ui_object_y_size (parent);
		}
		else
		{

			y *= get_screen_height (video_screen);
		}
	}

	return y + py;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_x_end (ui_object *obj, float x)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->x_end = x;

	set_ui_object_redraw (obj, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_area_ui_object_x_end (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return area->x_end;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_y_end (ui_object *obj, float y)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->y_end = y;

	set_ui_object_redraw (obj, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_area_ui_object_y_end (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return area->y_end;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_x_start (ui_object *obj, float x)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->x_start = x;

	set_ui_object_redraw (obj, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_area_ui_object_x_start (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return area->x_start;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_y_start (ui_object *obj, float y)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->y_start = y;

	set_ui_object_redraw (obj, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_area_ui_object_y_start (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return area->y_start;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_cx (ui_object *obj, float cx)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;
	
	area->cx = cx;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_area_ui_object_cx (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return area->cx;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_cy (ui_object *obj, float cy)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->cy = cy;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_area_ui_object_cy (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return area->cy;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_virtual_x (ui_object *obj, float x)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->virtual_coords = TRUE;

	area->x_end = x;
	area->x_start = x;

	set_ui_object_redraw (obj, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_area_ui_object_virtual_x (ui_object *obj)
{
	
	area_ui_object
		*area;

	float
		px = 0;

	ui_object
		*parent;

	if (get_ui_object_virtual_coords (obj))
	{

		// is this right ? check
	
		parent = get_ui_object_parent (obj);
	
		if (parent)
		{
	
			//px = get_ui_object_virtual_x (parent);
		}
	
		area = (area_ui_object *) obj->data;
	
		return area->x_start + px;
	}
	else
	{

		float
			x;

		ui_object
			*parent;
	
		parent = get_ui_object_parent (obj);
	
		if (parent)
		{
			
			x = (get_ui_object_x (obj) - get_ui_object_x (parent)) / get_ui_object_x_size (parent);
		}
		else
		{
			
			x = get_ui_object_x (obj) / get_screen_width (video_screen);
		}

		return x;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_virtual_y (ui_object *obj, float y)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->virtual_coords = TRUE;

	area->y_end = y;
	area->y_start = y;

	set_ui_object_redraw (obj, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_area_ui_object_virtual_y (ui_object *obj)
{
	
	area_ui_object
		*area;

	float
		py = 0;

	ui_object
		*parent;

	if (get_ui_object_virtual_coords (obj))
	{

		// is this right ? check
	
		parent = get_ui_object_parent (obj);
	
		if (parent)
		{
	
			//py = get_ui_object_virtual_y (parent);
		}
	
		area = (area_ui_object *) obj->data;
	
		return area->y_start + py;
	}
	else
	{

		float
			y;

		ui_object
			*parent;
	
		parent = get_ui_object_parent (obj);
	
		if (parent)
		{
			
			y = (get_ui_object_y (obj) - get_ui_object_y (parent)) / get_ui_object_y_size (parent);
		}
		else
		{

			y = get_ui_object_y (obj) / get_screen_height (video_screen);
		}

		return y;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_area_ui_object_position_functions (ui_object_types type)
{
	
	fn_set_ui_object_x [type] = set_area_ui_object_x;

	fn_get_ui_object_x [type] = get_area_ui_object_x;


	fn_set_ui_object_y [type] = set_area_ui_object_y;

	fn_get_ui_object_y [type] = get_area_ui_object_y;

	
	fn_set_ui_object_x_end [type] = set_area_ui_object_x_end;

	fn_get_ui_object_x_end [type] = get_area_ui_object_x_end;


	fn_set_ui_object_y_end [type] = set_area_ui_object_y_end;

	fn_get_ui_object_y_end [type] = get_area_ui_object_y_end;

	
	fn_set_ui_object_x_start [type] = set_area_ui_object_x_start;

	fn_get_ui_object_x_start [type] = get_area_ui_object_x_start;


	fn_set_ui_object_y_start [type] = set_area_ui_object_y_start;

	fn_get_ui_object_y_start [type] = get_area_ui_object_y_start;

	
	fn_set_ui_object_cx [type] = set_area_ui_object_cx;

	fn_get_ui_object_cx [type] = get_area_ui_object_cx;


	fn_set_ui_object_cy [type] = set_area_ui_object_cy;

	fn_get_ui_object_cy [type] = get_area_ui_object_cy;
	

	fn_set_ui_object_virtual_x [type] = set_area_ui_object_virtual_x;

	fn_get_ui_object_virtual_x [type] = get_area_ui_object_virtual_x;


	fn_set_ui_object_virtual_y [type] = set_area_ui_object_virtual_y;

	fn_get_ui_object_virtual_y [type] = get_area_ui_object_virtual_y;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
