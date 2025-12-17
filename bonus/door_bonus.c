/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:09:01 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/13 17:39:42 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"


void cast_rays(t_game *g)
{
    draw_ceiling_and_floor(g);
    int x = 0;
    t_ray ray;
    while (x < SCREEN_WIDTH)
    {
        init_ray(&ray, g, x);
        calculate_step(&ray, g);
        perform_dda(&ray, g);
        calculate_wall_distance(&ray, g);
        draw_textured_wall(g, x, &ray);
        x++;
    }
}