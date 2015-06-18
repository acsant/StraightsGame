#all: hello-cpp-world hello-c-world

#%: %.cc
#	g++ -std=c++98 $< -o $@

#%: %.c
#	gcc $< -o $@

CXX = g++ -std=c++98								# Variables and initialization
CXXFLAGS = -g -Wall -MMD				# builds dependency list in .d files
OBJECTS = straights.o Card.o Command.o Player.o PlayerID.o Deck.o GameManager.o Hand.o 
DEPENDS = ${OBJECTS:.o=.d} 				# substitute .o with .d
EXEC = Straights 

${EXEC}:${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o  ${EXEC}
	
clean:
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
	
-include ${DEPENDS}						# reads the .d files and returns
										# dependencies