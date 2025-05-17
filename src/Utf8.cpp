/**
 * @file Utf8.cpp
 *
 * This module containe the implementation of the Utf8::Utf8 class.
 *
 * © 2024 by Hatem Nabli
 */

#include <Utf8/Utf8.hpp>
namespace
{
    /**
     * This is the Unicode replacement character encoded as Utf8.
     */
    const std::vector<uint8_t> UTF8_ENCODED_REPLACEMENT_CHAR = {0xEF, 0xBF, 0xBD};

    /**
     * This is the Unicode replacement character as a code pont.
     */
    const Utf8::UnicodeCodePoint REPLACEMENT_CHARACTER = 0xFFFD;

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

    template <typename I>
    size_t log2n(I integer) {
        size_t n = 0;
        while (integer > 0)
        {
            ++n;
            integer >>= 1;
        }
        return n;
    }
}  // namespace
namespace Utf8
{
    std::vector<UnicodeCodePoint> AsciiToUnicode(const std::string& ascii) {
        return std::vector<UnicodeCodePoint>(ascii.begin(), ascii.end());
    }

    struct Utf8::Impl
    {
        /**
         * This is where we keep the current character
         * that is being decoded.
         */
        UnicodeCodePoint currentCharacterBeingDecoded = 0;
        /**
         * This is the number of input bytes that we still
         * need to read in before wa can fully assemble
         * the current character that is being decoded.
         */
        size_t numBytesRemainingToDecode = 0;
        /**
         * This is the number of input bytes total that made up the
         * current being decoded
         */
        size_t bytesTotalToDecodeCurrentCharacter = 0;
        /**
         * This flag indicates whether or not the encoded UTF-8
         * sequence decoded so far is valid.
         */
        bool isValidEncoding = true;
    };

    Utf8::~Utf8() = default;
    Utf8::Utf8(Utf8&&) = default;
    Utf8& Utf8::operator=(Utf8&&) = default;

    Utf8::Utf8() : impl_(new Impl) {}

    std::vector<uint8_t> Utf8::Encode(const std::vector<UnicodeCodePoint>& codePoints) {
        std::vector<uint8_t> encoding;
        for (auto codePoint : codePoints)
        {
            const auto numBits = log2n(codePoint);
            if (numBits <= 7)
            {
                encoding.push_back((UnicodeCodePoint)(codePoint & 0x7F));
            } else if (numBits <= 11)
            {
                encoding.push_back((UnicodeCodePoint)(((codePoint >> 6) & 0x1F) + 0xC0));
                encoding.push_back((UnicodeCodePoint)((codePoint & 0x3F) + 0x80));
            } else if (numBits <= 16)
            {
                if ((codePoint >= FIRST_SURROGATE) && (codePoint <= LAST_SURROGATE))
                {
                    encoding.insert(encoding.end(), UTF8_ENCODED_REPLACEMENT_CHAR.begin(),
                                    UTF8_ENCODED_REPLACEMENT_CHAR.end());
                } else
                {
                    encoding.push_back((UnicodeCodePoint)(((codePoint >> 12) & 0x0F) + 0xE0));
                    encoding.push_back((UnicodeCodePoint)(((codePoint >> 6) & 0x3F) + 0x80));
                    encoding.push_back((UnicodeCodePoint)((codePoint & 0x3F) + 0x80));
                }
            } else if ((numBits <= 21) && (codePoint <= LAST_LEGAL_UNICODE_CODE_POINT))
            {
                encoding.push_back((UnicodeCodePoint)(((codePoint >> 18) & 0x07) + 0xF0));
                encoding.push_back((UnicodeCodePoint)(((codePoint >> 12) & 0x3F) + 0x80));
                encoding.push_back((UnicodeCodePoint)(((codePoint >> 6) & 0x3F) + 0x80));
                encoding.push_back((UnicodeCodePoint)((codePoint & 0x3F) + 0x80));
            } else
            {
                encoding.insert(encoding.end(), UTF8_ENCODED_REPLACEMENT_CHAR.begin(),
                                UTF8_ENCODED_REPLACEMENT_CHAR.end());
            }
        }
        return encoding;
    }

    std::vector<UnicodeCodePoint> Utf8::Decode(const std::string& encoded) {
        return Decode(std::vector<uint8_t>(encoded.begin(), encoded.end()));
    }

    std::vector<UnicodeCodePoint> Utf8::Decode(const std::vector<uint8_t>& encoded) {
        std::vector<UnicodeCodePoint> output;
        for (auto octet : encoded)
        {
            if (impl_->numBytesRemainingToDecode == 0)
            {
                if ((octet & 0x80) == 0)
                {
                    output.push_back(octet);
                } else if ((octet & 0xE0) == 0xC0)
                {
                    impl_->numBytesRemainingToDecode = 1;
                    impl_->currentCharacterBeingDecoded = (octet & 0x1F);
                } else if ((octet & 0xF0) == 0xE0)
                {
                    impl_->numBytesRemainingToDecode = 2;
                    impl_->currentCharacterBeingDecoded = (octet & 0x0F);
                } else if ((octet & 0xF8) == 0xF0)
                {
                    impl_->numBytesRemainingToDecode = 3;
                    impl_->currentCharacterBeingDecoded = (octet & 0x07);
                } else
                {
                    // this is dangerous because the next character is likely a continuation
                    // character, and we'll end up outputting at least one more replacement
                    // character.
                    output.push_back(REPLACEMENT_CHARACTER);
                    impl_->isValidEncoding = false;
                }
                impl_->bytesTotalToDecodeCurrentCharacter = impl_->numBytesRemainingToDecode + 1;
            } else if ((octet & 0xC0) != 0x80)
            {
                output.push_back(REPLACEMENT_CHARACTER);
                impl_->isValidEncoding = false;
                impl_->numBytesRemainingToDecode = 0;
                const auto nextCodePoints = Decode(std::vector<uint8_t>{octet});
                output.insert(output.end(), nextCodePoints.begin(), nextCodePoints.end());
            } else
            {
                impl_->currentCharacterBeingDecoded <<= 6;
                impl_->currentCharacterBeingDecoded += (octet & 0x3F);
                if (--impl_->numBytesRemainingToDecode == 0)
                {
                    if (((impl_->bytesTotalToDecodeCurrentCharacter >= 2) &&
                         (impl_->currentCharacterBeingDecoded < 0x00080)) ||
                        ((impl_->bytesTotalToDecodeCurrentCharacter >= 3) &&
                         (impl_->currentCharacterBeingDecoded < 0x00800)) ||
                        ((impl_->bytesTotalToDecodeCurrentCharacter >= 4) &&
                         (impl_->currentCharacterBeingDecoded < 0x10000)))
                    {
                        output.push_back(REPLACEMENT_CHARACTER);
                        impl_->isValidEncoding = false;
                    } else
                    { output.push_back(impl_->currentCharacterBeingDecoded); }
                    impl_->currentCharacterBeingDecoded = 0;
                }
            }
        }
        return output;
    }

    bool Utf8::IsValidEncoding(const std::string& encoded, bool final) {
        (void)Decode(encoded);
        auto wasValidEncoding = impl_->isValidEncoding;
        if (final)
        {
            if (impl_->numBytesRemainingToDecode > 0)
            { wasValidEncoding = false; }
            impl_->isValidEncoding = true;
            impl_->numBytesRemainingToDecode = 0;
        }
        return wasValidEncoding;
    }
}  // namespace Utf8