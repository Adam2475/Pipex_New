#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_data data;

	data.f2 = open(av[4], O_CREAT |  O_RDWR | O_TRUNC, 0644);
	data.f1 = open(av[1], O_RDONLY);
	if (ac != 5)
		return (write(2, "arguments error", 15));
	if(data.f1 < 0 || data.f2 < 0)
		return (write(2, "open error", 10));
	pipex(&data, av, envp);
	return (0);
}