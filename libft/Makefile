CXX := g++
AR := ar
ARFLAGS := rcs

TARGET := Full_Libft.a

SUBDIRS := CMA \
           GetNextLine \
           Libft \
           Printf \
           ReadLine \
           PThread

LIBS := CMA/CustomMemoryAllocator.a \
        GetNextLine/GetNextLine.a \
        Libft/LibFT.a \
        Printf/Printf.a \
        ReadLine/ReadLine.a \
        PThread/PThread.a

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

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -f $(TARGET)

fclean: clean
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir fclean; \
	done
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
