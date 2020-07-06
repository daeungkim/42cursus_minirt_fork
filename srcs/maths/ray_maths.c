/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_maths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakim <dakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:12:36 by cjaimes           #+#    #+#             */
/*   Updated: 2020/07/06 15:38:04 by dakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// 오브젝트에 도달했는지 확인
static void	check_first_hit(t_geo **hit_obj, t_rt_param p,
			double *hit, t_list *first)
{
	if (p.v && p.i > 0 && (*hit < 0 || p.i < *hit))
	{
		*hit = p.i;
		*hit_obj = first->content;
	}
	if (p.v_2 && p.i_2 > 0 && (*hit < 0 || p.i_2 < *hit))
	{
		*hit = p.i_2;
		*hit_obj = first->content;
	}
	if (p.v_3 && p.i_3 > 0 && (*hit < 0 || p.i_3 < *hit))
	{
		*hit = p.i_3;
		*hit_obj = first->content;
	}
	if (p.v_4 && p.i_4 > 0 && (*hit < 0 || p.i_4 < *hit))
	{
		*hit = p.i_4;
		*hit_obj = first->content;
	}
}

t_rt_param	set_param(t_vector3 o, t_vector3 r, double i, void *ob)
{
	t_rt_param param;

	param.origin = o;
	param.ray = r;
	param.i = i;
	param.v = 0;
	param.i_2 = -1;
	param.v_2 = 0;
	param.i_3 = -1;
	param.v_3 = 0;
	param.i_4 = -1;
	param.v_4 = 0;
	param.object = ob;
	return (param);
}

/*
** We will rotate around each axis depending on orientation vector given
*/

// 각각의 픽셀의 스크린상의 좌표를 구하는 함수
t_vector3	compute_ray(const t_data *data, t_camera *cam,
						const double x, const double y)
{
	double		sc_height;
	double		sc_width;
	double		pix_shift;
	t_vector3	base_dir;
	t_vector3	ray;

	base_dir = scalar_vect(cam->vector_x, (double)SCREEN_L);
	// 카메라의 보는 뱡향이 (0,0,0)일경우 vector_x = (1, 0, 0) 따라서 base_dir = (10, 0, 0)
	// 스크린의 가로를 10으로 가정했을 때 스크린의 가로방향의 길이와 방향을 가진 벡터 생성
	sc_width = (double)SCREEN_L * tan(to_rad(cam->fov / 2)) * 2;
	// to_rad = 각도를 라디안으로 바꾸는 함수로 추정
	// sc_width = 가로 / 거리
	sc_height = sc_width * (data->res.y / data->res.x);
	// sc_height = 세로 / 거리
	pix_shift = sc_width / ((double)data->res.x - 1);
	// 한 픽셀의 값을 계산하고 다음 픽셀로 넘어갈 때 얼마식 이동해야하는지 계산
	/*
	ray = add_vect(base_dir, scalar_vect(cam->vector_z,
							((2 * (x + 0.5) - data->res.x) / 2) * pix_shift));
	ray = add_vect(ray, scalar_vect(cam->vector_y,
							((-2 * (y + 0.5) + data->res.y) / 2) * pix_shift));
	*/
	ray = add_vect(base_dir, scalar_vect(cam->vector_z,
							((2 * (x) - data->res.x) / 2) * pix_shift));
	ray = add_vect(ray, scalar_vect(cam->vector_y,
							((-2 * (y) + data->res.y) / 2) * pix_shift));
	// 원래는 x와 y에 0.5를 더해주었는데
	ray = normalise_vector(ray);
	// 계산된 벡터를 노말라이즈 함
	return (ray);
}

// 가장 가까운 object를 계산
t_geo		*find_closest_hit(t_data *d)
{
	t_geo		*hit_obj;
	t_list		*first;
	t_rt_param	p;

	hit_obj = 0;
	first = d->objects;
	// 모든 object와
	while (first)
	{
		p = set_param(d->ray_origin, d->ray, -1, 0);
		// p값을 초기화하는것 같음
		if (raytrace(first->content, &p))
		{
			// raytrace함수 maths/get_math/geo.c에 있음
			// raytrace함수가 ray와 물체가 만나는지 체크하는것 같음
			check_first_hit(&hit_obj, p, &(d->t), first);
		}
		//
		first = first->next;
	}
	if (hit_obj && hit_obj->ref && d->t > 0 && d->ref_lvl < d->max_ref)
		return (check_reflection(d, hit_obj));
	else if (hit_obj && hit_obj->gl &&
			hit_obj->obj_type == e_sphere && d->t > 0)
		return (check_refraction(d, hit_obj));
	return (hit_obj);
}

t_geo		*find_closest_hit_non_ref(t_data *data)
{
	t_geo		*hit_obj;
	t_list		*first;
	t_rt_param	p;

	hit_obj = 0;
	first = data->objects;
	while (first)
	{
		p = set_param(data->current_cam->pos, data->ray, -1, 0);
		if (raytrace(first->content, &p))
			check_first_hit(&hit_obj, p, &(data->t), first);
		first = first->next;
	}
	return (hit_obj);
}
