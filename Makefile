NAME = particle
SRC_DIR = sources
OBJ_DIR = obj
FILES = main.c log.c \
	init.c terminate.c \
	file.c \
	uniform.c shaders.c \
	mat4.c rotate.c \

SRCS = $(addprefix $(SRC_DIR)/, $(FILES))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJ_ALL_DIR = $(dir $(OBJS))

IFLAGS = -I ~/.brew/Cellar/glfw/3.2.1/include -I ~/.brew/Cellar/glew/2.1.0/include
CC = gcc
LIBFLAGS = -L ~/.brew/Cellar/glfw/3.2.1/lib/ -lglfw -L ~/.brew/Cellar/glew/2.1.0/lib -lGLEW
FRAMEWORK = -framework OpenGL -framework AppKit -framework OpenCL
RM = /bin/rm -f

all: build $(NAME)

build :
	@mkdir -p $(OBJ_ALL_DIR)

install:
	~/.brew/bin/brew install glfw
	~/.brew/bin/brew install glew

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LIBFLAGS) $(FRAMEWORK)
	@echo "Make $(NAME) :\033[1;32m DONE !\033[m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(IFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS)
	@echo "Make clean :\033[1;31m DONE !\033[m"

fclean : clean
	$(RM) -rf $(OBJ_ALL_DIR)
	$(RM) $(NAME)
	@echo "Make fclean :\033[1;31m DONE !\033[m"

re: fclean all

.PHONY: all clean fclean re build install
