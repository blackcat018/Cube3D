/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textur_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:09:01 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/24 13:10:44 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

double	wal_xx(t_ray *ray, t_game *g)
{
	double	wall_x;
	double	perp;

	perp = ray->perp_wall_dist;
	if (ray->side == 0)
		wall_x = g->player.y + perp * ray->dir_y;
	else
		wall_x = g->player.x + perp * ray->dir_x;
	wall_x = wall_x - (int)wall_x;
	return (wall_x);
}

mlx_texture_t	*wall_text(t_ray *ray, t_game *g)
{
	mlx_texture_t	*tex;

	tex = NULL;
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			tex = g->texture_east;
		else
			tex = g->texture_west;
	}
	else
	{
		if (ray->dir_y > 0)
			tex = g->texture_south;
		else
			tex = g->texture_north;
	}
	return (tex);
}

t_calc	refill(double perp, t_game *g)
{
	t_calc	ss;

	ss.line_height = (int)(g->screen_height / perp);
	ss.draw_start = -ss.line_height / 2 + g->screen_height / 2;
	if (ss.draw_start < 0)
		ss.draw_start = 0;
	ss.draw_end = ss.line_height / 2 + g->screen_height / 2;
	if (ss.draw_end >= g->screen_height)
		ss.draw_end = g->screen_height - 1;
	return (ss);
}

t_scalc	calculatin(double wall_x, mlx_texture_t *tex, t_calc value, t_game *g)
{
	t_scalc	ss;

	ss.pixels = (uint8_t *)tex->pixels;
	ss.tex_w = tex->width;
	ss.tex_h = tex->height;
	ss.tex_x = (int)(wall_x * (double)ss.tex_w);
	if (ss.tex_x < 0)
		ss.tex_x = 0;
	if (ss.tex_x >= ss.tex_w)
		ss.tex_x = ss.tex_w - 1;
	ss.step = (double)ss.tex_h / (double)value.line_height;
	ss.tex_pos = (value.draw_start - g->screen_height / 2.0 + value.line_height
			/ 2.0) * ss.step;
	return (ss);
}

void	draw_textured_wall(t_game *g, int x, t_ray *ray)
{
	t_calc		v;
	t_scalc		c;
	t_column	col;

	if (!g)
		return ;
	if (!init_texture_data(g, ray, &v, &c))
	{
		draw_wall(g, x, ray);
		return ;
	}
	col.game = g;
	col.x = x;
	draw_texture_column(&col, &v, &c, ray);
}
