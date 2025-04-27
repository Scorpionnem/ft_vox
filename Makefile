NAME := ft_vox

OBJ_DIR := ./obj/
INCLUDE_DIRS := ./includes/ ./GLFW/include/GLFW ./includes/glad ./includes/KHR ./includes/render ./includes/player

GLFWARCHIVE = GLFW/build/src/libglfw3.a

INCLUDE_DIRS := $(addprefix -I, $(INCLUDE_DIRS))

MAKE := @make --no-print-directory

SOURCE_DIR := ./src/

OBJ_DIR := ./obj/

OBJECTS = $(SOURCES:.cpp=.o)

CPP_FILES :=	main \
				utils/init utils/glad utils/utils \
				player/hooks player/Camera player/Input \
				render/Shader render/Texture \
				assets/Assets assets/Block assets/Chunk assets/World

CPP_FILES := $(addsuffix .cpp, $(CPP_FILES))

SOURCES := $(addprefix $(SOURCE_DIR), $(CPP_FILES))

OBJECTS := $(addprefix $(OBJ_DIR), $(CPP_FILES:.cpp=.o))
DEPS := $(addprefix $(OBJ_DIR), $(CPP_FILES:.cpp=.d))

CFLAGS = -MP -MMD -Wall -Werror -Wextra -g

all: glfw glad $(NAME)

glfw:
	@if ls | grep -q "GLFW"; then \
		echo "\033[32;1;4mGLFW Found\033[0m"; \
	else \
		echo "\033[31;1;4mGLFW Not Found\033[0m"; \
		echo "\033[31;1m Downloading it from github \033[0m"; \
		git clone https://github.com/glfw/glfw.git GLFW; \
		echo "\033[31;1mCompiling it\033[0m"; \
		cmake -S GLFW -B GLFW/build; \
		cmake --build GLFW/build; \
	fi

glad:
	
$(OBJECTS): $(OBJ_DIR)%.o : $(SOURCE_DIR)%.cpp
	@c++ $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(OBJ_DIR):
	@(cd $(SOURCE_DIR) && find . -type d -exec mkdir -p -- $(shell pwd)/$(OBJ_DIR){} \;)

$(NAME): $(OBJ_DIR) $(OBJECTS)
	@c++ $(OBJECTS) $(GLFWARCHIVE) -o $(NAME)
	@echo "\033[0;32mCompiled $(NAME)\033[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;32mCleaned objects\033[0m"

fclean:
	$(MAKE) clean
	@rm -f $(NAME)
	@echo "\033[0;32mCleaned everything\033[0m"

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)