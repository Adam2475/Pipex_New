#include "pipex.h"

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
	data->my_cmd_args = ft_split(av[2], 32);

	//printf("hello");

	// for (i = 0; data->my_cmd_args[i] != NULL; i++)
	// {
	// 	printf("%s\n", data->my_cmd_args[i]);
	// }
	// exit(0);
}
