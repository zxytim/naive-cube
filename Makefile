CXXSOURCES = $(shell find . -name '*.cpp')
OBJDIR = obj
OBJS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(CXXSOURCES))
CXX = g++
CXXFLAGS = -g #-Werror -Wall -Wextra 
LIBS = -lGL -lglut -lGLU

cube: $(OBJS)
	$(CXX) $(OBJS) -o cube $(CXXFLAGS) $(LIBS)
	@echo "Compilation succeed."

Makefile.dep: $(CXXSOURCES)
	for i in $(CXXSOURCES); do \
		$(CXX) -MM -MT "$(OBJDIR)/`echo $$i | sed -e 's/cpp\$$/o/g'`" $$i; \
	done > Makefile.dep

sinclude Makefile.dep

obj/%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(LIBS)


.PHONY: run gdb clean

run: cube
	./cube

gdb: cube
	gdb ./cube

clean:
	rm cube -f
	find . -name '*.o' -delete

hg:
	hg addremove
	hg commit -u zxytim
	hg push

