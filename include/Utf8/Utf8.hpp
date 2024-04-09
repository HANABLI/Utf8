#ifndef UTF8_HPP
#define UTF8_HPP
/**
 * @file Utf8.hpp
 * 
 * This module contains the declaration of the Utf8::Utf8 class.
 * 
 * © 2024 by Hatem Nabli
*/
#include <memory>


namespace Utf8 {

    class Utf8
    {
    public:

        ~Utf8();
        Utf8(const Utf8&) = delete; // Copy Constructor that creates a new object by making a copy of an existing object. 
        //It ensures that a deep copy is performed if the object contains dynamically allocated resources 
        Utf8(Utf8&&); // Move Constructor that transfers resources from an expiring object to a newly constructed object.
        Utf8& operator=(const Utf8&) = delete; //Copy Assignment Operation That assigns the values of one object to another object using the assignment operator (=)
        Utf8& operator=(Utf8&&); //Move Assignment Operator: Amove assignment operator efficiently transfers resources from one object to another.
    
    public:
        /**
        * This is the default constructor
        */
       Utf8();
        //public methods
    private:
        /* data */

        /**
         * This is the type of structure that contains the private
         * properties of the instance. It is defined in the implementation
         * and declared here to ensure that iwt is scoped inside the class.
        */
       struct Impl;

       /**
        * This contains the private properties of the instance.
        */       
       std::unique_ptr<struct Impl> impl_;

    };
    
}



#endif /*UTF8_HPP*/