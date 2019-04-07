#include "ft_nm_otool.h"



static int  ft_parser_arch32(char *data, int flag)
{
}

static int  ft_parser_arm(char *data, int flag)
{
    struct ar_hdr   *hdr_arm;
    struct ranlib	*ranlib;
	struct ranlib	elem;
	int             i;
    int             size;

	hdr_arm = (struct ar_hdr*)data;
    i = ft_atoi(ft_strchr(hdr_arm->ar_name, '/') + 1);
   size = *((int*)hdr_arm + sizeof(struct ar_hdr) + i);
   size /= sizeof(struct ranlib);
   ranlib = (struct ranlib*)data + sizeof(*hdr_arm) + i + 4;
   i = -1;
   while(++i < size)
   	elem = ranlib[i];
	return (EXIT_SUCCESS);
}

static int  ft_parser_fat(char *data, int flag)
{
}

int         ft_data_parser(char *file_name, char *data, int flag)
{
    unsigned int    magic;
    int             res;//?

	magic = *(unsigned int *)data;
	if (magic == MH_MAGIC_64)
        return (ft_parser_arch64(data, flag));
	if (magic == MH_MAGIC)
        return (ft_parser_arch32(data, flag));
    if (magic == FAT_MAGIC || magic == FAT_CIGAM)
        return (ft_parser_fat(data, flag));
    if (!ft_strncmp(data, ARMAG, SARMAG))
        return (ft_parser_arm(data + SARMAG, flag));
    return 0;
}