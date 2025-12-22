/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:23:07 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/21 11:36:18 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	check_player(char **map)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	ret = 0;
	if (!map)
		return (0);
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				ret++;
			j++;
		}
		i++;
	}
	return (ret);
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

void	fix_shit(t_pars *my_map, int k)
{
	char	*line;
	int		i;
	int		j;

	i = -1;
	while (my_map->map[++i] != NULL)
	{
		j = 0;
		if ((int)ft_strlen(my_map->map[i]) < k)
		{
			line = malloc(k + 1);
			if (!line)
				return (free_mymap(my_map));
			while (my_map->map[i][j] != '\0')
			{
				line[j] = my_map->map[i][j];
				j++;
			}
			while (j < k)
				line[j++] = ' ';
			line[k] = '\0';
			free(my_map->map[i]);
			my_map->map[i] = line;
		}
	}
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
