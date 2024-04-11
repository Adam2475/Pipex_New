#include "pipex.h"

void free_matrix(char **matrix)
{
    for (int i = 0; matrix[i] != NULL; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void	free_structure(t_data *data)
{
	free(data->cmd1);
	free(data->cmd2);
	free(data->my_line);
	free(data->path_from_envp);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		status;

	status = 0;
	if (ac != 5)
		return (write(2, "arguments error", 15));
	data.f2 = open(av[4], O_CREAT |  O_RDWR | O_TRUNC, 0644);
	data.f1 = open(av[1], O_RDONLY);
	if(data.f1 < 0 || data.f2 < 0)
		return (write(2, "open error", 10));
	status = pipex(&data, av, envp);
	if (status == 1)
		return (write(2, "error while initializing pipe", 28));
	else if (status == 2)
		return (write(2, "error while initializing fork", 28));
	free_structure(&data);
	free_matrix(data.my_cmd_args);
	free_matrix(data.my_cmd_args2);
	free_matrix(data.my_paths);
	return (0);
}
