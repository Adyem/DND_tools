CXX := g++
AR := ar
ARFLAGS := rcs

OBJDIR := objs
DEBUG_OBJDIR := objs_debug

TARGET := Full_Libft.a
DEBUG_TARGET := Full_Libft_debug.a

SUBDIRS := CMA \
           GetNextLine \
           Libft \
           Printf \
           ReadLine \
           PThread \
		   CPP_class \
		   Errno

LIBS := CMA/CustomMemoryAllocator.a \
        GetNextLine/GetNextLine.a \
        Libft/LibFT.a \
        Printf/Printf.a \
        ReadLine/ReadLine.a \
        PThread/PThread.a \
		CPP_class/CPP_class.a \
		Errno/errno.a

DEBUG_LIBS := CMA/CustomMemoryAllocator_debug.a \
              GetNextLine/GetNextLine_debug.a \
              Libft/LibFT_debug.a \
              Printf/Printf_debug.a \
              ReadLine/ReadLine_debug.a \
              PThread/PThread_debug.a \
			  CPP_class/CPP_class_debug.a \
			  Errno/errno_debug.a

CXXFLAGS := -Wall -Wextra -Werror -g -O0 -std=c++17

all: $(TARGET)

$(TARGET): $(LIBS)
	rm -f $(TARGET)
	mkdir -p temp_objs
	for lib in $(LIBS); do \
		cd temp_objs && $(AR) x ../$$lib; \
		cd ..; \
	done
	$(AR) $(ARFLAGS) $(TARGET) temp_objs/*.o
	rm -rf temp_objs

debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(DEBUG_LIBS)
	rm -f $(DEBUG_TARGET)
	mkdir -p temp_objs
	for lib in $(DEBUG_LIBS); do \
		cd temp_objs && $(AR) x ../$$lib; \
		cd ..; \
	done
	$(AR) $(ARFLAGS) $(DEBUG_TARGET) temp_objs/*.o
	rm -rf temp_objs

CPP_class/CPP_class.a:
	$(MAKE) -C CPP_class

CMA/CustomMemoryAllocator.a:
	$(MAKE) -C CMA

GetNextLine/GetNextLine.a:
	$(MAKE) -C GetNextLine

Libft/LibFT.a:
	$(MAKE) -C Libft

Printf/Printf.a:
	$(MAKE) -C Printf

ReadLine/ReadLine.a:
	$(MAKE) -C ReadLine

PThread/PThread.a:
	$(MAKE) -C PThread

Errno/errno.a:
	$(MAKE) -C Errno

Errno/errno_debug.a:
	$(MAKE) -C Errno debug

CMA/CustomMemoryAllocator_debug.a:
	$(MAKE) -C CMA debug

CPP_class/CPP_class_debug.a:
	$(MAKE) -C CPP_class debug

GetNextLine/GetNextLine_debug.a:
	$(MAKE) -C GetNextLine debug

Libft/LibFT_debug.a:
	$(MAKE) -C Libft debug

Printf/Printf_debug.a:
	$(MAKE) -C Printf debug

ReadLine/ReadLine_debug.a:
	$(MAKE) -C ReadLine debug

PThread/PThread_debug.a:
	$(MAKE) -C PThread debug

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

re: fclean all

both: all debug

.PHONY: all debug clean fclean re both
