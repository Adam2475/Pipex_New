#include "pipex.h"

int	parent_process(t_data *data, char **envp)
{
	int status;
	int i;
	char *cmd;
	char *tmp;

	waitpid(-1, &status, 0);
	if (dup2(data->f2, STDOUT_FILENO) < 0)
		return (-1);
	if (dup2(data->end[0], STDIN_FILENO) < 0)
		return (-1);
	close(data->end[1]);
	close(data->f2);
	while(data->my_paths[++i])
	{
		tmp = ft_strjoin(data->my_paths[i], "/");
		cmd = ft_strjoin(cmd, data->my_cmd_args[0]);
		execve(cmd, data->my_cmd_args, envp);
		perror("error:");
		free(tmp);
		free(cmd);
	}
	exit(EXIT_FAILURE);
}

int	child_process(t_data *data, char **envp)
{
	int i;
	char *cmd;

	i = -1;
	if (dup2(data->f1, STDIN_FILENO) < 0)
		return (-1);
	if (dup2(data->end[1], STDOUT_FILENO) < 0)
		return (-1);
	close(data->end[0]);
	close(data->f1);
	//printf("hello");
	while(data->my_paths[++i])
	{
		printf("%s\n", cmd);
		cmd = ft_strjoin(data->my_paths[i], data->my_cmd_args[0]);
		//printf("%s\n", cmd);
		execve(cmd, data->my_cmd_args, envp);
		//perror("error:");
		free(cmd);
	}
	return (EXIT_FAILURE);
}

void pipex(t_data *data, char **av, char **envp)
{
	pipe(data->end);
	env_parser(data, envp, av);
	data->cmd1 = ft_strdup(av[2]);
	data->cmd2 = ft_strdup(av[3]);
	data->parent = fork();
	if (data->parent < 0)
		return (perror(("fork:")));
	if (!data->parent)
		child_process(data, envp);
	else
		parent_process(data, envp);
}
