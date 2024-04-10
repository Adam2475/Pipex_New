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
			return (holder);
		free(tmp);
		free(holder);
		i++;
	}
	// while (--i >= 0)
	// 	free(data->my_paths[i]);
	// free(data->my_paths);
	write(2, "command not found : ", 20);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	return (NULL);
}


static char *retrieve_line(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			return (ft_strdup(envp[i]));
		i++;
	}
	return (NULL);
}

void env_parser(t_data *data, char **envp, char **av)
{
	data->my_line = retrieve_line(envp);
	data->path_from_envp = ft_substr(data->my_line, 5, 500);
	//printf("%s\n", data->path_from_envp);
	//exit(0);
	data->my_paths = ft_split(data->my_line, ':');
	//tokenize both commands
	data->my_cmd_args = ft_split(av[2], 32);
	data->my_cmd_args2 = ft_split(av[3], 32);
	// int i;
	// for (i = 0; data->my_cmd_args[i] != NULL; i++)
	// {
	// 	printf("%s\n", data->my_cmd_args[i]);
	// 	printf("%s\n", data->my_cmd_args2[i]);
	// }
	// exit(0);
}
