CXX := g++
AR := ar
ARFLAGS := rcs

OBJDIR := objs

TARGET := CustomMemoryAllocator.a

SRCS := cma_calloc.cpp \
        cma_strdup.cpp \
		cma_malloc.cpp \
		cma_free.cpp \
		cma_cleanup_all_memory.cpp \
		cma_cleanup_non_critical_memory.cpp \
		cma_add_page.cpp \
		cma_realloc.cpp \
		cma_itoa.cpp \
		cma_split.cpp \
		cma_strjoin.cpp \
		cma_free_double.cpp

HEADERS := CMA.hpp

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
