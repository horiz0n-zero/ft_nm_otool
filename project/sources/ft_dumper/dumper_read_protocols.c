/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_read_protocols.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 13:32:58 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/05 16:47:01 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

static inline void			read_protocol_methods(
		struct s_macho_binary *const bin,
		struct s_macho *const macho,
		struct s_protocol *const p)
{
	dumper_read_methods(macho, p->protocol->class_methods, &p->class_methods, &p->class_methods_count);
	dumper_read_methods(macho, p->protocol->instance_methods, &p->instance_methods, &p->instance_methods_count);
	dumper_read_methods(macho, p->protocol->optional_class_methods, &p->o_class_methods, &p->o_class_methods_count);
	dumper_read_methods(macho, p->protocol->optional_instance_methods, &p->o_instance_methods, &p->o_instance_methods_count);
	dumper_read_properties(macho, p->protocol->instance_properties, &p->properties, &p->properties_count);
	if (p->protocol->protocols)
		read_protocols(bin, macho, p->protocol->protocols, &p->protocols, &p->protocols_count);
	//	read_protocol
}

static void					read_protocol(
		struct s_macho_binary *const bin,
		struct s_macho *const macho,
		struct s_protocol *const p)
{
	struct s_section *const	s = section_addr_location(macho, p->value);

	if (s)
	{
		p->protocol = section_addr_offset(macho, s, p->value);
		if (macho->isswap)
			swap_protocol(p->protocol);
		p->name = section_addr_name(macho, p->protocol->name);
		read_protocol_methods(bin, macho, p);
		/*if (!(p->protocol->flags & RO_META) && p->protocol->isa)
		{
			p->meta = ft_memalloc(sizeof(struct s_protocol));
			p->value = p->protocol->isa;
			read_protocol(dumper, bin, macho, p->meta);
		}*/
	}
	else
		dumper_fatal("no section addr\n");
}

void						read_protocols(
		struct s_macho_binary *const bin,
		struct s_macho *const macho,
		const uint64_t value,
		struct s_protocol **const protocols, int *const protocols_count)
{
	uint64_t				*ptr;
	struct s_protocol		*protocol;
	struct s_section *const	s = section_addr_location(macho, value);
	int						index;

	if (!s)
		dumper_fatal("no section for addrss\n");
	ptr = section_addr_offset(macho, s, value);
	*protocols_count = (int)*ptr++;
	if (macho->isswap)
		*protocols_count = __builtin_bswap64(*protocols_count);
	if (!(*protocols = ft_memalloc(sizeof(struct s_protocol) * (size_t)*protocols_count)))
		return (set_error(bin, MRERR_MEM));
	protocol = *protocols;
	index = 0;
	while (index++ < *protocols_count)
	{
		if (macho->isswap)
			protocol->value = __builtin_bswap64(*ptr++);
		else
			protocol->value = *ptr++;
		read_protocol(bin, macho, protocol++);
		if (bin->error)
			break ;
	}
}

void						dumper_read_protocols(
		struct s_dumper *const dumper,
		struct s_macho_binary *const bin,
		struct s_macho *const macho)
{
	uint64_t *const			end = (void*)(((char*)dumper->proto_list->content) + dumper->proto_list->content_size);
	uint64_t				*ptr;
	int						count;
	struct s_protocol		*protocol;

	count = (int)(dumper->proto_list->content_size / sizeof(uint64_t));
	if (!(protocol = ft_memalloc(sizeof(struct s_protocol) * (size_t)count)))
		return (set_error(bin, MRERR_MEM));
	ptr = dumper->proto_list->content;
	dumper->protocols = protocol;
	dumper->protocols_count = count;
	while (ptr < end)
	{
		if (macho->isswap)
			protocol->value = __builtin_bswap64(*ptr++);
		else
			protocol->value = *ptr++;
		read_protocol(bin, macho, protocol++);
		if (bin->error)
			break ;
	}
}










