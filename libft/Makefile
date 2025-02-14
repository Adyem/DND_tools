CXX      := g++
AR       := ar
ARFLAGS  := rcs
CXXFLAGS := -Wall -Wextra -Werror -g -O0 -std=c++17

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
			SFML

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
  SFML/SFML

LIBS       := $(addsuffix .a, $(LIB_BASES))
DEBUG_LIBS := $(addsuffix _debug.a, $(LIB_BASES))

TARGET        := Full_Libft.a
DEBUG_TARGET  := Full_Libft_debug.a

.PHONY: all debug both clean fclean re

all: $(TARGET)
debug: $(DEBUG_TARGET)
both:  all debug
re: fclean all

$(TARGET): $(LIBS)
	rm -f $@
	mkdir -p temp_objs
	for lib in $(LIBS); do \
	  cd temp_objs && $(AR) x ../$$lib; \
	  cd ..; \
	done
	$(AR) $(ARFLAGS) $@ temp_objs/*.o
	rm -rf temp_objs

$(DEBUG_TARGET): $(DEBUG_LIBS)
	rm -f $@
	mkdir -p temp_objs
	for lib in $(DEBUG_LIBS); do \
	  cd temp_objs && $(AR) x ../$$lib; \
	  cd ..; \
	done
	$(AR) $(ARFLAGS) $@ temp_objs/*.o
	rm -rf temp_objs

%.a:
	$(MAKE) -C $(dir $@)

%_debug.a:
	$(MAKE) -C $(dir $@) debug

clean:
	@for dir in $(SUBDIRS); do \
	  $(MAKE) -C $$dir clean; \
	done
	rm -f $(TARGET) $(DEBUG_TARGET)

fclean: clean
	@for dir in $(SUBDIRS); do \
	  $(MAKE) -C $$dir fclean; \
	done
	rm -f $(TARGET) $(DEBUG_TARGET)
