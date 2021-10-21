#ifndef PARSER_H
#define PARSER_H

FILE *open_file(char *filename);
map_t read_file(FILE *fp);
int count_rows(FILE *fp);
void close_file(FILE *fp);
map_t handle_file(char *filename);
char *get_row(char *line);
void validate_line_data(int max_line_count, char *line, FILE *fp,
		int line_number);
int in_array(char needle, char *haystack, unsigned int haystack_size);
char *concat(const char *s1, const char *s2);
void free_map(map_t *map);
#endif
