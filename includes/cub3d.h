
#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>//-> strerror
# include <errno.h>
# include <math.h>
//#include <time.h> //droit de l'utiliser ??

# include <stdio.h>// -> <errno.h>
# define DP printf("%s : %d\n", __FILE__, __LINE__ );

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"

# define DEFAULT_WINDOW_X 1920//variable ordi
# define DEFAULT_WINDOW_Y 1080
# define MAP_INFO "012NSEW"
# define PLAYER_INIT_POS "NSEW"
/*
** Keys
*/
# define ESC 53
# define UP 13
# define DOWN 1
# define RIGHT 2
# define LEFT 0
# define SPACE 49
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
# define MOVE_SPEED 2
# define ROTATE_SPEED 2.5
# define FOV (70 * (M_PI / 180))
# define FPS 30 // pas besoin
# define PLAYER_WIDTH 10
/*
** map other info
*/
# define TILE_SIZE 30//widow_x / num_col
# define MINI_MAP 0.3
/*
** texuture info
*/
# define TEXTURE_HEIGHT 64
# define TEXTURE_WIDTH 64
int texture[TEXTURE_WIDTH][TEXTURE_HEIGHT];

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;		
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_ray
{
	float		angle;
	float		wall_x;
	float		wall_y;
	float		dist;
	int			is_vert;
	int			is_facing_up;
    int			is_facing_down;
	int			is_facing_right;
    int			is_facing_left;
	int 		stip_height;
    char		wall_content;
}				t_ray;

typedef struct	s_map
{
	char		**map;
	int			map_row;
	int			map_col;
	int			player_x;
	int			player_y;
	float		player_dir;
	int			tile;
}               t_map;

typedef struct	s_player
{
	float		x;
	float		y;
	int			turn_dir;
	int			walk_dir;
	float 		rotate_angle;
	float		move_speed;
	float		rotate_speed;

}               t_player;

typedef struct	s_info
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
	int				res_x;
	int				res_y;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*s;
	int 			f;
	int 			c;
	struct s_map 	*map;
	struct s_player player;
	float			last_frame;
	int				save;
	int				buf_rgb[DEFAULT_WINDOW_X][DEFAULT_WINDOW_Y];
}		        t_info;

t_ray   ray[800];
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
void	error_read_file_info(int fd, t_info *info);
void	error_global(char *s, t_info *info);
void	error_strerror(t_info *info);
/*
*	utils in file_read2.c   
*/
int		first_in_set(char c, char *set);
/*
** maths_utils.c
*/
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
void	print_ceiling_floor(t_info *info);
void	render_player(t_info *info, t_player *player);
void	render_ray(t_info *info);
void	clear_buf_rgb(t_info *info, int color);
void	write_buf_rgb(t_info *info);
void    generete_wall(t_info *info, t_player *player);
int 	loop_cub3d(t_info *info);
/*
** semi order
*/
int		keys_set(t_info *info);
int		is_wall(t_map *map, float x, float y);
void	caste_all_ray(t_info *info, t_player *player);

#endif