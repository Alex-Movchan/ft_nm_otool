
#ifndef FT_NM_OTOOL_H
#define FT_NM_OTOOL_H

#include "libft/libft.h"
#include "mach-o/loader.h"
#include "mach-o/loadet.h"
#include "mach-o/ranlib.h"
#include "mach-o/fat.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <ar.h>

#define SET_BIT(a, n) ((a) |= (1 << n))
#define RESET_BIT(a, n) ((a) &= ~(1 << n))
#define CHECK_BIT(a, n) ((a) & (1 << n))
#define BYTE 8
#define FLAG_J  1
#define FLAG_U  2
#define FLAG_UP_U  3
#define FLAG_P  4
#define FLAG_R  5
#ifndef FT_OTOOL
#ifndef FT_NM
#define PROGRAM_STATE 0
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
	int 			seqnum;
}					t_data;

typedef struct		s_arch_methods
{
	int             (*constructor_mtd)(struct s_object *);
    int             (*destructor_mtd)(struct s_object *);
    t_arch          (*get_event_arch)(struct s_object *);
    int             (*parser)(struct s_object *);
    int             (*sort_cmp)(void*, void*);
    int (*new_data)(struct s_object *, void *, int);
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
    t_arch			(*cllback_fat)(struct s_object *);
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
    int			    (*init_flag)(struct s_object *, int, char **);
    int			    (*object_process)(struct s_object *, int, char **);
    t_event         event;
    int    			flag;
}				    t_object;


void            ft_event_init(t_object *ptr_obj);
int         	ft_error(char *msg, char *param);
int         	ft_check_flag(int ac, char **av);
int             pars_arch32_mtd(t_object *ptr_obj);
void            ft_object_cronstructor(t_object *ptr_obj);
int             ft_destructor_mtd(t_object *ptr_obj);
int             ft_constructor_mtd(t_object *ptr_obj);
int             ft_parser_arch64(t_object *ptr_obj);
int             ft_cmp_arch64(void *ptr1, void *ptr2);
int     ft_cmp_arch32(void *ptr1, void *ptr2);
void            ft_free_datalist(t_data **head);
int             ft_add_datalist(t_object *ptr_obj, void *ptr_data, int seqnum);
int     ft_event_destructor(t_object *ptr_obj);
t_arch ft_event_fat_hendler(t_object *ptr_obj);
int     ft_pars_archv(t_object *ptr_obj);


#endif
