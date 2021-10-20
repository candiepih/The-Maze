#include "../inc/maze.h"

/**
 * open_file - opens a file
 * @filename: string pointer to file name
 * Return: File pointer
 */
FILE *open_file(char *filename)
{
	FILE *fp = NULL;

	fp = fopen(filename, "r");
	if (!fp)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	return (fp);
}

/**
 * count_rows - counts the number of lines in a file
 * @fp: File pointer
 * Return: number of lines in file
 */
int count_rows(FILE *fp)
{
	char ch;
	int lines = 0;

	while(!feof(fp))
	{
		ch = fgetc(fp);
		if(ch == '\n')
		{
			lines++;
		}
	}

	fseek(fp, 0, SEEK_SET);

	return (lines + 1);
}

/**
 * read_file - reads the content of a file
 * @fp: File pointer
 * Return: map_t data structure containing map data
 */
map_t read_file(FILE *fp)
{
	size_t line_count = 0;
	char *line = NULL;
	map_t map = {NULL, 0, 0};
	unsigned int line_number = 0, line_length_flag = 0;
	char *dup_line = NULL;

	map.rows = count_rows(fp);
	map.arr = malloc(sizeof(char *) * map.rows);

	while ((getline(&line, &line_count, fp)) != -1)
	{
		dup_line = strtok(strdup(line), "\n");
		if (line_length_flag == 0)
		{
			map.columns = strlen(dup_line);
			line_length_flag++;
		}
		validate_line_data(map.columns, dup_line, fp, (line_number + 1));
		map.arr[line_number] = dup_line;
		line_number++;
	}
	free(line);
	fseek(fp, 0, SEEK_SET);

	return (map);
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
void validate_line_data(int max_line_count, char *line, FILE *fp, int line_number)
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
		printf("Error line No. %d: The columns of the map should be equal.\n", line_number);
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
 * close_file - closes an opened file
 * @fp: File pointer
 * Return: nothing
 */
void close_file(FILE *fp)
{
	if (fp)
		fclose(fp);
}

/**
 * handle_file - calls all file handling functions
 * @filename: string pointer to file name
 * Return: map_t datastructure of map information
 */
map_t handle_file(char *filename)
{
	FILE *fp = NULL;
	map_t map;

	fp = open_file(filename);
	map = read_file(fp);
	close_file(fp);

	return (map);
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}