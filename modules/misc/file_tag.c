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

#include "misc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

file_tag_variable_type
	*file_tag_variables;

//static int
	//last_enum;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
   //**tag_strings,
	*system_tag_strings [] =
   {
      "UNUSED",
      "INVALID",

		"BIND_KEY",
		"CALCULATE",
		"CALL",
		"CREATE_EVENT",
		"CREATE_TRIGGER",
		"CREATE_VARIABLE",
		"ECHO_MESSAGE",
		"ELSE",
		"END",
		"END_EVENT",
		"ENDIF",
		"END_WHILE",
		"EVENT",
		"FILENAME",
		"FLOAT",
		"IF",
		"INT",
		"KEY_CODE",
		"KEY_MODIFIER",
		"KEY_STATE",
		"LET",
		"PATH",
		"SET_VARIABLE",
		"START",
		"TYPE",
		"VALUE",
		"VARIABLE",
		"WHILE",

      "UNKNOWN",
   };

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_file_tag_system (void)
{

	file_tag_variable_type
		*destroy_file_tag_variable;

	//tag_strings = application_tag_array;

	//last_enum = application_last_enum - FILE_TAG_UNKNOWN; // FILE_TAG_APPLICATION_FIRST_TAG

	while (file_tag_variables)
	{

		destroy_file_tag_variable = file_tag_variables;

		file_tag_variables = file_tag_variables->next;

		if (destroy_file_tag_variable->name)
		{

			free (destroy_file_tag_variable->name);
		}

		free (destroy_file_tag_variable);
	}

	file_tag_variables = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_file_tag_system (void)
{

	initialise_file_tag_system ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SET FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_file_tag (FILE *file_ptr, const char *application_enums [], int tag)
{

   //debug_assert (file_ptr);

	if (tag < 0)
	{

		fprintf (file_ptr, "\n:%s ", system_tag_strings [-tag]);
	}
	else
	{

		fprintf (file_ptr, "\n:%s ", application_enums [tag]);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_file_int (FILE *file_ptr, int value)
{

   //debug_assert (file_ptr);

   fprintf (file_ptr, "%d ", value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_file_float (FILE *file_ptr, float value)
{

   //debug_assert (file_ptr);

   fprintf (file_ptr, "%.02f ", value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_file_string (FILE *file_ptr, const char *string)
{

   //debug_assert (file_ptr);

   fprintf (file_ptr, "%s\0 ", string);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_file_enum (FILE *file_ptr, const char *enum_strings [], int enum_value)
{

   //debug_assert (file_ptr);

   fprintf (file_ptr, "%s ", enum_strings [enum_value]);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_file_new_line (FILE *file_ptr, int count)
{

   //debug_assert (file_ptr);

	while (count)
	{

		fprintf (file_ptr, "\n");

		count --;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_file_comment (FILE *file_ptr, const char *string)
{

   //debug_assert (file_ptr);

	fprintf (file_ptr, "\n//%s", string);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_file_tag (const char *line, const char *application_enums [], int last_application_enum)
{

   int
      current_tag = last_application_enum;

   if (*line == ':')
   {

      line ++;

      current_tag = FILE_TAG_UNKNOWN;

      while (current_tag != FILE_TAG_INVALID)
      {

         if (strcmpi (line, system_tag_strings [current_tag]) == 0)
         {

            break;
         }

         current_tag ++;
      }

		if ((current_tag == FILE_TAG_INVALID) && (application_enums))
		{

			current_tag = 0; 
	
			while (current_tag != last_application_enum)
			{
	
				if (strcmpi (line, application_enums [current_tag]) == 0)
				{
	
					break;
				}
	
				current_tag ++;
			}
		}
   }

	#if DEBUG_MODULE

	//ASSERT ((current_tag > FILE_TAG_INVALID) && (current_tag < FILE_TAG_UNKNOWN));
	debug_log ("FILE_TAG: get_file_tag = %s", tag_strings [current_tag]);

	#endif

   return current_tag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_next_file_tag (FILE *file_ptr, const char *application_enums [], int last_application_enum)
{

   int
		c_count,
      last_c,
      c;

   char
      line [260];

   int
      current_tag = last_application_enum;

   memset (line, 0, 260);

   //
   // Search for next :
   //

	last_c = 0;

   while ((c = fgetc (file_ptr)) != EOF)
   {

		//
		// skip lines starting with comments '//'
		//

      if ((c == '/') && (last_c == '/'))
      {

         fgets (line, 256, file_ptr);

			memset (line, 0, 260);
      }
      else if ((c == ':') && (last_c != '\\'))
      {

         // read off :

         c = fgetc (file_ptr);

         break;
      }

      last_c = c;
   }

   //
   // Read in next tag
   //

	c_count = 0;

   while ((c != EOF) && (c != '\n') && (c != ' ') && (c != '=') && (c != '	'))
   {

		line [c_count] = c;

		c_count ++;

		if (c_count > sizeof (line))
		{

			debug_fatal ("FILE_TAG: tag too long %s", line);
		}

      c = fgetc (file_ptr);
   }

   //
   // Compare tag with enums
   //

	#if DEBUG_MODULE

	debug_log ("FILE_TAG: read in %s", line);

	#endif

   if (c != EOF)
   {

      current_tag = FILE_TAG_UNKNOWN;

		// search system tags

      while (current_tag != FILE_TAG_INVALID)
      {

         if (strcmpi (line, system_tag_strings [-current_tag]) == 0)
         {

            break;
         }

         current_tag ++;
      }

		// search application tags

		if ((current_tag == FILE_TAG_INVALID) && (application_enums))
		{

			current_tag = 0; 
	
			while (current_tag != last_application_enum)
			{
	
				if (strcmpi (line, application_enums [current_tag]) == 0)
				{
	
					break;
				}
	
				current_tag ++;
			}
		}
   }
	else
	{

		current_tag = FILE_TAG_END;
	}

	#if DEBUG_MODULE

	//ASSERT ((current_tag > FILE_TAG_INVALID) && (current_tag < FILE_TAG_UNKNOWN));
	debug_log ("FILE_TAG: get_next_file_tag = %s", tag_strings [current_tag]);

	#endif

   return current_tag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_next_file_tag (FILE *file_ptr, const char *application_enums [], int last_application_enum)
{

   int
		c_count,
      last_c = 0,
      c;

   char
      line [260];

   int
      current_tag = last_application_enum;

   memset (line, 0, 260);

   //
   // Search for next :
   //

   while ((c = fgetc (file_ptr)) != EOF)
   {

		//
		// skip lines starting with comments '//'
		//

      if ((c == '/') && (last_c == '/'))
      {

         fgets (line, 256, file_ptr);

			memset (line, 0, 260);
      }
      else if ((c == ':') && (last_c != '\\'))
      {

         // read off :

         c = fgetc (file_ptr);

         break;
      }

      last_c = c;
   }

   //
   // Read in next tag
   //

	c_count = 0;

   while ((c != EOF) && (c != '\n') && (c != ' ') && (c != '=') && (c != '	'))
   {

		line [c_count] = c;

		c_count ++;

		if (c_count > sizeof (line))
		{

			debug_fatal ("FILE_TAG: check tag too long");
		}

      c = fgetc (file_ptr);
   }

   //
   // Compare tag with enums
   //

   if (c != EOF)
   {

      current_tag = FILE_TAG_UNKNOWN;

		// search system tags

      while (current_tag != FILE_TAG_INVALID)
      {

         if (strcmpi (line, system_tag_strings [-current_tag]) == 0)
         {

            break;
         }

         current_tag ++;
      }

		if ((current_tag == FILE_TAG_INVALID) && (application_enums))
		{

			current_tag = 0;
	
			while (current_tag != last_application_enum)
			{
	
				if (strcmpi (line, application_enums [current_tag]) == 0)
				{
	
					break;
				}
	
				current_tag ++;
			}
		}

      fseek (file_ptr, -((int)strlen (line) + 3), SEEK_CUR);
   }

	#if DEBUG_MODULE

	//ASSERT ((current_tag > FILE_TAG_INVALID) && (current_tag < FILE_TAG_UNKNOWN));
	debug_log ("FILE_TAG: check_next_file_tag = %s", tag_strings [current_tag]);

	#endif

   return current_tag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_next_file_int (FILE *file_ptr)
{

	int
		c,
		c_count,
		number;

	char
		text [256];

	memset (text, 0, sizeof (text));

	c_count = 0;

	c = fgetc (file_ptr);

	while ((c != '.') && (c != ',') && (c != '\n') && (c != ' ') && (c != '	'))
	{

		text [c_count] = c;

		c_count ++;

		if (c_count > sizeof (text))
		{

			debug_fatal ("FILE_TAG: get next int too long");
		}

		c = fgetc (file_ptr);
	}

	number = atoi (text);

	#if DEBUG_MODULE

	debug_log ("FILE_TAG: get_next_file_int = %d", number);

	#endif

	return number;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_next_file_float (FILE *file_ptr)
{

	double
		digit,
		result;

	int
		c,
		sign = 1,
		level;

	//
	// skim off crap
	//

	c = fgetc (file_ptr);

	while ((!isdigit (c)) && (c != '-'))
	{

		c = fgetc (file_ptr);
	}

	//
	// interger part
	//

	if (c == '-')
	{

		sign = -1;

		c = fgetc (file_ptr);
	}

	result = 0.0;

	while ((c != '.') && (c != ',') && (c != '\n') && (c != ' ') && (c != '	'))
	{

		result *= 10.0;

		result += (float) (c - '0');

		c = fgetc (file_ptr);
	}

	//
	// factional part
	//

	if (c == '.')
	{

		level = 1;

		c = fgetc (file_ptr);
	
		while ((c != ',') && (c != '\n') && (c != ' '))
		{

			level *= 10;
	
			digit = (float) (c - '0');

			digit /= level;

			result += digit;
	
			c = fgetc (file_ptr);
		}
	}

	#if DEBUG_MODULE

	debug_log ("FILE_TAG: get_next_file_float = %f", (result * sign));

	#endif

	return (result * sign);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_next_file_paragraph (FILE *file_ptr, char *buffer, int size)
{

	int
		last_c,
		character,
		count;

	memset (buffer, 0, size);

	count = 0;

	size -= 1;

	last_c = 0;

	while (((character = fgetc (file_ptr)) != EOF) && (count < size))
	{

		if ((character == ':') && (last_c != '\\'))
		{

			// rewind file point to before the :
			fseek (file_ptr, -1, SEEK_CUR);

			break;
		}
	
		last_c = character;

		if (character != '\\')
		{
	
			buffer [count ++] = character;
		}
	}

	#if DEBUG_MODULE

	debug_log ("FILE_TAG: get_next_file_paragraph = %s, strlen (%d)", buffer, strlen (buffer));

	#endif

	buffer [count] = '\0';

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_next_file_string (FILE *file_ptr, char *buffer, int size)
{

	char
		*ptr;

	memset (buffer, 0, size);

	if (fgets (buffer, size - 1, file_ptr))
	{
	
		ptr = strchr (buffer, '\n');
	
		*ptr = '\0';

		#if DEBUG_MODULE

		debug_log ("FILE_TAG: get_next_file_string = %s, strlen (%d)", buffer, strlen (buffer));

		#endif
	
		return TRUE;
	}
	else
	{

		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_next_file_word (FILE *file_ptr, char *buffer, int size)
{

	int
		character,
		count;

	memset (buffer, 0, size);

	count = 0;

	while ((character = fgetc (file_ptr)) != EOF)
	{

		if ((character == ' ') || (character == ',') || (character == '\n') || (character == '	'))
		{

			break;
		}

		buffer [count++] = character;
	}

	#if DEBUG_MODULE

	debug_log ("FILE_TAG: get_next_file_string = %s, strlen (%d)", buffer, strlen (buffer));

	#endif

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_next_file_enum (FILE *file_ptr, const char *enum_strings [], int last_enum)
{

	int
		c,
		tag,
		c_count;

	char
		buffer [256];

	tag = 0;

	memset (buffer, 0, 256);

   //
   // Read in line
   //

	c = fgetc (file_ptr);

	c_count = 0;

   while ((c != EOF) && (c != '\n') && (c != ' ') && (c != ',') && (c != '	') && (c != ' ') && (c != ':'))
   {

		buffer [c_count] = c;

		c_count ++;

		if (c_count > sizeof (buffer))
		{

			debug_fatal ("FILE_TAG: get next enum too long");
		}

      c = fgetc (file_ptr);
   }

	if (c_count > 0)
	{
	
  		while (tag <= last_enum)
		{

         if (strcmpi (buffer, enum_strings [tag]) == 0)
         {

            break;
         }

			tag ++;
		}
	}
	else
	{

		tag = last_enum;
	}


	if (tag > last_enum)
	{

		debug_fatal ("FILE_TAG: unrecognised tag %s", buffer);
	}

	#if DEBUG_MODULE

	debug_log ("FILE_TAG: get_next_file_enum = %s (index = %d)", enum_strings [tag], tag);

	#endif

	return tag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void register_file_tag_variable (const char *variable_name, int *variable)
{

	int
		next_id;

	file_tag_variable_type
		*new_variable;

	//
	// check if variable already registered
	//

	next_id = 0;

	new_variable = file_tag_variables;

	while (new_variable)
	{

		if (strcmpi (new_variable->name, variable_name) == 0)
		{

			return;
		}

		next_id ++;

		new_variable = new_variable->next;
	}

	//
	// Register new variable
	//

	new_variable = (file_tag_variable_type *) malloc (sizeof (file_tag_variable_type));

	memset (new_variable, 0, sizeof (file_tag_variable_type));

	new_variable->name = (char *) malloc ((strlen (variable_name) + 1));

	sprintf (new_variable->name, "%s", variable_name);

	new_variable->variable = variable;

	new_variable->id = next_id;

	new_variable->next = file_tag_variables;

	#if DEBUG_MODULE

	debug_log ("FILE_TAG: registered new variable %s to value %d", variable_name, *variable);

	#endif

	file_tag_variables = new_variable;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unregister_file_tag_variable (const char *variable_name)
{

	file_tag_variable_type
		*variable,
		*last_variable;

	//
	// check if variable already registered
	//

	last_variable = NULL;

	variable = file_tag_variables;

	while (variable)
	{

		if (strcmpi (variable->name, variable_name) == 0)
		{

			break;
		}

		last_variable = variable;

		variable = variable->next;
	}

	if (variable)
	{
	
		if (last_variable)
		{
	
			last_variable->next = variable->next;
		}
		else
		{
	
			file_tag_variables = variable->next;
		}

		#if DEBUG_MODULE

		debug_log ("FILE_TAG: unregistered variable %s", variable_name);

		#endif
	
		if (variable->name)
		{
	
			free (variable->name);
		}

		free (variable);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int *get_file_tag_variable (const char *variable_name)
{

	file_tag_variable_type
		*variable;

	variable = file_tag_variables;

	while (variable)
	{

		if (strcmpi (variable_name, variable->name) == 0)
		{

			#if DEBUG_MODULE

			debug_log ("FILE_TAG: get_file_tag_variable %s", variable_name);

			#endif

			return variable->variable;
		}

		variable = variable->next;
	}

	#if DEBUG_MODULE

	debug_log ("FILE_TAG: get_file_tag_variable %s, not found", variable_name);

	#endif

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int if_file_tag_variable (const char *variable_name, const char *operator_, int value)
{

	int
		return_value,
		*variable;

	#if DEBUG_MODULE

	debug_log ("FILE_TAG: IF %s %s %d", variable_name, operator, value);

	#endif

	return_value = FALSE;

	switch (*operator_)
	{

		case '=':
		{

			variable = get_file_tag_variable (variable_name);

			if (variable)
			{
	
				if (*variable == value)
				{
	
					return_value = TRUE;
				}
			}

			break;
		}

		case '<':
		{

			variable = get_file_tag_variable (variable_name);

			if (variable)
			{
	
				if (*variable < value)
				{
	
					return_value = TRUE;
				}
			}

			break;
		}

		case '>':
		{

			variable = get_file_tag_variable (variable_name);

			if (variable)
			{
	
				if (*variable > value)
				{
	
					return_value = TRUE;
				}
			}

			break;
		}
	}

	return return_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int if_file_tag_operator (int value1, const char *operator_, int value2)
{

	int
		return_value;
		//*variable;

	#if DEBUG_MODULE

	debug_log ("FILE_TAG: IF %d %s %d", value1, *operator, value2);

	#endif

	return_value = FALSE;

	switch (*operator_)
	{

		case '=':
		{

			if (value1 == value2)
			{

				return_value = TRUE;
			}

			break;
		}

		case '<':
		{

			if (value1 < value2)
			{

				return_value = TRUE;
			}

			break;
		}

		case '>':
		{

			if (value1 > value2)
			{

				return_value = TRUE;
			}

			break;
		}

		default:
		{

			char
				log_string [256];

			sprintf (log_string, "FILE_TAG: unknown operator %c", operator_ [0]);
			debug_fatal (log_string);
		}
	}

	return return_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int set_file_tag_variable (const char *variable_name, int value)
{

	int
		*variable;

	variable = get_file_tag_variable (variable_name);

	if (variable)
	{

		#if DEBUG_MODULE

		debug_log ("FILE_TAG: set_file_tag_variable %s = %d", variable_name, value);

		#endif

		*variable = value;

		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_variable_id (const char *variable_name)
{

	file_tag_variable_type
		*variable;

	variable = file_tag_variables;

	while (variable)
	{

		if (strcmpi (variable_name, variable->name) == 0)
		{

			#if DEBUG_MODULE

			debug_log ("FILE_TAG: get_variable_id %s = %d", variable_name, variable->id);

			#endif

			return variable->id;
		}

		variable = variable->next;
	}

	return -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *get_variable_name (int id)
{

	file_tag_variable_type
		*variable;

	variable = file_tag_variables;

	while (variable)
	{

		if (variable->id == id)
		{

			#if DEBUG_MODULE

			debug_log ("FILE_TAG: get_variable_name id %d = %s", id, variable->name);

			#endif

			return variable->name;
		}

		variable = variable->next;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_operator_id (const char *name)
{

	#if DEBUG_MODULE

	debug_log ("FILE_TAG: get_operator_id %c", name [0]);

	#endif

	switch (*name)
	{

		case '=':
		{

			return FILE_TAG_EQUALS;
		}

		case '<':
		{
			return FILE_TAG_LESS_THAN;
		}

		case '>':
		{

			return FILE_TAG_GREATER_THAN;
		}
	}

	return -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char get_operator_name (int id)
{

	#if DEBUG_MODULE

	debug_log ("FILE_TAG: get_operator_name %d", id);

	#endif

	switch (id)
	{

		case FILE_TAG_EQUALS:
		{

			return '=';
		}

		case FILE_TAG_LESS_THAN:
		{

			return '<';
		}

		case FILE_TAG_GREATER_THAN:
		{

			return '>';
		}
	}

	return '\0';
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
