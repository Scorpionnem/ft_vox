NAME :=	ft_vox

###

CXX :=	c++
CXXFLAGS :=	-Wall -Wextra -Werror -g -MP -MMD -std=c++17
LFLAGS :=	-lSDL2 -lGL

###

INCLUDE_DIRS :=	includes/\
				includes/Core\
				includes/Math\
				includes/Vox\
				includes/Utils\
				includes/Vox/World\
				includes/Vox/World/Chunk\
				includes/Vox/World/Generation\
				includes/Core/Resources\
				includes/Core/Resources/Cache\
				includes/Core/Rendering/Light\
				includes/Core/Rendering/Light/Cache\
				external/glad\
				external/stb_image

SRCS :=	main\
		Core/Window\
		Math/Vec3\
		Math/Vec3i\
		Math/Vec3d\
		Core/Engine\
		Core/Camera\
		Core/Resources/Shader\
		Core/Resources/Mesh\
		Core/Resources/Cache/MeshCache\
		Core/Resources/Cache/ShaderCache\
		Core/Rendering/Light/Cache/LightCache\
		Vox/VoxScene\
		Vox/World/World\
		Vox/Generation/ChunkGenerator\
		Math/Math

###

INCLUDE_DIRS :=	$(addprefix -I, $(INCLUDE_DIRS))

SRCS :=	$(addprefix src/, $(SRCS))
SRCS :=	$(addsuffix .cpp, $(SRCS))

SRCS +=	external/glad/glad.cpp\
		external/stb_image/stb_image.cpp

###

OBJ_DIR :=	obj

OBJS =	$(SRCS:%.cpp=$(OBJ_DIR)/%.o)
DEPS =	$(SRCS:%.cpp=$(OBJ_DIR)/%.d)

###

compile: stb_image glad
	@make -j all --no-print-directory

all: $(NAME)

EXTERNAL_DIR := external
$(EXTERNAL_DIR):
	@mkdir -p external

stb_image: $(EXTERNAL_DIR)
	@if ls external/stb_image | grep -q "stb_image.h"; then \
		printf ""; \
	else\
		echo "\033[31;1mDownloading stb_image.h\033[0m"; \
		mkdir -p external/stb_image; \
		curl --silent -o external/stb_image/stb_image.h https://raw.githubusercontent.com/nothings/stb/master/stb_image.h;\
		echo "\033[31;1mDownloaded stb_image.h\033[0m"; \
	fi

glad:
	@if ls external | grep -q "glad"; then \
		printf ""; \
	else \
		echo "\033[31;1mDownloading glad config\033[0m"; \
		git clone git@github.com:Scorpionnem/glad-config.git external/glad -q; \
		echo "\033[31;1mDownloaded glad config\033[0m"; \
	fi

$(NAME): $(OBJS)
	@echo Compiling $(NAME)
	@$(CXX) $(CXXFLAGS) $(LFLAGS) $(INCLUDE_DIRS) -o $@ $^

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

re: fclean compile

fclean: clean
	@echo Removed $(NAME)
	@rm -rf $(NAME)

clean:
	@echo Removed $(OBJ_DIR)
	@rm -rf $(OBJ_DIR)

.PHONY: all clean fclean re compile

-include $(DEPS)
