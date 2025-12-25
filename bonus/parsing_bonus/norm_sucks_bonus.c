/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_sucks_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:49:25 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/25 14:09:07 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

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

bool	check_border(char **map, int i, int j)
{
	if (j >= (int)ft_strlen(map[i - 1]) || (map[i - 1][j] != '1'
		&& map[i][j - 1] != '1'))
		return (false);
	if (j >= (int)ft_strlen(map[i + 1]) || (map[i + 1][j] != '1'
		&& map[i][j + 1] != '1'))
		return (false);
	if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
		return (false);
	return (true);
}
