CFLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++\
-Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align\
-Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy\
-Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness\
-Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual\
-Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion\
-Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn\
-Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default\
-Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast\
-Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing\
-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation\
-fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer\
-Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla\
-Itests -Isrc
-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

CC = g++

all : quadradq

OBJS_NAMES = equation_solver.o main.o io_handling.o logger.o complex.o
OBJDIR = build
OBJS = $(addprefix $(OBJDIR)/, $(OBJS_NAMES))

testing : CFLAGS += -DTEST
testing : OBJS += $(OBJDIR)/test.o
testing : $(OBJDIR)/test.o quadradq

quadradq : $(OBJS)
	$(CC) $(CFLAGS) -o quadradq $(OBJS)

$(OBJDIR)/main.o : src/main.cpp src/equation_solver.h tests/test.h src/io_handling.h src/logger.h src/complex.h
	$(CC) $(CFLAGS) -c src/main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/equation_solver.o : src/equation_solver.cpp src/equation_solver.h
	$(CC) $(CFLAGS) -c src/equation_solver.cpp -o $(OBJDIR)/equation_solver.o

$(OBJDIR)/test.o : tests/test.cpp tests/test.h
	$(CC) $(CFLAGS) -c tests/test.cpp -o $(OBJDIR)/test.o

$(OBJDIR)/io_handling.o : src/io_handling.cpp src/io_handling.h
	$(CC) $(CFLAGS) -c src/io_handling.cpp -o $(OBJDIR)/io_handling.o

$(OBJDIR)/logger.o : src/logger.cpp src/logger.h
	$(CC) $(CFLAGS) -c src/logger.cpp -o $(OBJDIR)/logger.o

$(OBJDIR)/complex.o : src/complex.cpp src/complex.h
	$(CC) $(CFLAGS) -c src/complex.cpp -o $(OBJDIR)/complex.o

clean :
	rm quadradq $(OBJS) $(OBJDIR)/test.o

html : docs/html/index.html
docs/html/index.html : main.cpp equation_solver.cpp equation_solver.h tests/test.cpp tests/test.h Doxyfile
	doxygen
