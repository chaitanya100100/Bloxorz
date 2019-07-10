FLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -lXinerama -lXcursor
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
CC = g++ -std=c++11
EXEC = a.out

all: $(EXEC)

$(EXEC): $(OBJ) $(FLAGS) glad.o
	$(CC) $^ -o $@

%.o : %.cpp
	$(CC) -c $<

glad.o : glad.c
	$(CC) -c $<

clean:
	rm $(OBJ) $(EXEC)
