/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:23:07 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/02 21:43:29 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	for_cardinal(char *line, char *word, char **cord, t_pars *my_map)
{
	int		s;
	char	*last;

	free(word);
	s = ft_count(line);
	if (s != 2)
	{
		free_mymap(my_map);
		return (0);
	}
	last = last_word(line);
	if (*cord == NULL)
		*cord = last;
	else
	{
		free(last);
		free_mymap(my_map);
		return (0);
	}
	return (1);
}

int	for_color(char *line, char *word, t_rgb **coll, t_pars *my_map)
{
	int		s;
	char	*last;

	free(word);
	s = ft_count(line);
	if (s != 2)
	{
		free_mymap(my_map);
		return (0);
	}
	last = last_word(line);
	if (*coll == NULL)
	{
		*coll = colors_parce(last);
		if (*coll == NULL)
		{
			free(last);
			free_mymap(my_map);
			return (0);
		}
	}
	else
	{
		free(last);
		free_mymap(my_map);
		return (0);
	}
	return (1);
}

int	for_map(char *line, char *word, t_pars *my_map)
{
	int		s;
	int		i;
	char	**new_map;

	free(word);
	if (my_map->map == NULL)
	{
		my_map->map = malloc(sizeof(char *) * 2);
		if (!my_map->map)
			return (0);
		my_map->map[0] = trim_line(line);
		my_map->map[1] = NULL;
	}
	else 
	{
		s = 0;
		while (my_map->map[s] != NULL)
			s++;
		new_map = malloc((s + 2) * sizeof(char *));
		if (!new_map)
			return (0);
		i = 0;
		while (i < s) 
		{
			new_map[i] = my_map->map[i];
			i++;
		}
		new_map[s] = trim_line(line);
		if (!new_map[s]) 
		{
			free(new_map);
			return (0);
		}
		new_map[s + 1] = NULL;
		free(my_map->map);
		my_map->map = new_map;
	}
	return (1);
}

int	fill_mapst(char *line, t_pars *my_map)
{
	char	*word;

	if (line == NULL)
		return (2);
	word = firs_word(line);
	if (ft_strncmp(word, "NO", 2) == 0 && ft_strlen(word) == ft_strlen("NO"))
	{
		if (for_cardinal(line, word, &my_map->no, my_map) == 0)
			return (0);
	}
	else if (ft_strlen(word) == ft_strlen("SO") 
		&& ft_strncmp(word, "SO", 2) == 0)
	{
		if (for_cardinal(line, word, &my_map->so, my_map) == 0)
			return (0);
	}
	else if (ft_strlen(word) == ft_strlen("EA") 
		&& ft_strncmp(word, "EA", 2) == 0)
	{
		if (for_cardinal(line, word, &my_map->ea, my_map) == 0)
			return (0);
	}
	else if (ft_strlen(word) == ft_strlen("WE") 
		&& ft_strncmp(word, "WE", 2) == 0)
	{
		if (for_cardinal(line, word, &my_map->we, my_map) == 0)
			return (0);
	}
	else if (ft_strlen(word) == ft_strlen("F") && ft_strncmp(word, "F", 1) == 0)
	{
		if(for_color(line,word, &my_map->floor, my_map) == 0)
			return (0);
	}
	else if (ft_strlen(word) == ft_strlen("C") && ft_strncmp(word, "C", 1) == 0)
	{
		if(for_color(line,word, &my_map->ceil, my_map) == 0)
			return (0);
	}
	else if (my_map->no != NULL && my_map->so != NULL && my_map->ea != NULL 
		&& my_map->we != NULL && my_map->floor != NULL 
		&& my_map->ceil != NULL && word[0] == '1' && my_map->stop == false)
	{
		if(for_map(line, word, my_map) == 0)
			return (0);
	}
	else
	{
		free(word);
		free_mymap(my_map);
		return (0);
	}
	return (1);
}