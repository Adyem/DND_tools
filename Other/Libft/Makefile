CXX := g++
AR := ar
ARFLAGS := rcs

TARGET := Full_Libft.a

SUBDIRS := CMA get_next_line Libft Printf ReadLine

LIBS := CMA/CustomMemoryAllocator.a \
        get_next_line/GetNextLine.a \
        Libft/LibFT.a \
        Printf/Printf.a \
        ReadLine/ReadLine.a

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
