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
    auto * thing3 = (AnObject*) thing->clone();
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
    delete thing3;
#if DEBUG_THIS || D_ObjectCountInitAndDeinitTest
    cout << "--Objects: " << Object::Count() << endl;
#endif

    std::cout <<   "\n********   END TEST: Objec Count & Deinint ********\n" << std::endl;

}




class Thing {
public:
    std::string name = "Hello, I'm Barry!";
};



void RMXObjectCloneTest(){
    std::cout << "\n\n******** BEGIN TEST: Object Cloning ********\n" << std::endl;
    auto * o = new Object();

#if DEBUG_THIS
    Object * o2 = o;
#endif
    Object * clone = o->clone();
    Object * clone2 = Object::Instantiate(clone);


    o->setName("o1");
    o->setDescription("I am the first object");

    clone->setName("Clone1");
    clone->setDescription("I am a clone of the first object");

    clone2->setName("clone2");
    clone2->setDescription("AND IM A CLONE OF A CLONE!");

    Thing barry = Thing();
    Thing * baz = Object::Instantiate(&barry);
    baz->name = "And I'm his bloody clone!";
#if DEBUG_THIS
    cout << "\nto_string:       " << o->toString() << endl;
    cout << "\npointer o:       " << o << endl;
    cout << "\npointer2 o2:     " << o2 << endl;
    cout << "\nclone pointer:   " << clone << endl;
    cout << "\nclone2 pointer:  " << clone2 << endl;



    cout << "\ninstance *o:     " << *o << endl;
    cout << "\ninstance2 *o2:   " << *o2 << endl;
    cout << "\nclone instance:  " << *clone << endl;
    cout << "\nclone2 instance: " << *clone2 << endl;

    cout << "\n         Barry:  " << barry.name << endl;
    cout << "\n           Baz:  " << baz->name << endl;
#endif
    //    cout << o->clone() << endl;

    //    OpenGLView::Run(argc, argv);

    //    NotificationCenter::Test();
    std::cout <<   "\n********   END TEST: Object Cloning ********\n" << std::endl;
}




int main()
{

    RMXObjectCountInitAndDeinitTest();

    RMXObjectCloneTest();

    RMXPrintableTest();

    return 0;
}