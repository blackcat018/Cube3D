/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:43:12 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/25 14:06:38 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

bool	check_content(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!(line[i] == ' ' || line[i] == '\n' || line[i] == '0'
				|| line[i] == '1' || line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'E' || line[i] == 'W' || line[i] == 'D'))
			return (false);
		i++;
	}
	if (line[i - 1] != '1')
		return (false);
	return (true);
}

bool	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!(line[i] == ' ' || line[i] == '1' || line[i] == '\n'))
			return (false);
		i++;
	}
	return (true);
}

bool	check_cell(char **map, int i, int j)
{
	if (j >= (int)ft_strlen(map[i - 1]) || map[i - 1][j] == ' ')
		return (false);
	if (j >= (int)ft_strlen(map[i + 1]) || map[i + 1][j] == ' ')
		return (false);
	if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
		return (false);
	return (true);
}

bool	check_zero_pos(char **map)
{
	int	i;
	int	j;

	if (!map || !map[0])
		return (false);
	i = 1;
	while (map[i + 1])
	{
		j = 1;
		while (map[i][j + 1])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'D')
				if (!check_cell(map, i, j))
					return (false);
			if (map[i][j] == 'D' && !check_border(map, i, j))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

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
			{
				ret++;
			}
			j++;
		}
		i++;
	}
	return (ret);
}
