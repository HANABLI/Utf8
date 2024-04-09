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

TEST(Utf8Tests, Symbols) {
    Utf8::Utf8 utf8;
    const std::vector< uint8_t > expectedEncoding{ 0x41, 0xE2, 0x89, 0xA2, 0xCE, 0x91, 0x2E };
    const auto actualEncoding = utf8.Encode({0x0041, 0x2262, 0x0391, 0x002E});
    ASSERT_EQ(expectedEncoding, actualEncoding);
}

TEST(Utf8Tests, EncodeJapanese_Test) {
    Utf8::Utf8 utf8;
    const std::vector< uint8_t > expectedEncoding{ 0xE6, 0x97, 0xA5, 0xE6, 0x9C, 0xAC, 0xE8, 0xAA, 0x9E };
    const auto actualEncoding = utf8.Encode({0x65E5, 0x672C, 0x8A9E});
    ASSERT_EQ(expectedEncoding, actualEncoding);
}

TEST(Utf8Test, StumpOfTree) {
    Utf8::Utf8 utf8;
    const std::vector< uint8_t > expectedEncoding{ 0xF0, 0xA3, 0x8E, 0xB4 };
    const auto actualEncoding = utf8.Encode({0x233B4});
    ASSERT_EQ(expectedEncoding, actualEncoding);
}