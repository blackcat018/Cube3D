/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:07:01 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/21 11:36:29 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	draw_wall(t_game *g, int x, t_ray *ray)
{
	t_wall	w;
	t_vline	l;

	w = get_wall(ray);
	l.g = g;
	l.x = x;
	l.start = 0;
	l.end = w.start;
	l.color = 0x333333FF;
	draw_vertical_line(&l);
	l.start = w.start;
	l.end = w.end;
	l.color = w.color;
	draw_vertical_line(&l);
	l.start = w.end;
	l.end = SCREEN_HEIGHT;
	l.color = 0x666666FF;
	draw_vertical_line(&l);
}

uint32_t	get_rgba(int r, int g, int b)
{
	return ((uint32_t)r << 24 | (uint32_t)g << 16 | (uint32_t)b << 8 | 255);
}

void	draw_ceiling_and_floor(t_game *G)
{
	int		x;
	t_vline	l;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		l.g = G;
		l.x = x;
		l.start = 0;
		l.end = SCREEN_HEIGHT / 2;
		l.color = get_rgba(G->my_map->ceil->r, G->my_map->ceil->g,
				G->my_map->ceil->b);
		draw_vertical_line(&l);
		l.start = SCREEN_HEIGHT / 2;
		l.end = SCREEN_HEIGHT;
		l.color = get_rgba(G->my_map->floor->r, G->my_map->floor->g,
				G->my_map->floor->b);
		draw_vertical_line(&l);
		x++;
	}
}

int	chack_arg(int argc, char **argv)
{
	int	s;

	if (argc < 2 || argc > 4)
		return (printf("erreur in args\n"), -1);
	if (ft_count(argv[1]) > 1)
		return (printf("erreur in file name\n"), -1);
	if (!chck_cub(argv[1]))
		return (printf("erreur in file name only '*.cub'\n"), -1);
	s = open(argv[1], O_RDONLY);
	if (s < 0)
		return (printf("erreur in oprning file\n"), -1);
	return (s);
}

int	chack_line(char *line, t_pars *my_map, int s)
{
	while (line != NULL && chack_empty_line(line) == 1)
	{
		free(line);
		if (my_map != NULL && my_map->map != NULL)
			my_map->stop = true;
		line = get_next_line(s);
	}
	if (fill_mapst(line, my_map) == 0)
	{
		free(line);
		return (printf("erreur in map\n"), 0);
	}
	free(line);
	return (1);
}
