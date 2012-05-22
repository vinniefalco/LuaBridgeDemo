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

#include "LuaBridge/LuaBridge3.h"
#include "LuaBridge/shared_ptr.h"

#include "UnitTests2.h"

#include "JUCEAmalgam/include/juce_core_amalgam.h"
 
using namespace juce;
using namespace luabridge3;

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
};

}

using namespace test3;

#if 0
template <class T>
void addGlobals (luabridge3::Namespace& n)
{
  n .addVariable ("global", &T::global)
    .addVariable ("globalRo", &T::global, false)
    .addProperty ("globalProp", &T::getProp, &T::setProp)
    .addProperty ("globalPropRo", &T::getProp)
    .addFunction ("globalFunc1", &T::func1)
    .addFunction ("globalFunc2", &T::func2)
    .addFunction ("globalFunc3", &T::func3)
    ;
}
#endif

void addUnitTests3 (lua_State* L)
{
  luabridge3::getGlobalNamespace (L)
    .beginNamespace ("test")
      .beginNamespace ("foo")
      .endNamespace ()
      .beginClass <A> ("A")
      .endClass ()
      .addVariable ("global", &global)
      .addVariable ("globalRo", &global, false)
      .addProperty ("prop", &getProp, &setProp)
      .addProperty ("propRo", &getProp)
      .addFunction ("func", &func)
    .endNamespace ()
    ;

}
