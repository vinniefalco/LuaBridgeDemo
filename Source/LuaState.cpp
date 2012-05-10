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

// for k,v in pairs(_G) do print(k,v) end

#if 0
static void print (lua_State* L, String text)
{
  lua_getglobal (L, "print");
  lua_pushvalue (L, -1);
  lua_pushstring (L, text.toUTF8 ());
  lua_call (L, 1, 0);
}

static int test ()
{
  return 42;
}
#endif

//==============================================================================

#if 0
class Object
{
private:
  Object (Object const&);
  Object& operator= (Object const&);

  LuaState& m_luaState;
  lua_State* m_lua;

public:
  Object (LuaState& luaState, lua_State* lua)
    : m_luaState (luaState)
    , m_lua (lua)
  {
    luabridge::scope m (m_lua);
    m.class_ <Object> ("Object")
      .method ("f1", &Object::f1)
      //.static_method ("t1", &Object::t1)
      ;
    luabridge::tdstack <luabridge::shared_ptr <Object> >::push (
      lua, luabridge::shared_ptr <Object> (this));
    lua_setglobal(lua, "obj");
  }

  ~Object ()
  {
  }

  void f1 ()
  {
    m_luaState.write ("f1\n");
  }

  static void s1 ()
  {
    //print ("t1\n");
  }
};
#endif

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
  lua_State* m_lua;

public:
  LuaStateImp () : m_lua (createEnvironment ())
  {
    //new Object (*this, m_lua);
  }

  ~LuaStateImp ()
  {
    lua_close (m_lua);
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
    text << "\n";
    luaState->print (text);
    return 0;
  }

  lua_State* createEnvironment ()
  {
    lua_State* L (luaL_newstate ());

    luaL_openlibs (L);

    // Hook the print function.
    lua_pushlightuserdata (L, this);
    lua_pushcclosure (L, &LuaStateImp::print, 1);
    lua_setglobal (L, "print");

    return L;
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

  void print (String text)
  {
    m_state.lines.add (text);

    m_listeners.call (&Listener::onLuaStatePrint, text);
  }

  void doString (String text)
  {
    int result = luaL_dostring (m_lua, text.toUTF8());

    if (result != 0)
    {
      print (lua_tostring (m_lua, -1));
    }

    print ("\n");
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
