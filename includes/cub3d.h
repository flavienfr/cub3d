
#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>//-> strerror
# include <errno.h>
# include <math.h>

# include <stdio.h>// -> <errno.h>
//# define DP printf("%s : %d\n", __FILE__, __LINE__ );

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
/*
** Default info
*/
# define DEFAULT_WINDOW_X 2560
# define DEFAULT_WINDOW_Y 1395
# define MAP_INFO "012NSEW"
# define PLAYER_INIT_POS "NSEW"
# define TILE_SIZE 1
/*
** Keys
*/
# define ESC 53
# define UP 13
# define DOWN 1
# define RIGHT 2
# define LEFT 0
# define SPACE 49
# define SHIFHT 257
/*
** color
*/
# define BLUE 255
# define RED 16711680
# define WHITE 16777215
# define BLACK 0
# define GREEN 65280
# define YELLOW 16776960
# define GREY 6579300
/*
** player config
*/
# define MOVE_SPEED 0.13
# define ROTATE_SPEED 2.5
# define FOV 60
# define RUN_SPEED 0.15
/*
** Mini map info
*/
# define MINI_MAP 0.2
/*
** texuture info
*/
# define NB_TEXTURE 5
# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3
# define TEX_S 4
# define TEXTURE_SIZE 64
/*
** Ray 
*/
# define FAC_UP 0
# define FAC_DOWN 1
# define FAC_LEFT 2
# define FAC_RIGHT 3

typedef struct	s_mini_map
{
	int		map;
	int		player;
}               t_mini_map;

typedef struct  s_anchor
{
	int 	x;
	int 	y;
	int 	y_goal;
	int 	x_goal;
}		        t_anchor;

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;		
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_tex
{
	int		tex[TEXTURE_SIZE][TEXTURE_SIZE];
	char	*path;
	int		*data;
	void	*ptr;
	int		width;
	int		height;
	int		bpp;
	int		size_l;
	int		endian;
}				t_tex;

typedef struct	s_ray
{
	float		angle;
	float		wall_x;
	float		wall_y;
	float		dist;
	int			is_vert;
	int			face_ud;
	int			face_lr;
	int 		stip_height;
    int			wall_content;
}				t_ray;

typedef struct	s_map
{
	char		**map;
	int			map_row;
	int			map_col;
	float		player_x;
	float		player_y;
	float		player_dir;
	int			tile;//what is?
}               t_map;

typedef struct	s_player
{
	float		x;
	float		y;
	int			turn_dir_r;
	int			turn_dir_l;
	int			walk_dir_u;
	int			walk_dir_d;
	float 		rotate_angle;
	float		move_speed;
	float		rotate_speed;

}               t_player;

typedef struct	s_info
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				res_x;
	int				res_y;
	int 			f;
	int 			c;
	float			fov;
	int				save;
	t_mini_map		m_map;
	struct s_map 	*map;
	struct s_player player;
	t_img			img;
	t_ray   		ray[DEFAULT_WINDOW_X];
	t_tex			tex[NB_TEXTURE];
	int				buf_rgb[DEFAULT_WINDOW_X][DEFAULT_WINDOW_Y];
}		        t_info;
/*
*   file_check.c
*/
void    check_info(t_info *info, t_map *map);
/*
*   file_read.c
*/
void	read_file_info(char *file, char *save, t_info *info);
/*
*   file_read2.c
*/
int     parse_file_info(int fd, char *line, t_info *info);
/*
*   structure.c
*/
t_ray   inisialize_ray(t_ray ray, float ray_angle);
t_map   *map_initialization(t_info *info);
t_info  *info_initialization();
void    info_free(t_info *info);
/*
*   error.c
*/
void	free_all(t_info *info);
void	error_preso(char *s, t_info *info);
void	error_global(t_info *info);
void	error_global_close_fd(int fd, t_info *info);
/*
*	utils in file_read2.c   
*/
int		first_in_set(char c, char *set);
/*
** utils.c
*/
int		first_in_set(char c, char *set);
float	norm_angle(float angle);
float	dist_point(float x1, float y1, float x2, float y2);
float	deg_to_rad(float deg);
float	rad_to_deg(float rad);
/*
** player.c
*/
void	init_player_on_map(t_info *info, t_map *map, t_player *player);
void	player_movement(t_map *map, t_player *player);
/*
**	en vrac
*/
void	current_utc_time(struct timespec *ts);
void	render_map(t_info *info, t_map *map);
void	render_player(t_info *info, t_player *player);
void	render_ray(t_info *info);
void	clear_buf_rgb(t_info *info, int color);
void	write_buf_rgb(t_info *info);
void    generete_wall(t_info *info, t_player *player);
int		loop_cub3d(t_info *info);
void	init_textute(t_info *info);
/*
** semi order
*/
int		keys_set(t_info *info);
int		is_wall(t_map *map, float x, float y);
void	caste_all_ray(t_info *info, t_player *player);

#endif