/*
 * MIT License
 *
 * Copyright (c) 2020 Denis Kovalchuk
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>
#include "utils.hpp"

TEST(UtilsTest, FormatTest)
{
    EXPECT_EQ(utils::format("string: %1%", "hello"), "string: hello");
    EXPECT_EQ(utils::format("double: %1%", 27.9), "double: 27.9");
    EXPECT_EQ(utils::format("integer: %1%", 42), "integer: 42");
    EXPECT_EQ(utils::format("%1% %2% %3%", "hello", 27.9, 42), "hello 27.9 42");
}

struct custom_type
{
    std::string s;
    double d;
    int i;
};

std::ostream & operator<<(std::ostream & os, const custom_type & value)
{
    return os << value.s << " " << value.d << " " << value.i;
}

TEST(UtilsTest, FormatCustomTypeTest)
{
    custom_type value {"hello", 27.9, 42};

    EXPECT_EQ(utils::format("%1%", value), "hello 27.9 42");
}
