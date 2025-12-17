/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czghoumi <czghoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:09:01 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/05 19:44:00 by czghoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

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

size_t	ft_strlenn(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdupp(const char *s1)
{
	char	*ptr;
	int		i;

	ptr = malloc(ft_strlenn((char *)s1) + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	ft_copy(char *dest, const char *src, size_t src_len)
{
	size_t	i;

	i = 0;
	while (i < src_len)
	{
		dest[i] = src[i];
		i++;
	}
}

char	*ft_strjoinn(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ptr;

	len1 = ft_strlenn(s1);
	len2 = ft_strlenn(s2);
	if (!s1 && !s2)
		return (NULL);
	if (s2 == NULL)
		return (free(s1), ft_strdupp(s1));
	if (s1 == NULL)
		return (ft_strdupp(s2));
	ptr = malloc(len1 + len2 + 1);
	if (ptr == NULL)
		return (free(s1), NULL);
	ft_copy(ptr, s1, len1);
	ft_copy(ptr + len1, s2, len2);
	ptr[len1 + len2] = '\0';
	free(s1);
	return (ptr);
}

int	ft_found(const char *str, char c)
{
	while (*str) 
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_read(char *str, char *buffer, int fd)
{
	int	bytes_read;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		str = ft_strjoinn(str, buffer);
		if (!str)
			return (free(str), str = NULL, NULL);
		if (ft_found(str, '\n') == 1)
			break ;
	}
	return (str);
}

char	*ft_char_front(char *s)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (s[len] != '\n' && s[len] != '\0')
		len++;
	if (s[len] == '\n')
		len++;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_char_back(char *s)
{
	int		i;
	int		len;
	int		remaining_len;
	char	*str;

	i = 0;
	len = 0;
	remaining_len = 0;
	while (s[len] != '\n' && s[len] != '\0')
		len++;
	if (s[len] == '\0')
		return (NULL);
	len++;
	while (s[len + remaining_len] != '\0')
		remaining_len++;
	str = malloc(remaining_len + 1);
	if (!str)
		return (NULL);
	while (i < remaining_len)
	{
		str[i] = s[len + i];
		i++;
	}
	str[i] = '\0';
	return (str);
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

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*tmp;
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(str), str = NULL, NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (free(str), str = NULL, NULL);
	str = ft_read(str, buffer, fd);
	free(buffer);
	if (str == NULL)
		return (free(str), str = NULL, NULL);
	if (str[0] == '\0')
		return (free(str), str = NULL, NULL);
	line = ft_char_front(str);
	if (!line)
		return (free(str), str = NULL, NULL);
	tmp = ft_char_back(str);
	if (!tmp)
		return (free(str), str = NULL, line);
	free(str);
	str = tmp;
	return (line);
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

int	for_color(char *line, char *word, t_rgb **coll, t_pars *my_map)
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
	if (*coll == NULL)
	{
		*coll = colors_parce(last);
		if (*coll == NULL)
		{
			free(last);
			free_mymap(my_map);
			return (0);
		}
	}
	else
	{
		free(last);
		free_mymap(my_map);
		return (0);
	}
	return (1);
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

int	for_map(char *line, char *word, t_pars *my_map)
{
	int		s;
	int		i;
	char	**new_map;

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
		{
			free(new_map);
			return (0);
		}
		new_map[s + 1] = NULL;
		free(my_map->map);
		my_map->map = new_map;
	}
	return (1);
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

int	fill_mapst(char *line, t_pars *my_map)
{
	char	*word;

	if (line == NULL)
		return (2);
	word = firs_word(line);
	if (ft_strncmp(word, "NO", 2) == 0 && ft_strlen(word) == ft_strlen("NO"))
	{
		if (for_cardinal(line, word, &my_map->no, my_map) == 0)
			return (0);
	}
	else if (ft_strlen(word) == ft_strlen("SO") 
		&& ft_strncmp(word, "SO", 2) == 0)
	{
		if (for_cardinal(line, word, &my_map->so, my_map) == 0)
			return (0);
	}
	else if (ft_strlen(word) == ft_strlen("EA") 
		&& ft_strncmp(word, "EA", 2) == 0)
	{
		if (for_cardinal(line, word, &my_map->ea, my_map) == 0)
			return (0);
	}
	else if (ft_strlen(word) == ft_strlen("WE") 
		&& ft_strncmp(word, "WE", 2) == 0)
	{
		if (for_cardinal(line, word, &my_map->we, my_map) == 0)
			return (0);
	}
	else if (ft_strlen(word) == ft_strlen("F") && ft_strncmp(word, "F", 1) == 0)
	{
		if(for_color(line,word, &my_map->floor, my_map) == 0)
			return (0);
	}
	else if (ft_strlen(word) == ft_strlen("C") && ft_strncmp(word, "C", 1) == 0)
	{
		if(for_color(line,word, &my_map->ceil, my_map) == 0)
			return (0);
	}
	else if (my_map->no != NULL && my_map->so != NULL && my_map->ea != NULL 
		&& my_map->we != NULL && my_map->floor != NULL 
		&& my_map->ceil != NULL && word[0] == '1' && my_map->stop == false)
	{
		if(for_map(line, word, my_map) == 0)
			return (0);
	}
	else
	{
		free(word);
		free_mymap(my_map);
		return (0);
	}
	return (1);
}


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

void ll()
{
	system ("leaks Cube3d_bonus");
}

bool	check_content(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!(line[i] == ' ' || line[i] == '\n' || line[i] == '0' 
				|| line[i] == '1' || line[i] == 'N' || line[i] == 'S' 
				|| line[i] == 'E' || line[i] == 'W' || line[i] == 'D'))
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
				|| map[i][j] == 'W' || map[i][j] == 'D')
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
bool check_dors(char **map)
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
			if ( map[i][j] == 'D')
			{
				if ((map[i][j-1]!='1' || map[i][j+1]!='1') && (map[i-1][j]!='1'  || map[i+1][j]!='1' ))
    				return false;
			}
			j++;
		}
		i++;
	}
	return (true);
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
	if (check_dors(map) != 1)
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
