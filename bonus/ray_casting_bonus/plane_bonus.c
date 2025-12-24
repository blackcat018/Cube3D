/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:15:18 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/23 14:34:14 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

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
	if (g->my_map->map[y][x] == 'd' || g->my_map->map[y][x] == '0'
		|| g->my_map->map[y][x] == 'N' || g->my_map->map[y][x] == 'S'
		|| g->my_map->map[y][x] == 'E' || g->my_map->map[y][x] == 'W')
		return (0);
	return (1);
}

int	door_in_front(t_game *g, int *mx, int *my)
{
	int		x;
	int		y;
	char	c;

	x = (int)floor(g->player.x + g->player.dir_x);
	y = (int)floor(g->player.y + g->player.dir_y);
	if (x < 0 || x >= g->map_width || y < 0 || y >= g->map_height)
		return (0);
	c = g->my_map->map[y][x];
	if (c == 'D' || c == 'd')
	{
		if (mx)
			*mx = x;
		if (my)
			*my = y;
		return (1);
	}
	return (0);
}

void	draw_textured_door(t_game *g, int x, t_ray *ray)
{
	t_calc			value;
	double			wall_x;
	mlx_texture_t	*tex;
	t_scalc			calc;
	uint32_t		color;

	if (!g)
		return ;
	value = refill(ray->perp_wall_dist, g);
	wall_x = wal_xx(ray, g);
	tex = g->texture_door;
	if (ray->perp_wall_dist <= 0.0 || !tex)
		return (draw_wall(g, x, ray));
	calc = calculatin(wall_x, tex, value, g);
	g->light = get_light_intensity(ray->perp_wall_dist);
	while (value.draw_start <= value.draw_end)
	{
		color = color_pixwls_img(&calc, ray);
		color = apply_lighting(color, g->light);
		mlx_put_pixel(g->img, x, value.draw_start, color);
		value.draw_start++;
	}
}

void	draw_ceiling_and_floor(t_game *g)
{
	draw_ceiling(g);
	draw_floor(g);
}
