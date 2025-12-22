/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:09:01 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/22 10:49:51 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

t_rgb	*colors_parce(char *word)
{
	char	**rgb;
	t_rgb	*color;

	if (check_comma(word) != 2)
	{
		free(word);
		return (NULL);
	}
	rgb = ft_split(word, ',');
	free(word);
	if (!rgb)
		return (NULL);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(rgb), NULL);
	if (!check_rgb(rgb))
		return (free_split(rgb), NULL);
	color = malloc(sizeof(t_rgb));
	if (!color)
		return (free_split(rgb), NULL);
	color->r = cub_atoi(rgb[0]);
	color->g = cub_atoi(rgb[1]);
	color->b = cub_atoi(rgb[2]);
	free_split(rgb);
	return (color);
}

char	*trim_line(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\0')
		i++;
	i--;
	while (i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i--;
	if (i < 0)
		return (NULL);
	new_line = malloc(i + 2);
	if (!new_line)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		new_line[j] = line[j];
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

int	check_size(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (map[i] != NULL)
		i++;
	if (i < 2)
		return (0);
	return (1);
}

int	check_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (map[i] != NULL)
	{
		if (check_content(map[i]) == false)
			return (0);
		i++;
	}
	if (check_size(map) != 1)
		return (0);
	if (check_line(map[0]) == false || check_line(map[i - 1]) == false)
		return (0);
	if (check_zero_pos(map) == false)
		return (0);
	if (check_player(map) != 1)
		return (0);
	return (1);
}

void	fill_map(t_pars *my_map)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (my_map->map[i] != NULL)
	{
		j = 0;
		while (my_map->map[i][j] != '\0')
		{
			if (j++ > k)
				k = j;
		}
		i++;
	}
	fix_shit(my_map, k);
}
