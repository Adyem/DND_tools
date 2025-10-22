#include "dnd_tools.hpp"
#include "initialize.hpp"
#include "libft/Libft/libft.hpp"

void    ft_initialize_character_template(t_char * dst, const t_char * src)
{
    unsigned char           *dst_bytes;
    const unsigned char     *src_bytes;
    size_t                  prefix_size;
    size_t                  suffix_offset;

    if (dst == ft_nullptr || src == ft_nullptr)
        return ;
    dst_bytes = reinterpret_cast<unsigned char *>(dst);
    src_bytes = reinterpret_cast<const unsigned char *>(src);
    prefix_size = offsetof(t_char, bufs);
    ft_memcpy(dst_bytes, src_bytes, prefix_size);
    dst->bufs = ft_initialize_buffs();
    dst->debufs = ft_initialize_debuffs();
    suffix_offset = offsetof(t_char, concentration);
    ft_memcpy(dst_bytes + suffix_offset, src_bytes + suffix_offset,
        sizeof(t_char) - suffix_offset);
    return ;
}
