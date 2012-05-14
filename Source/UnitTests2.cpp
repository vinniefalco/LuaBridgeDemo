//==============================================================================
/*
  https://github.com/vinniefalco/LuaBridge
  https://github.com/vinniefalco/LuaBridgeDemo
  
  Copyright (C) 2012, Vinnie Falco <vinnie.falco@gmail.com>
  Copyright (C) 2007, Nathan Reed

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

// for k,v in pairs (_G) do print (k, v) end

#include "Lua_5_2/lua.hpp"

#include "LuaBridge/LuaBridge.h"
#include "LuaBridge/shared_ptr.h"

#include "UnitTests2.h"

#include "JUCEAmalgam/include/juce_core_amalgam.h"
 
using namespace juce;
using namespace luabridge;

//==============================================================================
/**
  Wraps a lua_State to perform common tasks.
*/
class LuaStateWrapper
{
public:
  LuaStateWrapper (lua_State* L_) : L (L_)
  {
  }

  inline operator lua_State* ()
  {
    return L;
  }

  /** Print a message
  */
  void print (String text)
  {
    lua_getglobal (L, "print");
    lua_pushvalue (L, -1);
    lua_pushstring (L, text.toUTF8 ());
    lua_call (L, 1, 0);
  }

protected:
  lua_State* L;
};

//==============================================================================
/**
  Scoped lifetime management for a lua_State test environment.

  The test environment includes a traceback lua function as well as
  some convenience member functions.
*/
class ScopedLuaTestState : public LuaStateWrapper
{
public:
  explicit ScopedLuaTestState (TestHost& host)
    : LuaStateWrapper (host.createTestEnvironment ())
    , m_host (host)
  {
    lua_pushcfunction (L, &traceback); // push traceback
    m_errfunc_index = lua_gettop(L);
  }

  ~ScopedLuaTestState ()
  {
    lua_pop (L, 1);  // pop traceback

    m_host.destroyTestEnvironment (L);
  }

  /** Load and run a string
  */
  void load (char const* s)
  {
    int error;
    
    error = luaL_loadstring (L, s);
    
    if (!error)
      error = lua_pcall (L, 0, LUA_MULTRET, m_errfunc_index);

    if (error)
      print (lua_tostring (L, -1));
  }

  /** Call a function with arguments.
  */
  void call (int nArgs = 0)
  {
    int error = lua_pcall (L, nArgs, LUA_MULTRET, m_errfunc_index);

    if (error)
      print (lua_tostring (L, -1));
  }

private:
  // traceback function, adapted from lua.c
  // when a runtime error occurs, this will append the call stack to the error message
  static int traceback (lua_State *L)
  {
    // look up Lua's 'debug.traceback' function
    lua_getglobal (L, "debug");
    if (lua_istable (L, -1))
    {
      lua_getfield (L, -1, "traceback");
      if (lua_isfunction(L, -1))
      {
        lua_pushvalue (L, 1);     // pass error message
        lua_pushinteger (L, 2);   // skip this function and traceback
        lua_call (L, 2, 1);       // call debug.traceback
      }
      else
      {
        lua_pop (L, 2);
      }
    }
    else
    {
      lua_pop (L, 1);
    }

    return 1;
  }

private:
  ScopedLuaTestState& operator= (ScopedLuaTestState const&);

  TestHost& m_host;
  int m_errfunc_index;
};

//==============================================================================

struct test1
{
  static void run (TestHost& host)
  {
    ScopedLuaTestState L (host);

    L.load ("print (\"test1\")");
  }

private:
};

//==============================================================================

struct test2
{
  static void run (TestHost& host)
  {
    ScopedLuaTestState L (host);

    scope s (L);

    s.class_ <test2> ("test2")
      .constructor <void (*) (void), luabridge::shared_ptr> ()
      .method ("f", &test2::f);

    L.load ("test2 (): f();");
  }

  test2 ()
  {
  }

  void f ()
  {

  }
};

//==============================================================================

struct stacktests
{
  struct A
  {
    A ()
    {
    }

    void set (int value)
    {
      var () = value;
    }

    int get () const
    {
      return var ();
    }

    //void take (shared_ptr <A> p)
    void take (A*)
    {
    }

    void getState (lua_State*)
    {
    }

  private:
    static int& var ()
    {
      static int value = 0;
      return value;
    }
  };

  static void run (TestHost& host)
  {
    ScopedLuaTestState L (host);

    scope s (L);

    s.class_ <A> ("A")
      .constructor <void (*) (void), luabridge::shared_ptr> ()
      .method ("set", &A::set)
      .method ("take", &A::take)
      .method ("getState", &A::getState)
      ;

    L.load ("local function test () print (\"test1\"); end return test");
    L.call ();

    L.load ("local function test (t) print (t); end return test");
    tdstack <int>::push (L, 16);
    L.call (1);

    {
      A a;
      L.load ("local function test (a) a:set(42); end return test");
      tdstack <A>::push (L, a);
      L.call (1);
      String s;
      s << "value = " << String (a.get ());
      L.print (s);
    }

    {
      A a;
      A& ra (a);
      L.load ("local function test (a) a:set(50); end return test");
      tdstack <A>::push (L, ra);
      L.call (1);
      String s;
      s << "value = " << String (a.get ());
      L.print (s);
    }

    {
      L.load ("local function test () a=A(); a:take (a); end return test");
      L.call ();
    }
  }
};

//==============================================================================

#if 0
struct test3
{
  static void run (TestHost& host)
  {
    ScopedLuaTestState L (host);

    scope s (L);

    s.class_ <test3, std::shared_ptr> ("test3")
      .constructor <void (*) (void)> ()
      .method ("f", &test3::f);

    L.dostring ("test3 (): f();");
  }

  test3 ()
  {
  }

  void f ()
  {

  }
};
#endif

//==============================================================================

void runUnitTests2 (TestHost& host)
{
//  test1::run (host);
//  test2::run (host);
//  test3::run (host);

  stacktests::run (host);
}
