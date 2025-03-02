CXX      := g++
AR       := ar
ARFLAGS  := rcs
CXXFLAGS := -Wall -Wextra -Werror -g -O0 -std=c++17
TEST_EXEC         = test_executable
TEST_EXEC_DEBUG   = test_executable_debug

SUBDIRS :=  CMA \
            GetNextLine \
            Libft \
            Printf \
            ReadLine \
            PThread \
            CPP_class \
            Errno \
            Networking \
            Windows \
            Linux \
            SFML \
            encryption \
            RNG

LIB_BASES := \
  CMA/CustomMemoryAllocator \
  GetNextLine/GetNextLine \
  Libft/LibFT \
  Printf/Printf \
  ReadLine/ReadLine \
  PThread/PThread \
  CPP_class/CPP_class \
  Errno/errno \
  Networking/networking \
  Windows/Windows \
  Linux/Linux \
  SFML/SFML \
  encryption/encryption \
  RNG/RNG

LIBS       := $(addsuffix .a, $(LIB_BASES))
DEBUG_LIBS := $(addsuffix _debug.a, $(LIB_BASES))

TARGET        := Full_Libft.a
DEBUG_TARGET  := Full_Libft_debug.a

all: $(TARGET)

debug: $(DEBUG_TARGET)

both: all debug

re: fclean all

$(TARGET): $(LIBS)
	@echo "Linking libraries into $(TARGET)..."
	rm -f $@
	mkdir -p temp_objs
	@for lib in $(LIBS); do \
	  cd temp_objs && $(AR) x ../$$lib; \
	  cd ..; \
	done
	$(AR) $(ARFLAGS) $@ temp_objs/*.o
	rm -rf temp_objs

$(DEBUG_TARGET): $(DEBUG_LIBS)
	@echo "Linking libraries into $(DEBUG_TARGET)..."
	rm -f $@
	mkdir -p temp_objs
	@for lib in $(DEBUG_LIBS); do \
	  cd temp_objs && $(AR) x ../$$lib; \
	  cd ..; \
	done
	$(AR) $(ARFLAGS) $@ temp_objs/*.o
	rm -rf temp_objs

%.a:
	$(MAKE) -C $(dir $@)

%_debug.a:
	$(MAKE) -C $(dir $@) debug

test: $(TEST_EXEC)
test_debug: $(TEST_EXEC_DEBUG)
test_both: test test_debug

re_test: fclean test

SFML_LIBS := $(shell pkg-config --libs sfml-graphics sfml-window sfml-system)

$(TEST_EXEC): $(TARGET)
	@echo "Linking test executable..."
	$(CXX) __test_main.cpp $(TARGET) $(SFML_LIBS) -o $(TEST_EXEC)

$(TEST_EXEC_DEBUG): $(DEBUG_TARGET)
	@echo "Linking test executable (debug)..."
	$(CXX) __test_main.cpp $(DEBUG_TARGET) $(SFML_LIBS) -o $(TEST_EXEC_DEBUG)

clean:
	@for dir in $(SUBDIRS); do \
	  $(MAKE) -C $$dir clean; \
	done
	rm -f $(TARGET) $(DEBUG_TARGET) $(TEST_EXEC) $(TEST_EXEC_DEBUG)

fclean: clean
	@for dir in $(SUBDIRS); do \
	  $(MAKE) -C $$dir fclean; \
	done
	rm -f $(TARGET) $(DEBUG_TARGET)

.PHONY: all debug both re clean fclean test test_debug test_both re_test
