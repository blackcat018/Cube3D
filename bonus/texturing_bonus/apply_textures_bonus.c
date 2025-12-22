/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_textures_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:23:07 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/22 11:58:54 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

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

void	init_textures_null(t_game *g)
{
	g->texture_east = NULL;
	g->img_wall_east = NULL;
	g->texture_west = NULL;
	g->img_wall_west = NULL;
	g->texture_north = NULL;
	g->img_wall_north = NULL;
	g->texture_south = NULL;
	g->img_wall_south = NULL;
	g->texture_door = NULL;
	g->img_wall_door = NULL;
	g->texture_open1 = NULL;
	g->img_open1 = NULL;
	g->texture_open2 = NULL;
	g->img_open2 = NULL;
	g->texture_attack1 = NULL;
	g->img_attack1 = NULL;
	g->texture_attack2 = NULL;
	g->img_attack2 = NULL;
	g->texture_torch = NULL;
	g->img_torch = NULL;
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

int	fill_textur(t_pars *map, t_game *g)
{
	init_textures_null(g);
	g->mlx = mlx_init(g->screen_width, g->screen_height, "cub3d", true);
	if (!g->mlx)
		return (1);
	if (load_wall_textures(map, g))
		return (1);
	if (load_game_assets(g))
		return (1);
	return (0);
}
