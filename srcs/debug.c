/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:48:48 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/21 19:53:40 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	debug_directions(t_cub *cub)
{
	t_point normalized_player = normalize(cub->player.direction);
	drawline(cub, (t_point){SCREEN_SIZE_X / 4, SCREEN_SIZE_Y -  (SCREEN_SIZE_Y / 4)}, (t_point){SCREEN_SIZE_X / 4 + normalized_player.x * CIRCLE_SIZE,  SCREEN_SIZE_Y -  (SCREEN_SIZE_Y / 4) + normalized_player.y * CIRCLE_SIZE});
	circleBres(cub, SCREEN_SIZE_X / 4, SCREEN_SIZE_Y -  (SCREEN_SIZE_Y / 4), CIRCLE_SIZE + 1);
	circleBres(cub, SCREEN_SIZE_X / 4, SCREEN_SIZE_Y -  (SCREEN_SIZE_Y / 4), CIRCLE_SIZE);

	drawline(cub, (t_point){SCREEN_SIZE_X - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y -  (SCREEN_SIZE_Y / 4)}, (t_point){SCREEN_SIZE_X - SCREEN_SIZE_X / 4 + cub->player.camera.x * CIRCLE_SIZE,  SCREEN_SIZE_Y -  (SCREEN_SIZE_Y / 4) + cub->player.camera.y * CIRCLE_SIZE});
	circleBres(cub, SCREEN_SIZE_X -  SCREEN_SIZE_X / 4, SCREEN_SIZE_Y -  (SCREEN_SIZE_Y / 4), CIRCLE_SIZE);
	circleBres(cub, SCREEN_SIZE_X -  SCREEN_SIZE_X / 4, SCREEN_SIZE_Y -  (SCREEN_SIZE_Y / 4), CIRCLE_SIZE + 1);
}
