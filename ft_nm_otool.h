
#ifndef FT_NM_OTOOL_H
#define FT_NM_OTOOL_H

#include "libft/libft.h"
#include <mach-o/loader.h>
#include <mach-o/ranlib.h>
#include <mach-o/fat.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <ar.h>

#define SET_BIT(a, n) ((a) |= (1 << n))
#define RESET_BIT(a, n) ((a) &= ~(1 << n))
#define CHECK_BIT(a, n) ((a) & (1 << n))
#define ARCH_64_SHOW_ADDR 2
#define BYTE 8


#define ARCH_64 2
#define ARCH_32 1

#define GET_ARCH() (sizeof(void*) == 8 ? ARCH_64 : ARCH_32)
#define FLAG_SECTIONS 6
#define HEX 16
# define HEX_BASE "0123456789abcdef"
#ifndef FT_OTOOL
#ifndef FT_NM
#define PROGRAM_STATE 2
#else
#define PROGRAM_STATE 2
#endif
#else
#define PROGRAM_STATE 1
#endif

typedef enum	e_crash_lvl
{
    SUCCESS,
    ERROR_EVENT,
    WORNING,
    SYSTEM_ERROR,
    NULL_PTR,
    CRITICAL

}               t_crash_lvl;

typedef enum	e_program_state
{
    UNKNOWN_PROGRAM,
    OTOOL_PROGRAM,
    NM_PROGRAM
}               t_ptogram_state;

typedef enum	e_arch64_data_type
{
    UNKNOWN_DATA,
    SECTION,
    SYMTAB,
    FUNC_NAME
}				t_arch64;

typedef enum	e_arch
{
    UNKNOWN,
	FAT,
	ARCH32,
	ARCH64,
	ARMIVE
}				t_arch;

struct				s_object;


typedef struct		s_data
{
	struct s_data	*next;
	void			*ptr_data;
	unsigned long	addr;
	char			data_flag;
	int 			type;
	int 			seqnum;
}					t_data;

typedef struct		s_arch_methods
{
	int             (*constructor_mtd)(struct s_object *);
    int             (*destructor_mtd)(struct s_object *);
    int             (*parser)(struct s_object *);
    int             (*sort_cmp)(void*, void*);
    t_data *(*new_data)(struct s_object *, void *ptr_data, int type);
    void            (*print)(struct s_object *);
}					t_arch_methods;

typedef struct		s_event
{
	void			(*event_constructor)(struct s_object *);
	int				(*event_destructor)(struct s_object *);
	int				(*event_validetion)(struct s_object *);
	int				(*ft_event_hendler)(struct s_object *);
	int				(*event_hendler_destructor)(struct s_object *);
	int				(*event_crash)(struct s_object *, char *, char *, t_crash_lvl );
    int			(*cllback_fat)(struct s_object *);
	void            (*free_data)(t_data **);
	char			*file_name;
	void			*data_buff;
	t_data			*data;
    t_arch_methods  methods;
	struct stat		spcf;
	unsigned int    offset;
    t_crash_lvl     error_lvl;
}					t_event;

typedef struct      s_object
{
    void            (*object_cronstructor)(struct s_object *);
    int             (*object_destructor)(struct s_object *);
    int			    (*object_crash_destructor)(struct s_object *, char *, char *);
    int			    (*object_process)(struct s_object *, int, char **);
    t_event         event;
    int    			flag;
}				    t_object;


void            ft_event_init(t_object *ptr_obj);
int         	ft_error(char *msg, char *param);
void            ft_object_cronstructor(t_object *ptr_obj);
int             ft_destructor_mtd(t_object *ptr_obj);
int             ft_constructor_mtd(t_object *ptr_obj);
int             ft_parser_arch64(t_object *ptr_obj);
int             ft_cmp_arch64(void *ptr1, void *ptr2);
int     ft_cmp_arch32(void *ptr1, void *ptr2);
void            ft_free_datalist(t_data **head);
t_data          *ft_add_datalist(t_object *ptr_obj, void *ptr_data, int type);
int     ft_event_destructor(t_object *ptr_obj);
int  ft_event_fat_hendler(t_object *ptr_obj);
int     ft_pars_archv(t_object *ptr_obj);
void    ft_print_arch64(t_object *ptr_obj);
int  ft_parser_arch32(t_object *ptr_obj);
void    ft_print_arch32(t_object *ptr_obj);
void    ft_print_otool_arch64(t_object *ptr_obj);
uint8_t ft_get_func_type64(t_data *ptr_data, uint8_t type, uint8_t n_sect);
void ft_print_archv(t_object *ptr_obj);
int     get_archv_arch64(t_object *ptr_obj, void *ptr);
int     get_archv_arch32(t_object *ptr_obj, void *ptr);
int ft_object_event_hendler(t_object *ptr_obj);

#endif
