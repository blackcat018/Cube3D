/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:03:33 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/21 11:36:37 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	get_map_dimensions(t_game *g)
{
	int	i;
	int	max_width;
	int	len;

	i = 0;
	max_width = 0;
	while (g->my_map->map[i])
	{
		len = ft_strlen(g->my_map->map[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	g->map_height = i;
	g->map_width = max_width;
}

int	get_map_value(t_game *g, int x, int y)
{
	if (y < 0 || y >= g->map_height || x < 0)
		return (1);
	if (x >= (int)ft_strlen(g->my_map->map[y]))
		return (1);
	if (g->my_map->map[y][x] == '1')
		return (1);
	if (g->my_map->map[y][x] == '0' || g->my_map->map[y][x] == 'N'
		|| g->my_map->map[y][x] == 'S' || g->my_map->map[y][x] == 'E'
		|| g->my_map->map[y][x] == 'W')
		return (0);
	return (1);
}

void	set_map(t_pars *my_map)
{
	my_map->ea = NULL;
	my_map->no = NULL;
	my_map->so = NULL;
	my_map->we = NULL;
	my_map->map = NULL;
	my_map->stop = false;
	my_map->ceil = NULL;
	my_map->floor = NULL;
}

int	valid_map(t_pars *my_map)
{
	if (check_map(my_map->map) == 0)
	{
		free_mymap(my_map);
		my_map = NULL;
		return (printf("map form is not corect\n"), 0);
	}
	fill_map(my_map);
	if (my_map == NULL)
		return (printf("faild to malloc new map"), 0);
	return (1);
}

t_pars	*map_fill(int argc, char **argv)
{
	t_pars	*my_map;
	char	*line;
	int		s;
	int		l;

	s = chack_arg(argc, argv);
	if (s < 0)
		return (NULL);
	my_map = malloc(sizeof(t_pars));
	if (!my_map)
		return (printf("malloc failed\n"), NULL);
	set_map(my_map);
	line = get_next_line(s);
	while (line != NULL)
	{
		l = chack_line(line, my_map, s);
		if (l != 1)
			return (NULL);
		line = get_next_line(s);
	}
	free(line);
	l = valid_map(my_map);
	if (l != 1)
		return (NULL);
	return (my_map);
}
