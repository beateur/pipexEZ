
#include "pipex.h"
#include <stdio.h>

/*
	fd = open("./pouet", O_RDWR);
	dup2(fd, 0);
	char *args[3];
	args[0] = "/bin/wc";
	args[1] = "-l";
	args[2] = NULL;
	execve(args[0], args, NULL);
	return (0);
*/

void	fork_function(int *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		write(2, "FORK ERROR\n", 11);
		exit(1);
	}
}

size_t ft_strlen(const char *s)
{
	    int len = 0;
	    while (1)
	    {
	        unsigned x = *(unsigned*)s;
	        if((x & 0xFF) == 0) return len;
	        if((x & 0xFF00) == 0) return len + 1;
	        if((x & 0xFF0000) == 0) return len + 2;
	        if((x & 0xFF000000) == 0) return len + 3;
	        s += 4, len += 4;
	    }
}

int	open_file(char *filename, int mode)
{
		if (mode)
		{
			if (access(filename, F_OK))
			{
				write(2, "pipex: ", 7);
				write(2, filename, ft_strlen(filename));
				write(2, ", no such file or directory\n", 28);
				return (-1);
			}
			return (open(filename, O_RDONLY));
		}
		else
			return (open(filename, O_CREAT | O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
}

int		ft_strstr_index(char *str, char *tofind, int start)
{
	int		index;

	index = -1;
	if (ft_strlen(str) <= start)
		return (0);
	while (tofind[++index])
		if (str[index + start] != tofind[index])
			return (0);
	return (1);
}

void 	ft_strdel(char **ap)
{
	if (ap)
	{
		if (*ap)
		{
			free(*ap);
			*ap = NULL;
		}
	}
}

int	exit_program(t_pipex *pipex, int ret)
{
	// free cmd
	return (ret);
}

char 	**split_protection(char to_split, char **str, t_pipex *pipex)
{
	char	**ret;

	ret = ft_split(*str, ':');
	if (!ret)
	{
		ft_strdel(str);
		return (exit_program(pipex, 1));
	}
	return (ret);
}

void	parse_path(t_pipex *pipex, char *paths)
{
	char	*path;
	char	**splited;
	int		i;

	path = NULL;
	splited = split_protection(':', &paths, pipex);
	i = -1;
	while (splited[++i])
	{
		pipex->bin = NULL;
		path = ft_strjoin(splited[i], "/");
		pipex->bin = ft_strjoin(path, pipex->cmd[0]);
		fprintf(stderr, "for %s bin: %s\n", splited[i], pipex->bin);
		ft_strdel(path);
		path = NULL;
		if (!access(pipex->bin, F_OK | X_OK))
		{
			//free splited
			break ;
		}
		ft_strdel(pipex->bin);
	}
	// free splited
}

void 	get_path(char **env, t_pipex *pipex)
{
	int		i_env;

	i_env = -1;
	while (env[++i_env])
	{
		if (ft_strstr_index(env[i_env], "PATH=", 0))
			parse_path(pipex, env[i_env] + 5);
	}
}

void	exec(t_pipex *pipex, char **env, int parent)
{
	int		ret;

	get_path(env, pipex);
	ret = 0;
	if (parent)
	{
		ret = execve(pipex->bin, pipex->cmd, env);
		if (ret != -1)
			return ;
		write(2, "pipex: ", 6);
		write(2, pipex->cmd[0], ft_strlen(pipex->cmd[0]));
		write(2, ": command not found", 19);
	}
	else {
		ret = execve(pipex->bin, pipex->cmd, env);
		if (ret != -1)
			return ;
		write(2, "pipex: ", 7);
		write(2, pipex->cmd[0], ft_strlen(pipex->cmd[0]));
		write(2, ": command not found\n", 20);
	}
}

void 	process(t_pipex pipex, char **env, char **av)
{
	if (pipex.child_pid)
	{
		if (pipex.fd_infile != -1)
		{
			close(pipex.pipefd[0]);
			dup2(pipex.pipefd[1], 1);
			pipex.cmd = ft_split(av[2], ' ');
			exec(&pipex, env, 1);
		}
	}
	else
	{
		close(pipex.pipefd[1]);
		dup2(pipex.pipefd[0], 0);
		pipex.cmd = ft_split(av[3], ' ');
		exec(&pipex, env, 0);
	}
}

int	main (int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac == 5)
	{
		pipex.fd_infile = open_file(av[1], 1);
		pipex.fd_outfile = open_file(av[4], 0);
		dup2(pipex.fd_infile, 0);
		dup2(pipex.fd_outfile, 1);
		pipe(pipex.pipefd);
		fork_function(&pipex.child_pid);
		process(pipex, env, av);
		close(pipex.fd_outfile);
		close(pipex.fd_infile);
	}
	else
		write(2, "PIPEX USAGES: INFILE CMD1 CMD2 OUTFILE.\n", 40);
	return (0);
}
