#ifndef UTF8_HPP
#define UTF8_HPP
/**
 * @file Utf8.hpp
 * 
 * This module contains the declaration of the Utf8::Utf8 class.
 * 
 * © 2024 by Hatem Nabli
*/
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <memory>
#include <vector>


namespace Utf8 {
    /**
     * This represents a single character in Unicode.
    */
    typedef uint32_t UnicodeCodePoint;

    /**
     * This function is for convenience, converting a given ASCII string
     * into its equivalent sequence of UniCode code points.
     * 
     * @param[in] ascii
     *      This is the ASCII string to convert.
     * 
     * @return
     *      The Unicode code points for the given ASCII string are returned.
    */
   std::vector< UnicodeCodePoint > AsciiToUnicode(const std::string& ascii);
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
        /**
         * This method encodes the given sequence of Unicode code points
         * into UTF-8.
         * 
         * @param[in] codePoints
         *      Thes are the unicode code points to encode.
         * @return 
         *      The UTF-8 encoding of the given Unicode code points is returned
        */
        std::vector< uint8_t > Encode(const std::vector< UnicodeCodePoint >& codePoints);
       /**
        * This method accept the given sequence of UTF-8 encoded bytes,
        * and returns any Unicode code points formed from them.
        * 
        * Any partial code sequence at the end is held onto and used first
        * when this method is called again later.
        * 
        * this method accept a secquence of bites 
        * 
        * @param[in] encoded
        *       This is the encoded sequence of UTF-8 bytes to decode.
        * @return
        *       return all Unicode code points genereated by the decoder.
       */
       std::vector< UnicodeCodePoint > Decode(const std::vector< UnicodeCodePoint >& encoded );
       /**
        * This method accept the given sequence of UTF-8 encoded bytes,
        * and returns any Unicode code points formed from them.
        * 
        * Any partial code sequence at the end is held onto and used first
        * when this method is called again later.
        * 
        * this method accept a C++ string
        * 
        * @param[in] encoded
        *       This is the encoded sequence of UTF-8 bytes to decode.
        * @return
        *       return all Unicode code points genereated by the decoder.
       */
       std::vector< UnicodeCodePoint > Decode(const std::string& encoded );
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