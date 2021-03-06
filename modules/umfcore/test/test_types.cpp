/*
 * Copyright 2015 Intel(r) Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http ://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "test_precomp.hpp"

TEST(TestUmfRawBuffer, operatorAssign)
{
    umf::umf_rawbuffer buf;

    std::string s = "Some string containing text";
    umf::umf_rawbuffer sbuf(s.c_str(), s.size());

    buf = sbuf;

    ASSERT_EQ(buf.size(), s.size());
    ASSERT_EQ(std::string(buf.data(), buf.size()), s);
}


TEST(TestUmfRawBuffer, operatorAssignMove)
{
    std::string s = "Some string containing text";

    umf::umf_rawbuffer rbuf = umf::umf_rawbuffer(s.c_str(), s.size());
    ASSERT_EQ(rbuf.size(), s.size());
    ASSERT_EQ(std::string(rbuf.data(), rbuf.size()), s);
}


TEST(TestUmfRawBuffer, Constructors)
{
    umf::umf_rawbuffer emptyRb;
    ASSERT_EQ(emptyRb.size(), 0u);
    ASSERT_EQ(emptyRb.data(), nullptr);

    std::string str = "Here is a string containing text";
    std::vector<char> vecChar;
    for(size_t i = 0; i < str.size(); i++)
    {
        vecChar.push_back(str[i]);
    }

    umf::umf_rawbuffer vecRb(vecChar);
    ASSERT_EQ(vecRb.size(), str.size());
    ASSERT_EQ(std::string(vecRb.data(), vecRb.size()), str);

    umf::umf_rawbuffer rvecRb(std::move(vecChar));
    ASSERT_EQ(rvecRb.size(), str.size());
    ASSERT_EQ(std::string(rvecRb.data(), rvecRb.size()), str);

    umf::umf_rawbuffer otherRb(vecRb);
    ASSERT_EQ(otherRb.size(), str.size());
    ASSERT_EQ(std::string(otherRb.data(), otherRb.size()), str);

    umf::umf_rawbuffer rotherRb(umf::umf_rawbuffer(str.c_str(), str.size()));
    ASSERT_EQ(rotherRb.size(), str.size());
    ASSERT_EQ(std::string(rotherRb.data(), rotherRb.size()), str);

    umf::umf_rawbuffer sizeRb(str.size());
    ASSERT_EQ(sizeRb.size(), str.size());
    ASSERT_EQ(std::string(sizeRb.data(), sizeRb.size()), std::string(str.size(), '\0'));

    umf::umf_rawbuffer beginEndRb(str.data(), str.data()+str.size());
    ASSERT_EQ(beginEndRb.size(), str.size());
    ASSERT_EQ(std::string(beginEndRb.data(), beginEndRb.size()), str);
}
