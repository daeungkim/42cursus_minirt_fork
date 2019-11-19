/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:31:26 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/19 13:56:29 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <unistd.h>
int encode_rgb(int red, int green, int blue)
{
	return ((((red << 8) + green) << 8) + blue);
}

void draw_rect(void *mlx, void *win, int x, int y, int color, int height, int width)
{
	int scanner;

	scanner = 0;
	while (height--)
	{
		scanner = width;
		while (scanner--)
			mlx_pixel_put(mlx, win, x + scanner, y + height, color);
	}
}

int main()
{
	void *mlx_ptr;
	void *win_ptr;
	
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Dat_window");
	draw_rect(mlx_ptr, win_ptr, 50, 50, encode_rgb(255, 125, 0), 200, 300);
	//mlx_pixel_put(mlx_ptr, win_ptr, 50 , 50, 0XFFFFFF);
	mlx_loop(mlx_ptr);
	return (0);
}