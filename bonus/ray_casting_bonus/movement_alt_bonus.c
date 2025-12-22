/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_alt_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:16:33 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/22 10:17:31 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	apply_sprint(t_game *g, double *move_speed)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT_SHIFT) || 
		mlx_is_key_down(g->mlx, MLX_KEY_RIGHT_SHIFT))
		*move_speed = g->player.move_speed * 2.0;
	else
		*move_speed = g->player.move_speed;
}

void	handle_wasd(t_game *g, double move_speed)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
		move_forward(g, move_speed);
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
		move_backward(g, move_speed);
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
		move_left(g, move_speed);
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
		move_right(g, move_speed);
}
