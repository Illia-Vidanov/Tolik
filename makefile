# makefile to compile project

# Directories
SOURCEDIR := $(CURDIR)/src
IGNORE_DIRS :=
BUILDDIR := $(CURDIR)/build
OBJSDIR := $(CURDIR)/build/objs

# Variables
APP_NAME :=
DEBUG := -g
COMPILER := g++
FLAGS := -Wall -Wextra -Wdeprecated -pedantic-errors -fmax-errors=10 -Wshadow -std=c++17 #-funroll-loops
LIBS := -IEigen -Igcem
INCLUDES := -I$(SOURCEDIR)
ARGS :=
ECHO := @
PROGRESS := 1
DEFINES :=
INCLUDE_FILES_EXTENTIONS := .hpp .tpp .inl
ADDITIONAL_DEPENDENCIES :=
# Only one type is allowed 
SOURCE_FILES_EXTENTIONS := .cpp
# Needed for checking if makefile has changed
MAKEFILE_NAME := makefile
.DEFAULT_GOAL := compile
.ONESHELL:

# Note: I use findutils to locate files

#functions
src_to_obj = $(1:$(SOURCEDIR)/%$(suffix $(1))=$(OBJSDIR)/%.o)

# Find all folders in $(SOURCEDIR) ignoring $(IGNORE_DIRS)
SOURCE_FOLDERS := $(shell find $(SOURCEDIR) $(foreach dir,$(IGNORE_DIRS),-wholename $(dir) -prune -o ) -type d -print)

# Creates folders for object files and by replacing $(SOURCEDIR) to $(OBJSDIR) (using folder structure in order to prevent collisions between files with same name)
$(shell mkdir -p $(BUILDDIR))
$(foreach folder,$(SOURCE_FOLDERS),$(shell mkdir -p $(subst $(SOURCEDIR),$(OBJSDIR),$(folder))))

# Get all files we need to compile/link/include
SOURCES := $(foreach ext,$(SOURCE_FILES_EXTENTIONS),$(foreach folder,$(SOURCE_FOLDERS),$(wildcard $(folder)/*$(ext))))
# First find all include files from source folders
INCLUDE_FILES := $(foreach ext,$(INCLUDE_FILES_EXTENTIONS),$(foreach folder,$(SOURCE_FOLDERS),$(wildcard $(folder)/*$(ext))))
OBJS := $(foreach file,$(SOURCES),$(call src_to_obj,$(file)))


# Execute before/after compile
EXECUTE_BEFORE_COMPILE :=
EXECUTE_AFTER_COMPILE := mkdir -p $(BUILDDIR)/Tolik/lib $(BUILDDIR)/Tolik/include/Tolik; \
ar rvs $(BUILDDIR)/Tolik/lib/libTolik.a $(OBJS); \
xcopy //s //e //c //h //y $(patsubst \\c\\%,C:\\%,$(subst /,\\,$(SOURCEDIR))) $(patsubst \\c\\%,C:\\%,$(subst /,\\,$(BUILDDIR)/Tolik/include/Tolik)); \
$(foreach ext,$(SOURCE_FILES_EXTENTIONS),rm $(BUILDDIR)/Tolik/include/Tolik/*/*$(ext); ) \
true
$(shell $(EXECUTE_BEFORE_COMPILE))
# Need this to not leave an empty spot
EXECUTE_AFTER_COMPILE := $(if $(EXECUTE_AFTER_COMPILE),$(EXECUTE_AFTER_COMPILE),true)

# Get starting time of seconds since epoch
START_TIME := $(shell date +%s)


# All
all: run

# Run
run: compile
	$(call print,Running application!);
	$(BUILDDIR)/$(APP_NAME) $(ARGS)

precompile_header: $(ARGS)
	$(ECHO)$(call time_it,Compiled $(ARGS) in %E,$(COMPILER) $(DEBUG) $(ARGS) -c $(addsufix .gch,$(ARGS)) $(DEFIENS) $(FLAGS) $(INCLUDES) $(LIBS));
	$(call print,Compiled in total of $$(($$(date +%s) - $(START_TIME))) seconds!)

# Compile
ifneq ($(APP_NAME),)
compile: $(OBJS) $(MAKEFILE_NAME) $(ADDITIONAL_DEPENDENCIES)
	$(ECHO)$(call time_it,Compiled $(APP_NAME) in %E,$(COMPILER) $(DEBUG) $(OBJS) -o $(BUILDDIR)/$(APP_NAME) $(DEFIENS) $(FLAGS) $(INCLUDES) $(LIBS));
	$(EXECUTE_AFTER_COMPILE);
	$(call print,Compiled in total of $$(($$(date +%s) - $(START_TIME))) seconds!)
else
compile: $(OBJS) $(MAKEFILE_NAME)
	$(ECHO)$(EXECUTE_AFTER_COMPILE);
	$(call print,Compiled in total of $$(($$(date +%s) - $(START_TIME))) seconds!)
endif


# Defines

# Print
define print
if [ $(PROGRESS) ]; then echo $(1); fi
endef

define time_it
if [ $(PROGRESS) ]; then time --format="$(1)" $(2); else $(2); fi
endef

# Object files
define generate_rules
$(call src_to_obj,$(1)): $(1) $(INCLUDE_FILES) $(MAKEFILE_NAME) $(ADDITIONAL_DEPENDENCIES)
	$(ECHO)$(call time_it,Compiled $(notdir $(1)) in %E,$(COMPILER) $(DEBUG) -c $$< -o $$@ $(DEFIENS) $(FLAGS) $(INCLUDES) $(LIBS));
endef

$(foreach src,$(SOURCES),$(eval $(call generate_rules,$(src))))

# Cleaning
clean_pch:
	$(ECHO)rm -rf *.gch

clean_obj:
	$(ECHO)rm -rf $(OBJSDIR)

clean: clean_obj clean_pch
	$(ECHO)rm -rf $(BUILDDIR)