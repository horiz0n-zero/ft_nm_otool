# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/21 12:38:47 by afeuerst          #+#    #+#              #
#    Updated: 2019/03/21 14:01:20 by afeuerst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJECTS_LOCATION = ./objects/
INCLUDES = ./includes/

BINARY_LIBRARY = $(OBJECTS_LOCATION)binarylib.a
BINARY_SOURCES = $(shell find ./sources/binarylib -type f | grep "\.c")
BINARY_INCLUDES = $(INCLUDES)binarylib.h

FT_NM = ft_nm
FT_NM_SOURCES = $(shell find ./sources/ft_nm -type f | grep "\.c")
FT_NM_INCLUDES = $(INCLUDES)ft_nm.h

FT_OTOOL = ft_otool
FT_OTOOL_SOURCES = $(shell find ./sources/ft_otool -type f | grep "\.c")
FT_OTOOL_INCLUDES = $(INCLUDES)ft_otool.h

FLAGS = -O0 -g

all: $(BINARY_LIBRARY) $(FT_NM) $(FT_OTOOL)

$(BINARY_LIBRARY): $(BINARY_SOURCES) $(BINARY_INCLUDES)
	clang -I $(INCLUDES) $(BINARY_SOURCES) $(FLAGS) -c -o $(BINARY_LIBRARY)

$(FT_NM): $(FT_NM_SOURCES) $(FT_NM_INCLUDES) $(BINARY_LIBRARY)
	clang -I $(INCLUDES) $(BINARY_LIBRARY) $(FT_NM_SOURCES) $(FLAGS) -o $(FT_NM)

$(FT_OTOOL): $(FT_OTOOL_SOURCES) $(FT_OTOOL_INCLUDES) $(BINARY_LIBRARY)
	clang -I $(INCLUDES) $(BINARY_LIBRARY) $(FT_OTOOL_SOURCES) $(FLAGS) -o $(FT_OTOOL)

clean:
	rm -rf $(BINARY_LIBRARY).dSYM $(FT_NM).dSYM $(FT_OTOOL).dSYM

fclean: clean
	rm -rf $(BINARY_LIBRARY) $(FT_NM) $(FT_OTOOL)

re: fclean all
