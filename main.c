/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:05:58 by adapassa          #+#    #+#             */
/*   Updated: 2024/04/12 14:25:12 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s)
{
	char	*pt1;
	int		l;

	l = ft_strlen(s);
	pt1 = calloc(sizeof(char), (l + 1));
	if (!pt1)
		return (0);
	ft_memcpy(pt1, s, l);
	pt1[l] = '\0';
	return (pt1);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	if (c == 0)
		return (str + ft_strlen(s));
	while (s[i] != (unsigned char)c)
	{
		if (!str[i])
			break ;
		else
			i++;
	}
	if (str[i] != (unsigned char)c)
		return (NULL);
	return ((str + i));
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
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
	data.f1 = open(av[1], O_RDONLY);
	data.f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data.f1 < 0 || data.f2 < 0)
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
