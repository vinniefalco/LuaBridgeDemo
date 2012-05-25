//==============================================================================
/*
  https://github.com/vinniefalco/LuaBridge
  https://github.com/vinniefalco/LuaBridgeDemo
  
  Copyright (C) 2012, Vinnie Falco <vinnie.falco@gmail.com>

  License: The MIT License (http://www.opensource.org/licenses/mit-license.php)

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
*/
//==============================================================================

#include "Lua/LuaLibrary.h"
#include "LuaBridge/LuaBridge.h"

#include "Demo/JUCEAmalgam/include/juce_core_amalgam.h"
#include "Demo/JUCEAmalgam/include/juce_data_structures_amalgam.h"
#include "Demo/JUCEAmalgam/include/juce_events_amalgam.h"
#include "Demo/JUCEAmalgam/include/juce_graphics_amalgam.h"
#include "Demo/JUCEAmalgam/include/juce_gui_basics_amalgam.h"

using namespace juce;

#include "CConsole.h"
#include "CConsoleEdit.h"
#include "CConsoleText.h"
#include "CConsoleWindow.h"
#include "LuaState.h"

#include "CConsole.cpp"
#include "CConsoleEdit.cpp"
#include "CConsoleText.cpp"
#include "CConsoleWindow.cpp"
#include "LuaState.cpp"

#include "App.cpp"
