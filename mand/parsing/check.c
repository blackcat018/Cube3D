/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:23:07 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/21 11:40:58 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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

bool	check_content(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!(line[i] == ' ' || line[i] == '\n' || line[i] == '0'
				|| line[i] == '1' || line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'E' || line[i] == 'W'))
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
				|| map[i][j] == 'E' || map[i][j] == 'W')
				if (!check_cell(map, i, j))
					return (false);
			j++;
		}
		i++;
	}
	return (true);
}
