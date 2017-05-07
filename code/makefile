FLAGS = -lglfw -lGL -ldl
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
CC = g++ -std=c++11
EXEC = a.out

all: $(EXEC)

$(EXEC): $(OBJ) $(FLAGS)
	$(CC) $^ -o $@

%.o : %.cpp
	$(CC) -c $<

clean:
	rm $(OBJ) $(EXEC)
