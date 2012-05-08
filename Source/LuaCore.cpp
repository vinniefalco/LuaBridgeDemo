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

static int print (lua_State* lua)
{
  int nRetVal = 0;
  int nArg = lua_gettop (lua);

  String text;

  LuaCore* const luaCore = static_cast <LuaCore*> (
    lua_touserdata (lua, lua_upvalueindex (1)));

  for (int i = nArg; i>= 1; --i)
  {
    lua_pushvalue (lua, -i); // copy
    const char* s = lua_tostring (lua, -1);
    text << s;
    lua_pop (lua, 1);
  }

  luaCore->write (text);

  return nRetVal;
}

class LuaCoreImp : public LuaCore
{
private:
  struct State
  {
    StringArray lines;
  };

  State m_state;
  ListenerList <Listener> m_listeners;
  lua_State* m_lua;

public:
  LuaCoreImp ()
    : m_lua (luaL_newstate ())
  {
    luaL_openlibs (m_lua);

    lua_pushlightuserdata (m_lua, this);
    lua_pushcclosure (m_lua, print, 1);
    lua_setglobal (m_lua, "print");
  }

  ~LuaCoreImp ()
  {
    lua_close (m_lua);
  }

  void addListener (Listener* listener)
  {
    m_listeners.add (listener);
  }

  void removeListener (Listener* listener)
  {
    m_listeners.remove (listener);
  }

  void write (String text)
  {
    m_state.lines.add (text);

    m_listeners.call (&Listener::onLuaCoreOutput, text);
  }

  void doString (String text)
  {
    int result = luaL_dostring (m_lua, text.toUTF8());

    if (result != 0)
    {
      String errorMessage = lua_tostring (m_lua, -1);

      write (errorMessage);
    }
  }
};

LuaCore::~LuaCore ()
{
}

LuaCore* LuaCore::New ()
{
  return new LuaCoreImp;
}
