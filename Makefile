CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
DEBUG_CFLAGS = -g -O0 -DDEBUG
SRCDIR = src
BUILDDIR = build
TARGET = mostFrequentWords

# Automatically find all .c files in src directory
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

# Default target
all: $(TARGET)

# Debug build
debug-build: CFLAGS += $(DEBUG_CFLAGS)
debug-build: $(TARGET)

# Build the final executable
$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CC) $(OBJECTS) -o $(TARGET).exe

# Compile individual object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist (Windows compatible)
$(BUILDDIR):
ifeq ($(OS),Windows_NT)
	if not exist $(BUILDDIR) mkdir $(BUILDDIR)
else
	mkdir -p $(BUILDDIR)
endif

# Clean up build files (Windows compatible)
clean:
ifeq ($(OS),Windows_NT)
	if exist $(BUILDDIR) rmdir /s /q $(BUILDDIR)
	if exist $(TARGET).exe del $(TARGET).exe
else
	rm -rf $(BUILDDIR) $(TARGET)
endif

# Phony targets
.PHONY: all clean debug-build

# Enhanced debug target
debug:
	@echo "OS: $(OS)"
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "Target: $(TARGET).exe"