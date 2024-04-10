#include "pipex.h"

char	*find_cmd(char *cmd, t_data *data)
{
	int i = 0;
	char *tmp;
	char *holder;

	while (data->my_paths[i])
	{
		tmp = ft_strjoin(data->my_paths[i], "/");
		holder = ft_strjoin(tmp, cmd);
		if (access(holder, X_OK) == 0)
			return (free(tmp), holder);
		free(tmp);
		free(holder);
		i++;
	}
	write(2, "command not found : ", 20);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	// free_matrix(data->my_paths);
	// if (data->my_cmd_args != NULL)
	// 	free_matrix(data->my_cmd_args);
	// if (data->my_cmd_args2 != NULL)
	// 	free_matrix(data->my_cmd_args2);
	// free_structure(data);
	return (NULL);
}


static char *retrieve_line(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			return (ft_strdup(envp[i])); //	return (ft_strdup(&envp[i][5]));
		i++;
	}
	return (NULL);
}

void	env_parser(t_data *data, char **envp, char **av)
{
	data->my_line = retrieve_line(envp);
	data->path_from_envp = ft_substr(data->my_line, 5, 500);
	data->my_paths = ft_split(data->path_from_envp, ':');
	data->my_cmd_args = ft_split(av[2], 32);
	data->my_cmd_args2 = ft_split(av[3], 32);
}
