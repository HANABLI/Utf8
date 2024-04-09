/**
 * @file Utf8.cpp
 * 
 * This module containe the implementation of the Utf8::Utf8 class.
 * 
 * © 2024 by Hatem Nabli
*/

#include <Utf8\Utf8.hpp>
namespace {

    /**
     * This is the Unicode replacement character encoded as Utf8.
    */
    const std::vector< Utf8::UnicodeCodePoint > UTF8_ENCODED_REPLACEMENT_CHAR = {
        0xEF, 0xBF, 0xBD 
    };

    /**
     * This is the very last code point in Unicode tha is legal.
    */
    const Utf8::UnicodeCodePoint LAST_LEGAL_UNICODE_CODE_POINT = 0x10FFFF;
    /**
     * the hight and low surrogate halves used by UTF-16
     * (U+D800 through U+DFFF) and code points not encodable
     * by UTF-16 (those after U+10FFFF) are not legal Unicode values, and
     * their UTF-8 encoding must be treated as an invalid byte sequence.
    */
    const Utf8::UnicodeCodePoint FIRST_SURROGATE = 0xD800;
    const Utf8::UnicodeCodePoint LAST_SURROGATE = 0xDFFF;

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
                if (
                    (codePoint >= FIRST_SURROGATE)
                    && (codePoint <= LAST_SURROGATE)
                ) {
                    encoding.insert(
                        encoding.end(),
                        UTF8_ENCODED_REPLACEMENT_CHAR.begin(),
                        UTF8_ENCODED_REPLACEMENT_CHAR.end()
                    );
                } else {
                    encoding.push_back((UnicodeCodePoint)(((codePoint >> 12) & 0x0F) + 0xE0));
                    encoding.push_back((UnicodeCodePoint)(((codePoint >> 6) & 0x3F) + 0x80));
                    encoding.push_back((UnicodeCodePoint)((codePoint & 0x3F) + 0x80));
                }
            } else if ((numBits <= 21) && (codePoint <= LAST_LEGAL_UNICODE_CODE_POINT)) {
                encoding.push_back((UnicodeCodePoint)(((codePoint >> 18) & 0x07) + 0xF0));
                encoding.push_back((UnicodeCodePoint)(((codePoint >> 12) & 0x3F) + 0x80));
                encoding.push_back((UnicodeCodePoint)(((codePoint >> 6) & 0x3F) + 0x80));
                encoding.push_back((UnicodeCodePoint)((codePoint & 0x3F) + 0x80));
            } else {
                encoding.insert(
                    encoding.end(),
                    UTF8_ENCODED_REPLACEMENT_CHAR.begin(),
                    UTF8_ENCODED_REPLACEMENT_CHAR.end()
                );
            }
            
        }
        return encoding;
    }
}