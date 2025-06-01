/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:34:01 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/06/01 15:44:34 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static bool	handle_color_loop(char **tmp, int *i, int *rgb)
{
	while (tmp[(*i)])
	{
		if ((*i) > 2)
		{
			ft_free_arr(tmp);
			return (false);
		}
		rgb[(*i)] = extract_number(tmp[(*i)]);
		if (rgb[(*i)] == -1)
			break ;
		(*i)++;
	}
	return (true);
}

static void	ft_set_color(t_cub *cub, int rgb[3], char which)
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

	if ((which == 'F' && cub->found.floor)
		|| (which == 'C' && cub->found.ceiling))
		return (0);
	while (line && *line && is_space(*line))
		line++;
	tmp = ft_split(line, ',');
	if (!tmp)
		return (0);
	i = 0;
	if (!handle_color_loop(tmp, &i, rgb))
		return (0);
	ft_free_arr(tmp);
	if (i < 3)
		return (0);
	ft_set_color(cub, rgb, which);
	return (1);
}

bool	ft_load_map_loop(t_cub *cub, char *line, char **temp)
{
	while (!cub->error)
	{
		line = get_next_line(cub->fd);
		if (!line)
			break ;
		line = ft_remove_nl(line);
		if (!cub->found.map && checkline(cub, line))
			continue ;
		if (!check_map_line(cub, line, 0))
			cub->error = true;
		temp = append_cmd(cub->map, line);
		cub->map = temp;
		free(line);
	}
	return (true);
}
