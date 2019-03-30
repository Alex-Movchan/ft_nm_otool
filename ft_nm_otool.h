
#ifndef FT_NM_OTOOL_H
#define FT_NM_OTOOL_H

#include "libft/libft.h"
#include "loader.h"
#include "ranlib.h"
#include <fcntl.h>
#include <sys/stat.h>
# include <sys/mman.h>
#include <ar.h>

#define SET_BIT(a, n) ((a) |= (1 << n))
#define RESET_BIT(a, n) ((a) &= ~(1 << n))
#define CHECK_BIT(a, n) ((a) &= (1 << n))
#define FLAG_J  1
#define FLAG_U  2
#define FLAG_UP_U  3
#define FLAG_P  4
#define FLAG_R  5

typedef enum	s_arch
{
	FAT = 0,
	ARCH32,
	ARCH64,
	ARM
}				arch_t;

typedef struct s_dtata
{

}				data_t;

typedef struct	s_func
{
	int			(*parser)(char *bin, int flag, data_t data);
	void		(*print)(data_t data, int flag);

}				func_t;

int         	ft_error(char *msg, char *param);
int         	ft_check_flag(int ac, char **av);
int         	ft_data_parser(char *file_name, char *data, int flag);

#endif
