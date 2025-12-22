/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_load_fill_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:27:37 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/22 11:59:11 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

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

int	load_wall_textures(t_pars *map, t_game *g)
{
	if (load_tex_img(g, map->ea, &g->texture_east, &g->img_wall_east))
		return (1);
	if (load_tex_img(g, map->we, &g->texture_west, &g->img_wall_west))
		return (1);
	if (load_tex_img(g, map->no, &g->texture_north, &g->img_wall_north))
		return (1);
	if (load_tex_img(g, map->so, &g->texture_south, &g->img_wall_south))
		return (1);
	return (0);
}

int	load_game_assets(t_game *g)
{
	if (load_tex_img(g, "./textures/torch_hand.png", &g->texture_torch,
			&g->img_torch))
		return (1);
	if (load_tex_img(g, "./textures/attack1.png", &g->texture_attack1,
			&g->img_attack1))
		return (1);
	if (load_tex_img(g, "./textures/attack2.png", &g->texture_attack2,
			&g->img_attack2))
		return (1);
	if (load_tex_img(g, "./textures/open1.png", &g->texture_open1,
			&g->img_open1))
		return (1);
	if (load_tex_img(g, "./textures/open2.png", &g->texture_open2,
			&g->img_open2))
		return (1);
	if (load_tex_img(g, "joj.png", &g->texture_door, &g->img_wall_door))
		return (1);
	return (0);
}

int	load_tex_img(t_game *g, char *path, mlx_texture_t **tex, mlx_image_t **img)
{
	*tex = mlx_load_png(path);
	if (!(*tex))
		return (1);
	*img = mlx_texture_to_image(g->mlx, *tex);
	if (!(*img))
		return (1);
	return (0);
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
