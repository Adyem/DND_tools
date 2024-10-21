CXX := g++
AR := ar
ARFLAGS := rcs

OBJDIR := objs
DEBUG_OBJDIR := objs_debug

TARGET := LibFT.a
DEBUG_TARGET := LibFT_debug.a

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
DEBUG_OBJS := $(patsubst %.cpp,$(DEBUG_OBJDIR)/%.o,$(SRCS))

CXXFLAGS := -Wall -Wextra -Werror -g -O0 -std=c++17

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR)/%.o: %.cpp $(HEADERS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

debug: CXXFLAGS += -DDEBUG=1
debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(DEBUG_OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(DEBUG_OBJDIR)/%.o: %.cpp $(HEADERS) | $(DEBUG_OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR) $(DEBUG_OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(DEBUG_OBJDIR)

fclean: clean
	rm -f $(TARGET) $(DEBUG_TARGET)

re: fclean all

.PHONY: all debug clean fclean re
