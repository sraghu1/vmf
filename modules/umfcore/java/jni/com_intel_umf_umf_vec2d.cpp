#include<string>
#include<vector>
#include "umf/metadatastream.hpp"
#include "throwJavaException.hpp"

extern "C" {

using namespace umf;

/*
* Class:     com_intel_umf_umf_vec2d
* Method:    n_umf_vec2d
* Signature: ()J
*/
JNIEXPORT jlong JNICALL Java_com_intel_umf_umf_1vec2d_n_1umf_1vec2d__(JNIEnv *env, jclass);


JNIEXPORT jlong JNICALL Java_com_intel_umf_umf_1vec2d_n_1umf_1vec2d__(JNIEnv *env, jclass)
{
    static const char method_name[] = "umf_vec2d::n_1vec2d__";

    try
    {
        std::shared_ptr<umf_vec2d>* obj = new std::shared_ptr<umf_vec2d>(new umf_vec2d());
        return (jlong)obj;
    }
    catch (const std::exception &e)
    {
        throwJavaException(env, &e, method_name);
    }
    catch (...)
    {
        throwJavaException(env, 0, method_name);
    }

    return 0;
}

/*
 * Class:     com_intel_umf_umf_vec2d
 * Method:    n_umf_vec2d
 * Signature: (DD)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_umf_umf_1vec2d_n_1umf_1vec2d__DD(JNIEnv *env, jclass, jdouble x, jdouble y);


JNIEXPORT jlong JNICALL Java_com_intel_umf_umf_1vec2d_n_1umf_1vec2d__DD (JNIEnv *env, jclass, jdouble x, jdouble y)
{
    static const char method_name[] = "umf_vec2d::n_1vec2d__DD";

    try
    {
        std::shared_ptr<umf_vec2d>* obj = new std::shared_ptr<umf_vec2d>(new umf_vec2d((double)x, (double)y));
        return (jlong)obj;
    }
    catch (const std::exception &e)
    {
        throwJavaException(env, &e, method_name);
    }
    catch (...)
    {
        throwJavaException(env, 0, method_name);
    }

    return 0;
}

/*
 * Class:     com_intel_umf_umf_vec2d
 * Method:    n_setTo
 * Signature: (JJ)V
 */
/*JNIEXPORT void JNICALL Java_com_intel_umf_umf_1vec2d_n_1setTo(JNIEnv *env, jclass, jlong selfAddr, jlong otherAddr);


JNIEXPORT void JNICALL Java_com_intel_umf_umf_1vec2d_n_1setTo (JNIEnv *env, jclass, jlong selfAddr, jlong otherAddr)
{
    static const char method_name[] = "umf_vec2d::n_1setTo";

    try
    {
        std::shared_ptr<umf_vec2d>* self = (std::shared_ptr<umf_vec2d>*) selfAddr;
        std::shared_ptr<umf_vec2d>* other = (std::shared_ptr<umf_vec2d>*) otherAddr;

        if ((self == NULL) || (self->get() == NULL))
            UMF_EXCEPTION(NullPointerException, "Vec2d is null pointer.");

        if ((other == NULL) || (other->get() == NULL))
            UMF_EXCEPTION(NullPointerException, "Other vec2d is null pointer.");

        (**self) = (**other);
    }
    catch (const std::exception &e)
    {
        throwJavaException(env, &e, method_name);
    }
    catch (...)
    {
        throwJavaException(env, 0, method_name);
    }
}*/

/*
* Class:     com_intel_umf_umf_vec2d
* Method:    n_getX
* Signature: (J)D
*/
JNIEXPORT jdouble JNICALL Java_com_intel_umf_umf_1vec2d_n_1getX(JNIEnv *env, jclass, jlong self);


JNIEXPORT jdouble JNICALL Java_com_intel_umf_umf_1vec2d_n_1getX (JNIEnv *env, jclass, jlong self)
{
    static const char method_name[] = "umf_vec2d::n_1getX";

    try
    {
        std::shared_ptr<umf_vec2d>* obj = (std::shared_ptr<umf_vec2d>*) self;

        if ((obj == NULL) || (obj->get() == NULL))
            return 0;

        return (jdouble)((**obj).x);
    }
    catch (const std::exception &e)
    {
        throwJavaException(env, &e, method_name);
    }
    catch (...)
    {
        throwJavaException(env, 0, method_name);
    }

    return 0;
}

/*
* Class:     com_intel_umf_umf_vec2d
* Method:    n_getY
* Signature: (J)D
*/
JNIEXPORT jdouble JNICALL Java_com_intel_umf_umf_1vec2d_n_1getY(JNIEnv *env, jclass, jlong self);


JNIEXPORT jdouble JNICALL Java_com_intel_umf_umf_1vec2d_n_1getY(JNIEnv *env, jclass, jlong self)
{
    static const char method_name[] = "umf_vec2d::n_1getY";

    try
    {
        std::shared_ptr<umf_vec2d>* obj = (std::shared_ptr<umf_vec2d>*) self;

        if ((obj == NULL) || (obj->get() == NULL))
            return 0;

        return (jdouble)((**obj).y);
    }
    catch (const std::exception &e)
    {
        throwJavaException(env, &e, method_name);
    }
    catch (...)
    {
        throwJavaException(env, 0, method_name);
    }

    return 0;
}

/*
 * Class:     com_intel_umf_umf_vec2d
 * Method:    n_delete
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_intel_umf_umf_1vec2d_n_1delete(JNIEnv *env, jclass, jlong self);


JNIEXPORT void JNICALL Java_com_intel_umf_umf_1vec2d_n_1delete (JNIEnv *env, jclass, jlong self)
{
    static const char method_name[] = "umf_vec2d::n_1delete";

    try
    {
        std::shared_ptr<umf_vec2d>* obj = (std::shared_ptr<umf_vec2d>*) self;

        if ((obj == NULL) || (obj->get() == NULL))
            UMF_EXCEPTION(NullPointerException, "Vec2d is null pointer.");

        delete obj;
    }
    catch (const std::exception &e)
    {
        throwJavaException(env, &e, method_name);
    }
    catch (...)
    {
        throwJavaException(env, 0, method_name);
    }
}


}
