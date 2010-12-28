CXXSOURCES = $(shell find . -name '*.cpp')
HSOURCES = $(shell find . -name '*.h')
#GCHSOURCE = $(patsubst ./%.h, %.h.gch, $(HSOURCES))
OBJDIR = obj
OBJS = $(patsubst ./%.cpp, $(OBJDIR)/%.o, $(CXXSOURCES))
CXX = g++
DEFINES = -DDEBUG
CXXFLAGS = -g #-time -H #-Wall -Wextra -Werror 
LIBS = -lGL -lglut -lGLU
TARGET = naive-cube

#$(GCHSOURCE) 
$(TARGET): $(OBJS) 
	$(CXX) $(OBJS) -o $(TARGET) $(CXXFLAGS) $(LIBS) $(DEFINES)
	@echo "Compilation succeed."

Makefile.dep: $(CXXSOURCES) $(HSOURCES)
	for i in $(CXXSOURCES); do \
		obj=$(OBJDIR)/`echo $$i | sed -e 's/cpp\$$/o/g'`; \
		mkdir -p `dirname $$obj`; \
		$(CXX) -MM -MT $$obj $$i; \
	done > Makefile.dep; 
#	for i in $(HSOURCES); do \
#		$(CXX) -MM -MT $$i.gch $$i; \
#	done >> Makefile.dep

sinclude Makefile.dep

obj/%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(LIBS) $(DEFINES)

#%.h.gch: %.h
#	$(CXX) -o $@ -x c++-header $< $(CXXFLAGS) $(DEFINES)

.PHONY: run gdb clean hg cleanall

run: $(TARGET)
	./$(TARGET)

gdb: $(TARGET)
	gdb ./$(TARGET)

clean:
	rm $(TARGET) -f
	find . -name '*.o' -delete
	rm $(OBJDIR) -rf
	rm Makefile.dep -f

cleanall: clean
#	find . -name '*.gch' -delete

hg:
	make clean
	hg addremove
	hg commit -u zxytim
	hg push

