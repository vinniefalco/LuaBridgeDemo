/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file, created by The Introjucer 3.0.0
   Do not edit anything in this file!

*/

namespace BinaryData
{

//================== README.md ==================
static const unsigned char temp_1bef008b[] =
"<a href=\"http://lua.org\">\r\n"
"<img src=\"http://vinniefalco.github.com/LuaBridgeDemo/powered-by-lua.png\">\r\n"
"</a><br>\r\n"
"\r\n"
"# LuaBridgeDemo 1.0\r\n"
"\r\n"
"[LuaBridge][3] is a lightweight, dependency-free library for making C++ data,\r\n"
"functions, and classes available to Lua. It works with Lua revisions starting\r\n"
"from 5.1.2. [Lua][4] is a powerful, fast, lightweight, embeddable scripting\r\n"
"language.\r\n"
"\r\n"
"The LuaBridgeDemo is a stand-alone graphical program for compiling and running\r\n"
"the LuaBridge  test suite with an included interactive window where you can enter\r\n"
"and execute Lua statements in a persistent environment. The demo has these\r\n"
"features:\r\n"
"\r\n"
"- Cross platform: Compiles on Mac OS, Windows, iOS, Android, and GNU/Linux\r\n"
"\r\n"
"- No external dependencies: Comes with Lua, LuaBridge, and [JUCE][5], just build and run!\r\n"
"\r\n"
"- Demonstrates the usage of LuaBridge with functional code.\r\n"
"\r\n"
"Also included is a separate project for building a command line version of\r\n"
"the test suite, suitable as a starting point for building an automated\r\n"
"testing suite.\r\n"
"\r\n"
"This is the LuaBridge Demo application, and the corresponding registration code\r\n"
"to export classes `A` and `B` to Lua.\r\n"
"\r\n"
"<a href=\"https://github.com/vinniefalco/LuaBridgeDemo\">\r\n"
"<img src=\"http://vinniefalco.github.com/LuaBridgeDemo/LuaBridgeDemoScreenshot.png\">\r\n"
"</a><br>\r\n"
"\r\n"
"<a href=\"https://github.com/vinniefalco/LuaBridgeDemo/downloads\">\r\n"
"<img src=\"http://vinniefalco.github.com/images/ThreeOSDownloadNow.png\">\r\n"
"</a><br>\r\n"
"\r\n"
"### Version\r\n"
"\r\n"
"LuaBridgeDemo repository tracks the LuaBridge branches:\r\n"
"\r\n"
"- **[master][6]**: Tagged, stable release versions.\r\n"
"\r\n"
"- **[develop][7]**: Work in progress.\r\n"
"\r\n"
"## JUCE\r\n"
"\r\n"
"[JUCE][5] is licensed separately, visit http://rawmaterialsoftware.com for more\r\n"
"details.\r\n"
"\r\n"
"## License\r\n"
"\r\n"
"Copyright (C) 2012, [Vinnie Falco][1] ([e-mail][0]) <br>\r\n"
"Copyright (C) 2007, Nathan Reed <br>\r\n"
"  \r\n"
"Portions from The Loki Library: <br>\r\n"
"Copyright (C) 2001 by Andrei Alexandrescu\r\n"
"\r\n"
"License: The [MIT License][2]\r\n"
"\r\n"
"[0]: mailto:vinnie.falco@gmail.com \"Vinnie Falco (Email)\"\r\n"
"[1]: http://www.vinniefalco.com \"Vinnie Falco\"\r\n"
"[2]: http://www.opensource.org/licenses/mit-license.html \"The MIT License\"\r\n"
"[3]: https://github.com/vinniefalco/LuaBridge \"LuaBridge\"\r\n"
"[4]: http://lua.org \"The Lua Programming Language\"\r\n"
"[5]: http://www.rawmaterialsoftware.com \"The JUCE Library\"\r\n"
"[6]: https://github.com/vinniefalco/LuaBridgeDemo \"LuaBridgeDemo master branch\"\r\n"
"[7]: https://github.com/vinniefalco/LuaBridgeDemo/tree/develop \"LuaBridgeDemo develop branch\"\r\n";

const char* README_md = (const char*) temp_1bef008b;

//================== Tests.lua ==================
static const unsigned char temp_b6c6a671[] =
"-- test lua script to be run with the luabridge test program\r\n"
"\r\n"
"print(\"Running LuaBridge tests:\");\r\n"
"\r\n"
"-- enum from C++\r\n"
"FN_CTOR = 0\r\n"
"FN_DTOR = 1\r\n"
"FN_STATIC = 2\r\n"
"FN_VIRTUAL = 3\r\n"
"FN_PROPGET = 4\r\n"
"FN_PROPSET = 5\r\n"
"FN_STATIC_PROPGET = 6\r\n"
"FN_STATIC_PROPSET = 7\r\n"
"FN_OPERATOR = 8\r\n"
"NUM_FN_TYPES = 9\r\n"
"\r\n"
"-- function to print contents of a table\r\n"
"function printtable (t)\r\n"
"  for k, v in pairs(t) do\r\n"
"    if (type(v) == \"table\") then\r\n"
"      print(k .. \" =>\", \"(table)\");\r\n"
"    elseif (type(v) == \"function\") then\r\n"
"      print(k .. \" =>\", \"(function)\");\r\n"
"    elseif (type(v) == \"userdata\") then\r\n"
"      print(k .. \" =>\", \"(userdata)\");\r\n"
"    else\r\n"
"      print(k .. \" =>\", v);\r\n"
"    end\r\n"
"  end\r\n"
"end\r\n"
"\r\n"
"function assert (expr)\r\n"
"  if (not expr) then error(\"assert failed\", 2) end\r\n"
"end\r\n"
"\r\n"
"-- test functions registered from C++\r\n"
"\r\n"
"assert(testSucceeded());\r\n"
"assert(testRetInt() == 47);\r\n"
"assert(testRetFloat() == 47.0);\r\n"
"assert(testRetConstCharPtr() == \"Hello, world\");\r\n"
"assert(testRetStdString() == \"Hello, world\");\r\n"
"\r\n"
"testParamInt(47);                       assert(testSucceeded());\r\n"
"testParamBool(true);                    assert(testSucceeded());\r\n"
"testParamFloat(47.0);                   assert(testSucceeded());\r\n"
"testParamConstCharPtr(\"Hello, world\");  assert(testSucceeded());\r\n"
"testParamStdString(\"Hello, world\");     assert(testSucceeded());\r\n"
"testParamStdStringRef(\"Hello, world\");  assert(testSucceeded());\r\n"
"\r\n"
"-- test static methods of classes registered from C++\r\n"
"\r\n"
"A.testStatic();             assert(testAFnCalled(FN_STATIC));\r\n"
"B.testStatic();             assert(testAFnCalled(FN_STATIC));\r\n"
"B.testStatic2();            assert(testBFnCalled(FN_STATIC));\r\n"
"\r\n"
"-- test static properties of classes registered from C++\r\n"
"\r\n"
"assert(A.testStaticProp == 47);\r\n"
"assert(A.testStaticProp2 == 47);assert(testAFnCalled(FN_STATIC_PROPGET));\r\n"
"A.testStaticProp = 48;          assert(A.testStaticProp == 48);\r\n"
"A.testStaticProp2 = 49;         assert(testAFnCalled(FN_STATIC_PROPSET) and A.testStaticProp2 == 49);\r\n"
"\r\n"
"-- test classes registered from C++\r\n"
"\r\n"
"object1 = A(\"object1\");          assert(testAFnCalled(FN_CTOR));\r\n"
"object1:testVirtual();           assert(testAFnCalled(FN_VIRTUAL));\r\n"
"\r\n"
"object2 = B(\"object2\");         assert(testAFnCalled(FN_CTOR) and testBFnCalled(FN_CTOR));\r\n"
"object2:testVirtual();          assert(testBFnCalled(FN_VIRTUAL) and not testAFnCalled(FN_VIRTUAL));\r\n"
"\r\n"
"-- test functions taking and returning objects\r\n"
"\r\n"
"testParamAPtr(object1);          assert(object1:testSucceeded());\r\n"
"testParamAPtrConst(object1);     assert(object1:testSucceeded());\r\n"
"testParamConstAPtr(object1);     assert(object1:testSucceeded());\r\n"
"testParamSharedPtrA(object1);    assert(object1:testSucceeded());\r\n"
"\r\n"
"testParamAPtr(object2);          assert(object2:testSucceeded());\r\n"
"testParamAPtrConst(object2);     assert(object2:testSucceeded());\r\n"
"testParamConstAPtr(object2);     assert(object2:testSucceeded());\r\n"
"testParamSharedPtrA(object2);    assert(object2:testSucceeded());\r\n"
"\r\n"
"result = testRetSharedPtrA();    assert(result:getName() == \"from C\");\r\n"
"\r\n"
"-- test constness\r\n"
"\r\n"
"constA = testRetSharedPtrConstA();    assert(constA:getName() == \"const A\");\r\n"
"assert(constA.testVirtual == nil);\r\n"
"testParamConstAPtr(constA);        assert(constA:testSucceeded());\r\n"
"assert(pcall(testParamAPtr, constA) == false, \"attempt to call nil value\");\r\n"
"\r\n"
"-- test properties\r\n"
"\r\n"
"assert(object1.testProp == 47);\r\n"
"assert(object1.testProp2 == 47);    assert(testAFnCalled(FN_PROPGET));\r\n"
"assert(object2.testProp == 47);\r\n"
"assert(object2.testProp2 == 47);    assert(testAFnCalled(FN_PROPGET));\r\n"
"\r\n"
"object1.testProp = 48;          assert(object1.testProp == 48);\r\n"
"object1.testProp2 = 49;          assert(testAFnCalled(FN_PROPSET) and object1.testProp2 == 49);\r\n"
"\r\n"
"-- test operator overload\r\n"
"object1a = object1 + object1;      assert(testAFnCalled(FN_OPERATOR));\r\n"
"assert(object1a:getName() == \"object1 + object1\");\r\n"
"\r\n"
"print(\"All tests succeeded.\");\r\n";

const char* Tests_lua = (const char*) temp_b6c6a671;


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
        case 0xee58bcf8:  numBytes = 2500; return README_md;
        case 0x322b48ba:
        case 0x2a41f024:  numBytes = 3877; return Tests_lua;
        default: break;
    }

    numBytes = 0;
    return 0;
}

}
