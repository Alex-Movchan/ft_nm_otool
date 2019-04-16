#include "ft_nm_otool.h"

static unsigned int		rewers(int nb)
{
    unsigned int res;

    res = 0;
    res |= ((nb & 0xFF) << (3 * BYTE));
    res |= ((nb & 0xFF00) << BYTE);
    res |= ((nb & 0xFF0000) >> BYTE);
    res |= ((nb & 0xFF000000) >> (3 * BYTE));
    return (res);
}

unsigned int get_fat_offset(void *ptr)
{
    struct fat_header	*fat_headr;
    struct fat_arch		*arch;
    int					i;
    int					count;
    uint32_t			offset;

    if (!ptr)
        return (EXIT_FAILURE);
    offset = 0;
    fat_headr = (struct fat_header*)ptr;
    arch = (struct fat_arch*)(ptr + sizeof(fat_headr));
    count = rewers(fat_headr->nfat_arch);
    i = -1;
    while (++i < count)
    {
        if (CPU_TYPE_X86_64 == rewers(arch->cputype))
        {
            offset = rewers(arch->offset);
            break ;//?
        }
        arch = (struct fat_arch*)((void*)arch + sizeof(arch));
    }
    return (offset);
}

int ft_event_fat_hendler(t_object *ptr_obj)
{
    void            *data_cpy;
    unsigned int    offset;

    if (!ptr_obj)
        return (EXIT_FAILURE);
    if ((offset = get_fat_offset(ptr_obj->event.data_buff)) == 0)
        return (EXIT_FAILURE);
    data_cpy = ptr_obj->event.data_buff;
    ptr_obj->event.data_buff = data_cpy + offset;
    ptr_obj->event.offset += offset;
}