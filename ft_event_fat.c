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

static unsigned int get_fat_offset(void *ptr, int count)
{
    struct fat_header	*fat_headr;
    struct fat_arch		*arch;

    if (!ptr)
        return (EXIT_FAILURE);
    fat_headr = (struct fat_header*)ptr;
    arch = ptr + sizeof(struct fat_header) + sizeof(struct fat_arch) * count;
    return (fat_headr->magic == FAT_CIGAM ?  rewers(arch->offset) : arch->offset);
}

int ft_event_fat_hendler(t_object *ptr_obj)
{
    struct fat_header *fat_headr;
    unsigned int offset;
    unsigned int magic;

    int	count;
    int i;

    if (!ptr_obj)
        return (EXIT_FAILURE);
    fat_headr = (struct fat_header*)ptr_obj->event.data_buff;
    count =  fat_headr->magic == FAT_CIGAM ? rewers(fat_headr->nfat_arch) : fat_headr->nfat_arch;
    i = -1;
    while (++i < count)
    {
        offset = get_fat_offset(ptr_obj->event.data_buff, i);
        magic = *(unsigned int*)(ptr_obj->event.data_buff + offset);
        if (MH_MAGIC == magic && GET_ARCH() == ARCH_32)
            get_archv_arch32(ptr_obj, ptr_obj->event.data_buff + offset);
        else if (MH_MAGIC_64 == magic && GET_ARCH() == ARCH_64)
            get_archv_arch64(ptr_obj, ptr_obj->event.data_buff + offset);
    }
    ptr_obj->event.error_lvl = ERROR_EVENT;
    return (EXIT_SUCCESS);
}