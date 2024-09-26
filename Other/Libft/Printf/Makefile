CXX := g++
AR := ar
ARFLAGS := rcs

OBJDIR := objs

TARGET := printf.a

SRC_EXT := cpp
HEADER_EXT := hpp

SRCS := ft_printf.cpp
HEADERS := ft_printf.hpp

OBJS := $(patsubst %.$(SRC_EXT),$(OBJDIR)/%.o,$(SRCS))

CXXFLAGS := -Wall -Wextra -Werror -I.

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR)/%.o: %.$(SRC_EXT) %.$(HEADER_EXT) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
