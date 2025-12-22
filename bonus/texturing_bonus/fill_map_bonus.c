/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:23:07 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/22 11:59:02 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	dispatch_line(char *line, char *word, t_pars *m)
{
	if (!word)
		return (-1);
	if (ft_strlen(word) == 2 && ft_strncmp(word, "NO", 2) == 0)
		return (for_cardinal(line, word, &m->no, m));
	else if (ft_strlen(word) == 2 && ft_strncmp(word, "SO", 2) == 0)
		return (for_cardinal(line, word, &m->so, m));
	else if (ft_strlen(word) == 2 && ft_strncmp(word, "EA", 2) == 0)
		return (for_cardinal(line, word, &m->ea, m));
	else if (ft_strlen(word) == 2 && ft_strncmp(word, "WE", 2) == 0)
		return (for_cardinal(line, word, &m->we, m));
	else if (ft_strlen(word) == 1 && ft_strncmp(word, "F", 1) == 0)
		return (for_color(line, word, &m->floor, m));
	else if (ft_strlen(word) == 1 && ft_strncmp(word, "C", 1) == 0)
		return (for_color(line, word, &m->ceil, m));
	else if (m->no && m->so && m->ea && m->we && m->floor && m->ceil
		&& word[0] == '1' && m->stop == false)
		return (for_map(line, word, m));
	else
	{
		free(word);
		return (free_mymap(m), 0);
	}
	return (-1);
}

int	fill_mapst(char *line, t_pars *my_map)
{
	char	*word;
	int		ret;

	if (!line)
		return (2);
	word = firs_word(line);
	if (!word)
		return (0);
	ret = dispatch_line(line, word, my_map);
	if (ret == 0)
		return (0);
	return (1);
}
