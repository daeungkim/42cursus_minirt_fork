/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakim <dakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:23:56 by cjaimes           #+#    #+#             */
/*   Updated: 2020/07/07 12:33:33 by dakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	bcgrd_colour(int lvl, t_data *d)
{
	if (d->has_ref)
		return (encode_rgb(50 * 0.94, 50 * 0.975, 50 * 0.94));
	return (encode_rgb(50 * pow(0.94, lvl),
			50 * pow(0.975, lvl), 50 * pow(0.94, lvl)));
}

static void	init_pixel(t_data *d, int i, int j)
{
	d->t = -1;
	// object와의 거리 저장하는 변수 초기화
	d->ref_lvl = 0;
	// light계산에 필요한 변수로 추정 / 초기화
	d->ray = compute_ray(d, d->current_cam, j, i);
	// 픽셀의 스크린상의 위치 계산하는 함수로 추정
	// 잘 이해가 가지 않음
	// maths/ray_maths.c에 있음
	d->ray_origin = d->current_cam->pos;
	d->out = 1;
	d->has_ref = 0;
}

// 각각의 스레드에서 랜더링을 수행하는 함수
void		*compute_render_t(void *data)
{
	int			i;
	int			j;
	t_data		*d;

	d = data;
	i = d->start - 1;
	d->workable = d->data_add + (d->pixsizeline / 4) * d->start;
	// 스크린상의 픽셀값을 구하는 과정 수행
	while (++i < d->end)
	{
		if (i != d->start)
			d->workable += d->pixsizeline / 4;
		j = -1;
		while (++j < d->res.x)
		{
			init_pixel(d, i, j);
			// 각각의 픽셀이 스크린상에서 어디에 위치하는지 계산
			if ((d->cur_obj = find_closest_hit(d)))
				d->workable[j] = calc_colour_from_light(*d, d->cur_obj);
			else
				d->workable[j] = bcgrd_colour(d->ref_lvl, d);
		}
	}
	d->cur_obj = 0;
	return (NULL);
}

void		multithread_render(t_data *data)
{
	pthread_t	th[CORES];
	t_data		dups[CORES];
	int			i;

	i = -1;
	while (++i < CORES)
	{
		// 스레드 4개 생성으로 추정 쿼드코어?
		ft_memcpy((void *)&dups[i], (void *)data, sizeof(t_data));
		// 스레드 개수만큼 t_data변수를 복사
		dups[i].start = data->res.y / CORES * i;
		dups[i].end = data->res.y / CORES * (i + 1);
		// 한 스레드당 화면의 1/cores를 담당하는것 같음
		dups[i].end = i == CORES - 1 ? data->res.y : dups[i].end;
		// 마지막 스레드인경우 세로 해상도의 끝까지 다루도록 설정
		pthread_create(&th[i], NULL, compute_render_t, &dups[i]);
		// 각각의 스레드에서 compute_render_t함수 실행
	}
	while (i-- > 0)
	{
		// 생성된 쓰레드를 받아오는 부분
		pthread_join(th[i], NULL);
	}
	// 생성된 이미지를 화면에 넣어줌
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->mlx_img, 0, 0);
}
