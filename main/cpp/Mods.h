

#define targetLibName ("libil2cpp.so")

#include <unistd.h>
#include <pthread.h>
#include <android/native_window.h>
#include "ozModSharedLibraryManager.h"
#include "func.h"
bool fog, fpsbypass, wireframe, clrfilter;
ImColor clf, wfClr;
float wfLW = 1;
float gravity, frSpeed, bckSpeed, fov = 60, ortoSize = 3, nearCF = 1, camAspect = 1.889f, timescale = 1;
bool boolch = false;

ImVec4 colr = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

struct Vec2 //Эта структура отлично справляется с получением координат джойстика.  Тот Vector2 херня - он не работает!)
{
    float x, y;
};

/*
 * This method was decompiled and recreated from Unity Core
 * With IDA Pro PseudoCode.
 */
float UnityEngine_Vector3__Distance(
        Vector3 a,
        Vector3 b) {
    return sqrtf(
            (float)((float)((float)(a.y - b.y) * (float)(a.y - b.y))
                    + (float)((float)(a.x - b.x) * (float)(a.x - b.x)))
            + (float)((float)(a.z - b.z) * (float)(a.z - b.z)));
}

void (*IgnoreLayerCollision)(int layer1, int layer2, bool ignore);
void (*old_Transform_LookAt)(void *instance, void *target);

void (*set_useGravity)(void*, bool value);
void* (*il2cpp_resolve_icall_0)(const char *);
void* (*il2cpp_type_get_object)( void * type);
void* il2cpp_getMethod(const char *a1){
   void* result;
   result = il2cpp_resolve_icall_0(a1);
   return result;
}

/*
 * Method Signature of WorldToScreenPoint is: UnityEngine.Camera::WorldToScreenPoint_Injected(UnityEngine.Vector3&,UnityEngine.Camera/MonoOrStereoscopicEye,UnityEngine.Vector3&)
 *
 */
/*
 * This method was decompiled and recreated from Unity Core
 * With IDA Pro PseudoCode.
 */

Vector3 (*get_right)(void * t);
Vector3 (*get_pos)(void * t);
//Vector3 (*WorldToScreenPoint)(void*,Vector3 position);
void (*set_pos)(void * t, Vector3 w);
void (*set_enabled) (void* i,bool value);


void * eglHandle;
void *get_EGL() {
    void *mod = 0;
    while (!mod) {
        mod = dlopen("libEGL.so", RTLD_LAZY);
    }

    return mod;
}
void * glHandle;
void *get_GL() {
    void *mod = 0;
    while (!mod) {
        mod = dlopen("libGLESv2.so", RTLD_LAZY);
    }

    return mod;
}

EGLAPI EGLBoolean EGLAPIENTRY (*old_eglSwapBuffers) (EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY new_eglSwapBuffers (EGLDisplay dpy, EGLSurface surface) {



    UpdateInput();

    static bool WantTextInputLast = false;

    ImGuiIO& io = ImGui::GetIO();
    if (io.WantTextInput && !WantTextInputLast){
        diplayKeyboard(nullptr);
    }

    WantTextInputLast = io.WantTextInput;

    Render();

    if(!old_eglSwapBuffers(dpy, surface)){
        return false;
    }
    return true;
}
int32_t (*old_ANativeWindow_getWidth)(ANativeWindow* window);
int32_t new_ANativeWindow_getWidth(ANativeWindow* window){
    int32_t returnValue = old_ANativeWindow_getWidth(window);
    LOGI("I know that screen width is %d", returnValue);
    screenWidth = returnValue;
    return returnValue;
}

int32_t (*old_ANativeWindow_getHeight)(ANativeWindow* window);
int32_t new_ANativeWindow_getHeight(ANativeWindow* window){
    int32_t returnValue = old_ANativeWindow_getHeight(window);
    LOGI("I know that screen height is %d", returnValue);
    screenHeight = returnValue;
    return returnValue;
}

int32_t (*old_GetInt)();
int32_t GetInt(){
    return 10 + old_GetInt();//new value
}

void ImGuiImpl(bool swapbuffers = true){
    startTime = currentTimeInMilliseconds();
    screenWidth = 2340;
    screenHeight = 1080;
    setupGraphics( screenWidth, screenHeight);
    if(swapbuffers){
        auto swapBuffersSym = (const void*(*)(...))dlsym(eglHandle, "eglSwapBuffers");
        const char *dlsym_error = dlerror();
        if(dlsym_error){
            LOGE("Cannot load symbol 'eglSwapBuffers': %s", dlsym_error); //BlueStacks 5 issue
            return;
        }else{
            MSHookFunction(reinterpret_cast<void*>(swapBuffersSym), reinterpret_cast<void*>(new_eglSwapBuffers), reinterpret_cast<void**>(&old_eglSwapBuffers));
        }
    }

    MSHookFunction((void*)(ANativeWindow_getWidth), (void*)(new_ANativeWindow_getWidth), (void**)(&old_ANativeWindow_getWidth));
    MSHookFunction((void*)(ANativeWindow_getHeight), (void*)(new_ANativeWindow_getHeight), (void**)(&old_ANativeWindow_getHeight));

}

void* thread1(void* obj){
    LOGI("thread");
    //Initialize ESP Enemies.
    glHandle = get_GL();
    eglHandle = get_EGL();
    ImGuiImpl(true);
    int attempts = 1;
    bool tired = false;
    LOGI("thread2");
    do {
        sleep(1);
        if(attempts == 10){
       //     RequestToast((currentLang == 0 ? ("Ошибка при загрузке библиотеки игры. Функции могут не работать или работать неправильно.") : OBFUSCATE("Unable to load Game Library. Menu FeaturesStates can work incorectly.")));
        }
        if(attempts == 100) {
     //       RequestToast((currentLang == 0 ? (
       //             "Количество попыток загрузки библиотеки игры преввысило 100. Не вижу смысла ожидать.")
      //                                     : (
      //                      "Unable to load Game Library. Attempts is >= 100. Stopping Thread.")));

            pthread_exit(NULL);
        }
        attempts++;
    } while (!isLibraryLoaded(targetLibName));
    sleep(2); // Il2cpp can be not initialized
    LOGI("thread3");
    //RequestToast((currentLang == 0 ? ("Библиотека игры успешно загружена.") : ("Game Library Is Loaded.")));
    sleep(6);
    il2cpp_resolve_icall_0 = (void *(*)(const char *)) dlsym(get_il2cpp(), "il2cpp_resolve_icall");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        LOGE("Cannot load symbol 'il2cpp_resolve_icall_0': %s. Using offset instead", dlsym_error);
    }
    else {
        LOGI("thread4");
        inj();
    }
    return nullptr;
}

void ozME_StartThread(){

    pthread_t ptid;
    pthread_create(&ptid, NULL, thread1, NULL);
}

void InitMods(){
    LOGI("initmods");
    ozME_StartThread();
}