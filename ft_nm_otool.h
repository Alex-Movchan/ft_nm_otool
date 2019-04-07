
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
    CRITICAL,
    MULL_PTR,
    SYSTEM_ERROR,
    WORNING,
    ERROR_EVENT
}               t_crash_lvl;

typedef enum	e_program_state
{
    UNKNOWN_PROGRAM,
    OTOOL_PROGRAM,
    NM_PROGRAM
}               t_ptogram_state;

typedef enum	e_arch
{
    UNKNOWN,
	FAT,
	ARCH32,
	ARCH64,
	ARMIVE
}				t_arch;

struct      s_object;

typedef struct s_dtata
{

}				t_data;

typedef struct	s_methods
{
	int        (*destructor_mtd)(struct s_object *);
    t_arch      (*get_event_arch)(struct s_object *);
    int         (*constructor_mtd)(struct s_object *);
    int			(*parser)(struct s_object *);
    void		(*print)(struct s_object *);
}				t_methods;

typedef struct s_event
{
    void         (*event_constructor)(struct s_object *);
    int         (*event_destructor)(struct s_object *);
    int         (*event_validetion)(struct s_object *);
    int         (*ft_event_hendler)(struct s_object *);
    int         (*event_hendler_destructor)(struct s_object *);
    int         (*event_crash)(struct s_object *, char *, char *, t_crash_lvl );
    int         (*cllback_fat)(struct s_object *);
    char        *file_name;
    char        *data_buff;
    t_data      *data;
    t_methods   methods;
    struct stat spcf;

}               t_event;

typedef struct      s_object
{
    void            (*object_cronstructor)(struct s_object *);
    int             (*object_destructor)(struct s_object *);
    int			    (*object_crash_destructor)(struct s_object *, char *, char *);
    int			    (*init_flag)(struct s_object *, int, char **);
    int			    (*object_process)(struct s_object *, int, char **);
    t_event         event;
    unsigned int    flag;
}				    t_object;



void            ft_event_init(t_object *ptr_obj);
int         	ft_error(char *msg, char *param);
int         	ft_check_flag(int ac, char **av);
int             pars_arch64_mtd(t_object *ptr_obj);
int             pars_arch32_mtd(t_object *ptr_obj);
void            ft_object_cronstructor(t_object *ptr_obj);
int             ft_destructor_mtd(t_object *ptr_obj);
int             ft_constructor_mtd(t_object *ptr_obj);


#endif
