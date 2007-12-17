#global parameters
CC = g++
INCDIR= ./include/
#modifier le chemin pour l'emplacement ou est install�libnetwork
LIBNETWORK_LIBS=-L ./lib -lnetwork
CFLAGS= -g -I $(INCDIR) -Werror -Wall -ansi -pedantic

#EVA_client files
EVA_CLIENT_SOURCES= \
light.cpp load_texture.cpp eva_client.cpp material.cpp \
scene.cpp shape.cpp  texture.cpp \
traffic-light.cpp car-entity.cpp car-track.cpp \
steering-entity.cpp steering-system.cpp \
steering-behavior.cpp stay-on-track-behavior.cpp flee-behavior.cpp separation-behavior.cpp arrive-behavior.cpp seek-behavior.cpp wander-behavior.cpp \
vector-3d.cpp shape-part.cpp road-block.cpp \
transform.cpp tcp-text-server.cpp tcp-text-client.cpp tcp-text-socket.cpp \
baseshapes.cpp camera.cpp entity.cpp wall.cpp priority-behavior.cpp
EVA_CLIENT_OBJS=$(EVA_CLIENT_SOURCES:.cpp=.o)
EVA_CLIENT_LIBS=-lm -L/usr/X11R6/lib -lglut -lGL -lGLU -lX11 -lXi -lXmu \
	$(LIBNETWORK_LIBS)

#EVA_server files
EVA_SERVER_SOURCES=eva_server.cpp tcp-text-server.cpp tcp-text-client.cpp tcp-text-socket.cpp
EVA_SERVER_OBJS=$(EVA_SERVER_SOURCES:.cpp=.o)
EVA_SERVER_LIBS=$(LIBNETWORK_LIBS)

#gl_test files
GL_TEST_SOURCES=baseshapes.cpp camera.cpp entity.cpp \
light.cpp load_texture.cpp vector-3d.cpp gl_test.cpp material.cpp \
scene.cpp shape.cpp shape-part.cpp texture.cpp \
transform.cpp
GL_TEST_OBJS=$(GL_TEST_SOURCES:.cpp=.o)
GL_TEST_LIBS=-lm -L/usr/X11R6/lib -lglut -lGL -lGLU -lX11 -lXi -lXmu \
	$(LIBNETWORK_LIBS)

#network_test files
NETWORK_TEST_SOURCES=network_test.cpp tcp-text-server.cpp tcp-text-client.cpp tcp-text-socket.cpp vector-3d.cpp
NETWORK_TEST_OBJS=$(NETWORK_TEST_SOURCES:.cpp=.o)
NETWORK_TEST_LIBS=$(LIBNETWORK_LIBS)

all: eva_client eva_server gl_test network_test

eva_client: $(EVA_CLIENT_OBJS)
	$(CC) $(EVA_CLIENT_OBJS) -o eva_client $(EVA_CLIENT_LIBS)

eva_server: $(EVA_SERVER_OBJS)
	$(CC) $(EVA_SERVER_OBJS) -o eva_server $(EVA_SERVER_LIBS)

gl_test: $(GL_TEST_OBJS)
	$(CC) $(GL_TEST_OBJS) -o gl_test $(GL_TEST_LIBS)

network_test: $(NETWORK_TEST_OBJS)
	$(CC) $(NETWORK_TEST_OBJS) -o network_test $(NETWORK_TEST_LIBS)

%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	-rm $(EVA_CLIENT_OBJS) \
	$(EVA_SERVER_OBJS) \
	$(GL_TEST_OBJS) \
	$(NETWORK_TEST_OBJS) \
	eva_client eva_server gl_test network_test
