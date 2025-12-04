/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czghoumi <czghoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:23:07 by czghoumi          #+#    #+#             */
/*   Updated: 2025/11/09 23:59:23 by czghoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


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
		return (free(s1), ft_strdupp(s1));
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

char	*ft_read(char *str, char *buffer, int fd)
{
	int	bytes_read;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		str = ft_strjoinn(str, buffer);
		if (!str)
			return (free(str), str = NULL, NULL);
		if (ft_found(str, '\n') == 1)
			break ;
	}
	return (str);
}

char	*ft_char_front(char *s)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (s[len] != '\n' && s[len] != '\0')
		len++;
	if (s[len] == '\n')
		len++;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_char_back(char *s)
{
	int		i;
	int		len;
	int		remaining_len;
	char	*str;

	i = 0;
	len = 0;
	remaining_len = 0;
	while (s[len] != '\n' && s[len] != '\0')
		len++;
	if (s[len] == '\0')
		return (NULL);
	len++;
	while (s[len + remaining_len] != '\0')
		remaining_len++;
	str = malloc(remaining_len + 1);
	if (!str)
		return (NULL);
	while (i < remaining_len)
	{
		str[i] = s[len + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*tmp;
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(str), str = NULL, NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (free(str), str = NULL, NULL);
	str = ft_read(str, buffer, fd);
	free(buffer);
	if (str == NULL)
		return (free(str), str = NULL, NULL);
	if (str[0] == '\0')
		return (free(str), str = NULL, NULL);
	line = ft_char_front(str);
	if (!line)
		return (free(str), str = NULL, NULL);
	tmp = ft_char_back(str);
	if (!tmp)
		return (free(str), str = NULL, line);
	free(str);
	str = tmp;
	return (line);
}
