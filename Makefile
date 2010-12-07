CXXSOURCES = $(shell find . -name '*.cpp')
OBJDIR = obj
OBJS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(CXXSOURCES))
CXX = g++
DEFINES = -DDEBUG
CXXFLAGS = -g #-Wall -Wextra -Werror 
LIBS = -lGL -lglut -lGLU
TARGET = naive-cube

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(CXXFLAGS) $(LIBS) $(DEFINES)
	@echo "Compilation succeed."

Makefile.dep: $(CXXSOURCES)
	for i in $(CXXSOURCES); do \
		obj=$(OBJDIR)/`echo $$i | sed -e 's/cpp\$$/o/g'`; \
		mkdir -p `dirname $$obj`; \
		$(CXX) -MM -MT $$obj $$i; \
	done > Makefile.dep

sinclude Makefile.dep

obj/%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(LIBS) $(DEFINES)


.PHONY: run gdb clean

run: $(TARGET)
	./$(TARGET)

gdb: $(TARGET)
	gdb ./$(TARGET)

clean:
	rm $(TARGET) -f
	find . -name '*.o' -delete
	rm $(OBJDIR) -rf
	rm Makefile.dep -f

hg:
	make clean
	hg addremove
	hg commit -u zxytim
	hg push

