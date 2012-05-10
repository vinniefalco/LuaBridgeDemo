/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file, created by The Introjucer 3.0.0
   Do not edit anything in this file!

*/

namespace BinaryData
{

//================== LuaBridgeTests.lua ==================
static const unsigned char temp_56cb05ff[] =
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
"\tfor k, v in pairs(t) do\r\n"
"\t\tif (type(v) == \"table\") then\r\n"
"\t\t\tprint(k .. \" =>\", \"(table)\");\r\n"
"\t\telseif (type(v) == \"function\") then\r\n"
"\t\t\tprint(k .. \" =>\", \"(function)\");\r\n"
"\t\telseif (type(v) == \"userdata\") then\r\n"
"\t\t\tprint(k .. \" =>\", \"(userdata)\");\r\n"
"\t\telse\r\n"
"\t\t\tprint(k .. \" =>\", v);\r\n"
"\t\tend\r\n"
"\tend\r\n"
"end\r\n"
"\r\n"
"function assert (expr)\r\n"
"\tif (not expr) then error(\"assert failed\", 2) end\r\n"
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
"testParamInt(47);\t\t\t\t\t\tassert(testSucceeded());\r\n"
"testParamBool(true);\t\t\t\t\tassert(testSucceeded());\r\n"
"testParamFloat(47.0);\t\t\t\t\tassert(testSucceeded());\r\n"
"testParamConstCharPtr(\"Hello, world\");\tassert(testSucceeded());\r\n"
"testParamStdString(\"Hello, world\");\t\tassert(testSucceeded());\r\n"
"testParamStdStringRef(\"Hello, world\");\tassert(testSucceeded());\r\n"
"\r\n"
"-- test static methods of classes registered from C++\r\n"
"\r\n"
"A.testStatic();\t\t\t\t\t\t\tassert(testAFnCalled(FN_STATIC));\r\n"
"B.testStatic();\t\t\t\t\t\t\tassert(testAFnCalled(FN_STATIC));\r\n"
"B.testStatic2();\t\t\t\t\t\tassert(testBFnCalled(FN_STATIC));\r\n"
"\r\n"
"-- test static properties of classes registered from C++\r\n"
"\r\n"
"assert(A.testStaticProp == 47);\r\n"
"assert(A.testStaticProp2 == 47);\t\tassert(testAFnCalled(FN_STATIC_PROPGET));\r\n"
"A.testStaticProp = 48;\t\t\t\t\tassert(A.testStaticProp == 48);\r\n"
"A.testStaticProp2 = 49;\t\t\t\t\tassert(testAFnCalled(FN_STATIC_PROPSET) and A.testStaticProp2 == 49);\r\n"
"\r\n"
"-- test classes registered from C++\r\n"
"\r\n"
"object1 = A(\"object1\");\t\t\t\t\tassert(testAFnCalled(FN_CTOR));\r\n"
"object1:testVirtual();\t\t\t\t\tassert(testAFnCalled(FN_VIRTUAL));\r\n"
"\r\n"
"object2 = B(\"object2\");\t\t\t\t\tassert(testAFnCalled(FN_CTOR) and testBFnCalled(FN_CTOR));\r\n"
"object2:testVirtual();\t\t\t\t\tassert(testBFnCalled(FN_VIRTUAL) and not testAFnCalled(FN_VIRTUAL));\r\n"
"\r\n"
"-- test functions taking and returning objects\r\n"
"\r\n"
"testParamAPtr(object1);\t\t\t\t\tassert(object1:testSucceeded());\r\n"
"testParamAPtrConst(object1);\t\t\tassert(object1:testSucceeded());\r\n"
"testParamConstAPtr(object1);\t\t\tassert(object1:testSucceeded());\r\n"
"testParamSharedPtrA(object1);\t\t\tassert(object1:testSucceeded());\r\n"
"\r\n"
"testParamAPtr(object2);\t\t\t\t\tassert(object2:testSucceeded());\r\n"
"testParamAPtrConst(object2);\t\t\tassert(object2:testSucceeded());\r\n"
"testParamConstAPtr(object2);\t\t\tassert(object2:testSucceeded());\r\n"
"testParamSharedPtrA(object2);\t\t\tassert(object2:testSucceeded());\r\n"
"\r\n"
"result = testRetSharedPtrA();\t\t\tassert(result:getName() == \"from C\");\r\n"
"\r\n"
"-- test constness\r\n"
"\r\n"
"constA = testRetSharedPtrConstA();\t\tassert(constA:getName() == \"const A\");\r\n"
"assert(constA.testVirtual == nil);\r\n"
"testParamConstAPtr(constA);\t\t\t\tassert(constA:testSucceeded());\r\n"
"assert(pcall(testParamAPtr, constA) == false, \"attempt to call nil value\");\r\n"
"\r\n"
"-- test properties\r\n"
"\r\n"
"assert(object1.testProp == 47);\r\n"
"assert(object1.testProp2 == 47);\t\tassert(testAFnCalled(FN_PROPGET));\r\n"
"assert(object2.testProp == 47);\r\n"
"assert(object2.testProp2 == 47);\t\tassert(testAFnCalled(FN_PROPGET));\r\n"
"\r\n"
"object1.testProp = 48;\t\t\t\t\tassert(object1.testProp == 48);\r\n"
"object1.testProp2 = 49;\t\t\t\t\tassert(testAFnCalled(FN_PROPSET) and object1.testProp2 == 49);\r\n"
"\r\n"
"-- test operator overload\r\n"
"object1a = object1 + object1;\t\t\tassert(testAFnCalled(FN_OPERATOR));\r\n"
"assert(object1a:getName() == \"object1 + object1\");\r\n"
"\r\n"
"print(\"All tests succeeded.\");\r\n";

const char* LuaBridgeTests_lua = (const char*) temp_56cb05ff;


const char* getNamedResource (const char*, int&) throw();
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + *resourceNameUTF8++;

    switch (hash)
    {
        case 0xc0d6f059:
        case 0x1798b562:  numBytes = 3712; return LuaBridgeTests_lua;
        default: break;
    }

    numBytes = 0;
    return 0;
}

}
