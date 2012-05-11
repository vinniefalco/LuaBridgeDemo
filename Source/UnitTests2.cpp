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

#include "Lua_5_2/lua.hpp"

#include "LuaBridge/LuaBridge/luabridge.h"

#include "UnitTests2.h"

#include "JUCEAmalgam/include/juce_core_amalgam.h"

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
  void print (char const* text)
  {
    lua_getglobal (L, "print");
    lua_pushvalue (L, -1);
    lua_pushstring (L, text);
    lua_call (L, 1, 0);
  }

  /** Load and run a string
  */
  void dostring (char const* s)
  {
    int error;
    
    error = luaL_loadstring (L, s);
    
    if (!error)
      error = lua_pcall (L, 0, LUA_MULTRET, 0);

    if (error)
      print (lua_tostring (L, -1));
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

    L.dostring ("print (\"test1\")");
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
      .constructor <void (*) (void)> ()
      .method ("f", &test2::f);

    L.dostring ("test2 (): f();");
  }

  test2 ()
  {
  }

  void f ()
  {

  }
};

//==============================================================================
/*

What are attributes of the policy for a class:

- Whether or not the Lua code can create new objects
- How is the lifetime managed
- How is the object destroyed
- How a pointer to the class is extracted from the userdata


template <class T>
struct Policy
{
  
};

Implementation notes:

- Classes are always represented as a userdata with metatable

*/

template <typename T>
void push (lua_State* L, T t)
{
  // should never get here
  assert (0);
}

template <typename T>
void push (lua_State*, T*)
{
  assert (classname <T>::isRegistered ());
}

template <>
void push (lua_State*, char)
{
}

struct test3;

namespace luabridge
{
template <class T>
struct PolicyType
{
  static void test ()
  {
  }
};
template <>
class PolicyType <juce::ReferenceCountedObject*>
{
  //typedef class luabridge::OurSharedPtrPolicy <test3> type;
  static void test ()
  {
  }
};
}

struct test3 : public juce::ReferenceCountedObject
{
  static void run (TestHost& host)
  {
    ScopedLuaTestState L (host);

    luabridge::PolicyType <test3>::test ();

    test3* t = new test3;

    scope s (L);

    s.class_ <test3> ("test3")
      .method ("f", &test3::f);

    push (L, t);
    push (L, 'a');

    tdstack <shared_ptr <test3> >::push (L, shared_ptr <test3> ());
    
    lua_setglobal (L, "test3");

    L.dostring ("test3:f();");
  }

  test3 ()
  {
  }

  void f ()
  {
  }
};

//==============================================================================

void runUnitTests2 (TestHost& host)
{
  test1::run (host);
  test2::run (host);
  test3::run (host);
}
