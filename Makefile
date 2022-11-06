# Commands
RM = rm -rf

# Directories
build_REMDIR = ./build

# OS specific Definitions and Linkage
ifeq ($(OS),Windows_NT)
    #Windows Specific
	RM = del /s /q
	build_REMDIR = .\build
endif

clean:
	$(RM) $(build_REMDIR)\*