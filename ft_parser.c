#include "ft_nm_otool.h"


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
   while(++i < size) //?????
   	elem = ranlib[i];
	return (EXIT_SUCCESS);
}