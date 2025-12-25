/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:23:07 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/25 15:48:38 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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

void	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

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

int	check_wit_space(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
