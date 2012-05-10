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

CConsoleWindow::CConsoleWindow (LuaState& luaState)
  : DocumentWindow (
      TRANS("Lua Console"),
      Colours::black,
      DocumentWindow::allButtons,
      false)
{
  setSize (640, 480);

  setOpaque (true);
  setResizable (true, false);
  setDropShadowEnabled (false);
  //setUsingNativeTitleBar (true);
  setWantsKeyboardFocus (true);

  // must happen AFTER setUsingNativeTitleBar()
  Component::addToDesktop (getDesktopWindowStyleFlags());

  // must happen after addToDesktop()
  Component* c = new CConsole (luaState);
  c->setBounds (0, 0, 640, 480);
  setContentOwned (c, true);

  setSize (640, 480);

  centreWithSize (getWidth(), getHeight());

  grabKeyboardFocus ();
}

CConsoleWindow::~CConsoleWindow ()
{
}

void CConsoleWindow::closeButtonPressed ()
{
  JUCEApplication::getInstance()->quit ();
}
