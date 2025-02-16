CXX := g++
AR := ar
ARFLAGS := rcs

OBJDIR := objs
DEBUG_OBJDIR := objs_debug

TARGET := SFML.a
DEBUG_TARGET := SFML_debug.a

SRCS := create_window.cpp \
		translate_coordinates.cpp \
		add_sprite.cpp

HEADERS := SFML.hpp

OBJS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))
DEBUG_OBJS := $(patsubst %.cpp,$(DEBUG_OBJDIR)/%.o,$(SRCS))

SFML_CFLAGS := $(shell pkg-config --cflags sfml-graphics)
SFML_LIBS   := $(shell pkg-config --libs sfml-graphics)

CXXFLAGS := -Wall -Wextra -Werror -g -O0 -std=c++17 $(SFML_CFLAGS)

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
