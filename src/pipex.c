#include "../includes/pipex.h"

static int	open_file(char *file_name, char **envp, int flags, int mode)
{
	char	*new_path;
	int		fd;

	while (*envp)
	{
		if (ft_strncmp("PWD=", *envp, 4) == 0)
		{
			new_path = ft_strjoin(*envp + 4, file_name);
			break ;
		}
		else
			envp++;
	}
	if ((flags == (O_RDWR | O_CREAT | O_TRUNC)) || ft_access(new_path))
	{
		if (mode)
			fd = open(new_path, flags, S_IREAD | S_IWRITE);
		else
			fd = open(new_path, flags, S_IREAD);
		free(new_path);
		return (fd);
	}
	free(new_path);
	return (-1);
}

char	*get_path(char **envp, char **cmd)
{
	char	**paths;
	char	*path;

	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
		{
			paths = ft_split(*envp + 5, ':');
			while (*paths)
			{
				path = ft_strjoin(*paths, *cmd);
				if (access(path, F_OK) == 0)
					return (path_finder(&path, &paths));
				free(path);
				paths++;
			}
			return (NULL);
		}
		else
			envp++;
	}
	return (NULL);
}

static void	call_child(int *p, char **argv, char **envp)
{
	int		in;
	char	**cmd;
	char	*path;

	close(p[0]);
	dup2(p[1], 1);
	close(p[1]);
	in = open_file(argv[1], envp, O_RDONLY, 0);
	if (in == -1)
		exit(0);
	dup2(in, 0);
	cmd = ft_split(argv[2], ' ');
	path = get_path(envp, cmd);
	if (path == NULL || execve(path, cmd, envp) == -1)
	{
		ft_putstr_fd("Command not found: \n", 2);
		ft_putstr_fd(path, 2);
		exit(0);
	}
}

static void	call_father(int *p, char **argv, char **envp)
{
	int		out;
	char	**cmd;
	char	*path;

	out = open_file(argv[4], envp, O_RDWR | O_CREAT | O_TRUNC, 1);
	wait(0);
	close(p[1]);
	dup2(p[0], 0);
	close(p[0]);
	dup2(out, 1);
	cmd = ft_split(argv[3], ' ');
	path = get_path(envp, cmd);
	if (path == NULL || execve(path, cmd, envp) == -1)
	{
		ft_putstr_fd("Command not found\n", 2);
		ft_putstr_fd(path, 2);
		exit(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		p_fd[2];

	if (argc != 5)
	{
		ft_putstr_fd("Usage : ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (0);
	}
	if (pipe(p_fd) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Fork failed\n", 2);
		return (0);
	}
	if (pid == 0)
		call_child(p_fd, argv, envp);
	else
		call_father(p_fd, argv, envp);
	return (0);
}
