# ALL_DIRS := libs blossom5 blossom5/MinCost blossom5/GEOM
# ALL_SOURCES := $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
# ALL_OBJS := $(patsubst %.cpp, %.o, $(SOURCES))

CHRISTOFIDES_DIRS := libs christofides christofides/blossom5 christofides/blossom5/MinCost christofides/blossom5/GEOM
CHRISTOFIDES_SOURCES := $(foreach dir, $(CHRISTOFIDES_DIRS), $(wildcard $(dir)/*.cpp))
CHRISTOFIDES_OBJS := $(patsubst %.cpp, %.o, $(CHRISTOFIDES_SOURCES))

CFLAGS :=
CC := g++
LIBS :=
INCLUDES := -Ilibs -Ichristofides/blossom5
LIBDIR :=

all: christofides

christofides: ${CHRISTOFIDES_OBJS}
	${CC} ${CFLAGS} -o $@ ${CHRISTOFIDES_OBJS}

.cpp.o:
	$(CC) $(CFLAGS) ${INCLUDES} $< -c -o $@

clean:
	rm -f ${CHRISTOFIDES_OBJS}
