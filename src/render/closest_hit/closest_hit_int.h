/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_hit_int.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:54:01 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 13:48:53 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOSEST_HIT_INT_H
# define CLOSEST_HIT_INT_H

# include "../render_int.h"

/* Helper struct for cylinder intersection calculations */
typedef struct s_cyl_vars
{
	t_vec3 oc;        /* Origin to cylinder center */
	t_vec3 d_proj;    /* Ray direction projected onto radial plane */
	t_vec3 oc_proj;   /* Origin-to-center projected onto radial plane */
	double abc[3];    /* Quadratic coefficients [a, b, c] */
	double disc;      /* Discriminant */
	double t_vals[2]; /* Two intersection distances */
}				t_cyl_vars;

/* Sphere */
int		intersect_sphere(t_ray *ray, t_sphere *sphere, double *t);
void	process_sphere_hit(t_ray *ray, t_object *obj, double t, t_hit *closest);

/* Plane */
int		intersect_plane(t_ray *ray, t_plane *plane, double *t);
void	process_plane_hit(t_ray *ray, t_object *obj, double t, t_hit *closest);

/* Cylinder */
int		intersect_cylinder(t_ray *ray, t_cylinder *cyl, double *t);
void	process_cylinder_hit(t_ray *ray, t_object *obj, double t,
			t_hit *closest);

/* Cone */
int		intersect_cone(t_ray *ray, t_cone *cone, double *t);
void	process_cone_hit(t_ray *ray, t_object *obj, double t, t_hit *closest);

#endif
