/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:35:37 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/25 15:47:30 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

bool	chck_cub(char *arg)
{
	int	i;
	int	a;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == ' ')
			return (false);
		i++;
	}
	a = ft_strncmp(&arg[i - 4], ".cub", 4);
	if (a == 0)
		return (true);
	else
		return (false);
}

int	chack_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		else
			return (0);
	}
	return (1);
}

void	free_mymap(t_pars *my_map)
{
	int	i;

	i = 0;
	if (my_map == NULL)
		return ;
	if (my_map->no != NULL)
		free(my_map->no);
	if (my_map->so != NULL)
		free(my_map->so);
	if (my_map->we != NULL)
		free(my_map->we);
	if (my_map->ea != NULL)
		free(my_map->ea);
	if (my_map->ceil != NULL)
		free(my_map->ceil);
	if (my_map->floor != NULL)
		free(my_map->floor);
	if (my_map->map != NULL)
	{
		while (my_map->map[i] != NULL)
			free(my_map->map[i++]);
		free(my_map->map);
	}
	free(my_map);
}

int    check_rgb(char **rgb)
{
    int    i;

    i = 0;
    while (i < 3)
    {
        if(check_wit_space(rgb[i]))
            return (0);
        if (cub_atoi(rgb[i]) == -1)
            return (0);
        i++;
    }
    return (1);
}

int	check_comma(char *word)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] == ',')
			j++;
		i++;
	}
	return (j);
}
