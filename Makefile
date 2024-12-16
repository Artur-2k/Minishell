# Binary
BIN = minishell

# Compiler
CC = cc
CFLAGS = -I$(INC_DIR) -I$(LIB_DIR) -Wall -Wextra -Werror
#sanitize
#CFLAGS = -I$(INC_DIR) -I$(LIB_DIR) -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=leak -fsanitize=undefined -fno-omit-frame-pointer
VG = valgrind --leak-check=full --show-leak-kinds=all --suppressions=supressions --track-origins=yes --log-file=leaks.log
# --track-fds=all

# Color variables
RED = \033[0;31m
GRN = \033[0;32m
YEL = \033[0;33m
BLU = \033[0;34m
MAG = \033[0;35m
CYN = \033[0;36m
WHT = \033[0;37m
RES = \033[0m

# Directories
INC_DIR = inc/
LIB_DIR = libft/
SRC_DIR = src/
OBJ_DIR = obj/

# Files
MAIN_FILE = $(SRC_DIR)minishell.c
LIB = $(LIB_DIR)libft.a

# Find all .c files in src/ and its subdirectories
SRC_FILES := $(shell find $(SRC_DIR) -name '*.c' ! -name 'minishell.c')
# Create object file paths
OBJ_FILES := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_FILES))

TOTAL_FILES := $(words $(SRC_FILES))
COMPILED_FILES := $(shell if [ -d "$(OBJ_DIR)" ]; then find $(OBJ_DIR) -name "*.o" | wc -l; else echo 0; fi)

# Phony targets
.PHONY: all clean fclean re

# Rules
all: $(BIN)

$(BIN): $(LIB) $(MAIN_FILE) $(OBJ_FILES) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(MAIN_FILE) -lreadline $(OBJ_FILES) $(LIB) -o $@
	@printf "$(GRN)➾ Compilation progress: $$(echo "$(shell find $(OBJ_DIR) -name "*.o" | wc -l) $(TOTAL_FILES)" | awk '{printf "%.2f", $$1/$$2 * 100}')%% $(RES)\r"
	@echo "\n$(GRN)➾ [ ${BIN} ] created$(RES)"

$(LIB):
	@$(MAKE) --silent -C $(LIB_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(GRN)➾ Compilation progress: $$(echo "$(shell find $(OBJ_DIR) -name "*.o" | wc -l) $(TOTAL_FILES)" | awk '{printf "%.2f", $$1/$$2 * 100}')%%$(RES)\r"

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@$(MAKE) --silent -C $(LIB_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "${RED}➾ Cleaned the workspace${RES}"

fclean: clean
	@$(MAKE) --silent -C $(LIB_DIR) fclean
	@rm -f $(BIN)
	@rm -f leaks.log
	@rm -f leaks-old.log
	@rm -f supressions
	@echo "${RED}➾ Fully cleaned the workspace${RES}"

re: fclean all

#Debugging
leaks: all sup
	@if [ -f leaks.log ]; then mv leaks.log leaks-old.log; fi
	$(VG) ./$(BIN)

san: all sup
	@if [ -f leaks.log ]; then mv leaks.log leaks-old.log; fi
	ASAN_OPTIONS=suppressions=$(SUP_FILE) ./$(BIN)

gdb: re
	gdb --tui $(BIN)

# Supressoes de leaks
define SUP_BODY
{
   name
   Memcheck:Leak
   fun:*alloc
   ...
   obj:*/libreadline.so.*
   ...
}
{
    leak readline
    Memcheck:Leak
    ...
    fun:readline
}
{
    leak add_history
    Memcheck:Leak
    ...
    fun:add_history
}
endef


sup:
	$(file > supressions,$(SUP_BODY))

# Notes:
# $(file > sup,$(SUP_BODY)):
#	file é uma função do Make que escreve texto em um arquivo.
#	> indica que o arquivo será criado ou sobrescrito.
#	sup é o nome do arquivo que será criado.
#	$(SUP_BODY) é uma variável que contém o conteúdo a ser escrito no arquivo.
#
# @if [ -f leaks.log ]; then mv leaks.log leaks-old.log; fi  ===> se existir um log renomeia para old para manter a antiga
#
# :=
#	The := operator is particularly useful when:
#	You want to ensure a variable is set to a specific value at a specific point in the Makefile.
#	You're using the result of a shell command and you want it to be executed only once.
#	You want to avoid potential infinite recursion in variable definitions.