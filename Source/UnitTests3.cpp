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

namespace test3
{

int global = 0;

int prop = 0;

int getProp ()
{
  return prop;
}

void setProp (int i)
{
  prop = i;
}

void func ()
{
}

struct A
{
  static int staticVar;

  static int staticProp;

  static int getStaticProp ()
  {
    return staticProp;
  }

  static void setStaticProp (int v)
  {
    staticProp = v;
  }
 
  static void staticFunc ()
  {
  }

  int var;

  int prop;

  virtual ~A ()
  {
  }

  int getProp () const
  {
    return prop;
  }

  void setProp (int v)
  {
    prop = v;
  }

  void func ()
  {
  }

  void constFunc () const
  {
  }
};

int A::staticVar = 0;
int A::staticProp = 0;

struct B : public A
{
  static float staticVar;

  static float staticProp;

  static float getStaticProp ()
  {
    return staticProp;
  }

  static void setStaticProp (float v)
  {
    staticProp = v;
  }
 
  static void staticFunc ()
  {
  }

  float var;

  float prop;

  ~B ()
  {
  }

  float getProp () const
  {
    return prop;
  }

  void setProp (float v)
  {
    prop = v;
  }

  void func ()
  {
  }

  void constFunc () const
  {
  }
};

float B::staticVar = 0;
float B::staticProp = 0;

A a;
B b;

}

using namespace test3;

void addUnitTests3 (lua_State* L)
{
  luabridge::getGlobalNamespace (L)
    .beginNamespace ("test")
      .beginNamespace ("foo")
      .endNamespace ()
      .beginClass <A> ("A")
        .addStaticData ("staticVar", &A::staticVar)
        .addStaticData ("staticVarRo", &A::staticVar, false)
        .addStaticProperty ("staticProp", &A::getStaticProp, &A::setStaticProp)
        .addStaticProperty ("staticPropRo", &A::getStaticProp)
        .addStaticMethod ("staticFunc", &A::staticFunc)
        .addData ("var", &A::var)
        .addData ("varRo", &A::var, false)
        .addProperty ("prop", &A::getProp, &A::setProp)
        .addProperty ("propRo", &A::getProp)
        .addMethod ("func", &A::func)
        .addMethod ("constFunc", &A::constFunc)
      .endClass ()
      .beginClass <B> ("B")
        .addStaticData ("staticVar", &B::staticVar)
        .addStaticData ("staticVarRo", &B::staticVar, false)
        .addStaticProperty ("staticProp", &B::getStaticProp, &B::setStaticProp)
        .addStaticProperty ("staticPropRo", &B::getStaticProp)
        .addStaticMethod ("staticFunc", &B::staticFunc)
        .addData ("var", &B::var)
        .addData ("varRo", &B::var, false)
        .addProperty ("prop", &B::getProp, &B::setProp)
        .addProperty ("propRo", &B::getProp)
        .addMethod ("func", &B::func)
        .addMethod ("constFunc", &B::constFunc)
      .endClass ()
      .addVariable ("global", &global)
      .addVariable ("globalRo", &global, false)
      .addProperty ("prop", &getProp, &setProp)
      .addProperty ("propRo", &getProp)
      .addFunction ("func", &func)
    .endNamespace ()
    ;

  //luabridge::Stack <A const>::push (L, A());
  luabridge::Stack <A>::push (L, a);
  lua_setglobal (L, "a");
  luabridge::Stack <B>::push (L, b);
  lua_setglobal (L, "b");
}
