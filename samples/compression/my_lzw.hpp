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
#ifndef UMF_MY_LZW_HPP
#define UMF_MY_LZW_HPP

#include "umf/umf.hpp"

// User-created compression algorithm should implement Compressor interface
// Straightforward implementation of LZW algorithm
class MyLZWCompressor : public umf::Compressor
{
public:
    virtual void compress(const umf::umf_string& input, umf::umf_rawbuffer& output);

    virtual void decompress(const umf::umf_rawbuffer& input, umf::umf_string &output);

    std::shared_ptr<Compressor> createNewInstance() const
    {
        return std::shared_ptr<Compressor>(new MyLZWCompressor);
    }

    virtual umf::umf_string getId()
    {
        return "com.intel.umf.compressor.example.my_lzw";
    }
};


#endif /*UMF_MY_LZW_HPP */

