#include "pipex.h"

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
      else if (access(filename, R_OK))
      {
        write(2, "pipex: permission denied: ", 26);
				write(2, filename, ft_strlen(filename));
        write(2, "\n", 1);
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
	if ((int)ft_strlen(str) <= start)
		return (0);
	while (tofind[++index])
		if (str[index + start] != tofind[index])
			return (0);
	return (1);
}
