//
// Created by max on 10/10/17.
//
//#define DEBUG_RMX_OBJECT
//#define DEBUG_MALLOC


#include "Object.h"
#define DEBUG_THIS true

using namespace rmx;
using namespace std;

class PrintableTest : public Printable
{
    string mDesc;
public:

    explicit PrintableTest(const string& aDesc)
    {
        mDesc = aDesc;
    }

    string toString() override
    {
        return mDesc;
    }
};
void RMXPrintableTest() {
    std::cout <<   "\n******** BEGIN TEST: PRINTABLE ********\n" << std::endl;
    auto * theObject = new PrintableTest("Hello, world");
#if DEBUG_THIS || DEBUG_RMX_PRINTABLE
    cout << theObject << endl;
    cout << *theObject << endl;
#endif
    std::cout <<   "\n********   END TEST: PRINTABLE ********\n" << std::endl;
}

class AnObject : public Object {

};


void RMXObjectCountInitAndDeinitTest() {
    std::cout << "\n\n******** BEGIN TEST: Objec Count & Deinint ********\n" << std::endl;
#if DEBUG_THIS || D_ObjectCountInitAndDeinitTest
    //    cout << "List Count: " << Object::AllObjects()->count() << ", Object count: " << Object::Count() << endl;
#endif
//    Object::AllObjects()->deleteAll();
#if DEBUG_THIS || D_ObjectCountInitAndDeinitTest
    //    cout << "List Count: " << Object::AllObjects()->count() << ", Object count: " << Object::Count() << endl;
#endif


    auto * thing = new AnObject();
#if DEBUG_THIS || D_ObjectCountInitAndDeinitTest
    cout << "++Objects: " << Object::Count() << endl;
#endif
    auto * thing2 = new AnObject();
#if DEBUG_THIS || D_ObjectCountInitAndDeinitTest
    cout << "++Objects: " << Object::Count() << endl;
#endif

    delete thing;
#if DEBUG_THIS || D_ObjectCountInitAndDeinitTest
    cout << "--Objects: " << Object::Count() << endl;
#endif
    delete thing2;
#if DEBUG_THIS || D_ObjectCountInitAndDeinitTest
    cout << "--Objects: " << Object::Count() << endl;
#endif

    std::cout <<   "\n********   END TEST: Objec Count & Deinint ********\n" << std::endl;

}




class Thing {
public:
    std::string name = "Hello, I'm Barry!";
};



int main()
{

    RMXObjectCountInitAndDeinitTest();

    RMXPrintableTest();

    return 0;
}