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

#ifndef UMF_ENCRYPT_COMMON_HPP
#define UMF_ENCRYPT_COMMON_HPP

#include "umf/umf.hpp"

enum EncryptionScope
{
    OneField,
    OneMetadata,
    AllFieldDesc,
    AllMetaDesc,
    AllSchema,
    Whole
};

void generateEncryptedMetadata(umf::MetadataStream& mdStream, EncryptionScope scope);
void readAndDumpEncryptedMetadata(const umf::umf_string& videoFile,
                                  std::shared_ptr<umf::Encryptor> encryptor);

int encrypt_builtin(const std::string& videoFile, EncryptionScope scope);
int encrypt_custom(const std::string& videoFile, EncryptionScope scope);

#endif //UMF_ENCRYPT_COMMON_HPP
