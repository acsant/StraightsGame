#all: hello-cpp-world hello-c-world

#%: %.cc
#	g++ -std=c++98 $< -o $@

#%: %.c
#	gcc $< -o $@

CXX = g++ -std=c++0x								# Variables and initialization
CXXFLAGS = -g -Wall -MMD				# builds dependency list in .d files
OBJECTS = straights.o Card.o Command.o ComputerPlayer.o HumanPlayer.o Player.o PlayerID.o Deck.o GameManager.o Hand.o PlayerStrategy.o
DEPENDS = ${OBJECTS:.o=.d} 				# substitute .o with .d
EXEC = straights 

${EXEC}:${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o  ${EXEC}
	
clean:
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
	
-include ${DEPENDS}						# reads the .d files and returns
										# dependencies
