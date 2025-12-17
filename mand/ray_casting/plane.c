/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:15:18 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/17 12:20:46 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../cube.h"

void get_map_dimensions(t_game *g)
{
    int i = 0;
    int max_width = 0;
    
    while (g->my_map->map[i])
    {
        int len = ft_strlen(g->my_map->map[i]);
        if (len > max_width)
            max_width = len;
        i++;
    }
    g->map_height = i;
    g->map_width = max_width;
}

int get_map_value(t_game *g, int x, int y)
{
    if (y < 0 || y >= g->map_height || x < 0)
        return 1; 
    if (x >= (int)ft_strlen(g->my_map->map[y]))
        return 1; 
    if (g->my_map->map[y][x] == '1')
        return 1;
    if (g->my_map->map[y][x] == '0' || g->my_map->map[y][x] == 'N' || 
        g->my_map->map[y][x] == 'S' || g->my_map->map[y][x] == 'E' || 
        g->my_map->map[y][x] == 'W')
        return 0;
    return 1;
}
