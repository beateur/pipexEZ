#include "pipex.h"

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

void	free_array(char **arr)
{
	int	i;

	i = -1;
	if (arr)
		while (arr[++i])
			ft_strdel(&(arr[i]));
}

void	exit_program(t_pipex *pipex)
{
	free_array(pipex->cmd);
	if (pipex->bin)
		ft_strdel(&pipex->bin);
}
