/**
 * @file Utf8.cpp
 * 
 * This module containe the implementation of the Utf8::Utf8 class.
 * 
 * © 2024 by Hatem Nabli
*/

#include <Utf8\Utf8.hpp>

namespace Utf8 {

    std::vector< UnicodeCodePoint > AsciiToUnicode(const std::string& ascii) {
        return std::vector< UnicodeCodePoint >(
            ascii.begin(), 
            ascii.end()
        );
    }

    struct Utf8::Impl
    {

    };

    Utf8::~Utf8() = default;
    Utf8::Utf8(Utf8&&) = default;
    Utf8& Utf8::operator=(Utf8&&) = default;

    Utf8::Utf8():impl_(new Impl){

    }
}