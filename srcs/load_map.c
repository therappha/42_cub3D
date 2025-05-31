/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:59:23 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/31 19:06:18 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_open(char *map, t_cub *cub)
{
	cub->fd = open(map, O_RDONLY);
	if (cub->fd == -1)
		return (close(cub->fd), ft_putstr_fd("no file", 2),
			ft_putstr_fd(map, 2), ft_putstr_fd("\n", 2), 0);
	return (cub->fd);
}

static char	*ft_remove_nl(char *line)
{
	char	*temp;

	temp = line;
	line = ft_strtrim(line, "\n");
	if (temp)
		free(temp);
	return (line);
}

char	**append_cmd(char **cmd, char *newcmd)
{
	int		i;
	char	**result;

	i = 0;
	if (!cmd)
	{
		cmd = malloc(sizeof(char *) * 2);
		cmd[0] = ft_strdup(newcmd);
		cmd[1] = NULL;
		return (cmd);
	}
	while (cmd[i] != NULL)
		i++;
	result = malloc(sizeof(char **) * (i + 2));
	i = 0;
	while (cmd[i])
	{
		result[i] = ft_strdup(cmd[i]);
		i++;
	}
	result[i] = ft_strdup(newcmd);
	result[++i] = NULL;
	ft_free_arr(cmd);
	return (result);
}


/*NO assets/textures/ice.xpm
         SO assets/textures/lava.xpm        a
WE assets/textures/bricks.xpm
EA assets/textures/leaves.xpm


		F 101,    183,65
    C 100,200,200

while is space
F -> 101,183,65*/

int	is_space(char c)
{
	if ((c == 32) || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
	{
		i++;
	}
	if (line[i] && (line[i] == '1' || line[i] == '0'))
	{
		return (1);
	}
	return (0);
}

int	extract_path(t_cub *cub, t_image *image, char *line)
{
	int i;
	int starting;
	int ending;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	starting = i;
	while (line[i] && !is_space(line[i]))
		i++;
	ending = i - 1;
	while(line[i] && is_space(line[i]))
		i++;
	if (line[i])
	{
		cub->error = true;
		printf("invalid char after path\n");
		return (0);
	}
	if (image->path)
	{
		printf("error north texture duplicate\n");
		cub->error = true;
		return (0);
	}
	image->path = ft_strndupto(line, starting, ending);
	return (1);
}

int	extract_number(char *str)
{
	int		j;
	int		octect;
	char	number[4];

	j = 0;
	while (str[j] && is_space(str[j]))
		str++;
	while (j < 3 && str[j])
	{
		if (!ft_isdigit(str[j]))
			break;
		number[j] = str[j];
		j++;
	}
	number[j] = '\0';
	if (str[j] && (ft_isdigit(str[j]) || (!is_space(str[j]))))
		return (-1);
	while (str[j] && is_space(str[j]))
		j++;
	if (str[j] && str[j] != '\0')
		return (-1);
	octect = ft_atoi(number);
	if (octect < 0 || octect > 255)
		return (-1);
	 return (octect);
}
void	ft_set_color(t_cub *cub, int rgb[3], char which)
{
	int	i;
	int	color;

	color = 0;
	i = 0;
	while (i < 3)
	{
		if (rgb[i] == -1)
			color = -1;
		i++;
	}
	if (color != -1)
		color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	if (which == 'F')
	{
		cub->floor_color = color;
		cub->found.floor = true;
	}
	else
	{
		cub->found.ceiling = true;
		cub->ceiling_color = color;
	}

}
int	handle_color(t_cub *cub, char *line, char which)
{
	char	**tmp;
	int		i;
	int		rgb[3];

	if ((which == 'F' && cub->found.floor) ||
		(which == 'C' && cub->found.ceiling))
		return (0);
	while (line && *line && is_space(*line))
		line++;
	tmp = ft_split(line, ',');
	if (!tmp)
		return (0);
	i = 0;
	while (tmp[i])
	{
		if (i > 2)
		{
			ft_free_arr(tmp);
			return (0);
		}
		rgb[i] = extract_number(tmp[i]);
		if (rgb[i] == -1)
			break;
		i++;
	}
	ft_free_arr(tmp);
	if (i < 3)
		return (0);
	ft_set_color(cub, rgb, which);
	return (1);
}
int	check_assets(t_cub *cub, char *line)
{
	int		i;
	int		starting;
	int		ending;

	i = 0;
	starting = 0;
	ending = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (ft_strncmp("NO", line + i, 2) == 0)
	{
		i += 2;
		if (!extract_path(cub, &cub->textures[NORTH], line + i))
			return (0);
	}
	else if (ft_strncmp("SO", line + i, 2) == 0)
	{
		i += 2;
		if (!extract_path(cub, &cub->textures[SOUTH], line + i))
			return (0);
	}
	else if (ft_strncmp("EA", line + i, 2) == 0)
	{
		i += 2;
		if (!extract_path(cub, &cub->textures[EAST], line + i))
			return (0);
	}
	else if (ft_strncmp("WE", line + i, 2) == 0)
	{
		i += 2;
		if (!extract_path(cub, &cub->textures[WEST], line + i))
			return (0);
	}
	else if (ft_strncmp("F", line + i, 1) == 0)
	{
		if (!handle_color(cub, line + i + 1, 'F'))
		{
			cub->error = true;
			return (0);
		}
	}
	else if (ft_strncmp("C", line + i, 1) == 0)
	{
		if (!handle_color(cub, line + i + 1, 'C'))
		{
			cub->error = true;
			return (0);
		}
	}
	return (1);
}

int	checkline(t_cub *cub, char *line)
{
	int	exit;

	exit = 1;
	if (is_map(line))
	{
		cub->found.map = true;
		return 0;
	}
	if (!check_assets(cub, line))
		exit = 1;
	free(line);
	return (exit);
}

int	check_map_line(t_cub *cub, char *line)
{
	int	i;

	i = 0;
	cub->map_height++;
	if (line[0] == '\n' || line[i] == '\r')
		return (0);
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == '\r'
				|| line[i] == '\n' || line[i] == ' ')
			i++;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
				|| line[i] == 'W')
		{
			i++;
			if (!cub->found.player)
				cub->found.player = true;
			else
				return (0);
		}
		else
			return (0);
	}
	if ((int)ft_strlen(line) > cub->map_width)
		cub->map_width = ft_strlen(line);
	return (1);
}
int	ft_load_map(char *map, t_cub *cub)
{
	int		checker;
	char	*line;
	char	**temp;

	cub->error = false;
	checker = ft_open(map, cub);
	if (!checker)
		return (0);
	line = NULL;
	while (!cub->error)
	{
		line = get_next_line(cub->fd);
		if (!line)
			break ;
		line = ft_remove_nl(line);
		if (!cub->found.map && checkline(cub, line))
			continue;
		if (!check_map_line(cub, line))
			cub->error = true;
		temp = append_cmd(cub->map, line);
		cub->map = temp;
		free(line);
	}
	get_next_line(-1);
	if (cub->error)
		return (printf("error while parsing\n"), 0);
	return (1);
}

int	check_args(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 5)
		return (0);
	str = str + len - 4;
	if (ft_strncmp(".cub", str, 4) == 0)
	{
		return (1);
	}
	return (0);
}
