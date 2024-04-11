#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		f1;
	int		f2;
	int		end[2];
	pid_t	parent;
	char	*cmd1;
	char	*cmd2;
	char	*path_from_envp;
	char	**my_paths;
	char	**my_cmd_args;
	char	**my_cmd_args2;
	char	*my_line;
	//int		flag;
}	t_data;

/////////////////////////////////////////
int		pipex(t_data *data, char **av, char **envp);
int		child_process(t_data *data, char **envp);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
void	env_parser(t_data *data, char **envp, char **av);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *str, int c, size_t n);
char	**ft_split(const char *s, char c);
int		parent_process(t_data *data, char **envp);
char	*ft_strjoin(char const *s1, char const *s2);
char	*find_cmd(char *cmd, t_data *data);
void	free_matrix(char **matrix);
void	free_structure(t_data *data);
/////////////////////////////////////////

#endif
