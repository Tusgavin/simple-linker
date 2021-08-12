###############################################################################
########################### Parametros de Projeto #############################
###############################################################################

# TODO: altere a extensão dos arquivos (c ou cpp)
EXT = cpp
# TODO: altere a lista de forma que contenha todos os arquivos .cpp
#       do seu projeto (sem a extensão), que deve estar no diretório 
#       src/
SRCS_LIGADOR = $(patsubst %,%.$(EXT),main ligador)
SRCS_MONTADOR = $(patsubst %,%.$(EXT),main montador)
OBJS_LIGADOR = $(patsubst %,build/ligador/%.o,$(basename $(SRCS_LIGADOR)))
OBJS_MONTADOR = $(patsubst %,build/montador/%.o,$(basename $(SRCS_MONTADOR)))

###############################################################################
########################### Parametros de Ambiente ############################
###############################################################################

CC = gcc
CXX = g++
CCFLAGS = -Wall
CXXFLAGS = -Wall -g
CPPFLAGS = -Iinclude/
CPPFLAGSM = -Iinclude_m/

###############################################################################
################################ Executáveis ##################################
###############################################################################

all: bin/ligador bin/montador

ifeq ($(EXT), c)
bin/ligador: $(OBJS_LIGADOR)
	@echo "+ Compilando programa \"$@\""
	@$(CC) $(CCFLAGS) $(OBJS_LIGADOR) -o bin/ligador

bin/montador: $(OBJS_MONTADOR)
	@echo "+ Compilando programa \"$@\""
	@$(CC) $(CCFLAGS) $(OBJS_MONTADOR) -o bin/montador
else
bin/ligador: $(OBJS_LIGADOR)
	@echo "+ Compilando programa \"$@\""
	@$(CXX) $(CXXFLAGS) $(OBJS_LIGADOR) -o bin/ligador

bin/montador: $(OBJS_MONTADOR)
	@echo "+ Compilando programa \"$@\""
	@$(CXX) $(CXXFLAGS) $(OBJS_MONTADOR) -o bin/montador
endif

###############################################################################
################################## Objetos ####################################
###############################################################################

ifeq ($(EXT), c)
build/ligador/%.o: src/%.c
	@echo "- Compilando objeto \"$@\""
	@$(CC) $(CPPFLAGS) $(CCFLAGS) -c $< -o $@

build/montador/%.o: src_m/%.c
	@echo "- Compilando objeto \"$@\""
	@$(CC) $(CPPFLAGSM) $(CCFLAGS) -c $< -o $@
else
build/ligador/%.o: src/%.cpp
	@echo "- Compilando objeto \"$@\""
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

build/montador/%.o: src_m/%.cpp
	@echo "- Compilando objeto \"$@\""
	@$(CXX) $(CPPFLAGSM) $(CXXFLAGS) -c $< -o $@
endif


###############################################################################
################################# Auxiliares ##################################
###############################################################################

clean:
	rm -f bin/* $(OBJS_LIGADOR)
	rm -f bin/* $(OBJS_MONTADOR)
