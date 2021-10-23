#include "pipex.h"

char 	**split_protection(char to_split, char **str, t_pipex *pipex)
{
	char	**ret;

	ret = ft_split(*str, to_split);
	if (!ret)
	{
		ft_strdel(str);
		exit_program(pipex);
		return (NULL);
	}
	return (ret);
}
