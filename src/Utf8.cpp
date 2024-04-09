/**
 * @file Utf8.cpp
 * 
 * This module containe the implementation of the Utf8::Utf8 class.
 * 
 * © 2024 by Hatem Nabli
*/

#include <Utf8\Utf8.hpp>
namespace {

    template< typename I > size_t log2n(I integer) {
        size_t n = 0;
        while (integer > 0) {
            ++n;
            integer >>= 1;
        }
        return n;
    }
}
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

    std::vector< uint8_t > Utf8::Encode(const std::vector< UnicodeCodePoint >& codePoints) {
        std::vector< uint8_t > encoding;
        for (auto codePoint: codePoints) {
            const auto numBits = log2n(codePoint);
            if (numBits <= 7) {
                encoding.push_back((UnicodeCodePoint)(codePoint & 0x7F));
            } else if (numBits <= 11) {
                encoding.push_back((UnicodeCodePoint)(((codePoint >> 6) & 0x1F) + 0xC0));
                encoding.push_back((UnicodeCodePoint)((codePoint & 0x3F) + 0x80));
            } else if (numBits <= 16) {
                encoding.push_back((UnicodeCodePoint)(((codePoint >> 12) & 0x0F) + 0xE0));
                encoding.push_back((UnicodeCodePoint)(((codePoint >> 6) & 0x3F) + 0x80));
                encoding.push_back((UnicodeCodePoint)((codePoint & 0x3F) + 0x80));
            } else if (numBits <= 21) {
                encoding.push_back((UnicodeCodePoint)(((codePoint >> 18) & 0x07) + 0xf0));
                encoding.push_back((UnicodeCodePoint)(((codePoint >> 12) & 0x3F) + 0x80));
                encoding.push_back((UnicodeCodePoint)(((codePoint >> 6) & 0x3F) + 0x80));
                encoding.push_back((UnicodeCodePoint)((codePoint & 0x3F) + 0x80));
            }
            
        }
        return encoding;
    }
}