#
# Makefile for Six Degrees
#
# Project 2 (fall 2020)
#

# 

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 
INCLUDES = $(shell echo *.h)

SixDegrees: main.o SixDegrees.o CollabGraph.o Artist.o
	${CXX} -o $@ $^

Artist.o: Artist.cpp Artist.h 
	$(CXX) $(CXXFLAGS) -c Artist.cpp

SixDegrees.o: SixDegrees.cpp SixDegrees.h Artist.h CollabGraph.h
	$(CXX) $(CXXFLAGS) -c SixDegrees.cpp

CollabGraph.o: CollabGraph.cpp CollabGraph.h Artist.o
	$(CXX) $(CXXFLAGS) -c CollabGraph.cpp

main.o: main.cpp CollabGraph.h Artist.h SixDegrees.h
	$(CXX) $(CXXFLAGS) -c main.cpp

unit_test: unit_test_driver.o SixDegrees.o Artist.o CollabGraph.o
	$(CXX) $(CXXFLAGS) $^
%.o: %.cpp ${INCLUDES}
	${CXX} ${CXXFLAGS} -c $<

provide: 
	provide comp15 proj2phase2 artists.txt \
	cmd_basicPrint.txt cmd_extraLineTest.txt cmd_invalidCommands.txt \
	CollabGraph.cpp CollabGraph.h data_emptyLinetest.txt \ 
	data_extraLinetest.txt data_linearGraph.txt main.cpp Makefile README \
	SixDegrees.cpp SixDegrees.h smallArtists.txt unit_tests.h cmd_BFS.txt \
	cmd_cycleTest.txt cmd_disconnectedTest.txt cmd_emptyLinestest.txt \
	cmd_pathArtistonSelf.txt data_cycleGraph.txt data_disconnectedEnd.txt \
	cmd_ArtistnoExistingartist.txt cmd_notTest.txt cmd_DFS.txt \
	cmd_notEdgecases.txt cmd_notEdgecases2.txt cmd_notEdgecase3.txt
	
clean:
	rm -rf SixDegrees *.o *.dSYM
