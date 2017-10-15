//
//  Object.hpp
//  RMXKit
//
//  Created by Max Bilbow on 30/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <iostream>

namespace rmx {

    /*!
     *   @author Max Bilbow, 15-08-04 16:08:04
     *
     *   A simple interface that allows any object to be printed using std::cout << theObject or std::cout << *theObject.
     *   node the difference between theObject and *theObject; the former gives the pointer's location in memory and more detailed description.
     *   @code
     *   Printable * theObject = new Printable();
     *   theObject->setDescription("Hello, World!");
     *   cout << theObject << endl;
     *   cout << *theObject << endl;
     *   @endcode
     *
     *   rmx::ptr:  0x7fff5fbff798 >> N3rmx9PrintableE, info: Hello, World!
     *
     *   Hello, World!
     *
     *   @since 0.1
     */
    class Printable {
        
    protected:
    public:
        virtual std::string toString() = 0;
    };
}

/*!
 *  @author Max Bilbow, 15-08-04 17:08:53
 *  @param strm proceeding output
 *  @param a    the Printable object
 *  @return Prints the object's details, including location in memory, along with it's toString() method
 *  @since 0.1
 */
std::ostream& operator<<(std::ostream &strm,  rmx::Printable &a);

/*!
 *  @author Max Bilbow, 15-08-04 17:08:54
 *  @param strm proceeding output
 *  @param a    the Printable object pointer
 *  @return Prints the object's toString() method
 *  @since 0.1
 */
std::ostream& operator<<(std::ostream &strm,  rmx::Printable * a);

namespace rmx {

    /*!
     *  @author Max Bilbow, 15-08-04 17:08:49
     *
     *  Base object for all standart event listening and notification tools.
     *  @since 0.1
     */
    class Object : public Printable  {
        
        /*!
         *  @author Max Bilbow, 15-08-06 17:08:35
         *
         *  The number of instances created; used to assign the the unique _id on initialization.
         *  @since 0.1
         */
        static unsigned int _count;


        
        /*!
         *  @author Max Bilbow, 15-08-06 17:08:13
         *
         *  The unique id of the instance as an unsigned int.
         *  @since 0.1
         */
        unsigned int _id = 0;

        std::string mDescription;
        
    protected:
       
        /*!
         *  @author Max Bilbow, 15-08-06 17:08:27
         *
         *  The given name of the instance.
         *  @since 0.1
         */
        std::string name;


    public:

        void setDescription(const std::string &aDescription)
        {
            mDescription = aDescription;
        }

        /*!
         *  @author Max Bilbow, 15-08-06 17:08:50
         *
         *  @return The total number of rmx::Objects that currently exist in the system.
         *  @since 0.1
         */
        static unsigned int Count();
        
        /*!
         *  @author Max Bilbow, 15-08-06 16:08:21
         *
         *  @return the uniqueID assigned at initialization
         *  @since 0.2
         */
//        int getID();
        unsigned int uniqueID();
        
        /*!
         *  @author Max Bilbow, 15-08-06 16:08:41
         *
         *  Initiates with default name "Unnamed Object"
         *  @since 0.1
         */
        explicit Object(const std::string & name = "Unnamed Object");
       
        /*!
         *  @author Max Bilbow, 15-08-06 17:08:14
         *
         *  Deconstructor: removes the object from the list of active objects.
         *  @since 0.1
         */
        ~Object();
        
        /*!
         *  @author Max Bilbow, 15-08-06 16:08:50
         *
         *  Returns the name with the uniqueID in brackets
         *  For name without id, use Name();
         *  @return the name with the uniqueID
         *  @since 0.1
         *  @see Name()
         */
        std::string uniqueName();
        
        /*!
         *  @author Max Bilbow, 15-08-06 16:08:14
         *
         *  @return the given name of the object
         *  @since 0.1
         *  @see uniqueName()
         */
        std::string Name();

        /*!
         *  @author Max Bilbow, 15-08-06 16:08:25
         *
         *  Can be overriden as required.
         *  @return the unique name and description
         *  @since 0.1
         *  @see Printable
         */
        std::string toString() override;
        
        /*!
         *  @author Max Bilbow, 15-08-06 16:08:12
         *
         *  Setter for the name
         *  @param name any string
         *  @since 0.1
         *  @see uniqueName()
         */
        void setName(std::string aName)
        {
            name = std::move(aName);
        }

       
        /*!
         *  @author Max Bilbow, 15-08-06 16:08:21
         *
         *  @return the classname of the object as a string
         *  @since 0.2
         */
        std::string ClassName();


    };
    
}


#endif /* Object_hpp */












