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

namespace luabridge
{

#include "LuaBridge/RefCountedObject.h"

}

namespace newtests
{

using namespace luabridge;

struct A {
  virtual void print (lua_State* L) {
    luaL_dostring (L, "print ('called A::print')");
  }
};

struct B : A {
  virtual void print (lua_State* L) {
    luaL_dostring (L, "print ('called B::print')");
  }
};

void addToState (lua_State* L) {
  getGlobalNamespace (L)
    .beginNamespace ("test")
      .beginClass <A> ("A")
        .addConstructor <void (*)(void)> ()
        .addMethod ("print", &A::print)
      .endClass ()
      .deriveClass <B, A> ("B")
        .addConstructor <void (*)(void),
                         shared_ptr <B> > ()
      .endClass ()
    .endNamespace ();
}

//------------------------------------------------------------------------------

void performTest (TestHost& host, std::string script)
{
  lua_State* L = host.createTestEnvironment ();

  addToState (L);

  int result = luaL_loadstring (L, script.c_str ());

  if (result == LUA_OK)
  {
    result = lua_pcall (L, 0, 0, 0);
  }

  if (result == LUA_OK )
  {
    host.print (std::string ("PASS: ") + script);
  }
  else
  {
    std::string errorText = lua_tostring (L, -1);

    host.print (errorText);
  }

  host.destroyTestEnvironment (L);
}

//------------------------------------------------------------------------------

void testStack (lua_State* L)
{
  int const idx = lua_gettop (L);

  /*
  int i = 0;
  long l = 0;
  bool b = false;
  short s = 0;
  float f = 0;
  double d = 0;
  unsigned int ui = 0;
  unsigned char uc = 0;
  unsigned short us = 0;
  unsigned long ul = 0;
  char c = 'a';
  char const* cc = "";
  std::string ss = "";

  push (L, i);
  push (L, l);
  push (L, b);
  push (L, s);
  push (L, f);
  push (L, d);
  push (L, ui);
  push (L, uc);
  push (L, us);
  push (L, ul);
  push (L, c);
  push (L, cc);
  push (L, ss);

  A a;
  A const ac;

  push (L, &a);
  push (L, &ac);
  push <A&> (L, a);
  push <A const&> (L, a);

  RefCountedObjectPtr <A> pa;
  RefCountedObjectPtr <A const> pac;

  push (L, pa);
  push (L, pac);

  push (L, a);
  push (L, ac);

  luabridge::Stack <A*>::push (L, &a);
  lua_pop (L, 1);

  luabridge::Stack <A* const>::push (L, &a);
  lua_pop (L, 1);

  luabridge::Stack <A const*>::push (L, &a);
  lua_pop (L, 1);
  */

  lua_settop (L, idx);
}

void runTests (TestHost& host)
{
#if 0
  host.print ("Running newtests.");

  performTest (host, "a = test.A (); a = nil; collectgarbage ()");

  {
    lua_State* L = host.createTestEnvironment ();

    addToState (L);

    testStack (L);

    host.destroyTestEnvironment (L);
  }
#else

#endif
}

//------------------------------------------------------------------------------

}

void runNewTests (LuaState& state)
{
  newtests::addToState (state.getState ());

  newtests::runTests (state);
}
