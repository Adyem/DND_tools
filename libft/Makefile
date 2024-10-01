CXX := g++
AR := ar
ARFLAGS := rcs

TARGET := Full_Libft.a

SUBDIRS := CMA \
	   GetNextLine \
	   Libft \
	   Printf \
	   ReadLine \
	   PThread \
	   get_next_line

LIBS := CMA/CustomMemoryAllocator.a \
        GetNextLine/GetNextLine.a \
        Libft/LibFT.a \
        Printf/Printf.a \
        ReadLine/ReadLine.a \
	PThread/PThread.a \
	get_next_line/get_next_line.a

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

$(LIBS):
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

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
