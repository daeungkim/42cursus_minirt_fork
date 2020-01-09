/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 00:05:32 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/09 13:56:38 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	set_bmp(t_bmp *bmp, t_data *data)
{
	bmp->type[0] = 0x42;
	bmp->type[1] = 0x4D;
	bmp->size = 54 + data->res.x * data->res.y * 3;
	bmp->reserve = 0;
	bmp->offset = 54;
	bmp->dib_size = 40;
	bmp->width = data->res.x;
	bmp->height = data->res.y;
	bmp->plane = 1;
	bmp->bpp = 24;
	bmp->copmression = 0;
	bmp->array_size = data->res.x * data->res.y * 3;
	bmp->x_res = 2835;
	bmp->y_res = 2835;
	bmp->colour = 0;
	bmp->imp_colour = 0;
}

void	write_header(const int fd, t_bmp *bmp)
{
	write(fd, &(bmp->type), 2);
	write(fd, &(bmp->size), 4);
	write(fd, &(bmp->reserve), 4);
	write(fd, &(bmp->offset), 4);
	write(fd, &(bmp->dib_size), 4);
	write(fd, &(bmp->width), 4);
	write(fd, &(bmp->height), 4);
	write(fd, &(bmp->plane), 2);
	write(fd, &(bmp->bpp), 2);
	write(fd, &(bmp->copmression), 4);
	write(fd, &(bmp->array_size), 4);
	write(fd, &(bmp->x_res), 4);
	write(fd, &(bmp->y_res), 4);
	write(fd, &(bmp->colour), 4);
	write(fd, &(bmp->imp_colour), 4);
}

int		save_image(t_data *data)
{
	t_bmp	bmp;
	int		fd;
	int		x;
	int		y;
	char	*add;

	ft_putstr("Saving...\n");
	add = (char *)data->data_add;
	set_bmp(&bmp, data);
	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	write_header(fd, &bmp);
	y = data->res.y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < data->res.x)
		{
			write(fd, &(add[(y * data->res.x + x) * 4]), 3);
			x++;
		}
		y--;
	}
	close(fd);
	ft_putstr("Save done!\n");
	return (0);
}
