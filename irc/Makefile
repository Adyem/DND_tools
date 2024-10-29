CXX          := c++
CXXFLAGS     := -Wall -Werror -Wextra -std=c++98
DEBUGFLAGS   := -DDEBUG=1 -g
NAME         := irc_server
DEBUGNAME    := irc_server_debug

SRCS         := channel.cpp \
				check_input.cpp \
                create_socket.cpp \
                main.cpp \
                server_class.cpp \
                start_communication.cpp \
                client_class.cpp \
				new_client.cpp \
				kick.cpp \
				invite.cpp \
				part.cpp \
				quit.cpp \
				split_command.cpp \
				ping_pong.cpp \
				cap.cpp \
				excecute_cmd.cpp \
				send_handshake.cpp \
				data_handling.cpp \
				accept_client.cpp \
				private_msg.cpp \
				mode.cpp \
				topic.cpp \
				join.cpp \
				notice.cpp


OBJDIR       := objs
DEBUGOBJDIR  := debug_objs
OBJS         := $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))
DEBUGOBJS    := $(addprefix $(DEBUGOBJDIR)/, $(SRCS:.cpp=.o))
INCLUDES     := -I.

HEADERS      := irc.hpp \
                server_class.hpp \
                client_class.hpp \
				channel.hpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

debug: $(DEBUGOBJDIR)/$(DEBUGNAME)

$(DEBUGOBJDIR)/$(DEBUGNAME): $(DEBUGOBJS)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $(DEBUGOBJS) -o $(DEBUGNAME)

$(DEBUGOBJDIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(DEBUGOBJDIR)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(DEBUGOBJDIR)

fclean: clean
	rm -f $(NAME) $(DEBUGNAME)
	rm -rf $(OBJDIR) $(DEBUGOBJDIR)

re: fclean all

both: all debug

.PHONY: all debug clean fclean re both
