/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakim <dakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:31:26 by cjaimes           #+#    #+#             */
/*   Updated: 2020/07/07 13:01:28 by dakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mini_rt.h"
#include "key.h"
#include <unistd.h>
#include <time.h>

// t_data 변수 초기화 용도
void	set_data(t_data *data)
{
	data->save = 0;
	data->res.loaded = 0;
	data->amb.loaded = 0;
	data->cameras = 0;
	data->objects = 0;
	data->lights = 0;
	data->no_render_amb = encode_rgb(200, 200, 200);
	data->bckgd_colour = encode_rgb(50, 50, 50);
	data->render_mode = 1;
	data->cam_num = 0;
	data->obj_selected = 0;
	data->max_ref = 0;
}

void	print_data(t_data *d)
{
	t_list		*lst;
	t_camera	*camera;
	while (lst)
	{
		camera = lst->content;

	}

}

// raytracing을 execute시키는 함수인것 같음
int		exe_rt(t_data *d, char *file)
{
	if (!load_data(d, file))
		return (0);
		/*
	// 데이터 파싱 부분으로 추정 / parser/parser.c에 있음
	// 파일을 열고 문장단위로 데이터를 가져오는 함수
	d->mlx_ptr = mlx_init();
	if (!(d->mlx_img = mlx_new_image(d->mlx_ptr, d->res.x, d->res.y)))
		return (0);
	d->data_add = (int *)mlx_get_data_addr(d->mlx_img, &(d->pixsize),
					&(d->pixsizeline), &(d->endian));
	d->mlx_win = mlx_new_window(d->mlx_ptr, d->res.x, d->res.y, "Dat_window");
	// mlt 세팅
	d->current_cam = d->cameras->content;
	// 현재의 카메라 설정
	d->max_cam = ft_lstsize(d->cameras);
	// 최대 카메라 개수 저장
	multithread_render(d);
	// 레이트레이싱 수행
	// render.c에 있음
	*/
	return (1);
}

int		main(int ac, char **av)
{
	t_data	data;

	set_data(&data);
	// data 초기화
	if (ac == 3)
		if (!ft_strcmp(av[2], "-save"))
			data.save = 1;
	// 이미지 파일 저장여부 저장
		return (0);
	// 변수가 들어오지 않거나 두개 이상 들어온경우 에러처리
	// time(NULL);
	// 용도를 모르겠음 / 주석처리하여도 큰 문제 없이 돌아가는것 같음
	if (!exe_rt(&data, av[1]))
		return (0);
	// raytracing을 execute하는 함수


	/*
	if (data.save)
		return (save_image(&data, 0, 0));
	// 이미지파일로 만들어야하는 경우 이미지 저장을 수행하는것으로 추정
	mlx_hook(data.mlx_win, 2, (1L << 0), key_release, &data);
	mlx_hook(data.mlx_win, 17, (1L << 17), proper_exit, &data);
	mlx_hook(data.mlx_win, 5, (1L << 0), handle_click, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_window(data.mlx_ptr, data.mlx_win);
	// mlx 세팅관련 함수
	*/
	return (0);
}
