#include "../includes/pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char			*dst;
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	dst = (char *)malloc(sizeof(*dst) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!dst)
		return (NULL);
	while (*s1 != '\0')
		dst[i++] = *s1++;
	dst[i++] = '/';
	while (*s2 != '\0')
		dst[i++] = *s2++;
	dst[i] = '\0';
	return (dst);
}

int	ft_strncmp (char *s1, char *s2, size_t n)
{
	unsigned char	*s11;
	unsigned char	*s22;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (*s11 == '\0' && *s22 == '\0')
			break ;
		if (*s11 != *s22)
			return (*s11 - *s22);
		s11++;
		s22++;
		n--;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int	ft_access(char *path)
{
	if (access(path, F_OK) == -1 || access(path, R_OK) == -1
		|| access(path, W_OK) == -1)
	{
		ft_putstr_fd("File error\n", 2);
		return (0);
	}
	return (1);
}
