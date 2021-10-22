#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex {
		int			fd_outfile;
		int			fd_infile;
		int			pipefd[2];
		pid_t		child_pid;
		char		*bin;
		char		**cmd;
}			t_pipex;

char			**ft_split(char const *s, char c);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);

#endif
