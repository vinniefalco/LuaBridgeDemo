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

#include "LuaState.h"
#include "CConsoleWindow.h"
#include "UnitTests.h"
#include "UnitTests2.h"

class App : public JUCEApplication
{
private:
  ScopedPointer <LuaState> m_luaState;
  ScopedPointer <CConsoleWindow> m_window;

public:
  App()
    : m_luaState (LuaState::New ())
  {
  }

  ~App()
  {
  }

  void initialise (const String&)
  {
    // Do your application's initialisation code here..

    m_window = new CConsoleWindow (*m_luaState);

    m_window->setVisible (true);

    std::string errorString;
      
    errorString = runUnitTests (*m_luaState);
    if (errorString.size () > 0)
      m_luaState->print (errorString.c_str ());

    errorString = runUnitTests2 (*m_luaState);
    if (errorString.size () > 0)
      m_luaState->print (errorString.c_str ());

    addUnitTests2 (*m_luaState);
  }

  void shutdown()
  {
    // Do your application's shutdown code here..

    m_window = nullptr;
  }

  void systemRequestedQuit()
  {
    quit();
  }

  const String getApplicationName()
  {
    return "LuaBridge Demo";
  }

  const String getApplicationVersion()
  {
    return "1.0";
  }

  bool moreThanOneInstanceAllowed()
  {
    return true;
  }

  void anotherInstanceStarted (const String&)
  {

  }
};

START_JUCE_APPLICATION (App)
