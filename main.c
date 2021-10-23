
#include "pipex.h"

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

void	exec(t_pipex *pipex, char **env, int parent)
{
	int		ret;

	ret = 0;
	get_path(env, pipex);
	if (parent)
	{
		ret = execve(pipex->bin, pipex->cmd, env);
		if (ret != -1)
			return ;
		write(2, "pipex: ", 6);
		write(2, pipex->cmd[0], ft_strlen(pipex->cmd[0]));
		write(2, ": command not found\n", 20);
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

void init_pipex(t_pipex *pipex, char **av)
{
	pipex->fd_infile = open_file(av[1], 1);
	pipex->fd_outfile = open_file(av[4], 0);
	pipex->bin = NULL;
	pipex->cmd = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac == 5)
	{
		init_pipex(&pipex, av);
		dup2(pipex.fd_infile, 0);
		dup2(pipex.fd_outfile, 1);
		pipe(pipex.pipefd);
		fork_function(&pipex.child_pid);
		process(pipex, env, av);
		close(pipex.fd_outfile);
		close(pipex.fd_infile);
		exit_program(&pipex);
	}
	else
		write(2, "PIPEX USAGES: INFILE CMD1 CMD2 OUTFILE.\n", 40);
	return (0);
}
