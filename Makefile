CC=gcc
CFLAGS=-Wall -Wextra -O2
TARGET=main

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

test: $(TARGET)
	@echo "Executando testes do main.c:"
	@echo ""
	@echo "Problema 1: Network Delay Time (LeetCode 743)"
	@echo "  Exemplo 1 - times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2 (Esperado: 2):"
	@./$(TARGET) nwd 4 2 2 1 1 2 3 1 3 4 1
	@echo "  Exemplo 2 - times = [[1,2,1]], n = 2, k = 1 (Esperado: 1):"
	@./$(TARGET) nwd 2 1 1 2 1
	@echo "  Exemplo 3 - times = [[1,2,1]], n = 2, k = 2 (Esperado: -1):"
	@./$(TARGET) nwd 2 2 1 2 1
	@echo ""
	@echo "Problema 2: Min Cost to Connect All Points (LeetCode 1584)"
	@echo "  Exemplo 1 - points = [[0,0],[2,2],[3,10],[5,2],[7,0]] (Esperado: 20):"
	@./$(TARGET) mcap 0 0 2 2 3 10 5 2 7 0
	@echo "  Exemplo 2 - points = [[3,12],[-2,5],[-4,1]] (Esperado: 18):"
	@./$(TARGET) mcap 3 12 -2 5 -4 1
	@echo ""
	@echo "Problema 3: Course Schedule (LeetCode 207)"
	@echo "  Exemplo 1 - numCourses = 2, prerequisitos = [[1,0]] (Esperado: true):"
	@./$(TARGET) cs 2 1 0
	@echo "  Exemplo 2 - numCourses = 2, prerequisitos = [[1,0],[0,1]] (Esperado: false):"
	@./$(TARGET) cs 2 1 0 0 1
	@echo "  Exemplo 3 - numCourses = 4, prerequisitos = [[1,0],[2,0],[3,1],[3,2]] (Esperado: true):"
	@./$(TARGET) cs 4 1 0 2 0 3 1 3 2

clean:
	rm -f $(TARGET)
