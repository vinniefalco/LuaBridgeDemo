# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(TARGET_ARCH),)
  TARGET_ARCH := -march=native
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "LUA_USE_APICHECK" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "LUA_USE_APICHECK" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../
  TARGET := LuaBridgeDemo
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../
  TARGET := LuaBridgeDemo
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
  $(OBJDIR)/juce_core_amalgam_b9b4addc.o \
  $(OBJDIR)/juce_data_structures_amalgam_7e0eb61c.o \
  $(OBJDIR)/juce_events_amalgam_7d753996.o \
  $(OBJDIR)/juce_graphics_amalgam_f3add948.o \
  $(OBJDIR)/juce_gui_basics_amalgam_dc5a1886.o \
  $(OBJDIR)/LuaLibrary5.1.5_2cc1eeeb.o \
  $(OBJDIR)/LuaLibrary5.2.1_616fcc28.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking LuaBridgeDemo
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning LuaBridgeDemo
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)/*
	-@rm -rf $(OBJDIR)

strip:
	@echo Stripping LuaBridgeDemo
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/juce_core_amalgam_b9b4addc.o: ../../JUCEAmalgam/include/juce_core_amalgam.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core_amalgam.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_amalgam_7e0eb61c.o: ../../JUCEAmalgam/include/juce_data_structures_amalgam.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures_amalgam.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_amalgam_7d753996.o: ../../JUCEAmalgam/include/juce_events_amalgam.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events_amalgam.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_amalgam_f3add948.o: ../../JUCEAmalgam/include/juce_graphics_amalgam.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics_amalgam.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_amalgam_dc5a1886.o: ../../JUCEAmalgam/include/juce_gui_basics_amalgam.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics_amalgam.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LuaLibrary5.1.5_2cc1eeeb.o: ../../../Lua/LuaLibrary5.1.5.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LuaLibrary5.1.5.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LuaLibrary5.2.1_616fcc28.o: ../../../Lua/LuaLibrary5.2.1.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LuaLibrary5.2.1.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
