/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_intel_vmf_FieldValue */

#ifndef _Included_com_intel_vmf_FieldValue
#define _Included_com_intel_vmf_FieldValue
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_intel_vmf_FieldValue
 * Method:    n_FieldValue
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_intel_vmf_FieldValue_n_1FieldValue__
  (JNIEnv *, jclass);

/*
 * Class:     com_intel_vmf_FieldValue
 * Method:    n_FieldValue
 * Signature: (Ljava/lang/String;J)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_vmf_FieldValue_n_1FieldValue__Ljava_lang_String_2J
  (JNIEnv *, jclass, jstring, jlong);

/*
 * Class:     com_intel_vmf_FieldValue
 * Method:    n_getName
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_intel_vmf_FieldValue_n_1getName
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_intel_vmf_FieldValue
 * Method:    n_setTo
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_vmf_FieldValue_n_1setTo
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     com_intel_vmf_FieldValue
 * Method:    n_equals
 * Signature: (JJ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_intel_vmf_FieldValue_n_1equals
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     com_intel_vmf_FieldValue
 * Method:    n_getType
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_intel_vmf_FieldValue_n_1getType
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_intel_vmf_FieldValue
 * Method:    n_isEmpty
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_intel_vmf_FieldValue_n_1isEmpty
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_intel_vmf_FieldValue
 * Method:    n_getTypeName
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_intel_vmf_FieldValue_n_1getTypeName
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_intel_vmf_FieldValue
 * Method:    n_convertTo
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_intel_vmf_FieldValue_n_1convertTo
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_intel_vmf_FieldValue
 * Method:    n_delete
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_intel_vmf_FieldValue_n_1delete
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
