#include "../inc/err.h"

void free_paths_exit(char **paths, size_t amount)
{
	size_t i = 0;
	while (i < amount) {
		if (paths[i])
			free(paths[i]);
		else
			break;
		i++;
	}
	free(paths);
	exit(1);
}

void free_paths(char **paths, size_t amount)
{
	size_t i = 0;
	while (i < amount) {
		if (paths[i])
			free(paths[i]);
		else
			break;
		i++;
	}
	free(paths);
}