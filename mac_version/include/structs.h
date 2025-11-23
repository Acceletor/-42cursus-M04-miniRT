#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_vars
{
    void *mlx;
    void *win;
} t_vars;

typedef struct s_vec
{
    double x;
    double z;
    double y;
} t_vec;

// store the result of ray-object intersect
// raytracer updates this as it finds the nearest object
typedef struct s_inter  
{
    double t; // distance to intersection along the ray
    t_vec color; // final computed color at this point (after shading)
    t_vec hit; // the exact hit point = ray.orig + t * ray.dir
    t_vec norm; //surface normal at the hit point
} t_inter;


/* ====== Global element (appear once)======= */
typedef struct s_amb
{
    bool is_set;
    double ratio;
    t_vec color;
}   t_amb;

typedef struct s_cam
{
    bool is_set;
    t_vec pos;
    t_vec dir; // [-1, 1]
    double fov; // [0, 180]
} t_cam;

typedef struct s_light // at least 1
{
    t_vec pos;
    double ratio;
    t_vec color;
    struct s_light *next;
} t_light;


/* ====== Objects ======= */

typedef enum e_obj_type
{
    OBJ_SPHERE,
    OBJ_PLANE,
    OBJ_CYLINDER
} t_obj_type;

typedef struct s_objs
{
    t_obj_type type;
    void *data;
    struct s_objs *next;
} t_objs;

typedef struct s_sphere
{
   t_vec center;
   double diameter;
   t_vec color;
} t_sphere;

// typedef struct s_plane
// {
//     t_vec3 point;
//     t_vec3 normal
// } t_plane;


typedef struct s_scene
{
    t_vec col;
    t_cam cam;
    t_light *light;
    t_amb amb;
    t_objs *objs;
} t_scene;

typedef struct s_collector
{
    void * adr;
    struct s_collector *next;
} t_collector;


#endif