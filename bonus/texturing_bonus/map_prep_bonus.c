/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_prep_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:55:09 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/25 15:42:57 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	for_cardinal(char *line, char *word, char **cord, t_pars *my_map)
{
	int		s;
	char	*last;

	free(word);
	s = ft_count(line);
	if (s != 2)
	{
		free_mymap(my_map);
		return (0);
	}
	last = last_word(line);
	if (*cord == NULL)
		*cord = last;
	else
	{
		free(last);
		free_mymap(my_map);
		return (0);
	}
	return (1);
}

char	*remove_prefix_dup(const char *str, const char *prefix)
{
	size_t	len;
	size_t	out_len;
	char	*out;

	if (!str || !prefix)
		return (NULL);
	len = ft_strlen(prefix);
	if (ft_strncmp(str, prefix, len) != 0)
		return (strdup(str));
	out_len = ft_strlen(str + len);
	if (out_len > 0 && str[len + out_len - 1] == '\n')
		out_len--;
	out = malloc(out_len + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, str + len, out_len);
	out[out_len] = '\0';
	return (out);
}

int	for_color(char *line, char *word, t_rgb **coll, t_pars *my_map)
{
	char	*last;

	last = remove_prefix_dup(line, word);
	free(word);
	if (*coll == NULL)
	{
		*coll = colors_parce(last);
		if (*coll == NULL)
			return (free_mymap(my_map), 0);
	}
	else
	{
		free(last);
		return (free_mymap(my_map), 0);
	}
	return (1);
}

int	continu_map(char *line, t_pars *my_map)
{
	int		s;
	int		i;
	char	**new_map;

	s = 0;
	while (my_map->map[s] != NULL)
		s++;
	new_map = malloc((s + 2) * sizeof(char *));
	if (!new_map)
		return (0);
	i = 0;
	while (i < s)
	{
		new_map[i] = my_map->map[i];
		i++;
	}
	new_map[s] = trim_line(line);
	if (!new_map[s])
		return (free(new_map), 0);
	new_map[s + 1] = NULL;
	free(my_map->map);
	my_map->map = new_map;
	return (1);
}

int	for_map(char *line, char *word, t_pars *my_map)
{
	free(word);
	if (my_map->map == NULL)
	{
		my_map->map = malloc(sizeof(char *) * 2);
		if (!my_map->map)
			return (0);
		my_map->map[0] = trim_line(line);
		my_map->map[1] = NULL;
	}
	else
	{
		if (continu_map(line, my_map) == 0)
			return (0);
	}
	return (1);
}
