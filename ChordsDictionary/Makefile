CXX = g++
CFLAGS = -Wall -c -g
LFLAGS = -Wall -g
SOURCES = ChordsDictionary.cpp Chord.cpp ./pugixml/src/pugixml.cpp
INCLUDES = -I./pugixml/src
LIBS = 
OBJS = $(SOURCES:.cpp=.o)
MAIN = ChordsDictionary

$(MAIN): $(OBJS)
	$(CXX) $(OBJS) -o $@

.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SOURCES)
	makedepend $(INCLUDES) $^

