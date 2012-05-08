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

class LuaCoreImp : public LuaCore
{
private:
  ListenerList <Listener> m_listeners;

public:
  LuaCoreImp ()
  {
  }

  ~LuaCoreImp ()
  {
  }

  void addListener (Listener* listener)
  {
    m_listeners.add (listener);
  }

  void removeListener (Listener* listener)
  {
    m_listeners.remove (listener);
  }

  void doString (String text)
  {
  }
};

LuaCore::~LuaCore ()
{
}

LuaCore* LuaCore::New ()
{
  return new LuaCoreImp;
}

#if 0
class LuaDJ : vf::Uncopyable
{
private:
  ICore& m_core;

public:
  LuaDJ (ICore& core, lua_State* lua)
    : m_core (core)
  {
    luabridge::scope m (lua);

    m.class_ <LuaDJ> ("dj")
      .method ("print",       &LuaDJ::print)
      .method ("__tostring",  &LuaDJ::tostring)
      //.method ("setMainOutputGain", &LibDJ::setMainOutputGain)
      ;

    luabridge::tdstack <luabridge::shared_ptr <LuaDJ> >::push (
      lua, luabridge::shared_ptr <LuaDJ> (this));
    
    lua_setglobal(lua, "dj");
  }

  ~LuaDJ ()
  {
  }

  int print (lua_State* lua)
  {
    int nRetVal = 0;
    int nArg = lua_gettop (lua);

    String text;

    for (int i = nArg; i>= 1; --i)
    {
      lua_pushvalue (lua, -i); // copy
      size_t len;
      const char* s = lua_tolstring (lua, -1, &len);
      text << s;
      lua_pop (lua, 1);
    }

    m_core.getIConsole().write (text);

    return nRetVal;
  }

  int tostring (lua_State*)
  {
    int nRetVal = 1;
    //int nArg = lua_gettop (lua);

    return nRetVal;
  }

  /*
  void setMainOutputGain (double gain)
  {
    ICore& core = MainApp::getInstance().getICore();
    IMixer& mixer = core.getIMixer();
    mixer.GetParam(IMixer::paramMainOutputGain)->setNativeValue (gain);
  }
  */
};

//==============================================================================

class LuaCoreImp : public LuaCore, vf::Uncopyable
{
private:
  Core& m_core;
  lua_State* m_lua;

public:
  explicit LuaCoreImp (Core& core)
    : m_core (core)
    , m_lua (luaL_newstate ())
  {
    luaL_openlibs (m_lua);

    new LuaDJ (m_core, m_lua);

    int result = luaL_dostring (m_lua,
      /*
      "io.console={}; "
      "local old_write = io.write; "
      "function io.write(h, ...) "
      "	if h == io.console then "
      "		dj.print(...); "
      "	else"
      "		old_write(h, ...) "
      "	end "
      "end "
      " "
      */
      //"function print(...) "
      //"  dj:print(...); "
      //"end"
      "function print(...) "
      " io.write(...); "
      "end"
      );

    //result = luaL_dostring (m_lua, "print (1)");
    if (result != 0)
      throw vf::Error().fail (__FILE__, __LINE__, lua_tostring (m_lua, -1));
  }

  ~LuaCoreImp ()
  {
    lua_close (m_lua);
  }

  void doString (String chunk)
  {
    int result = luaL_dostring (m_lua, chunk.toUTF8());

    if (result != 0)
    {
      const char* szErr = lua_tostring (m_lua, -1);
      m_core.getIConsole().write (szErr);
      //Logger::writeToLog (szErr);
    }
  }
};

//==============================================================================

LuaCore::~LuaCore ()
{
}

LuaCore* LuaCore::New (Core& core)
{
  return new LuaCoreImp (core);
}
#endif


#if 0
/*
struct null_deleter
{
  void operator()(void const *) const
  {
  }
};
*/

static void loadStdLibs (lua_State* lua)
{
  static const luaL_Reg lualibs[] =
  {
    {"", luaopen_base},
    {LUA_LOADLIBNAME, luaopen_package},
    {LUA_TABLIBNAME, luaopen_table},
    {LUA_IOLIBNAME, luaopen_io},
  //{LUA_OSLIBNAME, luaopen_os},
    {LUA_STRLIBNAME, luaopen_string},
    {LUA_MATHLIBNAME, luaopen_math},
  //{LUA_DBLIBNAME, luaopen_debug},
    {0, 0}
  };

  const luaL_Reg* lib = lualibs;

  for ( ; lib->func; lib++)
  {
    lua_pushcfunction (lua, lib->func);
    lua_pushstring (lua, lib->name);
    lua_call (lua, 1, 0);
  }
}

//------------------------------------------------------------------------------

namespace Lua {

//------------------------------------------------------------------------------

class LibDJ
{
public:
  LibDJ (lua_State* lua)
  {
    luabridge::scope m (lua);

    m.class_<LibDJ> ("dj")
      .method ("print", &LibDJ::print)
      .method ("__tostring", &LibDJ::tostring)
      .method ("setMainOutputGain", &LibDJ::setMainOutputGain)
      ;

    luabridge::tdstack<luabridge::shared_ptr<LibDJ> >::
        push(lua, luabridge::shared_ptr<LibDJ>(this));
        lua_setglobal(lua, "dj");
  }

  int print (lua_State* lua)
  {
    int nRetVal = 0;
    int nArg = lua_gettop (lua);

    String text;

    for (int i = nArg; i>= 1; --i)
    {
      lua_pushvalue (lua, -i); // copy
      const char* s = lua_tostring (lua, -1);
      text << s;
      lua_pop (lua, 1);
    }

    //Logger::writeToLog (text);
    MainApp::getInstance().getICore().getIConsole ().write (text);

    return nRetVal;
  }

  int tostring (lua_State*)
  {
    int nRetVal = 1;
    //int nArg = lua_gettop (lua);

    return nRetVal;
  }

  void setMainOutputGain (double gain)
  {
    ICore& core = MainApp::getInstance().getICore();
    IMixer& mixer = core.getIMixer();
    mixer.GetParam(IMixer::paramMainOutputGain)->setNativeValue (gain);
  }
};

}

//------------------------------------------------------------------------------

class LuaCore::Imp
{
private:
  lua_State* m_lua;

public:
  Imp ()
  {
    m_lua = luaL_newstate();

    loadStdLibs (m_lua);

    new Lua::LibDJ (m_lua);

    int result = luaL_dostring (m_lua,
      /*
      "io.console={}; "
      "local old_write = io.write; "
      "function io.write(h, ...) "
      "	if h == io.console then "
      "		dj.print(...); "
      "	else"
      "		old_write(h, ...) "
      "	end "
      "end "
      " "
      */
      "function print(...) "
      "	dj:print(...); "
      "end"
      );

    if (result != 0)
      throw vf::Error().fail (__FILE__, __LINE__, lua_tostring (m_lua, -1));
  }

  ~Imp ()
  {
    lua_close (m_lua);
  }

  void doString (String chunk)
  {
    const char *szUtf8 = chunk.toUTF8();

    int result;

    result = luaL_dostring (m_lua, szUtf8);

    if (result != 0)
    {
      const char* szErr = lua_tostring (m_lua, -1);
      Logger::writeToLog (szErr);
    }
  }
};

#endif
