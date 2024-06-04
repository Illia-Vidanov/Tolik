# Directories
SOURCEDIR := src
LIBDIR := libs
BUILDDIR := build/lib
OBJSDIR := build/objs

# Variables
APPNAME :=
DEBUG := -g
COMPILER := g++
FLAGS := -Wall -fmax-errors=10 -Wshadow -std=c++17 #-funroll-loops
LIBS := -I$(LIBDIR)/Eigen -I$(LIBDIR)/gcem
# .o files
THIRDPARTY :=
PCHS :=
INCLUDES := -I$(SOURCEDIR)
ARGS :=
ECHO := @
PROGRESS := 1
DEFINES :=
INCLUDEFILESEXTENTIONS := hpp tpp inl
# Needed for checking if makefile has changed
MAKEFILENAME := makefile
.DEFAULT_GOAL := compile


# Note: I use findutils to locate files

# Find all folders in $(SOURCEDIR)
SOURCEFOLDERS := $(shell find $(SOURCEDIR) -type d)
# Find all thirdparty files if a directory is given
THIRDPARTY := $(foreach dir,$(THIRDPARTY),$(if $(wildcard $(dir)/.),$(foreach file,$(shell cd $(dir) && find -type f -name "*.o"),$(subst ./,$(dir)/,$(file))),$(dir)))

# Creates folders for object files and by replacing $(SOURCEDIR) to $(OBJSDIR) (using folder structure in order to prevent collisions between files with same name)
$(foreach folder,$(SOURCEFOLDERS),$(shell mkdir -p $(subst $(SOURCEDIR),$(OBJSDIR),$(folder))))
$(shell mkdir -p $(BUILDDIR))

# Get all files we need to compile/link/include
SOURCES := $(foreach folder,$(SOURCEFOLDERS),$(wildcard $(folder)/*.cpp))
# First find all include files from source folders
INCLUDEFILES := $(foreach ext,$(INCLUDEFILESEXTENTIONS),$(foreach folder,$(SOURCEFOLDERS),$(wildcard $(folder)/*.$(ext))))
OBJS := $(foreach file,$(SOURCES),$(file:$(SOURCEDIR)/%.cpp=$(OBJSDIR)/%.o))


# Execute before/after compile
EXECUTEBEFORECOMPILE :=
EXECUTEAFTERCOMPILE := ar rvs $(CURDIR)/$(BUILDDIR)/libTolik.a $(OBJS)
$(shell $(EXECUTEBEFORECOMPILE))


# All
all: run

# Run
run: compile
	$(ECHO)if [ $(PROGRESS) ]; then \
		echo Run!; \
	fi; \
	$(BUILDDIR)/$(APPNAME) $(ARGS)

precompileHeader: $(ARGS)
	$(ECHO)if [ $(PROGRESS) ]; then \
		echo Compiling $(notdir $(ARGS))...; \
	fi; \
	$(COMPILER) $(DEBUG) $(ARGS) -c $(addsufix .gch,$(ARGS)) $(DEFIENS) $(FLAGS) $(LIBS); \
	if [ $(PROGRESS) ]; then \
		echo Compiled!; \
	fi;

# Debug
debug: compile
	$(ECHO)if [ $(PROGRESS) ]; then \
		echo run Debug!; \
	fi; \
	gdb --args $(BUILDDIR)/$(APPNAME) $(ARGS)

# Compile
ifneq ($(APPNAME),)
compile: $(OBJS) $(MAKEFILENAME)
	$(ECHO)if [ $(PROGRESS) ]; then \
		echo Compiling $(APPNAME); \
	fi; \
	$(COMPILER) $(DEBUG) $(OBJS) $(THIRDPARTY) -o $(BUILDDIR)/$(APPNAME) $(DEFIENS) $(FLAGS) $(INCLUDES) $(LIBS); \
	if [ $(PROGRESS) ]; then \
		echo Compiled!; \
	fi; \
	$(EXECUTEAFTERCOMPILE)
else
compile: $(OBJS) $(MAKEFILENAME)
	$(ECHO)if [ $(PROGRESS) ]; then \
		echo Compiled!; \
	fi; \
	$(EXECUTEAFTERCOMPILE)
endif

# Object files
define generateRules
$(1:$(SOURCEDIR)/%.cpp=$(OBJSDIR)/%.o): $1 $(INCLUDEFILES) $(MAKEFILENAME)
	$(ECHO)if [ $(PROGRESS) ]; then \
		echo Compiling $(notdir $(1))...; \
	fi; \
	$(COMPILER) $(DEBUG) -c $$< -o $$@ $(DEFIENS) $(FLAGS) $(INCLUDES) $(LIBS) 

endef

$(foreach src,$(SOURCES),$(eval $(call generateRules,$(src))))
#$(info $(foreach src,$(SOURCES),$(call generateRules,$(src))))

# Cleaning
cleanObjFiles:
	$(ECHO)rm -r $(OBJSDIR)

clean: cleanObjFiles
	$(ECHO)rm -r $(BUILDDIR)