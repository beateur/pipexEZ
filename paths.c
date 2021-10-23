#include "pipex.h"

static void	parse_path(t_pipex *pipex, char *paths)
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
		ft_strdel(&path);
		path = NULL;
		if (!access(pipex->bin, F_OK | X_OK))
		{
			free_array(splited);
			break ;
		}
		ft_strdel(&pipex->bin);
	}
	free_array(splited);
}

void 	get_path(char **env, t_pipex *pipex)
{
	int		i_env;

	i_env = -1;
	while (env[++i_env])
	{
		if (ft_strstr_index(env[i_env], "PATH=", 0))
		{
			parse_path(pipex, env[i_env] + 5);
			break ;
		}
	}
}
