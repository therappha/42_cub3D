/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:10:27 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/06/01 15:44:36 by gde-la-r         ###   ########.fr       */
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

char	*ft_remove_nl(char *line)
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

int	is_space(char c)
{
	if ((c == 32) || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_map(char *line)
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
