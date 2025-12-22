/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:23:07 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/21 11:40:48 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_count(char const *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		if (s[i] != '\0')
			j++;
		while ((s[i] != ' ' || s[i] == '\t' || s[i] == '\n') && s[i] != '\0')
			i++;
	}
	return (j);
}

int	chack_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		else
			return (0);
	}
	return (1);
}

void	free_mymap(t_pars *my_map)
{
	int	i;

	i = 0;
	if (my_map == NULL)
		return ;
	if (my_map->no != NULL)
		free(my_map->no);
	if (my_map->so != NULL)
		free(my_map->so);
	if (my_map->we != NULL)
		free(my_map->we);
	if (my_map->ea != NULL)
		free(my_map->ea);
	if (my_map->ceil != NULL)
		free(my_map->ceil);
	if (my_map->floor != NULL)
		free(my_map->floor);
	if (my_map->map != NULL)
	{
		while (my_map->map[i] != NULL)
			free(my_map->map[i++]);
		free(my_map->map);
	}
	free(my_map);
}

char	*firs_word(char *line)
{
	int		i;
	int		start;
	int		len;
	char	*word;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	len = i - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = line[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	*last_word(char *line)
{
	int		i;
	int		start;
	char	*word;

	if (!line)
		return (NULL);
	i = ft_strlen(line);
	while (i > 0 && (line[i - 1] == ' ' || line[i - 1] == '\t' || 
			line[i - 1] == '\n'))
		i--;
	start = i;
	while (start > 0 && line[start - 1] != ' ' && line[start - 1] != '\t'
		&& line[start - 1] != '\n')
		start--;
	if (start == i)
		return (NULL);
	word = ft_substr(line, start, i - start);
	return (word);
}
