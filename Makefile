# Compiler settings
CC = g++
CFLAGS = -Wall -g 

# Service name
TARGET = program-service

# file root
SRCDIR = src
OBJDIR = obj
LIBDIR = lib

# Source file
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# Object file
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Include directories
INCLUDES = -I$(SRCDIR)

# Library link
LIBS = -L/usr/lib/x86_64-linux-gnu -lssl -lcrypto

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS) 

# Compile
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

# clean OBJ and TARGET
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean