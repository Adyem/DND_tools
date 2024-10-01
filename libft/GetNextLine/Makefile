CXX := g++
AR := ar
ARFLAGS := rcs

OBJDIR := objs

TARGET := GetNextLine.a

SRCS := get_next_line.cpp \
	get_next_line_utils.cpp

HEADERS := get_next_line.hpp

OBJS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

CXXFLAGS := -Wall -Wextra -Werror -g -O0 -std=c++17

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR)/%.o: %.cpp $(HEADERS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
