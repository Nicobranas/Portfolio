OBJS = main.o entite.o laser.o player.o guerrier.o lutin.o input.o mechant.o interface.o

TARGET = exec

#all: $(TARGET) #tests_catch
all : exec tests_catch

$(TARGET):$(OBJS)
	g++ -g -o $@ $^ -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2

%.o: %.cpp
	g++ -g -c $<

#compilation test
OBJS_TEST = entite.o tests_catch_mechant.o mechant.o tests_catch_interface.o interface.o  tests_catch_laser.o laser.o tests_catch_player.o player.o tests_catch_lutin.o lutin.o tests_catch_guerrier.o guerrier.o

tests_catch_mechant.o: tests_catch_mechant.cpp mechant.hpp catch.hpp data.hpp
	g++ -c tests_catch_mechant.cpp

tests_catch_interface.o: tests_catch_interface.cpp interface.hpp catch.hpp data.hpp
	g++ -c tests_catch_interface.cpp

tests_catch_laser.o: tests_catch_laser.cpp laser.hpp catch.hpp data.hpp
	g++ -c tests_catch_laser.cpp

tests_catch_player.o: tests_catch_player.cpp player.hpp catch.hpp data.hpp
	g++ -c tests_catch_player.cpp

tests_catch_lutin.o: tests_catch_lutin.cpp lutin.hpp catch.hpp data.hpp
	g++ -c tests_catch_lutin.cpp

tests_catch_guerrier.o: tests_catch_guerrier.cpp guerrier.hpp catch.hpp data.hpp
	g++ -c tests_catch_guerrier.cpp



tests_catch: $(OBJS_TEST)
	g++ -o tests_catch $(OBJS_TEST) -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2

clean:
	rm -rf *.o
	rm -f exec
	rm -f tests_catch
