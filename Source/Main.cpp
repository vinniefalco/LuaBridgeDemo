/*
  ==============================================================================

  Copyright (c) 2012, Vinnie Falco <vinnie.falco@gmail.com>

  This file is provided under the terms of the MIT License:

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  ==============================================================================
*/

#include "Lua_5_2/lua.hpp"

#include "LuaBridge/include/luabridge.hpp"

#include "JUCEAmalgam/include/juce_core_amalgam.h"
#include "JUCEAmalgam/include/juce_data_structures_amalgam.h"
#include "JUCEAmalgam/include/juce_events_amalgam.h"
#include "JUCEAmalgam/include/juce_graphics_amalgam.h"
#include "JUCEAmalgam/include/juce_gui_basics_amalgam.h"

using namespace juce;

#include "CConsole.h"
#include "CConsoleEdit.h"
#include "CConsoleText.h"
#include "CConsoleWindow.h"
#include "LuaCore.h"

#include "LuaBridge/src/luabridge.cpp"
#include "LuaBridge/src/shared_ptr.cpp"

#include "CConsole.cpp"
#include "CConsoleEdit.cpp"
#include "CConsoleText.cpp"
#include "CConsoleWindow.cpp"
#include "LuaCore.cpp"

#include "App.cpp"
