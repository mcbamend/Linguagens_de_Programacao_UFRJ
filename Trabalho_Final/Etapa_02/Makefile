CXX = g++
PYTHON = python3
PYTHON_CONFIG = python3-config

PROGRAMA = closetlog

FONTES = main.cpp \
         Menu.cpp \
         ClosetLog.cpp \
         IntegradorPython.cpp \
         Peca.cpp \
         Roupa.cpp \
         Calcado.cpp \
         Acessorio.cpp

OBJETOS = $(FONTES:.cpp=.o)
DEPENDENCIAS = $(OBJETOS:.o=.d)

PYTHON_INCLUDES = $(shell $(PYTHON_CONFIG) --includes)
PYTHON_BIBLIOTECAS = $(shell $(PYTHON_CONFIG) --embed --ldflags)

CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 \
           -MMD -MP $(PYTHON_INCLUDES)

.PHONY: all run verificar-python clean

all: $(PROGRAMA)

$(PROGRAMA): $(OBJETOS)
	$(CXX) $(OBJETOS) -o $(PROGRAMA) $(PYTHON_BIBLIOTECAS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

verificar-python:
	@echo "Verificando a configuracao do Python..."
	@$(PYTHON_CONFIG) --includes > /dev/null
	@$(PYTHON_CONFIG) --embed --ldflags > /dev/null
	@$(PYTHON) -c "import numpy; import sklearn; print('Python, NumPy e scikit-learn encontrados.')"

run: $(PROGRAMA)
	./$(PROGRAMA)

clean:
	rm -f $(OBJETOS) $(DEPENDENCIAS) $(PROGRAMA)

-include $(DEPENDENCIAS)