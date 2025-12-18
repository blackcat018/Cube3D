/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:23:07 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/18 08:11:46 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_pars	*map_fill(int argc, char **argv)
{
    t_pars	*my_map;
    char	*line;
    int		s;

    if (argc < 2 || argc > 4)
		return (printf("erreur in args\n"), NULL);
	if (ft_count(argv[1]) > 1)
		return (printf("erreur in file name\n"), NULL);
	if (!chck_cub(argv[1]))
		return (printf("erreur in file name only '*.cub'\n"), NULL);
	s = open(argv[1], O_RDONLY);
	if (s < 0)
		return (printf("erreur in oprning file\n"), NULL);
	my_map = malloc(sizeof(t_pars));
	if(!my_map)
		return 0;
	my_map->ea = NULL;
	my_map->no = NULL;
	my_map->so = NULL;
	my_map->we = NULL;
	my_map->map = NULL;
	my_map->stop = false;
	my_map->ceil = NULL;
    my_map->floor = NULL;
	line = get_next_line(s);
	while (line != NULL)
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
			printf("erreur in map\n");
			return (NULL);
		}
		free(line);
		line = get_next_line(s);
	}
	free(line);
	if (check_map(my_map->map) == 0)
	{
        free_mymap(my_map);
		my_map = NULL; 
		return(printf("map form is not corect\n"),NULL);
		
	}
	fill_map(my_map);
	if(my_map == NULL)
		return (printf("faild to malloc new map"), NULL);
    return (my_map);
}

int fill_tex(t_pars	*my_map, t_game *g)
{
    g->texture_south = mlx_load_png(my_map->so);
    if (!g->texture_south)
        return (1);
    g->img_wall_south = mlx_texture_to_image(g->mlx, g->texture_south);
    if (!(g->img_wall_south))
        return (1);
    g->texture_west = mlx_load_png(my_map->we);
    if (!g->texture_west)
        return (1);
    g->img_wall_west = mlx_texture_to_image(g->mlx, g->texture_west);
    if (!(g->img_wall_west))
        return (1);
    g->texture_torch = mlx_load_png("./textures/torch_hand.png");
    if (!g->texture_torch)
        return (1);
    g->img_torch = mlx_texture_to_image(g->mlx, g->texture_torch);
    if (!g->img_torch)
        return (1);
    g->texture_attack1 = mlx_load_png("./textures/attack1.png");
    if (!g->texture_attack1)
        return (1);
    g->img_attack1 = mlx_texture_to_image(g->mlx, g->texture_attack1);
    if (!g->img_attack1)
        return (1);
    g->texture_attack2 = mlx_load_png("./textures/attack2.png");
    if (!g->texture_attack2)
        return (1);
    g->img_attack2 = mlx_texture_to_image(g->mlx, g->texture_attack2);
    if (!g->img_attack2)
        return (1);
    return 0;
}
int    fill_textur(t_pars	*my_map, t_game *g)
{
    g->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
    if (!g->mlx)
        return (1);
    g->texture_east= mlx_load_png(my_map->ea);
    if (!g->texture_east)
        return (1);
    g->img_wall_east = mlx_texture_to_image(g->mlx, g->texture_east);
	if (!(g->img_wall_east))
		return (1);
    g->texture_north= mlx_load_png(my_map->no);
    if (!g->texture_north)
        return (1);
    g->img_wall_north = mlx_texture_to_image(g->mlx, g->texture_north);
	if (!(g->img_wall_north))
		return (1);
    if(fill_tex(my_map, g) == 1)
        return 1;
    return 0;
}

void    free_texturs(t_game *g)
{
    mlx_delete_texture(g->texture_east);
    mlx_delete_texture(g->texture_west);
    mlx_delete_texture(g->texture_north);
    mlx_delete_texture(g->texture_south);
    mlx_delete_texture(g->texture_torch);
    mlx_delete_texture(g->texture_attack1);
    mlx_delete_texture(g->texture_attack2);
    mlx_delete_image(g->mlx, g->img_wall_east);
    mlx_delete_image(g->mlx, g->img_wall_west);
    mlx_delete_image(g->mlx, g->img_wall_north);
    mlx_delete_image(g->mlx, g->img_wall_south);
    mlx_delete_image(g->mlx, g->img_torch);
    mlx_delete_image(g->mlx, g->img_attack1);
    mlx_delete_image(g->mlx, g->img_attack2);
    mlx_delete_image(g->mlx, g->img);
}
