CFLAGS = -g -Wall
LINK_FLAGS = -lm
NAME = examples

ALL_SOURCES = \
$(NAME).c \
alist.c \
aqueue.c \
array2d.c \
astack.c \
binarytree.c \
hashtable.c \
line.c \
list.c \
maxheap.c \
minheap.c \
plane.c \
queue.c \
stack.c \
transform.c \
util.c \
vector.c

ALL_OBJECTS = \
$(NAME).o \
alist.o \
aqueue.o \
array2d.o \
astack.o \
binarytree.o \
hashtable.o \
line.o \
list.o \
maxheap.o \
minheap.o \
plane.o \
queue.o \
stack.o \
transform.o \
util.o \
vector.o

all: $(ALL_OBJECTS)
	$(CC) $(CFLAGS) $(ALL_OBJECTS) -o $(NAME) $(LINK_FLAGS)

clean:
	rm -rf $(ALL_OBJECTS) $(NAME)
