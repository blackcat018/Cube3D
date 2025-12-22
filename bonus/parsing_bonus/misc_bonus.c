/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:37:05 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/22 10:48:20 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	ft_count(char const *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		if (s[i] != '\0')
			j++;
		while ((s[i] != ' ' || s[i] == '\t' || s[i] == '\n') && s[i] != '\0')
			i++;
	}
	return (j);
}

char	*firs_word(char *line)
{
	int		i;
	int		start;
	int		len;
	char	*word;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	len = i - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = line[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	*last_word(char *line)
{
	int		i;
	int		start;
	char	*word;

	if (!line)
		return (NULL);
	i = ft_strlen(line);
	while (i > 0 && (line[i - 1] == ' ' || line[i - 1] == '\t'
			|| line[i - 1] == '\n'))
		i--;
	start = i;
	while (start > 0 && line[start - 1] != ' ' && line[start - 1] != '\t'
		&& line[start - 1] != '\n')
		start--;
	if (start == i)
		return (NULL);
	word = ft_substr(line, start, i - start);
	return (word);
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

void	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}
