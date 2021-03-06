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

#ifndef UMF_COMPRESSOR_ZLIB_HPP
#define UMF_COMPRESSOR_ZLIB_HPP

#include "umf/compressor.hpp"

namespace umf {

/*!
 * \class ZLibCompressor
 * \brief Compression algorithm that uses ZLib library.
 * Currently runs Deflate algorithm with default settings.
 */
class UMF_EXPORT CompressorZlib : public Compressor
{
public:

    /*!
     * \brief Default constructor
     */
    CompressorZlib()
    { }

    /*!
     * \brief Compress data
     * \param [in]  input  input text data
     * \param [out] output binary buffer where to put compressed data
     */
    virtual void compress(const umf_string& input, umf_rawbuffer& output);

    /*!
     * \brief Decompress data
     * \param [in]  input  binary buffer with compressed input data
     * \param [out] output string where to put decompressed text data
     */
    virtual void decompress(const umf_rawbuffer& input, umf_string &output);

    /*!
     * \brief Create new instance of the compressor
     * \return Smart pointer to ICompressor instance
     */
    virtual std::shared_ptr<Compressor> createNewInstance() const
    {
        return std::shared_ptr<Compressor>(new CompressorZlib);
    }

    /*!
     * \brief Get the ID of current algorithm
     */
    virtual umf_string getId()
    {
        return Compressor::builtinId();
    }
};

} /* umf */

#endif /* UMF_COMPRESSOR_ZLIB_HPP */
