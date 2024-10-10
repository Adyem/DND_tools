CXX := g++
AR := ar
ARFLAGS := rcs

OBJDIR := objs

TARGET := LibFT.a

SRCS := ft_atoi.cpp \
	ft_bzero.cpp \
	ft_memchr.cpp \
	ft_memcmp.cpp \
	ft_memcpy.cpp \
	ft_memmove.cpp \
	ft_memset.cpp \
	ft_strchr.cpp \
	ft_strlcat.cpp \
	ft_strlcpy.cpp \
	ft_strlen.cpp \
	ft_strncmp.cpp \
	ft_strnstr.cpp \
	ft_strrchr.cpp \
	ft_atol.cpp \
	ft_isdigit.cpp

HEADERS := libft.hpp

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
