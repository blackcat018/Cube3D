/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 22:07:42 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/22 10:16:02 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	rotate_player(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

void	rotate_with_mouse(t_game *g)
{
	int32_t	mouse_x;
	int32_t	mouse_y;
	int32_t	center_x;
	int32_t	delta_x;
	double	rotation_speed;

	center_x = g->screen_width / 2;
	mlx_get_mouse_pos(g->mlx, &mouse_x, &mouse_y);
	delta_x = mouse_x - center_x;
	rotation_speed = 0.0015;
	if (delta_x != 0)
		rotate_player(&g->player, delta_x * rotation_speed);
	mlx_set_mouse_pos(g->mlx, center_x, g->screen_height / 2);
}

void	handle_mouse_rotation(t_game *g)
{
	static int	first_frame = 1;

	if (first_frame)
	{
		first_frame = init_mouse(g);
		return ;
	}
	rotate_with_mouse(g);
}

void	handle_rotation(t_game *g)
{
	static bool	o_was_down;
	bool		o_is_down;
	int			mx;
	int			my;

	o_is_down = mlx_is_key_down(g->mlx, MLX_KEY_E);
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
		rotate_player(&g->player, -g->player.rot_speed);
	if (mlx_is_key_down(g->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(g->mlx);
	if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
		rotate_player(&g->player, g->player.rot_speed);
	if (o_is_down && !o_was_down)
	{
		if (door_in_front(g, &mx, &my))
		{
			if (g->my_map->map[my][mx] == 'D')
				g->my_map->map[my][mx] = 'd';
			else if (g->my_map->map[my][mx] == 'd')
				g->my_map->map[my][mx] = 'D';
		}
	}
	o_was_down = o_is_down;
}
