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

int	extract_path(t_cub *cub, t_image *image, char *line)
{
	int	i;
	int	starting;
	int	ending;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	starting = i;
	while (line[i] && !is_space(line[i]))
		i++;
	ending = i - 1;
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i])
	{
		cub->error = true;
		return (print_error("Error\nInvalid char after path!\n"), 0);
	}
	if (image->path)
	{
		cub->error = true;
		return (print_error("Error\nDuplicated texture!\n"), 0);
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
			break ;
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

int	ft_load_map(char *map, t_cub *cub, int checker, char *line)
{
	char	**temp;

	temp = NULL;
	checker = ft_open(map, cub);
	if (!checker)
		return (0);
	line = NULL;
	ft_load_map_loop(cub, line, temp);
	get_next_line(-1);
	if (cub->error)
	{
		print_error("Error\nInvalid map!\n");
		return (0);
	}
	return (1);
}
