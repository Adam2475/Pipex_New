/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:05:55 by adapassa          #+#    #+#             */
/*   Updated: 2024/04/12 14:21:04 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_memset(void *str, int c, size_t n)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = str;
	while (i < n)
		ptr[i++] = c;
	return ((void *)ptr);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_memset ((unsigned char *)ptr, 0, nmemb * size);
	return (ptr);
}

int	child_process(t_data *data, char **envp)
{
	char	*cmd;

	if (dup2(data->f1, STDIN_FILENO) < 0)
		return (-1);
	if (dup2(data->end[1], STDOUT_FILENO) < 0)
		return (-1);
	close(data->end[0]);
	close(data->f1);
	cmd = find_cmd(data->my_cmd_args[0], data);
	if (!cmd)
		return (EXIT_FAILURE);
	execve(cmd, data->my_cmd_args, envp);
	free(cmd);
	return (EXIT_SUCCESS);
}

int	parent_process(t_data *data, char **envp)
{
	int		status;
	char	*cmd;

	waitpid(-1, &status, 0);
	if (dup2(data->f2, STDOUT_FILENO) < 0)
		return (-1);
	if (dup2(data->end[0], STDIN_FILENO) < 0)
		return (-1);
	close(data->end[1]);
	close(data->f2);
	cmd = find_cmd(data->my_cmd_args2[0], data);
	if (!cmd)
		return (EXIT_FAILURE);
	execve(cmd, data->my_cmd_args2, envp);
	free(cmd);
	return (EXIT_SUCCESS);
}

int	pipex(t_data *data, char **av, char **envp)
{
	if (pipe(data->end) < 0)
		return (1);
	env_parser(data, envp, av);
	data->cmd1 = ft_strdup(av[2]);
	data->cmd2 = ft_strdup(av[3]);
	data->parent = fork();
	if (data->parent < 0)
		return (2);
	if (!data->parent)
		child_process(data, envp);
	else
		parent_process(data, envp);
	return (0);
}
