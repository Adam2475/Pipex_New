#include "pipex.h"

int	parent_process(t_data *data, char **envp)
{
	int status;
	char *cmd;

	waitpid(-1, &status, 0);
	if (dup2(data->f2, STDOUT_FILENO) < 0)
		return (-1);
	if (dup2(data->end[0], STDIN_FILENO) < 0)
		return (-1);
	close(data->end[1]);
	close(data->f2);
	cmd = find_cmd(data->my_cmd_args2[0], data);
	if (cmd == NULL)
		exit(-1);
	execve(cmd, data->my_cmd_args2, envp);
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
	printf("%s\n", data->my_cmd_args2[0]);
	write(1, data->my_cmd_args2[0], 10);
	exit(1);
	cmd = find_cmd(data->my_cmd_args[0], data);
	//printf("%s\n", cmd);
	if (cmd == NULL)
		exit(-1);
	execve(cmd, data->my_cmd_args, envp);
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
