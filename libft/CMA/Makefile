CXX := g++
AR := ar
ARFLAGS := rcs

OBJDIR := objs
DEBUG_OBJDIR := objs_debug

TARGET := CustomMemoryAllocator.a
DEBUG_TARGET := CustomMemoryAllocator_debug.a

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

.PHONY: all clean fclean re debug

