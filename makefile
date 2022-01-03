cc=gcc
AR=ar
OBJECTS_MAIN=main.o
OBJECTS_LIB1=graph.o pq.o
FLAGS= -Wall -g 

all: graph
# main
graph: $(OBJECTS_MAIN) $(OBJECTS_LIB1)# my_mat
	$(cc) $(FLAGS) -o graph $(OBJECTS_MAIN) $(OBJECTS_LIB1)

$(OBJECTS_MAIN): main.c graph.h
	$(cc) $(FLAGS) -c main.c
	
$(OBJECTS_LIB1): graph.c pq.c graph.h pq.h
	$(cc) $(FLAGS) -c graph.c pq.c


.PHONY: clean all
clean:
	rm -f *.o  *.a *.so my_mat graph