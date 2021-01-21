OBJNAME := 	opentreegui
CPPC :=		g++
CPPFLAGS :=	-g -Wall -Werror -std=c++17 -Iinc
LD		:=	ar
LDFLAGS :=	-lsfml-graphics -lsfml-window -lsfml-system -lpthread
HEADERS :=	$(wildcard inc/*.hpp)
SRC :=		$(wildcard src/*.cpp)

OBJS :=		$(subst .cpp,.o,$(subst src/,obj/,$(SRC)))

.PHONY : all
all : lib$(OBJNAME).a examples

.PHONY : install-deps
install-deps :
	@echo "This is only for Debian! If you're not on Debian this won't work!"
	sudo apt install -y libsfml-dev build-essential

.PHONY : clean
clean :
	rm -rf sfml-ex
	rm -rf simple
	rm -rf lib$(OBJNAME).a
	rm -rf obj
	
obj/%.o : src/%.cpp $(HEADERS)
	mkdir -p obj
	$(CPPC) $(CPPFLAGS) -o $@ -c $<

.PHONY : examples
examples : sfml-ex simple text

sfml-ex : $(wildcard examples/sfml-example/*.cpp)
	$(CPPC) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

simple : lib$(OBJNAME).a $(wildcard examples/simple-example/*.cpp)
	$(CPPC) $(CPPFLAGS) -o $@ \
		$(wildcard examples/simple-example/*.cpp) -L. -lopentreegui $(LDFLAGS)

text : lib$(OBJNAME).a $(wildcard examples/text-example/*.cpp)
	$(CPPC) $(CPPFLAGS) -o $@ \
		$(wildcard examples/text-example/*.cpp) -L. -lopentreegui $(LDFLAGS)

lib$(OBJNAME).a : $(OBJS)
	$(LD) rcs $@ $(OBJS)
