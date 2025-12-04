/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:09:01 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/02 21:40:37 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

char	*firs_word(char *line)
{
	int		i;
	int		length;
	int		start;
	char	*word;

	i = 0;
	length = 0;
	while (line[i] == ' ' || line[i] == '\t' )
		i++;
	start = i;
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0' && line[i] != '\n')
	{
		length++;
		i++;
	}
	word = malloc(length + 1);
	if (!word) 
		return (NULL);
	i = 0;
	while (i < length)
	{
		word[i] = line[start + i];
		i++;
	}
	word[length] = '\0';
	return (word);
}

char	*last_word(char *line)
{
	int		i;
	int		length;
	int		start;
	char	*word;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\0')
		i++;
	i--;
	while (i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i--;
	if (i < 0)
		return (NULL);
	length = 0;
	start = i;
	while (i >= 0 && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
	{
		length++;
		i--;
	}
	start = i + 1;
	word = malloc(length + 1);
	if (!word) 
		return (NULL);
	i = 0;
	while (i < length)
	{
		word[i] = line[start + i];
		i++;
	}
	word[length] = '\0';
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
	if (i > 0)
		return (-1);
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
	if (str[i] != '\0')
		return (-1);
	return (result);
}

t_rgb	*colors_parce(char *word)
{
	char	**rgb;
	int		j;
	int		i;
	t_rgb	*color;

	rgb = ft_split(word, ',');
	if (!rgb)
		return (NULL);
	j = 0;
	while (rgb[j] != NULL)
		j++;
	i = 0;
	if (j != 3)
	{
		while (rgb[i] != NULL)
		{
			free (rgb[i]);
			i++;
		}
		free (rgb);
		return (NULL);
	}
	color = malloc(sizeof(t_rgb));
	if (!color)
		return (color);
	i = 0;
	while (rgb[i] != NULL)
	{
		if (cub_atoi(rgb[i]) == -1)
		{
			i = 0;
			while (rgb[i] != NULL)
			{
				free(rgb[i]);
				i++;
			}
			free(rgb);
			free(color);
			return (NULL);
		}
		i++;
	}
	color->r = cub_atoi(rgb[0]);
	color->g = cub_atoi(rgb[1]);
	color->b = cub_atoi(rgb[2]);
	free(word);
	i = 0;
	while (rgb[i] != NULL)
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
	return (color);
}

char	*trim_line(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\0')
		i++;
	i--;
	while (i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i--;
	if (i < 0)
		return (NULL);
	new_line = malloc(i + 2);
	if (!new_line)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		new_line[j] = line[j];
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

void ll()
{
	system ("leaks cub3D");
}

bool	check_content(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!(line[i] == ' ' || line[i] == '\n' || line[i] == '0' 
				|| line[i] == '1' || line[i] == 'N' || line[i] == 'S' 
				|| line[i] == 'E' || line[i] == 'W'))
			return (false); 
		i++;
	}
	if (line[i - 1] != '1')
		return (false);
	return (true);
}

bool	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!(line[i] == ' ' || line[i] == '1' || line[i] == '\n'))
			return (false);
		i++;
	}
	return (true);
}

bool	check_zero_pos(char **map)
{
	int	i;
	int	j;

	i = 1;
	if (!map || !map[0]) 
		return (false);
	while (map[i + 1] != NULL)
	{
		j = 1;
		while (map[i][j + 1] != '\0')
		{
			if (map[i][j] == '0' || map[i][j] == 'S' 
				|| map[i][j] == 'N' || map[i][j] == 'E' 
				|| map[i][j] == 'W')
			{
				if (j >= (int)ft_strlen(map[i - 1]) || map[i - 1][j] == ' ')
					return (false);
				if (j >= (int)ft_strlen(map[i + 1]) || map[i + 1][j] == ' ')
					return (false);
				if (map[i][j - 1] == ' ')
					return (false);
				if (map[i][j + 1] == ' ')
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

int	check_player(char **map)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	ret = 0;
	if (!map)
		return (0);
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'S' || map[i][j] == 'N' 
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				ret++;
			}
			j++;
		}
		i++;
	}
	return (ret);
}

int	check_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (map[i] != NULL)
	{
		if (check_content(map[i]) == false)
			return (0);
		i++;
	}
	if (check_line(map[0]) == false || check_line(map[i - 1]) == false)
		return (0);
	if (check_zero_pos(map) == false)
		return (0);
	if (check_player(map) != 1)
		return (0);
	return (1);
}

void	fill_map(t_pars *my_map)
{
	char	*line;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (my_map->map[i] != NULL)
	{
		j = 0;
		while (my_map->map[i][j] != '\0')
		{
			j++;
			if (j > k)
				k = j;
		}
		i++;
	}
	i = 0;
	while (my_map->map[i] != NULL)
	{
		j = 0;
		if ((int)ft_strlen(my_map->map[i]) < k)
		{
			line = malloc(k+1);
			if (!line)
			{
				free_mymap(my_map);
				return ;
			}
			while (my_map->map[i][j] != '\0')
			{
				line[j] = my_map->map[i][j];
				j++;
			}
			while (j < k)
			{
				line[j] = ' ';
				j++;
			}
			line[k] = '\0';
			free(my_map->map[i]);
			my_map->map[i] = line;
		}
		i++;
	}
}

// int	main(int argc, char **argv)
// {
// 	int		s;
// 	t_pars	*my_map;
// 	char	*line;

// 	if (argc < 2 || argc > 4)
// 		return (printf("erreur in args\n"), 1);
// 	if (ft_count(argv[1]) > 1)
// 		return (printf("erreur in file name\n"), 1);
// 	if (!chck_cub(argv[1]))
// 		return (printf("erreur in file name only '*.cub'\n"), 1);
// 	s = open(argv[1], O_RDONLY);
// 	if (s < 0)
// 		return (printf("erreur in oprning file\n"), 1);
// 	my_map = malloc(sizeof(t_pars));
// 	if(!my_map)
// 		return 0;
// 	my_map->ea = NULL;
// 	my_map->no = NULL;
// 	my_map->so = NULL;
// 	my_map->we = NULL;
// 	my_map->map = NULL;
// 	my_map->stop = false;
// 	my_map->ceil = NULL;
//     my_map->floor = NULL;
// 	line = get_next_line(s);
// 	while (line != NULL)
// 	{
// 		while (line != NULL && chack_empty_line(line) == 1)
// 		{
// 			free(line);
// 			if (my_map != NULL && my_map->map != NULL)
// 				my_map->stop = true;
// 			line = get_next_line(s);
// 		}
// 		if (fill_mapst(line, my_map) == 0)
// 		{
// 			free(line);
// 			printf("erreur in map\n");
// 			atexit(ll);
// 			return (1);
// 		}
// 		free(line);
// 		line = get_next_line(s);
// 	}
// 	free(line);
// 	if (check_map(my_map->map) == 0)
// 	{
// 		printf("map form is not corect\n");
// 		free_mymap(my_map);
// 		my_map = NULL; 
// 	}
// 	fill_map(my_map);
// 	if(my_map == NULL)
// 		return (printf("faild to malloc new map"), 1);
// 	printf("done\n");
// 	if (my_map != NULL)
// 		free_mymap(my_map);
// 	atexit(ll);
// }