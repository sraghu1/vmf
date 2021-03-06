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

/*
* This sample shows how to use checksum API for checking that video file was not modified.
*/

#include <iostream>
#include <fstream>
#include "umf/umf.hpp"

using namespace std;

void copyFile(const string& srcPath, const string& dstPath)
{
    ifstream src(srcPath, ios_base::binary | ios_base::in);
    ofstream dst(dstPath, ios_base::binary | ios_base::out);

    if (!src.is_open() || !dst.is_open())
        UMF_EXCEPTION(umf::Exception, "Can't copy " + srcPath + " to " + dstPath);

    dst << src.rdbuf();

    dst.close();
    src.close();
}

int main(int argc, char** argv)
{
    try
    {
        string srcFileName;
        if (argc > 1)
            srcFileName = argv[1];
        else
            throw umf::Exception("USAGE:\nchecksum-utility <video file path>");

        string ext = string(srcFileName, srcFileName.find_last_of('.'));
        string dstFileName = std::string(srcFileName, 0, srcFileName.find_last_of('.')) + "Test" + ext;

        copyFile(srcFileName, dstFileName);

        ifstream in(dstFileName, ios::binary);
        if (!in)
            throw umf::Exception(dstFileName + " not found");
        in.seekg(0, ios::end);
        long long originalFileSize = in.tellg();
        in.seekg(0, ios::beg);
        auto originalFileBuffer = unique_ptr<char[]>(new char[(unsigned int)originalFileSize]);
        in.read(originalFileBuffer.get(), originalFileSize);
        in.close();

        umf::MetadataStream stream;
        if (!stream.open(dstFileName, umf::MetadataStream::Update))
            throw umf::Exception("Can't open file by UMF stream");

        string originalFileChecksum = stream.computeChecksum();

        stream.setChecksum(originalFileChecksum);

        umf::umf_string TEST_SCHEMA_NAME = "TEST_SCHEMA_NAME";
        shared_ptr<umf::MetadataSchema> schema = make_shared<umf::MetadataSchema>(TEST_SCHEMA_NAME);

        UMF_METADATA_BEGIN("TEST_PROPERTY_NAME1")
            UMF_FIELD_INT("TEST_FIELD_NAME1")
            UMF_FIELD_INT("TEST_FIELD_NAME2")
            UMF_FIELD_INT("TEST_FIELD_NAME3")
            UMF_FIELD_INT("TEST_FIELD_NAME4")
            UMF_FIELD_REAL("TEST_FIELD_NAME5")
            UMF_FIELD_REAL("TEST_FIELD_NAME6")
            UMF_FIELD_REAL("TEST_FIELD_NAME7")
        UMF_METADATA_END(schema);

        UMF_METADATA_BEGIN("TEST_PROPERTY_NAME2")
            UMF_FIELD_INT("TEST_FIELD_NAME1")
            UMF_FIELD_INT("TEST_FIELD_NAME2")
            UMF_FIELD_INT("TEST_FIELD_NAME3")
            UMF_FIELD_INT("TEST_FIELD_NAME4")
            UMF_FIELD_REAL("TEST_FIELD_NAME5")
            UMF_FIELD_REAL("TEST_FIELD_NAME6")
            UMF_FIELD_REAL("TEST_FIELD_NAME7")
            UMF_FIELD_REAL("TEST_FIELD_NAME8")
        UMF_METADATA_END(schema);

        stream.addSchema(schema);

        for (int i = 0; i < 10; i++)
        {
            shared_ptr<umf::Metadata> md(new umf::Metadata(schema->findMetadataDesc("TEST_PROPERTY_NAME1")));
            md->setFieldValue("TEST_FIELD_NAME1", i);
            md->setFieldValue("TEST_FIELD_NAME2", 2 * i);
            md->setFieldValue("TEST_FIELD_NAME3", 3 * i);
            md->setFieldValue("TEST_FIELD_NAME4", 4 * i);
            md->setFieldValue("TEST_FIELD_NAME5", 5 * i);
            md->setFieldValue("TEST_FIELD_NAME6", i / 5.0);
            md->setFieldValue("TEST_FIELD_NAME7", i / 6.0);
            stream.add(md);

            shared_ptr<umf::Metadata> md2(new umf::Metadata(schema->findMetadataDesc("TEST_PROPERTY_NAME2")));
            md2->setFieldValue("TEST_FIELD_NAME1", i);
            md2->setFieldValue("TEST_FIELD_NAME2", 2 * i);
            md2->setFieldValue("TEST_FIELD_NAME3", 3 * i);
            md2->setFieldValue("TEST_FIELD_NAME4", 4 * i);
            md2->setFieldValue("TEST_FIELD_NAME5", 5 * i);
            md2->setFieldValue("TEST_FIELD_NAME6", i / 5.0);
            md2->setFieldValue("TEST_FIELD_NAME7", i / 6.0);
            md2->setFieldValue("TEST_FIELD_NAME8", i / 7.0);
            stream.add(md2);
        }

        stream.save();
        stream.close();

        if (!stream.reopen(umf::MetadataStream::ReadOnly))
            throw umf::Exception("Can't reopen file");

        originalFileChecksum = stream.getChecksum();

        long long xmpPacketSize, xmpPacketOffset;
        string modifiedFileChecksum = stream.computeChecksum(xmpPacketSize, xmpPacketOffset);

        stream.close();

        in.open(dstFileName, ios::binary);
        if (!in)
            throw umf::Exception(dstFileName + " not found!");
        in.seekg(0, ios::end);
        long long modifiedFileSize = in.tellg();
        in.seekg(0, ios::beg);
        auto modifiedFileBuffer = unique_ptr<char[]>(new char[(unsigned int)modifiedFileSize]);
        in.read(modifiedFileBuffer.get(), modifiedFileSize);
        in.close();

        cout << "Original file size = " << originalFileSize << endl;
        cout << "Modified file size = " << modifiedFileSize << endl << endl;

        cout << "Original file checksum = " << originalFileChecksum << endl;
        cout << "Modified file checksum = " << modifiedFileChecksum << endl << endl;

        if ((xmpPacketSize > 0) && (xmpPacketOffset >= 0))
        {
            cout << "XMP packet size = " << xmpPacketSize << endl;
            cout << "XMP packet offset = " << xmpPacketOffset << endl << endl;
        }

        if (originalFileChecksum == modifiedFileChecksum)
            return 0;

        long long differentBytesCounter = 0;
        for (long long i = 0; i < modifiedFileSize; i++)
        {
            if (i == xmpPacketOffset - 24)
            {
                i += xmpPacketSize + 24;
                if (i >= modifiedFileSize)
                    break;
            }

            if (differentBytesCounter < 10 && originalFileBuffer.get()[i] != modifiedFileBuffer.get()[i])
            {
                cout << i << "-th byte was changed from " << originalFileBuffer.get()[i] << " to " << modifiedFileBuffer.get()[i] << endl;
                differentBytesCounter++;
            }
        }

        cout << endl << "Total changed bytes: " << differentBytesCounter << endl;
        return 0;
    }
    catch (umf::Exception& e)
    {
        cout << "Fatal error: " << e.what() << endl;
        return -1;
    }
}
