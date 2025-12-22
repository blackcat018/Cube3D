/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:09:01 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/21 11:36:21 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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

int	cub_atoi(const char *str)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		if (result > 255)
			return (-1);
		i++;
	}
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] != '\0')
		return (-1);
	return (result);
}

int	check_rgb(char **rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
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

t_rgb	*colors_parce(char *word)
{
	char	**rgb;
	t_rgb	*color;

	if (check_comma(word) != 2)
	{
		free(word);
		return (NULL);
	}
	rgb = ft_split(word, ',');
	free(word);
	if (!rgb)
		return (NULL);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(rgb), NULL);
	if (!check_rgb(rgb))
		return (free_split(rgb), NULL);
	color = malloc(sizeof(t_rgb));
	if (!color)
		return (free_split(rgb), NULL);
	color->r = cub_atoi(rgb[0]);
	color->g = cub_atoi(rgb[1]);
	color->b = cub_atoi(rgb[2]);
	free_split(rgb);
	return (color);
}
