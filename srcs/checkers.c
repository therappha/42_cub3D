/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:54:37 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/06/01 15:44:35 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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

int	check_map_line(t_cub *cub, char *line, int i)
{
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

int	checkline(t_cub *cub, char *line)
{
	int	exit;

	exit = 1;
	if (is_map(line))
	{
		cub->found.map = true;
		return (0);
	}
	if (!check_assets(cub, line))
		exit = 1;
	free(line);
	return (exit);
}

static int	check_assets_utils(t_cub *cub, char *line, int *i)
{
	if (ft_strncmp("NO", line + *i, 2) == 0)
	{
		*i += 2;
		if (!extract_path(cub, &cub->textures[NORTH], line + *i))
			return (0);
	}
	else if (ft_strncmp("SO", line + *i, 2) == 0)
	{
		*i += 2;
		if (!extract_path(cub, &cub->textures[SOUTH], line + *i))
			return (0);
	}
	else if (ft_strncmp("EA", line + *i, 2) == 0)
	{
		*i += 2;
		if (!extract_path(cub, &cub->textures[EAST], line + *i))
			return (0);
	}
	else if (ft_strncmp("WE", line + *i, 2) == 0)
	{
		*i += 2;
		if (!extract_path(cub, &cub->textures[WEST], line + *i))
			return (0);
	}
	return (1);
}

int	check_assets(t_cub *cub, char *line)
{
	int		i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (!check_assets_utils(cub, line, &i))
		return (0);
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
