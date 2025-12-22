/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:23:07 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/21 11:42:28 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
