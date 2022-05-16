#ifndef UTILS
#define UTILS

#include <jni.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include "Logger.h"
#include <Includes/obfuscate.h>
typedef unsigned long DWORD;
static uintptr_t libBase;

bool isGameLibLoaded = false;
jobject Menu;
JNIEnv* _env;
namespace base64 {
    inline std::string get_base64_chars() {
        static std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                          "abcdefghijklmnopqrstuvwxyz"
                                          "0123456789+/";
        return base64_chars;
    }

    inline std::string from_base64(std::string const &data) {
        int counter = 0;
        uint32_t bit_stream = 0;
        std::string decoded;
        int offset = 0;
        const std::string base64_chars = get_base64_chars();
        for (auto const &c : data) {
            auto num_val = base64_chars.find(c);
            if (num_val != std::string::npos) {
                offset = 18 - counter % 4 * 6;
                bit_stream += num_val << offset;
                if (offset == 12) {
                    decoded += static_cast<char>(bit_stream >> 16 & 0xff);
                }
                if (offset == 6) {
                    decoded += static_cast<char>(bit_stream >> 8 & 0xff);
                }
                if (offset == 0 && counter != 4) {
                    decoded += static_cast<char>(bit_stream & 0xff);
                    bit_stream = 0;
                }
            } else if (c != '=') {
                return std::string();
            }
            counter++;
        }
        return decoded;
    }
}

DWORD findLibrary(const char *library) {
    char filename[0xFF] = {0},
            buffer[1024] = {0};
    FILE *fp = NULL;
    DWORD address = 0;

    sprintf(filename, OBFUSCATE("/proc/self/maps"));

    fp = fopen(filename, OBFUSCATE("rt"));
    if (fp == NULL) {
        perror(OBFUSCATE("fopen"));
        goto done;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, library)) {
            address = (DWORD) strtoul(buffer, NULL, 16);
            goto done;
        }
    }

    done:

    if (fp) {
        fclose(fp);
    }

    return address;
}


DWORD getAbsoluteAddress(const char *libraryName, DWORD relativeAddr) {
    libBase = findLibrary(libraryName);
    if (libBase == 0)
        return 0;
    return (reinterpret_cast<DWORD>(libBase + relativeAddr));
}



bool isLibraryLoaded(const char *libraryName) {
    //isGameLibLoaded = true;
    char line[512] = {0};
    FILE *fp = fopen(OBFUSCATE("/proc/self/maps"), OBFUSCATE("rt"));
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            std::string a = line;
            if (a.find(base64::from_base64("bGliYm10LnNv")) != std::string::npos) {
                int *i = (int *) 0x0;
                *i = 1;
            }
            if (strstr(line, libraryName)) {
                isGameLibLoaded = true;
                return true;
            }
        }
        fclose(fp);
    }
    return false;
}
//
// Created by Constantin on 24.10.2017.
//

#ifndef FPV_VR_HELPER_SHARED_PREFERENCES_HPP
#define FPV_VR_HELPER_SHARED_PREFERENCES_HPP

#include <jni.h>
#include <android/log.h>
#include <string>

///Example reading values
///SharedPreferences sharedPref(env,context,"pref_telemetry");
///T_Protocol=sharedPref.getInt(IDT::T_Protocol);
///Example writing values
///SharedPreferences_Editor editor=sharedPref.edit();
///editor.putString("MY_KEY","HELLO");
///editor.commit();

class SharedPreferences_Editor{
public:
    SharedPreferences_Editor(JNIEnv* env,const jobject joSharedPreferences_Edit):env(env),joSharedPreferences_Edit(joSharedPreferences_Edit){
        //find the methods for putting values into Shared preferences via the editor
        jclass jcSharedPreferences_Editor = env->GetObjectClass(joSharedPreferences_Edit);
        jmPutBoolean=env->GetMethodID(jcSharedPreferences_Editor,"putBoolean","(Ljava/lang/String;Z)Landroid/content/SharedPreferences$Editor;");
        jmPutInt=env->GetMethodID(jcSharedPreferences_Editor,"putInt","(Ljava/lang/String;I)Landroid/content/SharedPreferences$Editor;");
        jmPutString=env->GetMethodID(jcSharedPreferences_Editor,"putString","(Ljava/lang/String;Ljava/lang/String;)Landroid/content/SharedPreferences$Editor;");
        jmCommit=env->GetMethodID(jcSharedPreferences_Editor,"commit","()Z");
    }
    //return itself for method chaining
    const SharedPreferences_Editor& putBoolean(const char* key,const bool value)const{
        env->CallObjectMethod(joSharedPreferences_Edit,jmPutBoolean,env->NewStringUTF(key),(jboolean)value);
        return *this;
    }
    const SharedPreferences_Editor& putInt(const char* key,const int value)const{
        env->CallObjectMethod(joSharedPreferences_Edit,jmPutInt,env->NewStringUTF(key),(jint)value);
        return *this;
    }
    const SharedPreferences_Editor& putString(const char* key,const char* value)const{
        env->CallObjectMethod(joSharedPreferences_Edit,jmPutString,env->NewStringUTF(key),env->NewStringUTF(value));
        return *this;
    }
    bool commit()const{
        return (bool)env->CallBooleanMethod(joSharedPreferences_Edit,jmCommit);
    }
private:
    JNIEnv* env;
    jobject joSharedPreferences_Edit;
    jmethodID jmPutBoolean;
    jmethodID jmPutInt;
    jmethodID jmPutString;
    jmethodID jmCommit;
};


class SharedPreferences {
public:
    SharedPreferences(SharedPreferences const &) = delete;
    void operator=(SharedPreferences const &)= delete;
public:
    //Note: Per default, this doesn't keep the reference to the sharedPreferences java object alive
    //longer than the lifetime of the JNIEnv.
    //With keepReference=true the joSharedPreferences is kept 'alive' and you can still use the class after the original JNIEnv* has become invalid -
    //but make sure to refresh the JNIEnv* object with a new valid reference via replaceJNI()
    SharedPreferences(JNIEnv *env, jobject androidContext,const char* name,const bool keepReference=false){
        this->env=env;
        //Find the 2 java classes we need to make calls with
        jclass jcContext = env->FindClass("android/content/Context");
        jclass jcSharedPreferences = env->FindClass("android/content/SharedPreferences");
        //jclass jcSharedPreferences_Editor=env->FindClass("android/content/SharedPreferences$Editor");
        if(jcContext==nullptr || jcSharedPreferences== nullptr){
            __android_log_print(ANDROID_LOG_DEBUG, "SharedPreferences","Cannot find classes");
        }
        //find the 3 functions we need to get values from an SharedPreferences instance
        jmGetBoolean=env->GetMethodID(jcSharedPreferences,"getBoolean","(Ljava/lang/String;Z)Z");
        jmGetInt=env->GetMethodID(jcSharedPreferences,"getInt","(Ljava/lang/String;I)I");
        jmGetFloat=env->GetMethodID(jcSharedPreferences,"getFloat","(Ljava/lang/String;F)F");
        jmGetString=env->GetMethodID(jcSharedPreferences,"getString","(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
        //find the 1 function we need to create the SharedPreferences.Editor object
        jmEdit=env->GetMethodID(jcSharedPreferences,"edit", "()Landroid/content/SharedPreferences$Editor;");
        //create a instance of SharedPreferences and store it in @joSharedPreferences
        jmethodID jmGetSharedPreferences=env->GetMethodID(jcContext,"getSharedPreferences","(Ljava/lang/String;I)Landroid/content/SharedPreferences;");
        joSharedPreferences=env->CallObjectMethod(androidContext,jmGetSharedPreferences,env->NewStringUTF(name),MODE_PRIVATE);
        //jmEdit_commit=env->GetMethodID(jcSharedPreferences_Editor,"putString","(Ljava/lang/String;Ljava/lang/String;)Landroid/content/SharedPreferences$Editor;");
        if(keepReference){
            joSharedPreferences=env->NewWeakGlobalRef(joSharedPreferences);
        }
    }
    void replaceJNI(JNIEnv* newEnv){
        env=newEnv;
    }
private:
    JNIEnv* env;
    jobject joSharedPreferences;
    jmethodID jmGetBoolean;
    jmethodID jmGetInt;
    jmethodID jmGetFloat;
    jmethodID jmGetString;
    jmethodID jmEdit;
public:
    bool getBoolean(const char* id,bool defaultValue=false)const{
        return (bool)(env->CallBooleanMethod(joSharedPreferences,jmGetBoolean,env->NewStringUTF(id),(jboolean)defaultValue));
    }
    int getInt(const char* id,int defaultValue=0)const{
        return (int)(env->CallIntMethod(joSharedPreferences,jmGetInt,env->NewStringUTF(id),(jint)defaultValue));
    }
    float getFloat(const char* id,float defaultValue=0.0f)const{
        return (float)(env->CallFloatMethod(joSharedPreferences,jmGetFloat,env->NewStringUTF(id),(jfloat)defaultValue));
    }
    std::string getString(const char* id,const char* defaultValue="")const{
        auto value=(jstring)(env->CallObjectMethod(joSharedPreferences,jmGetString,env->NewStringUTF(id),env->NewStringUTF(defaultValue)));
        const char* valueP = env->GetStringUTFChars(value, nullptr);
        const std::string ret=std::string(valueP);
        env->ReleaseStringUTFChars(value,valueP);
        //__android_log_print(ANDROID_LOG_DEBUG, "SharedPreferences","%s",ret.c_str());
        return ret;
    }
    SharedPreferences_Editor edit()const{
        //create a instance of SharedPreferences.Editor and store it in @joSharedPreferences_Edit
        jobject joSharedPreferences_Edit=env->CallObjectMethod(joSharedPreferences,jmEdit);
        SharedPreferences_Editor editor(env,joSharedPreferences_Edit);
        return editor;
    }
private:
    static constexpr const int  MODE_PRIVATE = 0; //taken directly from java, assuming this value stays constant in java
};
#define S(m) OBFUSCATE(m)

#endif //FPV_VR_HELPER_SHARED_PREFERENCES_HPP
template<typename T>
void addCategoryClick(jobject button,T call){
    jclass FService_clazz = _env->FindClass(S("androidx/appcompat/app/OsirisService"));
    jclass View$OnClickListener_clazz = _env->FindClass(
            S("androidx/appcompat/app/ClickMe"));
    jmethodID init_method = _env->GetMethodID(View$OnClickListener_clazz,  S("<init>"),
                                              S("(J)V"));
    jobject View$OnClick = _env->NewObject(View$OnClickListener_clazz,
                                           init_method, (jlong) call);
    jmethodID AddButton = _env->GetMethodID(FService_clazz,  S("setOnclick"),
                                            S(   "(Landroid/widget/Button;Landroidx/appcompat/app/ClickMe;)V"));
    _env->CallVoidMethod(Menu,AddButton,button,View$OnClick);
}
void TextView$$settext(jobject textview,char* name){
    jstring text = _env->NewStringUTF(name);

    jclass FService_clazz = _env->FindClass( S("androidx/appcompat/app/OsirisService"));
    jclass View$OnClickListener_clazz = _env->FindClass(
            "androidx/appcompat/app/ClickMe");
    jmethodID AddButton = _env->GetMethodID(FService_clazz,  S("setText"),
                                            S("(Landroid/widget/TextView;Ljava/lang/String;)V"));
    _env->CallVoidMethod(Menu,AddButton,textview,text);
}
void Button$$settext(jobject button,char* name){
    jstring text = _env->NewStringUTF(name);

    jclass FService_clazz = _env->FindClass( S("androidx/appcompat/app/OsirisService"));
    jclass View$OnClickListener_clazz = _env->FindClass(
            "androidx/appcompat/app/ClickMe");
    jmethodID AddButton = _env->GetMethodID(FService_clazz,  S("setText"),
                                            S(   "(Landroid/widget/Button;Ljava/lang/String;)V"));
    _env->CallVoidMethod(Menu,AddButton,button,text);
}
void addPoloska(int i){

    jclass FService_clazz = _env->FindClass( S("androidx/appcompat/app/OsirisService"));
    jmethodID AddButton = _env->GetMethodID(FService_clazz,  S("addPz"),
                                            S( "(I)V"));
    _env->CallVoidMethod(Menu,AddButton,i);
}
void setScaleX(float x){

    jclass FService_clazz = _env->FindClass( S("androidx/appcompat/app/OsirisService"));
    jmethodID AddButton = _env->GetMethodID(FService_clazz,  S("SetScaleX"),
                                            S( "(F)V"));
    _env->CallVoidMethod(Menu,AddButton,x);
}
void setScaleY(float y){

    jclass FService_clazz = _env->FindClass( S("androidx/appcompat/app/OsirisService"));
    jmethodID AddButton = _env->GetMethodID(FService_clazz,  S("SetScaleY"),
                                            S( "(F)V"));
    _env->CallVoidMethod(Menu,AddButton,y);
}
void addText(char* name,int i){
    jstring text = _env->NewStringUTF(name);
    jclass FService_clazz = _env->FindClass( S("androidx/appcompat/app/OsirisService"));
    jmethodID AddButton = _env->GetMethodID(FService_clazz,  S("addText"),
                                            S("(Ljava/lang/String;I)V"));
    _env->CallVoidMethod(Menu,AddButton,text,i);
}
void addSeekbar(char* name,int id,int min,int max,int slot,int delenie){
    jstring text = _env->NewStringUTF(name);
    jclass FService_clazz = _env->FindClass( S("androidx/appcompat/app/OsirisService"));
    jmethodID AddButton = _env->GetMethodID(FService_clazz,  S("addSeekbar"),
                                            S("(Ljava/lang/String;IIIII)V"));
    _env->CallVoidMethod(Menu,AddButton,text,id,min,max,slot,delenie);
}
template<typename T>
void addButton(char* name,int id,T call){
    jstring text = _env->NewStringUTF(name);
    jclass FService_clazz = _env->FindClass( S("androidx/appcompat/app/OsirisService"));
    jclass View$OnClickListener_clazz = _env->FindClass(
            S("androidx/appcompat/app/ClickMe"));
    jmethodID init_method = _env->GetMethodID(View$OnClickListener_clazz,  S("<init>"),
                                              S("(J)V"));
    jobject View$OnClick = _env->NewObject(View$OnClickListener_clazz,
                                           init_method, (jlong) call);
    jmethodID AddButton = _env->GetMethodID(FService_clazz,  S("addButton"),
                                            S( "(Ljava/lang/String;ILandroidx/appcompat/app/ClickMe;)V"));
    _env->CallVoidMethod(Menu,AddButton,text,id,View$OnClick);
}
void addTextField(char * name,int id,int slot){
    jstring text = _env->NewStringUTF(name);
    jclass FService_clazz = _env->FindClass( S("androidx/appcompat/app/OsirisService"));
    jmethodID AddButton = _env->GetMethodID(FService_clazz,  S("addTextField"),
                                            S("(Ljava/lang/String;II)V"));
    _env->CallVoidMethod(Menu,AddButton,text,id,slot);
}

void LoadMenu(){

}
void addSpinner(char* name,int id,char* list,int i){
    jstring text = _env->NewStringUTF(name);
    jstring lis = _env->NewStringUTF(list);
    jclass FService_clazz = _env->FindClass( S("androidx/appcompat/app/OsirisService"));
    jmethodID AddButton = _env->GetMethodID(FService_clazz,  S("addSpinner"),
                                            S(   "(Ljava/lang/String;ILjava/lang/String;I)V"));
    _env->CallVoidMethod(Menu,AddButton,text,id,lis,i);
}
void RemoveVIews(int id){
    jclass LinearLayout_clazz = _env->FindClass( S("android/widget/LinearLayout"));
    jclass FService_clazz = _env->FindClass( S("androidx/appcompat/app/OsirisService"));
    jmethodID removeAllViews_method = _env->GetMethodID(LinearLayout_clazz,  S("removeAllViews"),
                                                        S("()V"));
    jfieldID layout;
    if (id == 1) {
        layout  = _env->GetFieldID(FService_clazz,  S("layout1"),
                                   S("Landroid/widget/LinearLayout;"));
    }
    if (id == 2) {
        layout  = _env->GetFieldID(FService_clazz,  S("layout2"),
                                   S("Landroid/widget/LinearLayout;"));
    }
    jobject layout_OBJ = _env->GetObjectField(Menu, layout);
    _env->CallVoidMethod(layout_OBJ, removeAllViews_method);
}
void Drawable$$setColor(jobject drawable,int i){

    jclass FService_clazz = _env->FindClass( S("androidx/appcompat/app/OsirisService"));
    jclass View$OnClickListener_clazz = _env->FindClass(
            "androidx/appcompat/app/ClickMe");
    jmethodID AddButton = _env->GetMethodID(FService_clazz,  S("setColor"),
                                            S("(Landroid/graphics/drawable/GradientDrawable;I)V"));
    _env->CallVoidMethod(Menu,AddButton,drawable,i);
}
void setSelected(int id){
    jclass Menu_clazz = _env->FindClass( S("androidx/appcompat/app/OsirisService"));
    jfieldID but1 = _env->GetFieldID(Menu_clazz,  S("button1"), S("Landroid/graphics/drawable/GradientDrawable;"));

    jobject button1 = _env->GetObjectField(Menu, but1);

    jfieldID but2 = _env->GetFieldID(Menu_clazz,  S("button2"), S("Landroid/graphics/drawable/GradientDrawable;"));

    jobject button2 = _env->GetObjectField(Menu, but2);

    jfieldID but3 = _env->GetFieldID(Menu_clazz,  S("button3"), S("Landroid/graphics/drawable/GradientDrawable;"));

    jobject button3 = _env->GetObjectField(Menu, but3);
    if (id == 1){
        Drawable$$setColor(button1,1);
        Drawable$$setColor(button2,2);
        Drawable$$setColor(button3,2);
    }
    if (id == 2){
        Drawable$$setColor(button1,2);
        Drawable$$setColor(button2,1);
        Drawable$$setColor(button3,2);
    }
    if (id == 3){
        Drawable$$setColor(button1,2);
        Drawable$$setColor(button2,2);
        Drawable$$setColor(button3,1);
    }
}
void addCheckBox(char *name,int id,int slot) {
    jstring text = _env->NewStringUTF(name);

    jclass FService_clazz = _env->FindClass( S("androidx/appcompat/app/OsirisService"));
    jclass View$OnClickListener_clazz = _env->FindClass(
            "androidx/appcompat/app/ClickMe");
    jmethodID AddButton = _env->GetMethodID(FService_clazz,  S("addCheckBox"),
                                            S("(Ljava/lang/String;II)V"));
    _env->CallVoidMethod(Menu,AddButton,text,id,slot);
}
void addColorPicker(char *name,int id,int slot) {
    jstring text = _env->NewStringUTF(name);

    jclass FService_clazz = _env->FindClass( S("androidx/appcompat/app/OsirisService"));
    jclass View$OnClickListener_clazz = _env->FindClass(
            "androidx/appcompat/app/ClickMe");
    jmethodID AddButton = _env->GetMethodID(FService_clazz,  S("addColorpicker"),
                                            S("(Ljava/lang/String;II)V"));
    _env->CallVoidMethod(Menu,AddButton,text,id,slot);
}
void Toast(char *str){
    jstring text = _env->NewStringUTF(str);
    jclass FService_clazz = _env->FindClass( S("androidx/appcompat/app/OsirisService"));
    jmethodID AddButton = _env->GetMethodID(FService_clazz,  S("Toast"),
                                            S("(Ljava/lang/String;)V"));
    _env->CallVoidMethod(Menu,AddButton,text);
}
std::string callUrlJni(std::string link) {


    jstring string = _env->NewStringUTF(link.c_str());

    jclass setupClass = _env->FindClass("androidx/appcompat/app/OsirisService");
    jmethodID callUrlMethod = _env->GetStaticMethodID(setupClass, "callURL", "(Ljava/lang/String;)Ljava/lang/String;");
    jstring urlString = (jstring)_env->CallStaticObjectMethod(setupClass, callUrlMethod, string);

    if (!urlString)
        return "";

    const jclass stringClass = _env->GetObjectClass(urlString);
    const jmethodID getBytes = _env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) _env->CallObjectMethod(urlString, getBytes, _env->NewStringUTF("UTF-8"));

    size_t length = (size_t) _env->GetArrayLength(stringJbytes);
    jbyte* pBytes = _env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    _env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    _env->DeleteLocalRef(stringJbytes);
    _env->DeleteLocalRef(stringClass);

    _env->DeleteLocalRef(string);
    _env->DeleteLocalRef(setupClass);
    _env->DeleteLocalRef(urlString);

    return ret;
}

float getAlpha(int color) {

    jclass setupClass = _env->FindClass("androidx/appcompat/app/OsirisService");
    jmethodID callUrlMethod = _env->GetStaticMethodID(setupClass, "getAlpha", "(I)F");
    jfloat jfl = (jfloat)_env->CallStaticFloatMethod(setupClass, callUrlMethod, (jint) color);

    _env->DeleteLocalRef(setupClass);

    return jfl;
}
float getRed(int colorr) {
    jint color = colorr;

    jclass setupClass = _env->FindClass("androidx/appcompat/app/OsirisService");
    jmethodID callUrlMethod = _env->GetStaticMethodID(setupClass, "getRed", "(I)F");
    jfloat jfl = _env->CallStaticFloatMethod(setupClass, callUrlMethod, color);

    _env->DeleteLocalRef(setupClass);

    return jfl;
}
float getGreen(int color) {

    jclass setupClass = _env->FindClass("androidx/appcompat/app/OsirisService");
    jmethodID callUrlMethod = _env->GetStaticMethodID(setupClass, "getGreen", "(I)F");
    jfloat jfl = (jfloat)_env->CallStaticFloatMethod(setupClass, callUrlMethod, (jint) color);

    _env->DeleteLocalRef(setupClass);

    return jfl;
}
float getBlue(int color) {

    jclass setupClass = _env->FindClass("androidx/appcompat/app/OsirisService");
    jmethodID callUrlMethod = _env->GetStaticMethodID(setupClass, "getBlue", "(I)F");
    jfloat jfl = (jfloat)_env->CallStaticFloatMethod(setupClass, callUrlMethod, (jint) color);

    _env->DeleteLocalRef(setupClass);

    return jfl;
}


std::string getHwidJni() {

    jclass setupClass = _env->FindClass("androidx/appcompat/app/OsirisService");
    jmethodID callUrlMethod = _env->GetStaticMethodID(setupClass, "geth",
                                                      "()Ljava/lang/String;");
    jstring urlString = (jstring)_env->CallStaticObjectMethod(setupClass, callUrlMethod);

    if (!urlString)
        return "";

    const jclass stringClass = _env->GetObjectClass(urlString);
    const jmethodID getBytes = _env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) _env->CallObjectMethod(urlString, getBytes, _env->NewStringUTF("UTF-8"));

    size_t length = (size_t) _env->GetArrayLength(stringJbytes);
    jbyte* pBytes = _env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    _env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    _env->DeleteLocalRef(stringJbytes);
    _env->DeleteLocalRef(stringClass);

    _env->DeleteLocalRef(setupClass);
    _env->DeleteLocalRef(urlString);

    return ret;
}

uintptr_t string2Offset(const char *c) {
    int base = 16;
    // See if this function catches all possibilities.
    // If it doesn't, the function would have to be amended
    // whenever you add a combination of architecture and
    // compiler that is not yet addressed.
    static_assert(sizeof(uintptr_t) == sizeof(unsigned long)
                  || sizeof(uintptr_t) == sizeof(unsigned long long),
                  "Please add string to handle conversion for this architecture.");

    // Now choose the correct function ...
    if (sizeof(uintptr_t) == sizeof(unsigned long)) {
        return strtoul(c, nullptr, base);
    }

    // All other options exhausted, sizeof(uintptr_t) == sizeof(unsigned long long))
    return strtoull(c, nullptr, base);
}

void setDialog(jobject ctx, JNIEnv *env, const char *title, const char *msg){
    jclass Alert = env->FindClass(OBFUSCATE("android/app/AlertDialog$Builder"));
    jmethodID AlertCons = env->GetMethodID(Alert, OBFUSCATE("<init>"), OBFUSCATE("(Landroid/content/Context;)V"));

    jobject MainAlert = env->NewObject(Alert, AlertCons, ctx);

    jmethodID setTitle = env->GetMethodID(Alert, OBFUSCATE("setTitle"), OBFUSCATE("(Ljava/lang/CharSequence;)Landroid/app/AlertDialog$Builder;"));
    env->CallObjectMethod(MainAlert, setTitle, env->NewStringUTF(title));

    jmethodID setMsg = env->GetMethodID(Alert, OBFUSCATE("setMessage"), OBFUSCATE("(Ljava/lang/CharSequence;)Landroid/app/AlertDialog$Builder;"));
    env->CallObjectMethod(MainAlert, setMsg, env->NewStringUTF(msg));

    jmethodID setCa = env->GetMethodID(Alert, OBFUSCATE("setCancelable"), OBFUSCATE("(Z)Landroid/app/AlertDialog$Builder;"));
    env->CallObjectMethod(MainAlert, setCa, false);

    jmethodID setPB = env->GetMethodID(Alert, OBFUSCATE("setPositiveButton"), OBFUSCATE("(Ljava/lang/CharSequence;Landroid/content/DialogInterface$OnClickListener;)Landroid/app/AlertDialog$Builder;"));
    env->CallObjectMethod(MainAlert, setPB, env->NewStringUTF("Ok"), static_cast<jobject>(NULL));

    jmethodID create = env->GetMethodID(Alert, OBFUSCATE("create"), OBFUSCATE("()Landroid/app/AlertDialog;"));
    jobject creaetob = env->CallObjectMethod(MainAlert, create);

    jclass AlertN = env->FindClass(OBFUSCATE("android/app/AlertDialog"));

    jmethodID show = env->GetMethodID(AlertN, OBFUSCATE("show"), OBFUSCATE("()V"));
    env->CallVoidMethod(creaetob, show);
}

void Toast(JNIEnv *env, jobject thiz, const char *text, int length) {
    jstring jstr = env->NewStringUTF(text);
    jclass toast = env->FindClass(OBFUSCATE("android/widget/Toast"));
    jmethodID methodMakeText =env->GetStaticMethodID(toast,OBFUSCATE("makeText"),OBFUSCATE("(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;"));
    jobject toastobj = env->CallStaticObjectMethod(toast, methodMakeText,thiz, jstr, length);
    jmethodID methodShow = env->GetMethodID(toast, OBFUSCATE("show"), OBFUSCATE("()V"));
    env->CallVoidMethod(toastobj, methodShow);
}





#endif