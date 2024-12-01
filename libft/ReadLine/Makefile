CXX := g++
AR := ar
ARFLAGS := rcs

OBJDIR := objs
DEBUG_OBJDIR := objs_debug

TARGET := ReadLine.a
DEBUG_TARGET := ReadLine_debug.a

SRCS := readline.cpp \
	clear_history.cpp \
	handle_keypress.cpp \
	suggestions.cpp \
	utilities.cpp \
	tab_completion.cpp \
	printeble_char.cpp \
	raw_mode.cpp \
	initialize.cpp

HEADERS := readline.hpp \
		   readline_internal.hpp

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

both: all debug

.PHONY: all debug clean fclean re both
