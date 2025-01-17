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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "userint2.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_state (ui_object *obj, int flag)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	if (area->state != flag)
	{
							
		area->state = flag;

		set_ui_object_redraw (obj, TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_state (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->state);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_drawable (ui_object *obj, int flag)
{

	ui_object
		*parent;
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	if (area->drawable!= flag)
	{
							
		area->drawable = flag;
	
  		if (area->drawable)
		{

			set_ui_object_redraw (obj, TRUE);
		}
		else
		{

			parent = get_ui_object_parent (obj);

			if (parent)
			{
	
				set_ui_object_redraw (parent, TRUE);
	
				while ((parent) && (get_ui_object_clear (parent)))
				{
	
					set_ui_object_redraw (parent, TRUE);
	
					parent = get_ui_object_parent (parent);
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_drawable (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->drawable);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_autosize (ui_object *obj, int flag)
{

	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;
	
  	area->autosize = flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_autosize (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->autosize);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_redraw (ui_object *obj, int flag)
{

	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	if (area->child)
	{

		set_ui_object_redraw_all (area->child, TRUE);
	}

	area->redraw = MAX_UI_REDRAW_NUMBER;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_redraw (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->redraw);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_area_ui_object_redraw_all (ui_object *obj, int flag)
{

	area_ui_object
		*area;

	if (obj)
	{
	
		area = (area_ui_object*) obj->data;
	
		if (area->child)
		{
	
			set_ui_object_redraw_all (area->child, flag);
		}
	
		if (area->next)
		{
	
			set_ui_object_redraw_all (area->next, flag);
		}

		if (flag)
		{
	
			area->redraw = MAX_UI_REDRAW_NUMBER;
		}
		else
		{

			area->redraw = 0;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_moveable (ui_object *obj, int flag)
{

	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	if (obj)
	{
	
		area = (area_ui_object*) obj->data;
	
		if (area->child)
		{
	
			set_ui_object_moveable (area->child, flag);
		}
	
		if (area->next)
		{
	
			set_ui_object_moveable (area->next, flag);
		}
	
		area->moveable = flag;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_moveable (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->moveable);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_resizeable (ui_object *obj, int flag)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->resizeable = flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_resizeable (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->resizeable);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_list_item (ui_object *obj, int flag)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->list_item = flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_list_item (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->list_item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_item_number (ui_object *obj, int number)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->item_number = number;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_item_number (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->item_number);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_item_number2 (ui_object *obj, int number)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->item_number2 = number;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_item_number2 (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->item_number2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_clear (ui_object *obj, int flag)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->clear = flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_clear (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->clear);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_user_flag1 (ui_object *obj, int value)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->user_flag1 = value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_user_flag1 (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->user_flag1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_user_flag2 (ui_object *obj, int value)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->user_flag2 = value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_user_flag2 (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->user_flag2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_user_flag3 (ui_object *obj, int value)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->user_flag3 = value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_user_flag3 (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->user_flag3);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_user_flag4 (ui_object *obj, int value)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->user_flag4 = value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_user_flag4 (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->user_flag4);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_virtual_coords (ui_object *obj, int value)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->virtual_coords = value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_virtual_coords (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->virtual_coords);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_tool_tips_timer (ui_object *obj, int value)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->tool_tips_timer = value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_tool_tips_timer (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->tool_tips_timer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_highlightable (ui_object *obj, int flag)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->highlightable = flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_highlightable (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->highlightable);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_highlighted (ui_object *obj, int flag)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->highlighted = flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_highlighted (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->highlighted);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_t_value (ui_object *obj, float t)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->t = t;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_area_ui_object_t_value (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->t);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_time_length (ui_object *obj, int time)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->time_length = time;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_time_length (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->time_length);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_start_time (ui_object *obj, int start_time)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->start_time = start_time;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_start_time (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->start_time);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_offset_time (ui_object *obj, int offset_time)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	area->offset_time = offset_time;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_area_ui_object_offset_time (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object*) obj->data;

	return (area->offset_time);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_area_ui_object_flag_functions (ui_object_types type)
{

	fn_set_ui_object_state [type] 		= set_area_ui_object_state;

	fn_get_ui_object_state [type] 		= get_area_ui_object_state;

	fn_set_ui_object_drawable [type] 	= set_area_ui_object_drawable;

	fn_get_ui_object_drawable [type] 	= get_area_ui_object_drawable;

	fn_set_ui_object_autosize [type] 	= set_area_ui_object_autosize;

	fn_get_ui_object_autosize [type] 	= get_area_ui_object_autosize;

	fn_set_ui_object_redraw [type] 		= set_area_ui_object_redraw;

	fn_get_ui_object_redraw [type] 		= get_area_ui_object_redraw;

	fn_set_ui_object_redraw_all [type] 	= set_area_ui_object_redraw_all;

	fn_set_ui_object_moveable [type] 	= set_area_ui_object_moveable;

	fn_get_ui_object_moveable [type] 	= get_area_ui_object_moveable;

	fn_set_ui_object_resizeable [type] 	= set_area_ui_object_resizeable;

	fn_get_ui_object_resizeable [type] 	= get_area_ui_object_resizeable;

	fn_set_ui_object_list_item [type] 	= set_area_ui_object_list_item;

	fn_get_ui_object_list_item [type] 	= get_area_ui_object_list_item;

	fn_set_ui_object_item_number [type]	= set_area_ui_object_item_number;

	fn_get_ui_object_item_number [type] = get_area_ui_object_item_number;

	fn_set_ui_object_item_number2 [type]	= set_area_ui_object_item_number2;

	fn_get_ui_object_item_number2 [type] = get_area_ui_object_item_number2;

	fn_set_ui_object_clear [type] 		= set_area_ui_object_clear;

	fn_get_ui_object_clear [type] 		= get_area_ui_object_clear;

	fn_set_ui_object_user_flag1 [type] 	= set_area_ui_object_user_flag1;

	fn_get_ui_object_user_flag1 [type] 	= get_area_ui_object_user_flag1;

	fn_set_ui_object_user_flag2 [type] 	= set_area_ui_object_user_flag2;

	fn_get_ui_object_user_flag2 [type] 	= get_area_ui_object_user_flag2;

	fn_set_ui_object_user_flag3 [type] 	= set_area_ui_object_user_flag3;

	fn_get_ui_object_user_flag3 [type] 	= get_area_ui_object_user_flag3;

	fn_set_ui_object_user_flag4 [type] 	= set_area_ui_object_user_flag4;

	fn_get_ui_object_user_flag4 [type]	= get_area_ui_object_user_flag4;

	fn_set_ui_object_virtual_coords [type] = set_area_ui_object_virtual_coords;

	fn_get_ui_object_virtual_coords [type]	 = get_area_ui_object_virtual_coords;

	fn_set_ui_object_tool_tips_timer [type] = set_area_ui_object_tool_tips_timer;

	fn_get_ui_object_tool_tips_timer [type] = get_area_ui_object_tool_tips_timer;

	fn_set_ui_object_highlighted [type] = set_area_ui_object_highlighted;

	fn_get_ui_object_highlighted [type] = get_area_ui_object_highlighted;

	fn_set_ui_object_highlightable [type] = set_area_ui_object_highlightable;

	fn_get_ui_object_highlightable [type] = get_area_ui_object_highlightable;

	fn_set_ui_object_t_value [type] = set_area_ui_object_t_value;

	fn_get_ui_object_t_value [type] = get_area_ui_object_t_value;

	fn_set_ui_object_time_length [type] = set_area_ui_object_time_length;

	fn_get_ui_object_time_length [type] = get_area_ui_object_time_length;

	fn_set_ui_object_start_time [type] = set_area_ui_object_start_time;

	fn_get_ui_object_start_time [type] = get_area_ui_object_start_time;

	fn_set_ui_object_offset_time [type] = set_area_ui_object_offset_time;

	fn_get_ui_object_offset_time [type] = get_area_ui_object_offset_time;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
