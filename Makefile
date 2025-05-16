# Определяем компилятор и флаги
CC = g++
CFLAGS = -Wall -g

# Определяем имена файлов
DLL_NAME = example.dll
EXE_NAME = main.exe

# Исходные файлы
DLL_SOURCES = example.cpp 
EXE_SOURCES = main.cpp

# Правило по умолчанию
all: $(DLL_NAME) $(EXE_NAME)

# Правило для сборки DLL
$(DLL_NAME): $(DLL_SOURCES)
	$(CC) $(CFLAGS) -shared -o $@ $^

# Правило для сборки EXE
$(EXE_NAME): $(EXE_SOURCES)
	$(CC) $(CFLAGS) -L. -lexample -o $@ $^

# Правило для очистки
clean:
	rm -f $(DLL_NAME) $(EXE_NAME)