/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 00:05:32 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/14 11:35:53 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <time.h>

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

char	*get_current_time_name(char *str)
{
	time_t		t;
	struct tm	*info;
	size_t		str_len;

	time(&t);
	ft_memset(str, 0, 50);
	info = localtime(&t);
	ft_strcpy(str, "screenshot_");
	str_len = strftime(str + 11, 39, "%F-%T", info);
	ft_strcat(str, ".bmp");
	free(info);
	return (str);
}

int		save_image(t_data *data, int x, int y)
{
	t_bmp	bmp;
	int		fd;
	char	*add;
	char	name[50];

	ft_putstr("Saving...\n");
	add = (char *)data->data_add;
	set_bmp(&bmp, data);
	fd = open(get_current_time_name(name), O_CREAT | O_WRONLY | O_TRUNC, 0666);
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
