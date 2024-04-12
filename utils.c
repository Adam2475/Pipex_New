/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:05:50 by adapassa          #+#    #+#             */
/*   Updated: 2024/04/12 14:21:29 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	s3 = (char *)calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (0);
	if (!s2)
		return (free(s3), ft_strdup(s1));
	if (s1)
	{
		while (s1[i[0]] != '\0')
		{
			s3[i[0]] = s1[i[0]];
			i[0]++;
		}
	}
	while (s2[i[1]] != '\0')
	{
		s3[i[0] + i[1]] = s2[i[1]];
		i[1]++;
	}
	s3[i[0] + i[1]] = '\0';
	return (s3);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (!dest && !src)
		return (0);
	while (++i < n)
		((char *)dest)[i] = ((char *)src)[i];
	return (dest);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((!*big && !*little) || !*little)
		return ((char *)big);
	if (!*big)
	{
		return (0);
	}
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
			{
				return ((char *)big + i);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub_str;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
	{
		sub_str = ft_calloc(sizeof(char), 1);
		return (sub_str);
	}
	if (ft_strlen(s) - start > len)
		sub_str = malloc(sizeof(char) * ((len + 1)));
	else
		sub_str = malloc(sizeof(char)
				* (((unsigned int)ft_strlen(s) - start) + 1));
	if (sub_str == NULL)
		return (NULL);
	i = 0;
	while ((char)s[start] && (size_t)i < len)
	{
		sub_str[i++] = (char)s[start];
		start++;
	}
	sub_str[i] = 0;
	return (sub_str);
}
