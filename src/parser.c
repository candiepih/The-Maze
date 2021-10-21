#include "../inc/maze.h"



/**
 * count_rows - counts the number of lines in a file
 * @fp: File pointer
 * Return: number of lines in file
 */
int count_rows(FILE *fp)
{
	char ch;
	int lines = 0;

	while (!feof(fp))
	{
		ch = fgetc(fp);
		if (ch == '\n')
		{
			lines++;
		}
	}

	fseek(fp, 0, SEEK_SET);

	return (lines + 1);
}



/**
 * in_array - checks if a certain value is in an array
 * @needle: value to look for in array
 * @haystack: Pointer to string
 * @haystack_size: length of the array @haystack
 * Return: (0) if value not in array otherwise (1) if found in array
 */
int in_array(char needle, char *haystack, unsigned int haystack_size)
{
	unsigned int i;

	for (i = 0; i < haystack_size; i++)
	{
		if (haystack[i] == needle)
			return (1);
	}

	return (0);
}

/**
 * validate_line_data - check for errors in lines in file
 * @max_line_count: check maximum limit to lines length
 * @line: the line to check it's validity
 * @fp: File pointer
 * @line_number: current line number checking
 * Return: nothing
 */
void validate_line_data(int max_line_count, char *line, FILE *fp,
		int line_number)
{
	char valid_digits[] = {'0', '1'};
	int i;
	unsigned int line_length = strlen(line);

	if (!line)
		return;
	if (line_length != (unsigned int)max_line_count)
	{
		free(line);
		close_file(fp);
		printf("Error line No. %d: The columns of the map should be equal.\n",
				line_number);
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < max_line_count; i++)
	{
		if ((in_array(line[i], valid_digits, max_line_count)) == 0)
		{

			printf("Error line No. %d: Invalid map values found.\n", line_number);
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * concat - concatenates two strings
 * @s1: destination string
 * @s2: source string to concatenate
 * Return: New string with @s1 and @s2
 */
char *concat(const char *s1, const char *s2)
{
	char *result = NULL;

	result = malloc(strlen(s1) + strlen(s2) + 1);
	if (!result)
		return (NULL);

	strcpy(result, s1);
	strcat(result, s2);
	return (result);
}

/**
 * free_map - frees 2D map of map_t
 * @map: data structure of map_t containing map information
 * Return: nothing
 */
void free_map(map_t *map)
{
	int i;

	for (i = 0; i < map->rows; i++)
		free(map->arr[i]);
	free(map->arr);
}
