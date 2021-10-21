#include "../inc/maze.h"

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

