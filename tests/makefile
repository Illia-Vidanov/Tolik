# makefile to compile unit tests

# Directories
SOURCEDIR := $(CURDIR)
LIBDIR := C:/Programming/c++/Tolik/libs
BUILDDIR := $(CURDIR)

# Variables
EXE_EXTENTION = exe
DEBUG := -g
COMPILER := g++ -x c++
FLAGS := -Wall -fmax-errors=10 -Wshadow -std=c++17 #-funroll-loops
LIBS := -I$(LIBDIR)/Eigen -I$(LIBDIR)/gcem -LC:/Programming/c++/Tolik/build/lib -lTolik -lgtest
PCHS :=
INCLUDES := -I$(SOURCEDIR) -IC:/Programming/c++/Tolik/src
ECHO := @
PROGRESS := 1
DEFINES :=
INCLUDE_FILES_EXTENTIONS := hpp tpp inl
ADDITIONAL_DEPENDENCIES := $(foreach ext,$(INCLUDE_FILES_EXTENTIONS),$(foreach folder,$(shell find C:/Programming/c++/Tolik/src -type d),$(wildcard $(folder)/*.$(ext))))
# Only one type is allowed 
SOURCE_FILES_EXTENTION := test
# Needed for checking if makefile has changed
MAKEFILE_NAME := makefile
.DEFAULT_GOAL := run


# Note: I use findutils to locate files

# Find all folders in $(SOURCEDIR)
SOURCE_FOLDERS := $(shell find $(SOURCEDIR) -type d)

# Get all files we need to compile/link/include
SOURCES := $(foreach folder,$(SOURCE_FOLDERS),$(wildcard $(folder)/*.$(SOURCE_FILES_EXTENTION)))
# First find all include files from source folders
INCLUDE_FILES := $(foreach ext,$(INCLUDE_FILES_EXTENTIONS),$(foreach folder,$(SOURCE_FOLDERS),$(wildcard $(folder)/*.$(ext))))
EXES = $(foreach file,$(SOURCES),$(file:$(SOURCEDIR)/%.$(SOURCE_FILES_EXTENTION)=$(BUILDDIR)/%.$(EXE_EXTENTION)))


# Execute before/after compile
EXECUTE_BEFORE_COMPILE :=
EXECUTE_AFTER_COMPILE :=
$(shell $(EXECUTE_BEFORE_COMPILE))


# All
all: run

# Run
run: compile
	$(ECHO)if [ $(PROGRESS) ]; then \
		echo Run!; \
	fi; \
	for $(EXE_EXTENTION) in *.$(EXE_EXTENTION); do ./$$$(EXE_EXTENTION); done

# Compile
compile: $(EXES) $(MAKEFILE_NAME)
	$(ECHO)$(EXECUTE_AFTER_COMPILE) \
	if [ $(PROGRESS) ]; then \
		echo Compiled!; \
	fi;

define generate_rules
$(1:$(SOURCEDIR)/%.$(SOURCE_FILES_EXTENTION)=$(BUILDDIR)/%.$(EXE_EXTENTION)): $(1) $(INCLUDE_FILES) $(MAKEFILE_NAME) $(ADDITIONAL_DEPENDENCIES)
	$(ECHO)if [ $(PROGRESS) ]; then \
		echo Compiling $(notdir $(1))...; \
	fi; \
	$(COMPILER) $(DEBUG) $$< -o $$@ $(DEFIENS) $(FLAGS) $(INCLUDES) $(LIBS) 

endef

$(foreach src,$(SOURCES),$(eval $(call generate_rules,$(src))))

# Cleaning
clean:
	$(ECHO)rm *.exe