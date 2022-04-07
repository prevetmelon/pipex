#include "../includes/pipex.h"

char	*path_finder(char **path, char ***paths)
{
	while (**paths)
		(*paths)++;
	(*paths)--;
	while (*(*paths))
		free(*(*paths)--);
	(*paths)++;
	free(*paths);
	return (*path);
}
