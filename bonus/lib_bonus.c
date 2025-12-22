/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:02:49 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/22 12:03:38 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

size_t	ft_strlenn(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdupp(const char *s1)
{
	char	*ptr;
	int		i;

	ptr = malloc(ft_strlenn((char *)s1) + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	ft_copy(char *dest, const char *src, size_t src_len)
{
	size_t	i;

	i = 0;
	while (i < src_len)
	{
		dest[i] = src[i];
		i++;
	}
}

char	*ft_strjoinn(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ptr;

	len1 = ft_strlenn(s1);
	len2 = ft_strlenn(s2);
	if (!s1 && !s2)
		return (NULL);
	if (s2 == NULL)
		return (free(s1), NULL);
	if (s1 == NULL)
		return (ft_strdupp(s2));
	ptr = malloc(len1 + len2 + 1);
	if (ptr == NULL)
		return (free(s1), NULL);
	ft_copy(ptr, s1, len1);
	ft_copy(ptr + len1, s2, len2);
	ptr[len1 + len2] = '\0';
	free(s1);
	return (ptr);
}

int	ft_found(const char *str, char c)
{
	while (*str) 
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}
