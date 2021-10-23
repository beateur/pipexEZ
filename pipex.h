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
void 			get_path(char **env, t_pipex *pipex);
char 			**split_protection(char to_split, char **str, t_pipex *pipex);
void 			ft_strdel(char **ap);
void			free_array(char **arr);
void			exit_program(t_pipex *pipex);
int				ft_strstr_index(char *str, char *tofind, int start);
int				open_file(char *filename, int mode);
size_t 		ft_strlen(const char *s);
void			fork_function(int *pid);
int				main(int ac, char **av, char **env);

#endif
