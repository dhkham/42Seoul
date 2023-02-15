/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:25:28 by dkham             #+#    #+#             */
/*   Updated: 2023/02/15 20:42:01 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	mandelbrot(t_data *frctl)
{
	int	i;
	int	j;

	i = 0;
	while (i < frctl->width)
	{
		j = 0;
		while (j < frctl->height)
		{
			get_c(frctl, i, j);
			get_iter(frctl);
			if (frctl->iter == frctl->max)
				frctl->new_col = 0x00000000;
			else
				frctl->new_col = frctl->base_col * frctl->iter;
			my_mlx_pixel_put(frctl, i, j, frctl->new_col);
			j++;
		}
		i++;
	}
}

void	get_c(t_data *frctl, int x, int y)
{
	frctl->c_a =  (x - ((double)frctl->width / 2)) / ((double)frctl->width / 4) * frctl->zoom;
	frctl->c_b = -(y - ((double)frctl->height / 2)) / ((double)frctl->height / 4) * frctl->zoom;
}

void	get_iter(t_data *frctl)
{
	double	x;
	double	y;
	double	tmp;

	frctl->iter = 0;
	frctl->max = 100;
	x = 0;
	y = 0;
	while (x * x + y * y <= 2 * 2 && frctl->iter < frctl->max)
	{
		tmp = (x * x) - (y * y) + frctl->c_a;
		y = (2 * x * y) + frctl->c_b;
		x = tmp;
		frctl->iter = frctl->iter + 1;
	}
}
