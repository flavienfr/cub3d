
#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>//-> strerror
# include <errno.h>
# include <math.h>

# include <stdio.h>// -> <errno.h>
# define DP printf("%s : %d\n", __FILE__, __LINE__ );

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"

//#define WINDOW_X 500
//#define WINDOW_Y 500
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
** player config
*/
# define MOVE_SPEED 100.0
# define ROTATE_SPEED 0.5
# define FOV 60
/*
** map other info
*/
# define TILE_SIZE 30 //widow_x / num_col

typedef struct  s_map
{
	char	**map;
	int		map_row;
	int		map_col;
	int		player_x;
	int		player_y;
	float	player_dir;
	int		tile;
}               t_map;

typedef struct  s_player
{
	int		x;
	int		y;
	int		turn_dir;
	int		walk_dir;
	float 	rotate_angle;
	float	move_speed;
	float	rotate_speed;

}               t_player;

typedef struct  s_info
{
	void			*mlx_ptr;
	void			*win_ptr;

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
	struct s_player *player;
	int				save;
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

#endif