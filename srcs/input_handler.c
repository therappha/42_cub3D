/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:09:07 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/21 17:18:08 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	key_pressed(int keysym, t_cub *cub)
{
	if (keysym == XK_Escape)
		free_displays(cub);
	return (1);
}

int	key_released(int keysym, t_cub *cub)
{
	(void)keysym;
	(void)cub;

	return (1);
}
