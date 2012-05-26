/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file, created by The Introjucer 3.0.0
   Do not edit anything in this file!

*/

namespace BinaryData
{

//================== README.md ==================
static const unsigned char temp_35b328e9[] =
"# LuaBridgeDemo\n"
"\n"
"The LuaBridgeDemo is a stand-alone graphical program for compiling and running\n"
"the test suite with an included interactive window where you can enter execute\n"
"Lua statements in a persistent environment. The demo has these features:\n"
"\n"
"- Cross platform: Compiles on Mac OS, Windows, iOS, Android, and GNU/Linux\n"
"\n"
"- No external dependencies: Comes with Lua, LuaBridge, and [JUCE][5], just build and run!\n"
"\n"
"- Demonstrates the usage of LuaBridge with functional code.\n"
"\n"
"Also included is a separate project for building a command line version of\n"
"the test suite, suitable as a starting point for building an automated\n"
"testing suite.\n"
"\n"
"[LuaBridge][3] is a lightweight, dependency-free library for making C++ data,\n"
"functions, and classes available to Lua. It works with Lua revisions starting\n"
"from 5.1.2. [Lua][4] is a powerful, fast, lightweight, embeddable scripting\n"
"language.\n"
"\n"
"This is what the application looks like:\n"
"\n"
"<a href=\"https://github.com/vinniefalco/LuaBridgeDemo\">\n"
"<img src=\"http://vinniefalco.github.com/LuaBridgeDemo/LuaBridgeDemoScreenshot.png\">\n"
"</a><br>\n"
"\n"
"<a href=\"https://github.com/vinniefalco/LuaBridgeDemo/downloads\">\n"
"<img src=\"http://vinniefalco.github.com/images/ThreeOSDownloadNow.png\">\n"
"</a><br>\n"
"\n"
"## JUCE\n"
"\n"
"[JUCE][5] is licensed separately, visit http://rawmaterialsoftware.com for more\n"
"details.\n"
"\n"
"## License\n"
"\n"
"Copyright (C) 2012, [Vinnie Falco][1] ([e-mail][0]) <br>\n"
"Copyright (C) 2007, Nathan Reed <br>\n"
"  \n"
"Portions from The Loki Library: <br>\n"
"Copyright (C) 2001 by Andrei Alexandrescu\n"
"\n"
"License: The [MIT License][2]\n"
"\n"
"[0]: mailto:vinnie.falco@gmail.com \"Vinnie Falco (Email)\"\n"
"[1]: http://www.vinniefalco.com \"Vinnie Falco\"\n"
"[2]: http://www.opensource.org/licenses/mit-license.html \"The MIT License\"\n"
"[3]: https://github.com/vinniefalco/LuaBridge \"LuaBridge\"\n"
"[4]: http://lua.org \"The Lua Programming Language\"\n"
"[5]: http://www.rawmaterialsoftware.com \"The JUCE Library\"\n";

const char* README_md = (const char*) temp_35b328e9;

//================== Tests.lua ==================
static const unsigned char temp_13ae9e33[] =
"-- test lua script to be run with the luabridge test program\n"
"\n"
"print(\"Running LuaBridge tests:\");\n"
"\n"
"-- enum from C++\n"
"FN_CTOR = 0\n"
"FN_DTOR = 1\n"
"FN_STATIC = 2\n"
"FN_VIRTUAL = 3\n"
"FN_PROPGET = 4\n"
"FN_PROPSET = 5\n"
"FN_STATIC_PROPGET = 6\n"
"FN_STATIC_PROPSET = 7\n"
"FN_OPERATOR = 8\n"
"NUM_FN_TYPES = 9\n"
"\n"
"-- function to print contents of a table\n"
"function printtable (t)\n"
"  for k, v in pairs(t) do\n"
"    if (type(v) == \"table\") then\n"
"      print(k .. \" =>\", \"(table)\");\n"
"    elseif (type(v) == \"function\") then\n"
"      print(k .. \" =>\", \"(function)\");\n"
"    elseif (type(v) == \"userdata\") then\n"
"      print(k .. \" =>\", \"(userdata)\");\n"
"    else\n"
"      print(k .. \" =>\", v);\n"
"    end\n"
"  end\n"
"end\n"
"\n"
"function assert (expr)\n"
"  if (not expr) then error(\"assert failed\", 2) end\n"
"end\n"
"\n"
"-- test functions registered from C++\n"
"\n"
"assert(testSucceeded());\n"
"assert(testRetInt() == 47);\n"
"assert(testRetFloat() == 47.0);\n"
"assert(testRetConstCharPtr() == \"Hello, world\");\n"
"assert(testRetStdString() == \"Hello, world\");\n"
"\n"
"testParamInt(47);                       assert(testSucceeded());\n"
"testParamBool(true);                    assert(testSucceeded());\n"
"testParamFloat(47.0);                   assert(testSucceeded());\n"
"testParamConstCharPtr(\"Hello, world\");  assert(testSucceeded());\n"
"testParamStdString(\"Hello, world\");     assert(testSucceeded());\n"
"testParamStdStringRef(\"Hello, world\");  assert(testSucceeded());\n"
"\n"
"-- test static methods of classes registered from C++\n"
"\n"
"A.testStatic();             assert(testAFnCalled(FN_STATIC));\n"
"B.testStatic();             assert(testAFnCalled(FN_STATIC));\n"
"B.testStatic2();            assert(testBFnCalled(FN_STATIC));\n"
"\n"
"-- test static properties of classes registered from C++\n"
"\n"
"assert(A.testStaticProp == 47);\n"
"assert(A.testStaticProp2 == 47);assert(testAFnCalled(FN_STATIC_PROPGET));\n"
"A.testStaticProp = 48;          assert(A.testStaticProp == 48);\n"
"A.testStaticProp2 = 49;         assert(testAFnCalled(FN_STATIC_PROPSET) and A.testStaticProp2 == 49);\n"
"\n"
"-- test classes registered from C++\n"
"\n"
"object1 = A(\"object1\");          assert(testAFnCalled(FN_CTOR));\n"
"object1:testVirtual();           assert(testAFnCalled(FN_VIRTUAL));\n"
"\n"
"object2 = B(\"object2\");         assert(testAFnCalled(FN_CTOR) and testBFnCalled(FN_CTOR));\n"
"object2:testVirtual();          assert(testBFnCalled(FN_VIRTUAL) and not testAFnCalled(FN_VIRTUAL));\n"
"\n"
"-- test functions taking and returning objects\n"
"\n"
"testParamAPtr(object1);          assert(object1:testSucceeded());\n"
"testParamAPtrConst(object1);     assert(object1:testSucceeded());\n"
"testParamConstAPtr(object1);     assert(object1:testSucceeded());\n"
"testParamSharedPtrA(object1);    assert(object1:testSucceeded());\n"
"\n"
"testParamAPtr(object2);          assert(object2:testSucceeded());\n"
"testParamAPtrConst(object2);     assert(object2:testSucceeded());\n"
"testParamConstAPtr(object2);     assert(object2:testSucceeded());\n"
"testParamSharedPtrA(object2);    assert(object2:testSucceeded());\n"
"\n"
"result = testRetSharedPtrA();    assert(result:getName() == \"from C\");\n"
"\n"
"-- test constness\n"
"\n"
"constA = testRetSharedPtrConstA();    assert(constA:getName() == \"const A\");\n"
"assert(constA.testVirtual == nil);\n"
"testParamConstAPtr(constA);        assert(constA:testSucceeded());\n"
"assert(pcall(testParamAPtr, constA) == false, \"attempt to call nil value\");\n"
"\n"
"-- test properties\n"
"\n"
"assert(object1.testProp == 47);\n"
"assert(object1.testProp2 == 47);    assert(testAFnCalled(FN_PROPGET));\n"
"assert(object2.testProp == 47);\n"
"assert(object2.testProp2 == 47);    assert(testAFnCalled(FN_PROPGET));\n"
"\n"
"object1.testProp = 48;          assert(object1.testProp == 48);\n"
"object1.testProp2 = 49;          assert(testAFnCalled(FN_PROPSET) and object1.testProp2 == 49);\n"
"\n"
"-- test operator overload\n"
"object1a = object1 + object1;      assert(testAFnCalled(FN_OPERATOR));\n"
"assert(object1a:getName() == \"object1 + object1\");\n"
"\n"
"print(\"All tests succeeded.\");\n";

const char* Tests_lua = (const char*) temp_13ae9e33;


const char* getNamedResource (const char*, int&) throw();
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + *resourceNameUTF8++;

    switch (hash)
    {
        case 0x64791dc8:
        case 0xee58bcf8:  numBytes = 1889; return README_md;
        case 0x322b48ba:
        case 0x2a41f024:  numBytes = 3770; return Tests_lua;
        default: break;
    }

    numBytes = 0;
    return 0;
}

}
