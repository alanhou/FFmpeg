#include <jni.h>
#include <string>

#define JNI_CLASS_PATH "org/alanhou/testc2j/Student"
extern "C" JNIEXPORT jstring JNICALL
Java_org_alanhou_testc2j_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    // step 1
    jclass clazz = env->FindClass(JNI_CLASS_PATH);

    // step2
    jmethodID method_init_id = env->GetMethodID(clazz, "<init>", "()V");
    jmethodID method_set_id = env->GetMethodID(clazz, "setYear", "(I)V");
    jmethodID method_get_id = env->GetMethodID(clazz, "getYear", "()I");

    // step 3
    jobject obj = env->NewObject(clazz, method_init_id);

    // step 4
    env->CallVoidMethod(obj, method_set_id, 18);
    int year = env->CallIntMethod(obj, method_get_id);

    char tmp[80];
    sprintf(tmp, "%d", year);

    std::string hello = "Hello from C++, year=";
    hello.append(tmp);
    return env->NewStringUTF(hello.c_str());
}
