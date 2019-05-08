/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dumper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:04:06 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/08 11:15:02 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

static struct s_dumper			g_dumper =
{
	0,
	STDOUT_FILENO,
	NULL,

	NULL,
	NULL,
	NULL,

	NULL,
	0
};

static const struct s_argument	g_arguments[256] =
{
	['o'] = {"output", DUMPER_O, 1, &g_dumper.output},
	['s'] = {"show-crypt", DUMPER_S, 0, NULL},
	['u'] = {"uuid", DUMPER_U, 0, NULL},
	['f'] = {"force", DUMPER_F, 0, NULL},
	['b'] = {"bytes-count-type", DUMPER_B, 0, NULL}
};

static const char				*g_usages[] =
{
	"usage:\n\n",
	"-o --output file          Redirect output to file.\n",
	"-s --show-crypt           Show information about LC_ENCRYPTION_INFO(_64).\n"
	"-u --uuid                 Show Universally Unique IDentifier (UUID)\n",
	"                          a 128-bit value guaranteed to be unique over both space and time.\n"
	"-f --force                Force the generation of the header,\n",
	"                          even if LC_ENCRYPTION is set. this option can cause a crash or a bad result\n",
	"-b --bits--type           don't use native types use types that contain bits like intx_t uintx_t\n"
};

static void						dumper_usage(void)
{
	int							index;

	index = 0;
	while (index < (sizeof(g_usages) / sizeof(g_usages[0])))
	{
		write(STDERR_FILENO, g_usages[index], ft_strlen(g_usages[index]));
		++index;
	}
}

static inline void				dumper_process_generate(
		struct s_macho_binary *const bin,
		struct s_macho *const macho)
{
	if (g_dumper.proto_list)
		dumper_read_protocols(&g_dumper, bin, macho); // bin->error ???
	if (g_dumper.cat_list)
		dumper_read_categories(&g_dumper, bin, macho);
	dumper_read_class(&g_dumper, bin, macho);
	dumper_generate_header(&g_dumper, bin);
	if (bin->error)
		return ((void)ft_fprintf(STDERR_FILENO, "ft_dumper: %s: %s.\n", bin->file, bin->error));
}

static void						dumper_process(const char *const file)
{
	struct s_macho_binary		*bin;
	int							select;
	int							index;

	if (g_dumper.flags & DUMPER_O)
		if ((g_dumper.fdoutput = open(g_dumper.output, O_RDWR | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH)) < 0)
			return ((void)(ft_fprintf(STDERR_FILENO, "ft_dumper: cannot create %s\n", g_dumper.output)));
	bin = get_macho_binary(file);
	if (bin->error)
		ft_fprintf(STDERR_FILENO, "ft_dumper: %s: %s.\n", file, bin->error);
	else
	{
		index = select_arch(bin, &select);
		if (dumper_get_sections(bin->macho + index, &g_dumper))
			ft_fprintf(STDERR_FILENO, "ft_dumper: %s: no objc data.\n", file);
		else if (bin->macho[index].statics)
			ft_fprintf(STDERR_FILENO, "ft_dumper: %s: archive unsupported.\n", file);
		else if (g_dumper.encryption && !(g_dumper.flags & DUMPER_F) &&
				((struct encryption_info_command*)g_dumper.encryption->content)->cryptid)
			ft_fprintf(STDERR_FILENO, "ft_dumper: %s: file is encrypted.\n", file);
		else
			dumper_process_generate(bin, bin->macho + index);
	}
	if (g_dumper.fdoutput != STDOUT_FILENO)
		close(g_dumper.fdoutput);
	unget_macho_binary(bin);
}

int								main(int argc, char **argv)
{
	char						*error;

	if (!(argv = arguments_get(++argv, g_arguments, &g_dumper.flags, &error)))
	{
		ft_fprintf(STDERR_FILENO, "ft_dumper: %s\n", error);
		dumper_usage();
		return (EXIT_FAILURE);
	}
	if (g_dumper.flags & DUMPER_S)
		dumper_show_lc_encryption(argv);
	if (g_dumper.flags & DUMPER_U)
		dumper_show_uuid(argv);
	if (!(g_dumper.flags & (DUMPER_S | DUMPER_U)))
	{
		if (*argv && *(argv + 1))
			ft_fprintf(STDERR_FILENO, "ft_dumper: can only generate header for one specified file\n");
		else if (!*argv)
			dumper_process("a.out");
		else
			dumper_process(*argv);
	}
	return (EXIT_SUCCESS);
}
