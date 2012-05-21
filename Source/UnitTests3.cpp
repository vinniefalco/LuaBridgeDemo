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

#include "LuaBridge/LuaBridge2.h"
#include "LuaBridge/shared_ptr.h"

#include "UnitTests2.h"

#include "JUCEAmalgam/include/juce_core_amalgam.h"
 
using namespace juce;
using namespace luabridge2;

namespace test
{

template <class T>
struct G
{
  static T global;

  static T prop;

  static int getProp ()
  {
    return prop;
  }

  static void setProp (T v)
  {
    prop = v;
  }

  static void func1 ()
  {
  }

  static T func2 (T const*)
  {
    return T ();
  }

  static void func3 (T)
  {
  }
};

template <class T>
T G <T>::global;

template <class T>
T G <T>::prop;

template <class T>
struct A
{
  static T staticData;

  static T staticProperty;

  static T getStaticProperty ()
  {
    return staticProperty;
  }

  static void setStaticProperty (T v)
  {
    staticProperty = v;
  }

  static void staticMethod ()
  {
  }

  T dataMember;

  T propertyMember;

  A ()
  {
  }

  ~A ()
  {
    staticData = 0;
  }

  T getProperty () const
  {
    return propertyMember;
  }

  void setProperty (T t)
  {
    propertyMember = t;
  }

  void method ()
  {
  }

  void constMethod (int) const
  {
  }
};

template <class T>
T A <T>::staticData = 0;

template <class T>
T A <T>::staticProperty = 0;

struct B
{
  static int staticData;

  static int staticProperty;

  static int getStaticProperty ()
  {
    return staticProperty;
  }

  static void setStaticProperty (int v)
  {
    staticProperty = v;
  }

  static void staticMethod ()
  {
  }

  int dataMember;

  int propertyMember;

  int getProperty () const
  {
    return propertyMember;
  }

  void setProperty (int t)
  {
    propertyMember = t;
  }

  void method ()
  {
  }

  void constMethod (int) const
  {
  }
};

int B::staticData = 0;

int B::staticProperty = 0;

struct C
{
  static float staticData;

  static float staticProperty;

  static float getStaticProperty ()
  {
    return staticProperty;
  }

  static void setStaticProperty (float v)
  {
    staticProperty = v;
  }

  static void staticMethod ()
  {
  }

  float dataMember;

  float propertyMember;

  float getProperty () const
  {
    return propertyMember;
  }

  void setProperty (float t)
  {
    propertyMember = t;
  }

  void method ()
  {
  }

  void constMethod (float) const
  {
  }
};

float C::staticData = 0;

float C::staticProperty = 0;

class D
{
public:
  int m_d;

  virtual void foo ()
  {
    m_d = 1;
  }
};

class E : public D
{
public:
  int m_e;

  void foo ()
  {
    m_d = 2;
  }
};

}

template <class T>
void addGlobals (luabridge2::Namespace& n)
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

template <class T>
void addTemplateClass (luabridge2::Namespace& n, char const* name)
{
  n .beginClass <T> (name)
      .addStaticData ("staticData", &T::staticData)
      .addStaticData ("staticDataRo", &T::staticData, false)
      .addStaticProperty ("staticProperty", &T::getStaticProperty, &T::setStaticProperty)
      .addStaticProperty ("staticPropertyRo", &T::getStaticProperty)
      .addStaticMethod ("staticMethod", &T::staticMethod)
      .addData ("dataMember", &T::dataMember)
      .addData ("dataMemberRo", &T::dataMember, false)
      .addProperty ("property", &T::getProperty, &T::setProperty)
      .addProperty ("propertyRo", &T::getProperty)
      .addMethod ("method", &T::method)
      .addMethod ("constMethod", &T::constMethod)
    .endClass ()
    ;
}

void addUnitTests3 (lua_State* L)
{
  addGlobals <test::G <int> > (
    getGlobalNamespace()
      .beginNamespace ("test"));

  addTemplateClass <test::A <int> > (
    getGlobalNamespace()
      .beginNamespace ("test"),
      "A");

  addTemplateClass <test::B> (
    getGlobalNamespace()
      .beginNamespace ("test"),
      "B");

  addTemplateClass <test::C> (
    getGlobalNamespace()
      .beginNamespace ("test"),
      "C");

  addTemplateClass <test::A <float> > (
    getGlobalNamespace()
      .beginNamespace ("test")
        .beginNamespace ("detail"),
      "A2");

  getGlobalNamespace()
    .beginNamespace ("test")
      .beginClass <test::D> ("D")
        .addData ("d", &test::D::m_d)
        .addMethod ("foo", &test::D::foo)
      .endClass ()
      .deriveClass <test::E, test::D> ("E")
        .addData ("e", &test::E::m_e)
      .endClass ()
    .endNamespace ()
    ;

  getGlobalNamespace ().addToState (L);

  luabridge2::Stack <test::B>::push (L, test::B ());
  lua_setglobal (L, "b");

  //luabridge2::Stack <test::C const>::push (L, test::C ());
  //lua_setglobal (L, "c");
}
