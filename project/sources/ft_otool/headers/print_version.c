/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_version.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 14:18:10 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 09:16:47 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"
/*
   static const char						*g_platforms[] =
   {
   "MACOS",
   "IOS",
   "TVOS",
   "WATCHOS",
   "BRIDGEOS"
   };

   static const char						*g_tools[] =
   {
   "CLANG",
   "SWIFT",
   "LD"
   };
   */
void									print_min_version(
		struct s_loadcommand *const lc)
{
	struct version_min_command *const	v = lc->content;

	ft_printf("%22s %u.%u.%u\n", "version",
			(v->version >> 16) & 0xffff,
			(v->version >> 8) & 0xff,
			v->version & 0xff);
	ft_printf("%22s %u.%u.%u\n", "sdk",
			(v->sdk >> 16) & 0xffff,
			(v->sdk >> 8) & 0xff,
			v->sdk & 0xff);
}
/*
   void									print_build_version(
   struct s_loadcommand *const lc)
   {
   struct build_version_command *const	b = lc->content;
   struct build_tool_version			*ptr;
   int									index;

   ft_printf("%22s %u (%s)\n", "platform", b->platform,
   ((b->platform >= PLATFORM_MACOS && b->platform <= PLATFORM_BRIDGEOS) ?
   g_platforms[b->platform - 1] : "???"));
   ft_printf("%22s %u.%u.%u\n", "minos",
   (b->minos >> 16) & 0xffff,
   (b->minos >> 8) & 0xff,
   b->minos & 0xff);
   ft_printf("%22s %u.%u.%u\n", "sdk",
   (b->sdk >> 16) & 0xffff),
   (b->sdk >> 8) & 0xff,
   b->sdk & 0xff);
   ft_printf("%22s %u\n", "ntools", b->ntools);
   ptr = ((char*)lc->content) + sizeof(*b));
   index = 0;
   while (index < b->ntools && index < 3)
   print_btool_version(ptr + index++);
   }

   static void								print_btool_version(
   struct build_tool_version *const b)
   {
   ft_printf("%22s %u (%s)\n", "tool", b->tool,
   (b->tool >= TOOL_CLANG && b->tool <= TOOL_LD) ?
   g_tools[b->tool] : "???");
   ft_printf("%22s %u\n", "version", b->version);
   }*/

void									print_source_version(
		struct s_loadcommand *const lc)
{
	struct source_version_command		*s;
	int									n[5];

	s = lc->content;
	n[0] = (s->version >> 40) & 0xffffff;
	n[1] = (s->version >> 30) & 0x3ff;
	n[2] = (s->version >> 20) & 0x3ff;
	n[3] = (s->version >> 10) & 0x3ff;
	n[4] = s->version & 0x3ff;
	if (n[4] != 0)
		ft_printf("%22s %llu.%llu.%llu.%llu.%llu\n", "version", n[0], n[1], n[2], n[3], n[4]);
	else if (n[3] != 0)
		ft_printf("%22s %llu.%llu.%llu.%llu\n", "version", n[0], n[1], n[2], n[3]);
	else if (n[2] != 0)
		ft_printf("%22s %llu.%llu.%llu\n", "version", n[0], n[1], n[2]);
	else
		ft_printf("%22s %llu.%llu\n", "version", n[0], n[1]);
}
