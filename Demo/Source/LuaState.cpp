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

class LuaStateImp : public LuaState
{
private:
  struct State
  {
    StringArray lines;
  };

  State m_state;
  ListenerList <Listener> m_listeners;
  lua_State* L;

public:
  LuaStateImp () : L (createEnvironment ())
  {
  }

  ~LuaStateImp ()
  {
    lua_close (L);
  }

  lua_State* getState ()
  {
    return L;
  }

  static void* getTracebackKey ()
  {
    static char key;
    return &key;
  }

  // traceback function, adapted from lua.c
  // when a runtime error occurs, this will append the call stack to the error message
  //
  static int tracebackFunction (lua_State* L)
  {
    // look up Lua's 'debug.traceback' function
    lua_getglobal(L, "debug");
    if (!lua_istable(L, -1))
    {
      lua_pop(L, 1);
      return 1;
    }
    lua_getfield(L, -1, "traceback");
    if (!lua_isfunction(L, -1))
    {
      lua_pop(L, 2);
      return 1;
    }
    lua_pushvalue(L, 1);  /* pass error message */
    lua_pushinteger(L, 2);  /* skip this function and traceback */
    lua_call(L, 2, 1);  /* call debug.traceback */
    return 1;
  }

  // from luaB_print()
  //
  static int print (lua_State *L)
  {
    LuaState* const luaState = static_cast <LuaState*> (
      lua_touserdata (L, lua_upvalueindex (1)));

    String text;
    int n = lua_gettop(L);  /* number of arguments */
    int i;
    lua_getglobal(L, "tostring");
    for (i=1; i<=n; i++) {
      const char *s;
      size_t l;
      lua_pushvalue(L, -1);  /* function to be called */
      lua_pushvalue(L, i);   /* value to print */
      lua_call(L, 1, 1);
      s = lua_tolstring(L, -1, &l);  /* get result */
      if (s == NULL)
        return luaL_error(L,
           LUA_QL("tostring") " must return a string to " LUA_QL("print"));
      if (i>1) text << " ";
      text << String (s, l);
      lua_pop(L, 1);  /* pop result */
    }
    luaState->print (std::string (text.toUTF8 ()));
    return 0;
  }

  lua_State* createEnvironment ()
  {
    lua_State* L_ (luaL_newstate ());

    luaL_openlibs (L_);

    // Hook the print function.
    // Must happen after opening the io lib.
    //
    lua_pushlightuserdata (L_, this);
    lua_pushcclosure (L_, &LuaStateImp::print, 1);
    lua_setglobal (L_, "print");

    // Install the traceback
    lua_pushcfunction (L_, tracebackFunction);
    lua_rawsetp (L_, LUA_REGISTRYINDEX, getTracebackKey ());

    return L_;
  }
  
  //----------------------------------------------------------------------------
  //
  // LuaState
  //
  //----------------------------------------------------------------------------

  void addListener (Listener* listener)
  {
    m_listeners.add (listener);
  }

  void removeListener (Listener* listener)
  {
    m_listeners.remove (listener);
  }

  void print (std::string text)
  {
    String s (text.c_str ());

    m_state.lines.add (s);

    m_listeners.call (&Listener::onLuaStatePrint, s);
  }

  int pcall (int numberOfArguments, int numberOfReturnValues)
  {
    return LuaState::pcall (L, numberOfArguments, numberOfReturnValues);
  }

  void doString (String text)
  {
    int result = luaL_dostring (L, text.toUTF8());

    if (result != 0)
    {
      print (std::string (lua_tostring (L, -1)));
    }
  }

  //----------------------------------------------------------------------------
  //
  // TestHost
  //
  //----------------------------------------------------------------------------

  lua_State* createTestEnvironment ()
  {
    return createEnvironment ();
  }

  void destroyTestEnvironment (lua_State* L)
  {
    lua_close (L);
  }
};

LuaState::~LuaState ()
{
}

LuaState* LuaState::New ()
{
  return new LuaStateImp;
}

int LuaState::pcall (lua_State* L, int numberOfArguments, int numberOfReturnValues)
{
  // push msgh
  lua_rawgetp (L, LUA_REGISTRYINDEX, LuaStateImp::getTracebackKey ());
  int msgh = -(numberOfArguments+2);
  lua_insert (L, msgh);

  int result = lua_pcall (L, numberOfArguments, numberOfReturnValues, msgh);

  // remove msgh
  if (result == LUA_OK)
    lua_remove (L, -(numberOfReturnValues+1));
  else
    lua_remove (L, -2);

  return result;
}

