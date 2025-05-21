/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:59:23 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/21 17:35:59 by rafaelfe         ###   ########.fr       */
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
	result[i++] = ft_strdup(newcmd);
	result[i] = NULL;
	return (result);
}

int	ft_load_map(char *map, t_cub *cub)
{
	int		checker;
	char	*line;
	char	**temp;

	checker = ft_open(map, cub);
	if (!checker)
		return (0);
	line = NULL;
	while (1)
	{
		line = get_next_line(cub->fd);
		if (!line)
			break ;
		line = ft_remove_nl(line);
		temp = append_cmd(cub->map, line);
		if (cub->map)
			ft_free_arr(cub->map);
		cub->map = temp;
		free(line);
	}
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
