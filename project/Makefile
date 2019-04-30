# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/21 12:38:47 by afeuerst          #+#    #+#              #
#    Updated: 2019/04/30 17:00:53 by afeuerst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJECTS_LOCATION = ./objects/
INCLUDES = ./includes/

MACHOREADER_LIBRARY = $(OBJECTS_LOCATION)machoreader.a
MACHOREADER_SOURCES = $(shell find ./sources/machoreader/ -type f | grep "\.c")
MACHOREADER_OBJECTS = $(MACHOREADER_SOURCES:.c=.o)
MACHOREADER_INCLUDES = $(INCLUDES)machoreader.h

FT_NM = ft_nm
FT_NM_SOURCES = $(shell find ./sources/ft_nm -type f | grep "\.c")
FT_NM_INCLUDES = $(INCLUDES)ft_nm.h

FT_OTOOL = ft_otool
FT_OTOOL_SOURCES = $(shell find ./sources/ft_otool -type f | grep "\.c")
FT_OTOOL_INCLUDES = $(INCLUDES)ft_otool.h

FT_DUMPER = ft_dumper
FT_DUMPER_SOURCES = $(shell find ./sources/ft_dumper -type f | grep "\.c")
FT_DUMPER_INCLUDES = $(INCLUDES)ft_dumper.h

FLAGS = -O0 -g -fsanitize=address 
FLAGS_MACHOREADER_OBJECTS = -c $(FLAGS)
FLAGS_MACHOREADER = -r -arch $(shell uname -m)

all: $(MACHOREADER_LIBRARY) $(FT_NM) $(FT_OTOOL) $(FT_DUMPER)

$(MACHOREADER_LIBRARY): $(MACHOREADER_INCLUDES) $(MACHOREADER_OBJECTS)
	@ld $(addprefix $(OBJECTS_LOCATION), $(notdir $(MACHOREADER_OBJECTS))) $(FLAGS_MACHOREADER) -o $(MACHOREADER_LIBRARY)
	@printf "\r\033[0K\033[38;5;82m$(notdir $(MACHOREADER_LIBRARY))\n"

%.o: %.c
	@clang -I $(INCLUDES) $(FLAGS_MACHOREADER_OBJECTS) -o $(OBJECTS_LOCATION)$(notdir $@) $<
	@printf "\r\033[0K\033[38;5;226m%-30s -> \033[38;5;154m%s\033[0m" $(notdir $<) $(notdir $@)

$(FT_NM): $(FT_NM_SOURCES) $(FT_NM_INCLUDES) $(MACHOREADER_LIBRARY)
	clang -I $(INCLUDES) $(MACHOREADER_LIBRARY) $(FT_NM_SOURCES) $(FLAGS) -o $(FT_NM)

$(FT_OTOOL): $(FT_OTOOL_SOURCES) $(FT_OTOOL_INCLUDES) $(MACHOREADER_LIBRARY)
	clang -I $(INCLUDES) $(MACHOREADER_LIBRARY) $(FT_OTOOL_SOURCES) $(FLAGS) -o $(FT_OTOOL)

$(FT_DUMPER): $(FT_DUMPER_SOURCES) $(FT_DUMPER_INCLUDES) $(MACHOREADER_LIBRARY)
	clang -I $(INCLUDES) $(MACHOREADER_LIBRARY) $(FT_DUMPER_SOURCES) $(FLAGS) -o $(FT_DUMPER)

clean:
	rm -rf $(MACHOREADER_LIBRARY).dSYM $(FT_NM).dSYM $(FT_OTOOL).dSYM $(FT_DUMPER).dSYM
	rm -rf $(addprefix $(OBJECTS_LOCATION), $(notdir $(MACHOREADER_OBJECTS)))

fclean: clean
	rm -rf $(MACHOREADER_LIBRARY) $(FT_NM) $(FT_OTOOL) $(FT_DUMPER)

re: fclean all
