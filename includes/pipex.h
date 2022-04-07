#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>

int		ft_strlen(char *str);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
int		ft_access(char *path);
char	*path_finder(char **path, char ***paths);

#endif
