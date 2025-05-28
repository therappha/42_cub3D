#include "../includes/cub.h"

float move_towards(float start, float goal, float step);

bool is_colliding(t_point posA, t_point sizeA, t_point posB, t_point sizeB);

void	reset_collisions(t_cub *cub)
{
	cub->player.collision.is_colliding = false;
	cub->player.collision.right = false;
	cub->player.collision.left = false;
	cub->player.collision.up = false;
	cub->player.collision.down = false;
}

char	get_tile(t_cub *cub, int x, int y);

void	move(t_cub *cub)
{
	if (!cub->player.is_on_ground)
	{
		cub->player.velocity.y += GRAVITY * cub->delta;
	}
	else
	{
		cub->player.velocity.y = 0;
	}
	if (cub->player.jump && cub->player.is_on_ground)
	{
		cub->player.is_on_ground = false;
		cub->player.velocity.y = -JUMP_SPEED;
		cub->player.jump = false;
	}

	if (cub->player.direction.x != 0)
	{
		cub->player.velocity.x += cub->player.direction.x * ACCEL * cub->delta;
		cub->player.velocity.x = clamp(cub->player.velocity.x, -MAX_SPEED, MAX_SPEED);
	}
	else if (fabs(cub->player.velocity.x) > 0)
	{
		if (cub->player.velocity.x > 0)
			cub->player.velocity.x = move_towards(cub->player.velocity.x, 0, FRICTION * cub->delta);
		else if (cub->player.velocity.x < 0)
			cub->player.velocity.x = move_towards(cub->player.velocity.x, 0, FRICTION * cub->delta);
	}
	else
		cub->player.velocity.x = 0;

	t_point newpos;
	newpos.x = cub->player.pos.x + cub->player.velocity.x * cub->delta;
	newpos.y = cub->player.pos.y + cub->player.velocity.y * cub->delta;

	if (cub->player.velocity.x <= 0)
	{
		if (ft_strchr("BP1", get_tile(cub, newpos.x + 0.0f, cub->player.pos.y + 0.0f)) || ft_strchr("BP1", get_tile(cub, newpos.x + 0.0f, cub->player.pos.y + 0.9f)))
		{
			newpos.x = (int)newpos.x + 1;
			cub->player.velocity.x = 0;
		}

	}
	else
	{
		if (ft_strchr("BP1", get_tile(cub, newpos.x + 1.0f, cub->player.pos.y + 0.0f)) || ft_strchr("BP1", get_tile(cub, newpos.x + 1.0f, cub->player.pos.y + 0.9)))
		{
			newpos.x = (int)newpos.x;
			cub->player.velocity.x = 0;

		}
	}
	if (cub->player.velocity.y < 0)
	{
			if (ft_strchr("BP1", get_tile(cub, newpos.x + 0.0f, newpos.y + 0.0f)) || ft_strchr("BP1", get_tile(cub, newpos.x + 0.9f, newpos.y + 0.0f)))
			{
				newpos.y = (int)newpos.y + 1;
				cub->player.velocity.y = 0;

			}
	}
	else
	{
			if (ft_strchr("BP1", get_tile(cub, newpos.x + 0.0f, newpos.y + 1.0f)) || ft_strchr("BP1", get_tile(cub, newpos.x + 0.9f, newpos.y + 1.0f)))
			{
				newpos.y = (int)newpos.y;
				cub->player.velocity.y = 0;
				cub->player.is_on_ground = true;
			}
			else
				cub->player.is_on_ground = false;
	}

		cub->player.pos.x = newpos.x;
		cub->player.pos.y = newpos.y;
}

char	get_tile(t_cub *cub, int x, int y)
{
	if (x >= 0 && x < cub->map_width && y >= 0 && y < cub->map_height)
	{
		return cub->map[y][x];
	}
	else
		return '.';
}

float move_towards(float start, float goal, float step)
{
	if (start < goal)
		return (fminf(start + step, goal));
	else if (start > goal)
		return (fmaxf(start - step, goal));
	else
		return (start);
}

bool is_colliding(t_point posA, t_point sizeA, t_point posB, t_point sizeB)
{
	float leftA = posA.x;
	float rightA = posA.x + sizeA.x;
	float upA = posA.y;
	float downA = posA.y + sizeA.y;
	float leftB = posB.x;
	float rightB = posB.x + sizeB.x;
	float upB = posB.y;
	float downB = posB.y + sizeB.y;

	// Standard AABB collision test
	if (!(rightA > leftB && leftA < rightB && downA > upB && upA < downB))
		return (false);

	return true;
}
