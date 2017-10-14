OUTDIR = build

all: debug release

debug: debugdir
	g++ -g -o $(OUTDIR)/debug/strata_solver main.cpp StrataMap.cpp Solver.cpp

debugdir:
	mkdir -p $(OUTDIR)/debug

release: releasedir
	g++ -o $(OUTDIR)/release/strata_solver main.cpp StrataMap.cpp Solver.cpp

releasedir:
	mkdir -p $(OUTDIR)/release
