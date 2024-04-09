/**
 * @file Utf8Tests.cpp
 * 
 * This module contains unit Tests of the Utf8::Utf8 class 
 * 
 * © 2024 by Hatem Nabli
*/

#include <gtest/gtest.h>
#include <Utf8/Utf8.hpp>

TEST(Utf8Tests, PlaceHolder_Test) {
    Utf8::Utf8 utf8;
    ASSERT_TRUE(true);
}

TEST(Utf8Tests, AsciiToUnicode_Test) {
    const std::vector< Utf8::UnicodeCodePoint > expectedEncodingPoints{ 0x48, 0x65, 0x6C, 0x6C, 0x6F };
    const auto actualCodePoints = Utf8::AsciiToUnicode("Hello");
}

TEST(Utf8Tests, EncodeAscii) {
    Utf8::Utf8 utf8;
    const std::vector< uint8_t > expectedEncoding{ 0x48, 0x65, 0x6C, 0x6C, 0x6F };
    const auto actualEncoding = utf8.Encode(Utf8::AsciiToUnicode("Hello"));
    ASSERT_EQ(expectedEncoding, actualEncoding);
}