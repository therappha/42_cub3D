/* ************************************************************************** */
/*    */
/*  :::::::::::   */
/*   main.c   :+::+:    :+:   */
/*    +:+ +:+   +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+ +#+  */
/*+#+#+#+#+#+   +#+     */
/*   Created: 2025/01/25 17:42:20 by rafaelfe    #+#    #+# */
/*   Updated: 2025/05/15 16:45:52 by rafaelfe   ###   ########.fr */
/*    */
/* ************************************************************************** */

#include "../includes/cub.h"

float delta;

float speed = 3;
t_player player;


long long last_frame_time;

void	ft_free(t_cub *cub, char *line)
{
	int	i;

	if (line)
		free(line);
	i = 0;
	if (cub && cub->map)
	{
		while (cub->map[i])
			free(cub->map[i++]);
		free(cub->map);
	}
}

void	ft_free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return ;
}

int	ft_open(char *map, t_cub *cub)
{
	cub->fd = open(map, O_RDONLY);
	if (cub->fd == -1)
		return (close(cub->fd), ft_putstr_fd("no file", 2),
			ft_putstr_fd(map, 2), ft_putstr_fd("\n", 2), 0), 0;
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
	free(cmd);
	return (result);
}

int	ft_load_map(char *map, t_cub *cub)
{
	int		checker;
	char	*line;

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
		cub->map = append_cmd(cub->map, line);
		free(line);
	}
	return (1);
}

int	update(t_cub *cub);
int key_released(int keysym, t_cub *cub);
int	key_pressed(int keysym, t_cub *cub);


void	cub_init(t_cub *cub)
{
	cub->fd = 0;
	cub->map = NULL;
	cub->map_height = 0;
	cub->map_width = 0;
}

void	get_player_pos(t_cub *cub)
{
	int x = 0;
	int	y = 0;

	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == 'P')
			{
				player.pos.x = x;
				player.pos.y = y;
			}
			x++;
		}
		y++;
	}
	player.plane.x = 0;
	player.plane.y = 0.66;
}

void get_textures(t_cub *cub)
{
	int x = 64;
	int y = 64;


	cub->north_texture.img = mlx_xpm_file_to_image(cub->mlx_ptr, \
			"./assets/north.xpm", &x, &y);
	cub->north_texture.addr = mlx_get_data_addr(cub->north_texture.img, \
			&cub->north_texture.bits_per_pixel, &cub->north_texture.line_length, \
			&cub->north_texture.endian);
	cub->east_texture.img = mlx_xpm_file_to_image(cub->mlx_ptr, \
			"./assets/east.xpm", &x, &y);
	cub->east_texture.addr = mlx_get_data_addr(cub->east_texture.img, \
			&cub->east_texture.bits_per_pixel, &cub->east_texture.line_length, \
			&cub->east_texture.endian);
	cub->west_texture.img = mlx_xpm_file_to_image(cub->mlx_ptr, \
			"./assets/west.xpm", &x, &y);
	cub->west_texture.addr = mlx_get_data_addr(cub->west_texture.img, \
			&cub->west_texture.bits_per_pixel, &cub->west_texture.line_length, \
			&cub->west_texture.endian);
	cub->south_texture.img = mlx_xpm_file_to_image(cub->mlx_ptr, \
			"./assets/south.xpm", &x, &y);
	cub->south_texture.addr = mlx_get_data_addr(cub->south_texture.img, \
			&cub->south_texture.bits_per_pixel, &cub->south_texture.line_length, \
			&cub->south_texture.endian);

}
int	main(int ac, char **av)
{
	t_cub	cub;
	(void)av; (void) ac;
	if (ac != 2)
		return (0);
	if (!check_args(av[1]))
	{
		ft_printf("Error, Could not read file!\n");
		return (0);
	}
	cub_init(&cub);
	init_window(&cub);
	ft_load_map(av[1], &cub);
	for (int i = 0; cub.map[i]; i++)
	{
		printf("%s\n", cub.map[i]);
		cub.map_height++;
	}
	cub.map_width = ft_strlen(cub.map[0]);
	get_textures(&cub);
	mlx_hook(cub.win_ptr, DestroyNotify, 0L, free_displays, &cub);
	get_player_pos(&cub);
	last_frame_time = get_time();
	mlx_hook(cub.win_ptr, 02, (1L<<0), key_pressed, &cub);
	mlx_hook(cub.win_ptr, 03, (1L<<1), key_released, &cub);
	mlx_loop_hook(cub.mlx_ptr, update, &cub);

	mlx_loop(cub.mlx_ptr);
}

int	key_pressed(int keysym, t_cub *cub)
{

	if (keysym == XK_Escape)
		free_displays(cub);
	if (keysym == XK_A || keysym == XK_a)
	{
		player.direction.x += -1;
		if (player.direction.x < -1)
			player.direction.x = -1;
	}

	if (keysym == XK_D || keysym == XK_d)
	{
		player.direction.x += 1;
		if (player.direction.x > 1)
			player.direction.x = 1;
	}
	if (keysym == XK_w || keysym == XK_W)
	{
		player.direction.y += -1;
		if (player.direction.y < -1)
			player.direction.y = -1;
	}

	if (keysym == XK_S || keysym == XK_s)
	{
		player.direction.y += 1;
		if (player.direction.y > 1)
			player.direction.y = 1;
	}
	if (keysym == XK_space)
	{

	}
	return (0);
}

int key_released(int keysym, t_cub *cub)
{
	(void)(cub);
	if (keysym == XK_A || keysym == XK_a)
	{
		player.direction.x += 1;
	}

	if (keysym == XK_D || keysym == XK_d)
	{
		player.direction.x -= 1;
	}
	if (keysym == XK_W || keysym == XK_w)
	{
		player.direction.y += 1;
	}

	if (keysym == XK_S || keysym == XK_s)
	{
		player.direction.y -= 1;
	}

	return (0);
}

void	move()
{
	if (player.direction.x != 0)
	{
		player.pos.x += player.direction.x * speed * delta;
	}
	if (player.direction.y != 0)
	{
		player.pos.y += player.direction.y * speed * delta;
	}
}




void	drawrect(t_image *image, t_point pos, t_point size, int color)
{
	int	x = 0;
	int y = 0;

	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			ft_pixelput(image, pos.x + x, pos.y + y++, color);
		}
		x++;
	}
}

unsigned int darken_color(unsigned int color, float factor)
{
	if (factor < 0.0f) factor = 0.0f;
	if (factor > 1.0f) factor = 1.0f;

	unsigned char r = (color >> 16) & 0xFF;
	unsigned char g = (color >> 8) & 0xFF;
	unsigned char b = color & 0xFF;

	r = (unsigned char)(r * factor);
	g = (unsigned char)(g * factor);
	b = (unsigned char)(b * factor);

	return (r << 16) | (g << 8) | b;
}
void	drawsky(t_image *image, t_point pos, t_point size, int color)
{
	int	x = 0;
	int y = 0;


	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			float factor = 1.0f - ((float)y / size.y); // from 1.0 at top to 0.0 at bottom
			int shaded = darken_color(color, factor);
			ft_pixelput(image, pos.x + x, pos.y + y++, shaded);
		}
		x++;
	}
}

void	drawfloor(t_image *image, t_point pos, t_point size, int color)
{
	int	x = 0;
	int y = 0;
	float factor;
	int shaded;

	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			factor = ((float)y / size.y); // from 1.0 at top to 0.0 at bottom
			shaded = darken_color(color, factor);
			ft_pixelput(image, pos.x + x, pos.y + y++, shaded);
		}
		x++;
	}
}

void drawCircle(t_cub *cub, int xc, int yc, int x, int y)
{
	ft_pixelput(&cub->image, xc+x, yc+y, 0x00FF00);
	ft_pixelput(&cub->image, xc-x, yc+y, 0x00FF00);
	ft_pixelput(&cub->image, xc+x, yc-y, 0x00FF00);
	ft_pixelput(&cub->image, xc-x, yc-y, 0x00FF00);
	ft_pixelput(&cub->image, xc+y, yc+x, 0x00FF00);
	ft_pixelput(&cub->image, xc-y, yc+x, 0x00FF00);
	ft_pixelput(&cub->image, xc+y, yc-x, 0x00FF00);
	ft_pixelput(&cub->image, xc-y, yc-x, 0x00FF00);
}


void circleBres(t_cub *cub, int xc, int yc, int r){

	int x = 0, y = r;
	int d = 3 - 2 * r;
	drawCircle(cub, xc, yc, x, y);
	while (y >= x)
	{
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;

		x++;
		drawCircle(cub, xc, yc, x, y);
	}
}

t_point get_mouse_position(t_cub *cub)
{
	int x = 0;
	int y = 0;

	mlx_mouse_get_pos(cub->mlx_ptr, cub->win_ptr, \
			&x, &y);
	if (x > SCREEN_SIZE_X)
		x = SCREEN_SIZE_X;
	else if (x < 0)
		x = 0;
	if (y > SCREEN_SIZE_Y)
		y = SCREEN_SIZE_Y;
	else if (y < 0)
		y = 0;
	return ((t_point){x, y});
}


void	calculate_Delta(void)
{
	delta = (get_time() - last_frame_time) / 1000.0f;
	last_frame_time = get_time();
}

void drawmap(t_cub *cub)
{
	int	x = 0;
	int y = 0;

	int drawx;
	int drawy;

	while (cub->map[y])
	{
		x = 0;
		while(cub->map[y][x])
		{

			drawx = x * TILE_SIZE -  player.pos.x * TILE_SIZE + SCREEN_SIZE_X / 4;
			drawy = y * TILE_SIZE - player.pos.y * TILE_SIZE + SCREEN_SIZE_Y / 2;
			if (drawx + TILE_SIZE >= SCREEN_SIZE_X / 2 || drawx < 0  || drawy < 0 || drawy + TILE_SIZE >= SCREEN_SIZE_Y)
			{
				x++;
				continue;
			}

			if (cub->map[y][x] == '1')
				drawrect(&cub->image, (t_point){drawx, drawy },  (t_point){TILE_SIZE -1, TILE_SIZE -1}, 0xFFFFFF);
			x++;
		}
		y++;
	}
}



void get_direction(t_cub *cub)
{
	//double x1 = player.pos.x * TILE_SIZE - 1;
	//double y1 = player.pos.y * TILE_SIZE - 1;

	double x1 = SCREEN_SIZE_X / 4;
	double y1 = SCREEN_SIZE_Y / 2;
	double x2 = get_mouse_position(cub).x;
	double y2 = get_mouse_position(cub).y;

	double dx = x2 - x1;
	double dy = y2 - y1;

	double length = sqrt(dx * dx + dy * dy);

	if (length != 0)
	{
		player.camera.x = dx / length; // Assign normalized dx
		player.camera.y = dy / length; // Assign normalized dy
	}
	else
	{
		player.camera.x = 0;
		player.camera.y = 0;
	}
	player.plane.x = -player.camera.y * 0.50;
	player.plane.y = player.camera.x * 0.50;
}


void	drawrect_texture(t_cub *cub, t_point pos, t_point size, int drawStart, int lineHeight, float step, int texX , t_image *texture, double perpWallDist)
{
	int	x = 0;
	int y = 0;
	int texY;
	int color;
	double texPos;
	float factor = 1.0f / (1.0f + perpWallDist * 0.2f);

	texPos = (drawStart - SCREEN_SIZE_Y / 2 + lineHeight / 2) * step;
	if (texPos < 0)
		texPos = 0;
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			texY = (int)texPos;
			texPos += step;
			if (texY < 0)
				texY = 0;
			if (texY >= 64)
				texY = 63;
			color = *(int *)((*texture).addr + (texY * (*texture).line_length + texX * ((*texture).bits_per_pixel / 8)));
			color = darken_color(color, factor);
			ft_pixelput(&cub->game, pos.x + x, pos.y + y++, color);
		}
		x++;
	}
}

t_image  *get_wall_color_from_direction(t_cub *cub, int side, float ray_x, float ray_y)
{

/*North	0	-1
South	0	+1
East	+1	0
West	-1	0*/
	if (side == 0)
	{
		if (ray_x > 0)
			return &cub->west_texture;
		else
			return &cub->east_texture;
	}
	else
	{
		if (ray_y > 0)
			return &cub->north_texture;
		else
			return &cub->south_texture;
	}
}

void	raycast(t_cub *cub)
{
	for(int x = 0; x < SCREEN_SIZE_X / 2; x++)
	{
		double cameraX = 2*x/(double)(SCREEN_SIZE_X / 2)-1; //x-coordinate in camera space
		double rayDirX =  player.camera.x + player.plane.x * cameraX;
		double rayDirY = player.camera.y + player.plane.y* cameraX;

		int mapX = (int)(player.pos.x);
		int mapY = (int)(player.pos.y);
		double sideDistX;
		double sideDistY;

		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player.pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player.pos.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player.pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player.pos.y) * deltaDistY;
		}


	while (hit == 0)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		//Check if ray has hit a wall
		if (mapX < 0 || mapY < 0 || mapX >= cub->map_width || mapY >= cub->map_height)
			break;
		if (cub->map[mapY][mapX] == '1')
			hit = 1;
	}

	if (side == 0)
		perpWallDist = (mapX - player.pos.x + (1 - stepX) / 2) / rayDirX;
	else
		perpWallDist = (mapY - player.pos.y + (1 - stepY) / 2) / rayDirY;


	if (perpWallDist < 0.01)
	perpWallDist = 0.01;
	int lineHeight = (int)(SCREEN_SIZE_Y / perpWallDist);

	int drawStart = -lineHeight / 2 + SCREEN_SIZE_Y / 2;
	if (drawStart < 0) drawStart = 0;
	int drawEnd = lineHeight / 2 + SCREEN_SIZE_Y / 2;
	if (drawEnd >= SCREEN_SIZE_Y) drawEnd = SCREEN_SIZE_Y - 1;


	double wallX;
	if (side == 0)
		wallX = player.pos.y + perpWallDist * rayDirY;
	else
		wallX = player.pos.x + perpWallDist * rayDirX;
	wallX -= floor((wallX));

	int texX = (int)(wallX * (double)(64));
	if(side == 0 && rayDirX < 0)
		texX = 64 - texX - 1;
	if(side == 1 && rayDirY > 0)
		texX = 64 - texX - 1;
	if (lineHeight < 1)
		lineHeight = 1;
	double step = 1.0 * 64 / lineHeight;

	t_image *texture = get_wall_color_from_direction(cub, side, rayDirX, rayDirY);
	drawrect_texture(cub,  (t_point){x, drawStart}, (t_point){1, drawEnd - drawStart},  drawStart, lineHeight, step , texX, texture, perpWallDist);
}
}



double	last_time = 0;
double	current_time;
double	frame_time;
int		fps;

void	game_loop(t_cub *cub)
{
	current_time = get_time();
	frame_time = current_time - last_time;
	last_time = current_time;

	if (frame_time > 0)
		fps = (int)(1000.0 / frame_time);
	char *fps_str = ft_itoa(fps); // Convert int to string
	mlx_string_put(cub->mlx_ptr, cub->win_ptr, 10, SCREEN_SIZE_Y - 10, 0xffffff, fps_str);
	free(fps_str);
}


int	update(t_cub *cub)
{
	calculate_Delta();

	(*cub).image.img = mlx_new_image((*cub).mlx_ptr, SCREEN_SIZE_X / 2, SCREEN_SIZE_Y);
	(*cub).image.addr = mlx_get_data_addr((*cub).image.img, &(*cub).image.bits_per_pixel, &(*cub).image.line_length, &(*cub).image.endian);
	cub->game.img = mlx_new_image((*cub).mlx_ptr, SCREEN_SIZE_X / 2, SCREEN_SIZE_Y);
	cub->game.addr = mlx_get_data_addr((*cub).game.img, &(*cub).game.bits_per_pixel, &(*cub).game.line_length, &(*cub).game.endian);
	circleBres(cub, SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 2, TILE_SIZE / 2 - 4);
	drawsky(&cub->game, (t_point){0, 0}, (t_point){SCREEN_SIZE_X, SCREEN_SIZE_Y / 2}, 0x3299CC);
	drawfloor(&cub->game, (t_point){SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2}, (t_point){SCREEN_SIZE_X, SCREEN_SIZE_Y / 2}, 0x238E23);
	get_direction(cub);
	drawline(cub, (t_point){ SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 2}, get_mouse_position(cub));
	drawmap(cub);
	move();
	raycast(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->game.img, SCREEN_SIZE_X / 2, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->game.img);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image.img, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->image.img);
	game_loop(cub);
	return (1);
}
