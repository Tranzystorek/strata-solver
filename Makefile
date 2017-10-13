debug:
	g++ -g -o strata_solver_debug main.cpp StrataMap.cpp

release:
	g++ -o strata_solver main.cpp StrataMap.cpp
