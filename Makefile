NAME :=	ft_vox

###

EXTERNAL_DIR := external

###

CXX :=	c++
CXXFLAGS :=	-Wall -Wextra -Werror -g -MP -MMD -std=c++17 -O3 # -fsanitize=address -fno-omit-frame-pointer
LFLAGS :=	-lSDL2 -lGL

###

INCLUDE_DIRS :=	external/imgui/\
				includes/\
				includes/Core\
				includes/Math\
				includes/Vox\
				includes/Utils\
				includes/Vox/World\
				includes/Vox/World/Block\
				includes/Vox/World/Chunk\
				includes/Vox/World/Generation\
				includes/Vox/World/Generation/Noise\
				includes/Core/Resources\
				includes/Core/Resources/Cache\
				includes/Core/Rendering/Light\
				includes/Core/Rendering/Light/Cache\
				external/glad\
				external/\
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
		Vox/World/Chunk/Chunk\
		Vox/World/Block/BlockType\
		Vox/World/Block/BlockState\
		Vox/World/Block/BlockProperty\
		Vox/World/Generation/ChunkGenerator\
		Vox/World/Generation/Spline\
		Vox/World/Generation/Noise/Perlin2D\
		Math/Math

###

INCLUDE_DIRS :=	$(addprefix -I, $(INCLUDE_DIRS))

SRCS :=	$(addprefix src/, $(SRCS))
SRCS :=	$(addsuffix .cpp, $(SRCS))

SRCS +=	external/glad/glad.cpp\
		external/stb_image/stb_image.cpp

IMGUI := $(EXTERNAL_DIR)/imgui
IMGUI_SRCS_RAW =	imgui.cpp\
					imgui_draw.cpp\
					imgui_widgets.cpp\
					imgui_tables.cpp\
					imgui_demo.cpp\
					backends/imgui_impl_opengl3.cpp\
					backends/imgui_impl_sdl2.cpp
IMGUI_SRCS = $(addprefix $(IMGUI)/, $(IMGUI_SRCS_RAW))

SRCS +=	$(IMGUI_SRCS)

###

OBJ_DIR :=	obj

OBJS =	$(SRCS:%.cpp=$(OBJ_DIR)/%.o)
DEPS =	$(SRCS:%.cpp=$(OBJ_DIR)/%.d)

###

compile: stb_image glad imgui json
	@make -j all --no-print-directory

all: $(NAME)

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

json:
	@if ls external | grep -q "json.h"; then \
		printf ""; \
	else\
		echo "\033[31;1mDownloading json.h\033[0m"; \
		curl --silent -o external/json.h https://raw.githubusercontent.com/nlohmann/json/refs/heads/develop/single_include/nlohmann/json.hpp;\
		echo "\033[31;1mDownloaded json.h\033[0m"; \
	fi

glad: $(EXTERNAL_DIR)
	@if ls external | grep -q "glad"; then \
		printf ""; \
	else \
		echo "\033[31;1mDownloading glad config\033[0m"; \
		git clone git@github.com:Scorpionnem/glad-config.git external/glad -q; \
		echo "\033[31;1mDownloaded glad config\033[0m"; \
	fi

imgui: $(EXTERNAL_DIR)
	@if ls external | grep -q "imgui"; then \
		printf ""; \
	else \
		echo "\033[31;1mDownloading imgui config\033[0m";\
		git clone https://github.com/ocornut/imgui.git $(IMGUI) -q;\
		echo "\033[31;1mDownloaded imgui config\033[0m";\
	fi

$(NAME): $(OBJS)
	@echo Compiling $(NAME)
	@$(CXX) $(CXXFLAGS) $(LFLAGS) $(INCLUDE_DIRS) -o $@ $^
	@echo Compiled $(NAME)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@
	@echo Compiled $@

re: fclean compile

fclean: clean
	@echo Removed $(NAME)
	@rm -rf $(NAME)

clean:
	@echo Removed $(OBJ_DIR)
	@rm -rf $(OBJ_DIR)

.PHONY: all clean fclean re compile

-include $(DEPS)
