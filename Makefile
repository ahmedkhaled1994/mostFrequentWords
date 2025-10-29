CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -Icfg
DEBUG_CFLAGS = -g -O0 -DDEBUG
SRCDIR = src
CFGDIR = cfg
BUILDDIR = build
TARGET = mostFrequentWords
INCLUDEDIR = include

# Automatically find all .c files in src and cfg directories
SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(CFGDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(wildcard $(SRCDIR)/*.c)) \
          $(patsubst $(CFGDIR)/%.c,$(BUILDDIR)/%.o,$(wildcard $(CFGDIR)/*.c))

# Find all header files
HEADERS = $(wildcard $(INCLUDEDIR)/*.h) $(wildcard $(CFGDIR)/*.h)

# Default target
all: $(TARGET)

# Debug build
debug-build: CFLAGS += $(DEBUG_CFLAGS)
debug-build: $(TARGET)

# Build the final executable
$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CC) $(OBJECTS) -o $(TARGET).exe

# Compile source files from src directory
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile source files from cfg directory
$(BUILDDIR)/%.o: $(CFGDIR)/%.c | $(BUILDDIR)
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

# Enhanced debug target with file listings
debug:
	@echo "=== BUILD CONFIGURATION ==="
	@echo "OS: $(OS)"
	@echo "CC: $(CC)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "Target: $(TARGET).exe"
	@echo ""
	@echo "=== DIRECTORIES ==="
	@echo "Source Dir: $(SRCDIR)"
	@echo "Config Dir: $(CFGDIR)"
	@echo "Include Dir: $(INCLUDEDIR)"
	@echo "Build Dir: $(BUILDDIR)"
	@echo ""
	@echo "=== SOURCE FILES ==="
	@echo "Sources: $(SOURCES)"
	@echo ""
	@echo "=== HEADER FILES ==="
	@echo "Headers: $(HEADERS)"
	@echo ""
	@echo "=== OBJECT FILES ==="
	@echo "Objects: $(OBJECTS)"
	@echo ""
	@echo "=== INCLUDE PATHS ==="
	@echo "Include paths: -Iinclude -Icfg"