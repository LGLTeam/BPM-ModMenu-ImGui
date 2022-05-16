#include "obfuscator.hpp"
#include <GLES2/gl2.h>
#include "EGL/egl.h"
#include "font.h"

#include <android/asset_manager_jni.h>
JavaVM *publicJVM;
#include "sys/time.h"
void Render();
static void UpdateInput();
int inputChar = 0;
long long currentTimeInMilliseconds(){
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

bool setupGraphics(int width, int height);

int startTime, screenWidth, screenHeight;
int currentLang = 1;

jobject activity;
class ImDrawData;

void ImGui_ImplAndroidGLES2_RenderDrawLists(ImDrawData*data);

#include "GLES3/gl3.h"

#include <string>
#include <android/input.h>
#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,"ozMod", __VA_ARGS__))
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,"ozMod",__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,"ozMod",__VA_ARGS__)
#define  LOGDE(...)  __android_log_print(ANDROID_LOG_DEFAULT,"ozMod",__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,"ozMod",__VA_ARGS__)
#define  LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,"ozMod",__VA_ARGS__)
#define  LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,"ozMod",__VA_ARGS__)
#define  LOGU(...)  __android_log_print(ANDROID_LOG_UNKNOWN,"ozMod",__VA_ARGS__)
#define  LOGS(...)  __android_log_print(ANDROID_LOG_SLIENT,"ozMod",__VA_ARGS__)
static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
                                                    = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}
bool HandleInputEvent(JNIEnv *jenv,
int motionEvent, int x, int y,
int p);
jobject UnityPlayer_CurrentActivity_fid;
void diplayKeyboard(JNIEnv* newEnv) {
    LOGI("Display keybrd");
    JNIEnv* env = NULL;
    if(newEnv != nullptr){
        env = newEnv;
    } else {
        jint jni_return = publicJVM->GetEnv((void**)&env, JNI_VERSION_1_6);
        if (jni_return == JNI_ERR){
            return;
        }
        jni_return = publicJVM->AttachCurrentThread(&env, NULL);
        if (jni_return != JNI_OK){
            return;
        }
    }

    jclass aycls = env->FindClass("android/app/Activity");
    jmethodID gss = env->GetMethodID(aycls, "getSystemService",
                                     "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject ss = env->CallObjectMethod(UnityPlayer_CurrentActivity_fid, gss, env->NewStringUTF("input_method"));
    jclass imcls = env->FindClass("android/view/inputmethod/InputMethodManager");
    jmethodID tgsifm = env->GetMethodID(imcls, "toggleSoftInput", "(II)V");
    env->CallVoidMethod(ss, tgsifm, 2,0);
}
#include <vector>
#include "Substrate/CydiaSubstrate.h"
#include "imgui_impl_android.h"
#include "Mods.h"

static jobject getGlobalContext(JNIEnv *env)
{
    jclass activityThread = env->FindClass("android/app/ActivityThread"); //Don't care about that error. It didn't find class because its hidden android core class.
    jmethodID currentActivityThread = env->GetStaticMethodID(activityThread, ozObfuscate("currentActivityThread"), ozObfuscate("()Landroid/app/ActivityThread;"));
    jobject at = env->CallStaticObjectMethod(activityThread, currentActivityThread);

    jmethodID getApplication = env->GetMethodID(activityThread, ozObfuscate("getApplication"), ozObfuscate("()Landroid/app/Application;"));
    jobject context = env->CallObjectMethod(at, getApplication);
    return context;
}

 bool m_needClearMousePos;
typedef enum {
    TOUCH_ACTION_DOWN = 0,
    TOUCH_ACTION_UP,
    TOUCH_ACTION_MOVE,
    TOUCH_ACTION_COUNT
} TOUCH_ACTION;

typedef struct {
    TOUCH_ACTION action;
    float x;
    float y;
    int pointers;
    float y_velocity;
    float x_velocity;
}TOUCH_EVENT;
 TOUCH_EVENT g_LastTouchEvent;
static void UpdateInput() {
    // Update buttons
    ImGuiIO &io = ImGui::GetIO();

    // Mouse buttons: 0=left, 1=right, 2=middle + extras. ImGui itself mostly only uses left button
    // (BeginPopupContext** are using right button). Others buttons allows us to track if the mouse
    // is being used by your application + available to user as a convenience via IsMouse** API.
    // TOUCH_ACTION_MOVE -> MousePos
    // TOUCH_ACTION_DOWN -> MouseDown[0] true, left button
    // TOUCH_ACTION_UP -> MouseDown[0] false. left button
    // TOUCH_ACTION_POINTER_DOWN -> multi finger as scroll, set MouseWheel. MouseWheelH not used
    if (TOUCH_ACTION_DOWN <= g_LastTouchEvent.action &&
        g_LastTouchEvent.action <= TOUCH_ACTION_MOVE) {

        io.MousePos.x = g_LastTouchEvent.x;
        io.MousePos.y = g_LastTouchEvent.y;
    }
    switch (g_LastTouchEvent.action) {
        case TOUCH_ACTION_MOVE:
            if (g_LastTouchEvent.pointers > 1) {
                io.MouseWheel = g_LastTouchEvent.y_velocity;
                io.MouseDown[0] = false;
            }
            else {
                io.MouseWheel = 0;
            }
            break;
        case TOUCH_ACTION_DOWN:
            io.MouseDown[0] = true;
            break;
        case TOUCH_ACTION_UP:
            io.MouseDown[0] = false;
            //g_KeyEventQueues[event_key_code].push(event_action);
            break;
        default:
            break;
    }
}

bool    HandleInputEvent(JNIEnv *jenv,
                                                                 int motionEvent, int x, int y,
                                                                 int p) {
    // Need to make sure the coordinate (x,y) here is relative to the top left of the surface
    // This is how the behavior of GLSurfaceView.onTouchEvent
    // If the coordinate is obtained in a different way. This should be adjusted accordingly
    if (motionEvent < TOUCH_ACTION_COUNT) {
        float velocity_y = (float)((float)y - g_LastTouchEvent.y) / 100.f;
        g_LastTouchEvent = {.action = (TOUCH_ACTION) motionEvent, .x = static_cast<float>(x), .y = static_cast<float>(y), .pointers = p, .y_velocity = velocity_y};
    }
    else {
        //LOGE("invalid action index: %d", motionEvent);
    }
    //LOGI("x: %d y: %d", x, y);
    return true;
}

ImVec4 imClearColor;
bool showTestWindow;
bool showAnotherWindow;

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI(ozObfuscate("GL %s = %s\n"), name, v);
}
GLuint gProgram;
GLuint gvPositionHandle;
GLuint vbo;
const GLfloat gTriangleVertices[] = { 0.0f, 1.0f, -1.0f, -1.0f,
                                      1.0f, -1.0f };
void ozTheme()
{
    ImGuiStyle* style = &ImGui::GetStyle();

    style->WindowBorderSize = 0;
    style->WindowRounding = 0;
    style->WindowTitleAlign = ImVec2(0.5, 0.5);
    style->WindowPadding = ImVec2(0,0);
    style->WindowMinSize = ImVec2(100, 100);
    style->ScrollbarSize = 10;
    style->Colors[ImGuiCol_Border] = ImVec4(0, 0, 0, 1.0f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(1.0f, 0.1f, 0.1f, 1.0f);

    style->Colors[ImGuiCol_CheckMark] = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
   // style->FramePadding = ImVec2(8, 6);
    style->Colors[ImGuiCol_Button] = ImColor(22,26,37, 255);
    style->Colors[ImGuiCol_ButtonActive] = ImColor(46,54,67, 255);
    style->Colors[ImGuiCol_ButtonHovered] = ImColor(22,26,37, 255);
    style->Colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    style->Colors[ImGuiCol_TitleBgActive]          = ImVec4(75.0f/255.0f, 0.0f, 130.0f/255.0f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    style->Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
    style->Colors[ImGuiCol_SeparatorActive] = ImColor(76, 76, 76, 255);
    style->Colors[ImGuiCol_SeparatorHovered] = ImColor(76, 76, 76, 255);

    style->Colors[ImGuiCol_FrameBg] = ImColor(28,34,46, 255);
    style->Colors[ImGuiCol_FrameBgActive] = ImColor(28,34,46, 255);
    style->Colors[ImGuiCol_FrameBgHovered] = ImColor(28,34,46, 255);
    //style->Colors[ImGuiCol_ScrollbarBg] = ImColor(37, 36, 37, 255);
    style->Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 0);
    style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 255);
    style->Colors[ImGuiCol_HeaderHovered] = ImColor(46, 46, 46, 255);
}

// Unfortunately, the native KeyEvent implementation has no getUnicodeChar() function.
// Therefore, we implement the processing of KeyEvents in MainActivity.kt and poll
// the resulting Unicode characters here via JNI and send them to Dear ImGui.
static int UpdateKeyboardInput(JNIEnv*java_env)
{
    // Send the actual characters to Dear ImGui
    ImGuiIO& io = ImGui::GetIO();

    if (inputChar != 0){
        io.AddInputCharacter(inputChar);
        inputChar = 0;
    }
    return 0;
}
#include "tabs.h"
#include "ESP/Esp.h"

ImFont* BigText;
ImFont* Text;

bool setupGraphics(int w, int h) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ozTheme();
    ImGui::GetStyle().WindowRounding = 3;
    ImGui::GetStyle().Alpha = 1;
    ImGui::GetStyle().WindowMinSize = ImVec2(100,100);
    io.BackendPlatformName = ("imgui_impl_android");
    // Disable loading/saving of .ini file from disk.
    // FIXME: Consider using LoadIniSettingsFromMemory() / SaveIniSettingsToMemory() to save in appropriate location for Android.
    io.IniFilename =  nullptr;
    ImGui_ImplAndroidGLES2_Init();
    // Setup keyboard input
    io.KeyMap[ImGuiKey_Tab] = AKEYCODE_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = AKEYCODE_DPAD_LEFT;   // also covers physical keyboard arrow key
    io.KeyMap[ImGuiKey_RightArrow] = AKEYCODE_DPAD_RIGHT; // also covers physical keyboard arrow key
    io.KeyMap[ImGuiKey_UpArrow] = AKEYCODE_DPAD_UP;       // also covers physical keyboard arrow key
    io.KeyMap[ImGuiKey_DownArrow] = AKEYCODE_DPAD_DOWN;   // also covers physical keyboard arrow key
    io.KeyMap[ImGuiKey_PageUp] = AKEYCODE_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = AKEYCODE_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = AKEYCODE_MOVE_HOME;
    io.KeyMap[ImGuiKey_End] = AKEYCODE_MOVE_END;
    io.KeyMap[ImGuiKey_Insert] = AKEYCODE_INSERT;

    io.KeyMap[ImGuiKey_Backspace] = 67;
    io.KeyMap[ImGuiKey_Space] = AKEYCODE_SPACE;
    io.KeyMap[ImGuiKey_Enter] = 66;
    io.KeyMap[ImGuiKey_Escape] = AKEYCODE_ESCAPE;
    io.KeyMap[ImGuiKey_KeyPadEnter] = AKEYCODE_NUMPAD_ENTER;
    io.KeyMap[ImGuiKey_A] = AKEYCODE_A;
    io.KeyMap[ImGuiKey_C] = AKEYCODE_C;
    io.KeyMap[ImGuiKey_V] = AKEYCODE_V;
    io.KeyMap[ImGuiKey_X] = AKEYCODE_X;
    io.KeyMap[ImGuiKey_Y] = AKEYCODE_Y;
    io.KeyMap[ImGuiKey_Z] = AKEYCODE_Z;

    io.Fonts->ClearFonts();

    ImGui::GetStyle().ScaleAllSizes(3);
    ImFontConfig font_cfg;
    font_cfg.SizePixels = 22.0f;
    font_cfg.GlyphRanges = io.Fonts->GetGlyphRangesCyrillic();
    //io.Fonts->AddFontDefault(&font_cfg);

    io.Fonts->AddFontFromMemoryTTF(&Font, sizeof Font, 22.0f,&font_cfg); //стандартный шрифт

    BigText = io.Fonts->AddFontFromMemoryTTF(&Font, sizeof Font, 40,&font_cfg); //стандартный шрифт
    //Logo = io.Fonts->AddFontFromMemoryTTF(&Font, sizeof Font, 18); //шрифт лого



    //io.Fonts->AddFontFromFileTTF("DroidSans.ttf", 13.0f);

    //setup GL drawing
    glGenBuffers(1, &vbo);
    checkGlError("glGenBuffer");

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    checkGlError("glBindBuffer");

    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(GLfloat), gTriangleVertices, GL_STATIC_DRAW);
    checkGlError("glBufferData");

    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)nullptr);
    checkGlError("glVertexAttribPointer");

    glEnableVertexAttribArray(gvPositionHandle);
    checkGlError("glVertexAttribArray");

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    checkGlError("glBindBuffer");

    glViewport(0,0,w,h);

    return true;
}




void button(const char* label, int& currentTab, int newTab, ImVec2 size)
{
    if (ImGui::Button(label, size))
        currentTab = newTab;
}

void line(int newId)
{
    std::string id = ("imguipp_line_" + std::to_string(newId));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
    {
        ImGui::BeginChild(id.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 1), false);
        ImGui::Separator();
        ImGui::EndChild();
    }
    ImGui::PopStyleColor();
}
void center_text(const char* text, int lineId , bool separator)
{
    if (text == nullptr)
        return;

    ImGui::Spacing();
    ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
    ImGui::Text("%s", text);
    ImGui::Spacing();

    if (true == separator)
        line(lineId);
}

void center_text_ex(const char* text, float width_available, int lineId,  bool separator)
{
    if (text == nullptr)
        return;

    ImGui::Spacing();
    ImGui::SameLine((width_available / 2) - (ImGui::CalcTextSize(text).x / 2));
    ImGui::Text("%s", text);
    ImGui::Spacing();

    if (true == separator)
        line(lineId);
}

namespace other
{
    float get_window_size_x()
    {
        return ImGui::GetWindowSize().x;
    }

    float get_window_size_y()
    {
        return ImGui::GetWindowSize().y;
    }

    ImVec2 get_window_size()
    {
        return ImGui::GetWindowSize();
    }

}

ImVec4 to_vec4(float r, float g, float b, float a)
{
    return ImVec4(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
}
static bool show_app_console = false;
static bool show_app_log = false;
static bool WantTextInputLast = false;
bool show_paint = false;
bool showStyleEditor;
#define GAME_NAME "Granny 3"
#define GAME_VER "1.1.1"
class g_FontTexture;
float testCol, testCol2, testCol3,testCol4;

void chkBoxHandler(int i , bool a){
       if(IgnoreLayerCollision){
           IgnoreLayerCollision(0,8, a);
       }

    "Жмот";
}

void DrawContentFor(int i){

switch(i){
    case 0:
        if(ImGui::SliderFloat("Time Scale 1", &timescale, 0, 5)){
            set_timeScale(timescale);
        }
        if(ImGui::Checkbox("Enable",&boolch))
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorPicker3("clear color", (float*)&colr); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        break;

}


}
void cmdExecuteSystem(const char* input){
    printf("%s", input);
}
bool drawBehindMenu = true;
//btw void* and void * does not have diffrence.
ImDrawList* getDrawList(){
    ImDrawList *drawList;
    if(drawBehindMenu){
        drawList = ImGui::GetBackgroundDrawList();
    } else {
        drawList = ImGui::GetForegroundDrawList(ImGui::GetMainViewport());
    }
    return drawList;
}
//Render the menu
bool opened = false;


ImVec4 esp_color = ImVec4(1, 1, 1, 1.00f);
ImVec4 glow_color = ImVec4(1, 1, 1, 1.00f);
ImVec4 circleColor = ImVec4(1, 1, 1, 1.00f);
float rel_anim = 1;

bool menuOpen = true;
bool openedd;
bool vrk = true;
bool aimm = false;

ImVec2 world2screen_c(Vector3 pos, bool &checker) {
    Vector3 worldPoint = world2screen(camera,pos,2);
    checker = worldPoint.z > 1;
    return ImVec2(worldPoint.x,screenHeight - worldPoint.y);
}

ImVec2 world2screen_i(Vector3 pos) {
    Vector3 worldPoint = world2screen(camera,pos,2);
    return ImVec2(worldPoint.x,screenHeight - worldPoint.y);
}

Vector2 ImV_to_UV(ImVec2 v) {
    return Vector2(v.x,v.y);
};

ImVec2 UV_to_ImV(Vector2 v) {
    return ImVec2(v.x,v.y);
};

void Draw3dBox(Vector3 pos, float angle, Vector3 scale, ImColor color,float stroke = 2, float outline_size = 0, float cornersize = 50) {
    cornersize /= 10;

    bool checker;
    world2screen_c(pos,checker);

    if (!checker) {
        return;
    }

    Vector3 scaleRot = Vector3(sin((double) angle *(PI *2) /(double) 360)*(scale.x) /2 ,scale.y/2,cos((double) angle *(PI *2) /(double) 360)*(scale.z) /2 );


        scaleRot = Vector3(sin((double) (angle + 0) *(PI *2) /(double) 360)*(scale.x) /2 ,scale.y/2,cos((double) (angle + 0) *(PI *2) /(double) 360)*(scale.z) /2 );
        auto down_leftup = ImVec2(world2screen_i(Vector3(pos.x + scaleRot.x, pos.y - scaleRot.y, pos.z + scaleRot.z)));

        scaleRot = Vector3(sin((double) (angle + 90) *(PI *2) /(double) 360)*(scale.x) /2 ,scale.y/2,cos((double) (angle + 90) *(PI *2) /(double) 360)*(scale.z) /2 );
        auto down_rightup = ImVec2(world2screen_i(Vector3(pos.x + scaleRot.x, pos.y - scaleRot.y, pos.z + scaleRot.z)));

        scaleRot = Vector3(sin((double) (angle + 270) *(PI *2) /(double) 360)*(scale.x) /2 ,scale.y/2,cos((double) (angle + 270) *(PI *2) /(double) 360)*(scale.z) /2 );
        auto down_leftbottom = ImVec2(world2screen_i(Vector3(pos.x + scaleRot.x, pos.y - scaleRot.y, pos.z + scaleRot.z)));

        scaleRot = Vector3(sin((double) (angle + 180) *(PI *2) /(double) 360)*(scale.x) /2 ,scale.y/2,cos((double) (angle + 180) *(PI *2) /(double) 360)*(scale.z) /2 );
        auto down_rightbottom = ImVec2(world2screen_i(Vector3(pos.x + scaleRot.x, pos.y - scaleRot.y, pos.z + scaleRot.z)));



        scaleRot = Vector3(sin((double) (angle + 0) *(PI *2) /(double) 360)*(scale.x) /2 ,scale.y/2,cos((double) (angle + 0) *(PI *2) /(double) 360)*(scale.z) /2 );
        auto top_leftup = ImVec2(world2screen_i(Vector3(pos.x + scaleRot.x, pos.y + scaleRot.y, pos.z + scaleRot.z)));

        scaleRot = Vector3(sin((double) (angle + 90) *(PI *2) /(double) 360)*(scale.x) /2 ,scale.y/2,cos((double) (angle + 90) *(PI *2) /(double) 360)*(scale.z) /2 );
        auto top_rightup = ImVec2(world2screen_i(Vector3(pos.x + scaleRot.x, pos.y + scaleRot.y, pos.z + scaleRot.z)));

        scaleRot = Vector3(sin((double) (angle + 270) *(PI *2) /(double) 360)*(scale.x) /2 ,scale.y/2,cos((double) (angle + 270) *(PI *2) /(double) 360)*(scale.z) /2 );
        auto top_leftbottom = ImVec2(world2screen_i(Vector3(pos.x + scaleRot.x, pos.y + scaleRot.y, pos.z + scaleRot.z)));

        scaleRot = Vector3(sin((double) (angle + 180) *(PI *2) /(double) 360)*(scale.x) /2 ,scale.y/2,cos((double) (angle + 180) *(PI *2) /(double) 360)*(scale.z) /2 );
        auto top_rightbottom = ImVec2(world2screen_i(Vector3(pos.x + scaleRot.x, pos.y + scaleRot.y, pos.z + scaleRot.z)));

        //down

        auto old_col = color;

                stroke += outline_size;
                color = ImColor(0,0,0,255);

            //--------------------------------------//
            //down_leftup - down_rightup
            ImGui::GetBackgroundDrawList()->AddLine(down_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftup),ImV_to_UV(down_rightup),0.2)),color,stroke);
            ImGui::GetBackgroundDrawList()->AddLine(down_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightup),ImV_to_UV(down_leftup),0.2)),color,stroke);


            //ImGui::GetBackgroundDrawList()->AddLine(down_rightup,down_leftup,color,stroke);

            //down_rightup - down_rightbottom
    ImGui::GetBackgroundDrawList()->AddLine(down_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightup),ImV_to_UV(down_rightbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(down_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightbottom),ImV_to_UV(down_rightup),0.2)),color,stroke);



    //down_rightbottom - down_leftbottom
    ImGui::GetBackgroundDrawList()->AddLine(down_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightbottom),ImV_to_UV(down_leftbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(down_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftbottom),ImV_to_UV(down_rightbottom),0.2)),color,stroke);


    //down_leftbottom - down_leftup
    ImGui::GetBackgroundDrawList()->AddLine(down_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftbottom),ImV_to_UV(down_leftup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(down_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftup),ImV_to_UV(down_leftbottom),0.2)),color,stroke);


    //top

            //top_leftup - top_rightup
    ImGui::GetBackgroundDrawList()->AddLine(top_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftup),ImV_to_UV(top_rightup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightup),ImV_to_UV(top_leftup),0.2)),color,stroke);


    //top_rightup - top_rightbottom
    ImGui::GetBackgroundDrawList()->AddLine(top_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightup),ImV_to_UV(top_rightbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightbottom),ImV_to_UV(top_rightup),0.2)),color,stroke);


    //top_rightbottom - top_leftbottom
    ImGui::GetBackgroundDrawList()->AddLine(top_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightbottom),ImV_to_UV(top_leftbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftbottom),ImV_to_UV(top_rightbottom),0.2)),color,stroke);


    //top_leftbottom - top_leftup
    ImGui::GetBackgroundDrawList()->AddLine(top_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftbottom),ImV_to_UV(top_leftup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftup),ImV_to_UV(top_leftbottom),0.2)),color,stroke);


    //down - top

            //down_leftup - top_leftup
    ImGui::GetBackgroundDrawList()->AddLine(down_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftup),ImV_to_UV(top_leftup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftup),ImV_to_UV(down_leftup),0.2)),color,stroke);


    //down_rightup - top_rightup
    ImGui::GetBackgroundDrawList()->AddLine(down_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightup),ImV_to_UV(top_rightup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightup),ImV_to_UV(down_rightup),0.2)),color,stroke);

            //down_rightbottom - top_rightbottom
    ImGui::GetBackgroundDrawList()->AddLine(down_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightbottom),ImV_to_UV(top_rightbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightbottom),ImV_to_UV(down_rightbottom),0.2)),color,stroke);

            //down_leftbottom - top_leftbottom
    ImGui::GetBackgroundDrawList()->AddLine(down_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftbottom),ImV_to_UV(top_leftbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftbottom),ImV_to_UV(down_leftbottom),0.2)),color,stroke);

        //--------------------------------------//

        stroke = outline_size;
        color = old_col;

        //--------------------------------------//

    //down_leftup - down_rightup
    ImGui::GetBackgroundDrawList()->AddLine(down_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftup),ImV_to_UV(down_rightup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(down_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightup),ImV_to_UV(down_leftup),0.2)),color,stroke);


    //ImGui::GetBackgroundDrawList()->AddLine(down_rightup,down_leftup,color,stroke);

    //down_rightup - down_rightbottom
    ImGui::GetBackgroundDrawList()->AddLine(down_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightup),ImV_to_UV(down_rightbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(down_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightbottom),ImV_to_UV(down_rightup),0.2)),color,stroke);



    //down_rightbottom - down_leftbottom
    ImGui::GetBackgroundDrawList()->AddLine(down_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightbottom),ImV_to_UV(down_leftbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(down_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftbottom),ImV_to_UV(down_rightbottom),0.2)),color,stroke);


    //down_leftbottom - down_leftup
    ImGui::GetBackgroundDrawList()->AddLine(down_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftbottom),ImV_to_UV(down_leftup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(down_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftup),ImV_to_UV(down_leftbottom),0.2)),color,stroke);


    //top

    //top_leftup - top_rightup
    ImGui::GetBackgroundDrawList()->AddLine(top_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftup),ImV_to_UV(top_rightup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightup),ImV_to_UV(top_leftup),0.2)),color,stroke);


    //top_rightup - top_rightbottom
    ImGui::GetBackgroundDrawList()->AddLine(top_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightup),ImV_to_UV(top_rightbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightbottom),ImV_to_UV(top_rightup),0.2)),color,stroke);


    //top_rightbottom - top_leftbottom
    ImGui::GetBackgroundDrawList()->AddLine(top_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightbottom),ImV_to_UV(top_leftbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftbottom),ImV_to_UV(top_rightbottom),0.2)),color,stroke);


    //top_leftbottom - top_leftup
    ImGui::GetBackgroundDrawList()->AddLine(top_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftbottom),ImV_to_UV(top_leftup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftup),ImV_to_UV(top_leftbottom),0.2)),color,stroke);


    //down - top

    //down_leftup - top_leftup
    ImGui::GetBackgroundDrawList()->AddLine(down_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftup),ImV_to_UV(top_leftup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftup),ImV_to_UV(down_leftup),0.2)),color,stroke);


    //down_rightup - top_rightup
    ImGui::GetBackgroundDrawList()->AddLine(down_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightup),ImV_to_UV(top_rightup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightup),ImV_to_UV(down_rightup),0.2)),color,stroke);

    //down_rightbottom - top_rightbottom
    ImGui::GetBackgroundDrawList()->AddLine(down_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightbottom),ImV_to_UV(top_rightbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightbottom),ImV_to_UV(down_rightbottom),0.2)),color,stroke);

    //down_leftbottom - top_leftbottom
    ImGui::GetBackgroundDrawList()->AddLine(down_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftbottom),ImV_to_UV(top_leftbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftbottom),ImV_to_UV(down_leftbottom),0.2)),color,stroke);


        //--------------------------------------//



}


void Draw3dBox_o(Vector2 pos, Vector3 scale, ImColor color,float stroke = 2, float outline_size = 0, float cornersize = 50) {
    cornersize /= 10;

   auto down_leftup = ImVec2(pos.x - scale.x / 2 - scale.z/8, pos.y + scale.y/2 - scale.z/4);

   auto down_rightup = ImVec2(pos.x + scale.x / 2 - scale.z/8, pos.y + scale.y/2 - scale.z/4);

    auto down_leftbottom = ImVec2(pos.x - scale.x / 2 + scale.z/8, pos.y + scale.y/2 + scale.z/4);

   auto down_rightbottom = ImVec2(pos.x + scale.x / 2 + scale.z/8, pos.y + scale.y/2 + scale.z/4);



    auto top_leftup = ImVec2(pos.x - scale.x / 2 - scale.z/8, pos.y - scale.y/2 - scale.z/4);

    auto top_rightup = ImVec2(pos.x + scale.x / 2 - scale.z/8, pos.y - scale.y/2 - scale.z/4);

    auto top_leftbottom = ImVec2(pos.x - scale.x / 2 + scale.z/8, pos.y - scale.y/2 + scale.z/4);

    auto top_rightbottom = ImVec2(pos.x + scale.x / 2 + scale.z/8, pos.y - scale.y/2 + scale.z/4);

    //down

    auto old_col = color;

    stroke += outline_size;
    color = ImColor(0,0,0,255);

    //--------------------------------------//
    //down_leftup - down_rightup
    ImGui::GetBackgroundDrawList()->AddLine(down_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftup),ImV_to_UV(down_rightup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(down_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightup),ImV_to_UV(down_leftup),0.2)),color,stroke);


    //ImGui::GetBackgroundDrawList()->AddLine(down_rightup,down_leftup,color,stroke);

    //down_rightup - down_rightbottom
    ImGui::GetBackgroundDrawList()->AddLine(down_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightup),ImV_to_UV(down_rightbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(down_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightbottom),ImV_to_UV(down_rightup),0.2)),color,stroke);



    //down_rightbottom - down_leftbottom
    ImGui::GetBackgroundDrawList()->AddLine(down_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightbottom),ImV_to_UV(down_leftbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(down_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftbottom),ImV_to_UV(down_rightbottom),0.2)),color,stroke);


    //down_leftbottom - down_leftup
    ImGui::GetBackgroundDrawList()->AddLine(down_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftbottom),ImV_to_UV(down_leftup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(down_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftup),ImV_to_UV(down_leftbottom),0.2)),color,stroke);


    //top

    //top_leftup - top_rightup
    ImGui::GetBackgroundDrawList()->AddLine(top_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftup),ImV_to_UV(top_rightup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightup),ImV_to_UV(top_leftup),0.2)),color,stroke);


    //top_rightup - top_rightbottom
    ImGui::GetBackgroundDrawList()->AddLine(top_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightup),ImV_to_UV(top_rightbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightbottom),ImV_to_UV(top_rightup),0.2)),color,stroke);


    //top_rightbottom - top_leftbottom
    ImGui::GetBackgroundDrawList()->AddLine(top_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightbottom),ImV_to_UV(top_leftbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftbottom),ImV_to_UV(top_rightbottom),0.2)),color,stroke);


    //top_leftbottom - top_leftup
    ImGui::GetBackgroundDrawList()->AddLine(top_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftbottom),ImV_to_UV(top_leftup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftup),ImV_to_UV(top_leftbottom),0.2)),color,stroke);


    //down - top

    //down_leftup - top_leftup
    ImGui::GetBackgroundDrawList()->AddLine(down_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftup),ImV_to_UV(top_leftup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftup),ImV_to_UV(down_leftup),0.2)),color,stroke);


    //down_rightup - top_rightup
    ImGui::GetBackgroundDrawList()->AddLine(down_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightup),ImV_to_UV(top_rightup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightup),ImV_to_UV(down_rightup),0.2)),color,stroke);

    //down_rightbottom - top_rightbottom
    ImGui::GetBackgroundDrawList()->AddLine(down_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightbottom),ImV_to_UV(top_rightbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightbottom),ImV_to_UV(down_rightbottom),0.2)),color,stroke);

    //down_leftbottom - top_leftbottom
    ImGui::GetBackgroundDrawList()->AddLine(down_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftbottom),ImV_to_UV(top_leftbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftbottom),ImV_to_UV(down_leftbottom),0.2)),color,stroke);

    //--------------------------------------//

    stroke = outline_size;
    color = old_col;

    //--------------------------------------//

    //down_leftup - down_rightup
    ImGui::GetBackgroundDrawList()->AddLine(down_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftup),ImV_to_UV(down_rightup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(down_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightup),ImV_to_UV(down_leftup),0.2)),color,stroke);


    //ImGui::GetBackgroundDrawList()->AddLine(down_rightup,down_leftup,color,stroke);

    //down_rightup - down_rightbottom
    ImGui::GetBackgroundDrawList()->AddLine(down_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightup),ImV_to_UV(down_rightbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(down_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightbottom),ImV_to_UV(down_rightup),0.2)),color,stroke);



    //down_rightbottom - down_leftbottom
    ImGui::GetBackgroundDrawList()->AddLine(down_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightbottom),ImV_to_UV(down_leftbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(down_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftbottom),ImV_to_UV(down_rightbottom),0.2)),color,stroke);


    //down_leftbottom - down_leftup
    ImGui::GetBackgroundDrawList()->AddLine(down_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftbottom),ImV_to_UV(down_leftup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(down_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftup),ImV_to_UV(down_leftbottom),0.2)),color,stroke);


    //top

    //top_leftup - top_rightup
    ImGui::GetBackgroundDrawList()->AddLine(top_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftup),ImV_to_UV(top_rightup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightup),ImV_to_UV(top_leftup),0.2)),color,stroke);


    //top_rightup - top_rightbottom
    ImGui::GetBackgroundDrawList()->AddLine(top_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightup),ImV_to_UV(top_rightbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightbottom),ImV_to_UV(top_rightup),0.2)),color,stroke);


    //top_rightbottom - top_leftbottom
    ImGui::GetBackgroundDrawList()->AddLine(top_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightbottom),ImV_to_UV(top_leftbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftbottom),ImV_to_UV(top_rightbottom),0.2)),color,stroke);


    //top_leftbottom - top_leftup
    ImGui::GetBackgroundDrawList()->AddLine(top_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftbottom),ImV_to_UV(top_leftup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftup),ImV_to_UV(top_leftbottom),0.2)),color,stroke);


    //down - top

    //down_leftup - top_leftup
    ImGui::GetBackgroundDrawList()->AddLine(down_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftup),ImV_to_UV(top_leftup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_leftup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftup),ImV_to_UV(down_leftup),0.2)),color,stroke);


    //down_rightup - top_rightup
    ImGui::GetBackgroundDrawList()->AddLine(down_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightup),ImV_to_UV(top_rightup),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_rightup,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightup),ImV_to_UV(down_rightup),0.2)),color,stroke);

    //down_rightbottom - top_rightbottom
    ImGui::GetBackgroundDrawList()->AddLine(down_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_rightbottom),ImV_to_UV(top_rightbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_rightbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_rightbottom),ImV_to_UV(down_rightbottom),0.2)),color,stroke);

    //down_leftbottom - top_leftbottom
    ImGui::GetBackgroundDrawList()->AddLine(down_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(down_leftbottom),ImV_to_UV(top_leftbottom),0.2)),color,stroke);
    ImGui::GetBackgroundDrawList()->AddLine(top_leftbottom,UV_to_ImV(Vector2::Lerp(ImV_to_UV(top_leftbottom),ImV_to_UV(down_leftbottom),0.2)),color,stroke);


    //--------------------------------------//



}

void AddColorPicker (const char*name, ImVec4 &color) {
    ImGuiColorEditFlags misc_flags = ImGuiColorEditFlags_AlphaPreview;
    static ImVec4 backup_color;

    bool open_popup = ImGui::ColorButton((std::string(name) + "##3b").c_str(), color, misc_flags);
    ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
    //open_popup |= ImGui::Button("Palette");
    if (open_popup)
    {
        ImGui::OpenPopup(name);
        backup_color = color;
    }
    if (ImGui::BeginPopup(name))
    {
        ImGui::Text("Select Color");
        ImGui::Separator();
        ImGui::ColorPicker4("##picker", (float*)&color, misc_flags | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
        ImGui::SameLine();

        ImGui::BeginGroup(); // Lock X position
        ImGui::Text("Current");
        ImGui::ColorButton("##current", color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40));
        ImGui::Text("Previous");
        if (ImGui::ColorButton("##previous", backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40)))
            color = backup_color;
        ImGui::EndGroup();
        ImGui::EndPopup();
    }
}

static int td = 0;

void Render(){


    //ImGui::PushFont(Logo);

    ImGuiIO& io = ImGui::GetIO();
    if(!ImGui::get_cmdExecutorHaveVal()){
        ImGui::set_cmdExecutor(&cmdExecuteSystem);
    }
    //Creating A new ImGui Frame for our backend
    ImGui_ImplAndroidGLES2_NewFrame(screenWidth, screenHeight, currentTimeInMilliseconds()-startTime);

    {
        ImGui::SetNextWindowSize(ImVec2(100, 100));

        ImGui::Begin(("open"), &openedd, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
        //ImGui::SetNextWindowPos(ImVec2(screenWidth/2, 10));
        //ImGui::SetNextWindowSize(ImVec2(300, 20));



        if (ImGui::Button("OPEN",ImVec2(100,100))) {
            menuOpen = !menuOpen;
        }
        ImGui::End();
    }



    if (menuOpen) {

        ImGui::SetNextWindowSize(ImVec2(800, 700));

        ImGui::Begin(("Ваше окно"), &opened,
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);

        ImGui::SetNextWindowBgAlpha(0);

        ImGuiWindow *window = ImGui::GetCurrentWindow();

        ImGui::SetNextWindowPos(ImVec2(0, 0));



        ImGui::SetCursorPos(ImVec2(36, 22));

        //if (ImGui::Button(("Some text"), ImVec2(50, 20))) {

        //}

        //ImGui::SetCursorPos(ImVec2(36, 50));

        //static bool test = false;

        //ImGui::Checkbox("Text", &test);

        //ImGui::SetCursorPos(ImVec2(36, 100));
        //ImGui::Text("Text");


        ImVec2 pos = ImGui::GetWindowPos();
        window->DrawList->AddRectFilled(ImVec2(0 + pos.x, 0 + pos.y),
                                        ImVec2(800 + pos.x, 80 + pos.y), ImColor(22,26,37, 255),
                                        5);
        window->DrawList->AddRect(ImVec2(0 + pos.x + 1, 0 + pos.y + 1),
                                  ImVec2(800 + pos.x - 1, 80 + pos.y + 1), ImColor(0, 0, 0, 255), 5,
                                  0, 2);

        window->DrawList->AddRectFilled(ImVec2(0 + pos.x, 0 + pos.y),
                                        ImVec2(800 + pos.x, 10 + pos.y), ImColor(80,113,192, 255),
                                        5,ImDrawFlags_RoundCornersTop);

        window->DrawList->AddRectFilledMultiColor(ImVec2(0 + pos.x, 10 + pos.y),
                                                  ImVec2(800 + pos.x, 30 + pos.y),
                                                  ImColor(80,113,192, 100),
                                                  ImColor(80,113,192, 100),
                                                  ImColor(80,113,192, 0), ImColor(80,113,192, 0));


        window->DrawList->AddRectFilled(ImVec2(0 + pos.x, 100 + pos.y),
                                        ImVec2(800 + pos.x, 700 + pos.y), ImColor(22,26,37, 255),
                                        5);
        window->DrawList->AddRect(ImVec2(0 + pos.x + 1, 100 + pos.y + 1),
                                  ImVec2(800 + pos.x - 1, 700 + pos.y - 1), ImColor(0, 0, 0, 255),
                                  5, 0, 2);


        window->DrawList->AddLine(ImVec2(180 + pos.x, 30 + pos.y), ImVec2(180 + pos.x, 60 + pos.y),
                                  ImColor(255, 255, 255, 200), 1.5f);

        ImGui::SetCursorPos(ImVec2(20, 10));
        //ImGui::Text("alternative");
        window->DrawList->AddText(ImGui::GetFont(), 30, ImVec2(30 + pos.x, 30 + pos.y),
                                  ImColor(255, 255, 255, 255), "alternative", nullptr, 0, nullptr);

        float rel_pos = 1;

        if ((espenable && vrk) || (aimm && !vrk)) {

            rel_anim *= 1.5;

            if (rel_anim > 30) {
                rel_anim = 30;
            }
        } else {
            rel_anim = 1;
        }

        ImGui::SetCursorPos(ImVec2(180 + 20, 30));
        if (ImGui::Button2("aimbot", ImVec2(90, 30),!vrk?ImColor(46,54,67):ImColor(46,54,67,0))) {
            vrk = false;
        }

        ImGui::SetCursorPos(ImVec2(180 + 20 + 110, 30));
        if(ImGui::Button2("players", ImVec2(90, 30),vrk?ImColor(46,54,67):ImColor(46,54,67,0))) {
            vrk = true;

        }

        ImGui::ShowDemoWindow();

        float pmtm = 15;



        if (vrk) {
            float offset = 0;


            ImGui::SetCursorPos(ImVec2(20 + offset, 120 + 10));

            if (ImGui::BeginListBox("  ", ImVec2(360, 560 - 15))) {

                ImGui::SetCursorPos(ImVec2(360/2 - ImGui::CalcTextSize("Wallhack").x/2, 15 + rel_pos - ImGui::CalcTextSize("WALLHACK").y / 2));
                ImGui::Text("Wallhack");

                rel_pos += 10;
                ImGui::SetCursorPos(ImVec2(20, 20 + rel_pos));
                ImGui::Checkbox("esp", &espenable);

                if (espenable) {
                    rel_pos += rel_anim;
                    ImGui::SetCursorPos(ImVec2(50, 20 + rel_pos));
                    ImGui::Checkbox("box", &espbox);

                    if (espbox) {
                        rel_pos += rel_anim + 10;
                        ImGui::SetCursorPos(ImVec2(45, 20 - 10 + rel_pos));
                        const char* items[] = {"2d", "3d"};
                        ImGui::Combo("dim", &td, items, IM_ARRAYSIZE(items));

                        rel_pos += rel_anim + 20;
                        ImGui::SetCursorPos(ImVec2(50, 20 + rel_pos));
                        ImGui::SliderFloat("box stroke", &espstroke, 1, 5);

                        rel_pos += rel_anim + 10;
                        ImGui::SetCursorPos(ImVec2(50, 20 + rel_pos));
                        ImGui::SliderFloat("box round", &espround, 0, 10);

                        rel_pos += rel_anim + 10;
                        ImGui::SetCursorPos(ImVec2(50, 20 + rel_pos));
                        ImGui::SliderFloat("box outline", &esphptextsize, 0, 3);
                        rel_pos += rel_anim + 5;
                    } else {
                        rel_pos += rel_anim;
                    }

                    ImGui::SetCursorPos(ImVec2(50, 20 + rel_pos));
                    ImGui::Checkbox("name", &espname);

                    if (espname) {
                        rel_pos += rel_anim + 10;
                        ImGui::SetCursorPos(ImVec2(50, 20 + rel_pos));
                        ImGui::SliderFloat("name scale", &espnamesize, 10, 30);

                        rel_pos += rel_anim + 10;
                        ImGui::SetCursorPos(ImVec2(50, 20 + rel_pos));
                        ImGui::SliderFloat("name shadow", &espnameshadow, 0, 2);
                        rel_pos += rel_anim + 5;
                    } else {
                        rel_pos += rel_anim;
                    }

                    ImGui::SetCursorPos(ImVec2(50, 20 + rel_pos));
                    ImGui::Checkbox("tracer", &esptracer);


                    ImGui::SetCursorPos(ImVec2(360 - 50, 20 - 13));
                    AddColorPicker("esp color", *(ImVec4 *) &esp_color);

                    rel_pos += 5;
                }


                rel_pos += 30;

                ImGui::SetCursorPos(ImVec2(20, 20 + rel_pos));
                ImGui::Checkbox("glow", &enableGlow);

                ImGui::SetCursorPos(ImVec2(90, 20 - 13 + rel_pos));

                if (enableGlow) {
                    AddColorPicker("glow color", *(ImVec4 *) &glow_color);
                }

                ImGui::EndListBox();
            }

            window->DrawList->AddRectFilled(ImVec2(offset + 20 + pos.x, 120 + 5 + 560 - 10 + pos.y),
                                            ImVec2(offset + 360 + 20 + pos.x, 120 + 5 + 560 + pos.y), ImColor(28,34,46, 255),
                                            5,ImDrawFlags_RoundCornersBottom);
            window->DrawList->AddRectFilledMultiColor(ImVec2(offset + 20 + pos.x, 120 + 5 + 560 - 30 + pos.y),
                                                      ImVec2(offset + 360 + 20 + pos.x, 120 + 5 + 560 - 10 + pos.y),
                                                      ImColor(28,34,46, 0),
                                                      ImColor(28,34,46, 0),
                                                      ImColor(28,34,46, 255),
                                                      ImColor(28,34,46, 255));
            window->DrawList->AddRect(ImVec2(offset + 20 + pos.x, 120 + pos.y),
                                            ImVec2(offset + 360 + 20 + pos.x, 120 + 10 + 560 + pos.y), ImColor(0,0,0, 255),
                                            5,0, 2);
            window->DrawList->AddRectFilled(ImVec2(offset + 20 + pos.x, 120 + pos.y),
                                            ImVec2(offset + 360 + 20 + pos.x, 120 + 10 + pos.y), ImColor(80,113,192, 255),
                                            5,ImDrawFlags_RoundCornersTop);


            offset = 360 + 40;
            rel_pos = 1;

            ImGui::SetCursorPos(ImVec2(20 + offset, 120 + 10));

            if (ImGui::BeginListBox("   ", ImVec2(360, 560 - 15))) {

                ImGui::SetCursorPos(ImVec2(360/2 - ImGui::CalcTextSize("Chams").x/2, 15 + rel_pos - ImGui::CalcTextSize("WALLHACK").y / 2));
                ImGui::Text("Chams");

                rel_pos += 10;
                ImGui::SetCursorPos(ImVec2(20, 20 + rel_pos));
                ImGui::Checkbox("chams", &espenable);

                ImGui::EndListBox();
            }

            window->DrawList->AddRectFilled(ImVec2(offset + 20 + pos.x, 120 + 5 + 560 - 10 + pos.y),
                                            ImVec2(offset + 360 + 20 + pos.x, 120 + 5 + 560 + pos.y), ImColor(28,34,46, 255),
                                            5,ImDrawFlags_RoundCornersBottom);
            window->DrawList->AddRectFilledMultiColor(ImVec2(offset + 20 + pos.x, 120 + 5 + 560 - 30 + pos.y),
                                                      ImVec2(offset + 360 + 20 + pos.x, 120 + 5 + 560 - 10 + pos.y),
                                                      ImColor(28,34,46, 0),
                                                      ImColor(28,34,46, 0),
                                                      ImColor(28,34,46, 255),
                                                      ImColor(28,34,46, 255));
            window->DrawList->AddRect(ImVec2(offset + 20 + pos.x, 120 + pos.y),
                                      ImVec2(offset + 360 + 20 + pos.x, 120 + 10 + 560 + pos.y), ImColor(0,0,0, 255),
                                      5,0, 2);
            window->DrawList->AddRectFilled(ImVec2(offset + 20 + pos.x, 120 + pos.y),
                                            ImVec2(offset + 360 + 20 + pos.x, 120 + 10 + pos.y), ImColor(80,113,192, 255),
                                            5,ImDrawFlags_RoundCornersTop);
        }
        else {

            if (aimm) {
                rel_pos += rel_anim;


                ImGui::SetCursorPos(ImVec2(50, 120 + rel_pos));
                ImGui::Checkbox("draw fov", &drawingCircle);

                    rel_pos += rel_anim + 10;
                    ImGui::SetCursorPos(ImVec2(50, 120 + rel_pos));
                    ImGui::SliderFloat("fov", &circlesize22, 1, 100);

                    circlesize = circlesize22*5;


                ImGui::SetCursorPos(ImVec2(90, 120 - 13));
                ImGui::ColorEdit3("   ", (float *) &circleColor);
            }

            ImGui::SetCursorPos(ImVec2(20, 120));
            ImGui::Checkbox("aim", &aimm);

            rel_pos += 30;
            ImGui::SetCursorPos(ImVec2(20, 120 + rel_pos));
            ImGui::Checkbox("bhop", &bhop);

            rel_pos += 30;
            ImGui::SetCursorPos(ImVec2(20, 120 + rel_pos));
            ImGui::Checkbox("fast strafes", &strafe);

            rel_pos += 30;
            ImGui::SetCursorPos(ImVec2(20, 120 + rel_pos));
            ImGui::Checkbox("no recoil", &feature15);

            rel_pos += 30;
            ImGui::SetCursorPos(ImVec2(20, 120 + rel_pos));
            ImGui::Checkbox("no spread", &feature12);


            AimArms = aimm;
            AimBody = aimm;
            AimHead = aimm;
            AimLegs = aimm;

            //playerLine = boolean;

            //esptracer = boolean;
            feature28 = aimm;
        }



        //open_popup |= ImGui::Button("Palette");




        rg = glow_color.x * 100;
        gg = glow_color.y * 100;
        bg = glow_color.z * 100;

        ImDrawList *drawList = getDrawList();

        float pos_prev = 340;

        if (espenable) {
            drawList->AddRectFilled(ImVec2(0 + pos.x - pos_prev, 75 + pos.y),
                                    ImVec2(300 + pos.x - pos_prev, 525 + pos.y),
                                    ImColor(22,26,37, 255), 5);
            drawList->AddRect(ImVec2(0 + pos.x + 1 - pos_prev, 75 + pos.y + 1),
                              ImVec2(300 + pos.x - 1 - pos_prev, 525 + pos.y - 1),
                              ImColor(0, 0, 0, 255), 5, 0, 2);

            if (espname) {
                drawList->AddText(ImGui::GetFont(), espnamesize,
                                  ImVec2(pos.x - ((pos_prev-40) / 2 + 40) -
                                         (ImGui::CalcTextSize("nickname").x * (espnamesize / 22)) /
                                         2,

                                         pos.y + 100 + 50 +
                                         espnameshadow - ImGui::CalcTextSize("nickname").y * (espnamesize / 22)),
                                  ImColor(0, 0, 0, 200),
                                  "nickname",
                                  nullptr,
                                  0.0f, nullptr);

                drawList->AddText(ImGui::GetFont(), espnamesize,
                                  ImVec2(pos.x - ((pos_prev-40) / 2 + 40) -
                                         (ImGui::CalcTextSize("nickname").x * (espnamesize / 22)) /
                                         2,

                                         pos.y + 100 + 50 -
                                         espnameshadow - ImGui::CalcTextSize("nickname").y * (espnamesize / 22)),
                                  ImColor((int) (esp_color.x * 255), (int) (esp_color.y * 255),
                                          (int) (esp_color.z * 255), 255),
                                  "nickname",
                                  nullptr,
                                  0.0f, nullptr);
            }
            if (espbox) {

                if (td == 1) {
                    Draw3dBox_o(Vector2(pos.x - ((pos_prev-40) / 2 + 40), pos.y + 300 ),Vector3(200,300,200),ImColor((int)(esp_color.x * 255), (int)(esp_color.y * 255), (int)(esp_color.z * 255), (int)(esp_color.w * 255)),esphptextsize,espstroke,100);
                }
                else {

                    drawList->AddRect(
                            ImVec2(pos.x - ((pos_prev-40) / 2 + 40) - 100, pos.y + 300 - 150),
                            ImVec2(pos.x - ((pos_prev-40) / 2 + 40) + 100, pos.y + 300 + 150),
                            ImColor(0, 0, 0, 255), espround, 0, espstroke + esphptextsize);


                    drawList->AddRect(
                            ImVec2(pos.x - ((pos_prev-40) / 2 + 40) - 100, pos.y + 300 - 150),
                            ImVec2(pos.x - ((pos_prev-40) / 2 + 40) + 100, pos.y + 300 + 150),
                            ImColor((int) (esp_color.x * 255), (int) (esp_color.y * 255),
                                    (int) (esp_color.z * 255), 255), espround, 0, espstroke);
                }
            }
            if (esptracer) {
                drawList->AddLine(ImVec2(screenWidth / 2, screenHeight),
                                  ImVec2(pos.x - ((pos_prev-40) / 2 + 40), pos.y + 100 + 350),
                                  ImColor((int) (esp_color.x * 255), (int) (esp_color.y * 255),
                                          (int) (esp_color.z * 255), 255), 2);
            }
        }
    }



    if (camera && espinst && checkkk && playerss && checkPlayer && WeaponInst && WeaponObject) {
        ImDrawList *drawList = getDrawList();

        if (drawingCircle) {
            drawList->AddCircle(ImVec2(screenWidth/2,screenHeight/2),circlesize*2,ImColor((int)(circleColor.x * 255), (int)(circleColor.y * 255), (int)(circleColor.z * 255), 255),100,2);
        }

        if (!espManager->enemies->empty() && espenable) {

            for (int i = 0; i < espManager->enemies->size(); i++) {
                if ((*espManager->enemies)[i]->object != nullptr) {
                    void *player = (*espManager->enemies)[i]->object;
                    void *plobj = *(void **) ((uint64_t) player + 0x14);
                    if (plobj) {
                        std::string name;
                        std::string weapon;
                        int health;

                        testtt = (*espManager->enemies)[i]->isVisible;
                        if (visible) {
                            visibletest = testtt;
                        } else {
                            visibletest = true;
                        }
                        if (testtt) {
                            color = Color(vR, vG, vB);
                        } else {
                            color = Color(invR, invG, invB);
                        }

                        health = (*espManager->enemies)[i]->health;


                        if (visibletest && player) {
                            Vector3 PosNew;
                            PosNew = (*espManager->enemies)[i]->wts1;
                            Vector3 PosNeww;
                            PosNeww = (*espManager->enemies)[i]->wts2;


                            if (PosNew.z > 1.f && health > 0) {



                                if (espname) {
                                    drawList->AddText(ImGui::GetFont(), espnamesize,
                                                      ImVec2((*espManager->enemies)[i]->wts1.x - (ImGui::CalcTextSize((*espManager->enemies)[i]->name.c_str()).x * (espnamesize / 22))/2,
                                                             screenHeight -
                                                             (*espManager->enemies)[i]->wts2.y +
                                                             espnameshadow - ImGui::CalcTextSize((*espManager->enemies)[i]->name.c_str()).y),
                                                      ImColor(0, 0, 0, 200),
                                                      (*espManager->enemies)[i]->name.c_str(),
                                                      nullptr,
                                                      0.0f, nullptr);

                                    drawList->AddText(ImGui::GetFont(), espnamesize,
                                                      ImVec2((*espManager->enemies)[i]->wts1.x - (ImGui::CalcTextSize((*espManager->enemies)[i]->name.c_str()).x * (espnamesize / 22))/2,
                                                             screenHeight -
                                                             (*espManager->enemies)[i]->wts2.y -
                                                             espnameshadow - ImGui::CalcTextSize((*espManager->enemies)[i]->name.c_str()).y),
                                                      ImColor((int)(esp_color.x * 255), (int)(esp_color.y * 255), (int)(esp_color.z * 255), 255),
                                                      (*espManager->enemies)[i]->name.c_str(),
                                                      nullptr,
                                                      0.0f, nullptr);
                                }
                                if (espbox) {
                                    if (td == 1) {
                                        Draw3dBox((*espManager->enemies)[i]->pos + Vector3(0,1,0),((*espManager->enemies)[i]->rot.x + 45) * (180/PI),Vector3(1,2,1),ImColor((int)(esp_color.x * 255), (int)(esp_color.y * 255), (int)(esp_color.z * 255), (int)(esp_color.w * 255)),esphptextsize,espstroke,100);
                                    }
                                    else {
                                        drawList->AddRect(
                                                ImVec2(PosNew.x + (((screenHeight - PosNeww.y) -
                                                                    (screenHeight - PosNew.y)) /
                                                                   4), screenHeight - PosNeww.y),
                                                ImVec2(PosNew.x - (((screenHeight - PosNeww.y) -
                                                                    (screenHeight - PosNew.y)) /
                                                                   4), screenHeight - PosNew.y),
                                                ImColor(0, 0, 0, 255), espround, 0, espstroke + esphptextsize);



                                        drawList->AddRect(
                                                ImVec2(PosNew.x + (((screenHeight - PosNeww.y) -
                                                                    (screenHeight - PosNew.y)) /
                                                                   4), screenHeight - PosNeww.y),
                                                ImVec2(PosNew.x - (((screenHeight - PosNeww.y) -
                                                                    (screenHeight - PosNew.y)) /
                                                                   4), screenHeight - PosNew.y),
                                                ImColor((int)(esp_color.x * 255), (int)(esp_color.y * 255), (int)(esp_color.z * 255), (int)(esp_color.w * 255)), espround, 0, espstroke);

                                    }
                                }
                                if (esptracer) {
                                    drawList->AddLine(ImVec2(screenWidth / 2, screenHeight),
                                                      ImVec2(PosNew.x, screenHeight - PosNew.y),
                                                      ImColor(0, 0, 0, 255), espstroke + esphptextsize);

                                    drawList->AddLine(ImVec2(screenWidth / 2, screenHeight),
                                                      ImVec2(PosNew.x, screenHeight - PosNew.y),
                                                      ImColor((int)(esp_color.x * 255), (int)(esp_color.y * 255), (int)(esp_color.z * 255), (int)(esp_color.w * 255)), espstroke);
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    if (menuOpen) {
        ImGui::End();
    }

    ImGui::EndFrame();

    ImGui::Render();
    ImGui_ImplAndroidGLES2_RenderDrawLists(ImGui::GetDrawData()); //Draw ImGui Draw Data with our Android Backend
}

jint (*old_RegisterNatives )(JNIEnv*, jclass, JNINativeMethod*,jint);
bool (*old_nativeInjectEvent )(JNIEnv*, jobject ,jobject event);
bool hook_nativeInjectEvent(JNIEnv* env, jobject instance,jobject event){
       jclass tchcls = env->FindClass(ozObfuscate("android/view/MotionEvent"));
        jclass kycls = env->FindClass(ozObfuscate("android/view/KeyEvent"));
        jmethodID ga = env->GetMethodID(kycls, ozObfuscate("getAction"),
                                    ozObfuscate("()I"));
        if(env->IsInstanceOf(event, kycls) && env->CallIntMethod(event, ga) == 0) {
            jmethodID gkc = env->GetMethodID(kycls, ozObfuscate("getKeyCode"), ozObfuscate("()I"));
            jmethodID guc = env->GetMethodID(kycls, ozObfuscate("getUnicodeChar"), ozObfuscate("()I"));
            int keyCode = env->CallIntMethod(event, gkc);
            ImGuiIO& io = ImGui::GetIO();
            switch (keyCode) {
                case 19:
                     inputChar = keyCode;
                    break;
                case 20:
                    inputChar = keyCode;
                    break;
                case 21:
                    inputChar = keyCode;
                    break;
                case 22:
                    inputChar = keyCode;
                    break;
                case 61:
                    inputChar = keyCode;
                    break;
                case 66:
                    inputChar = keyCode;
                    break;
                case 67:
                    inputChar = keyCode;
                    break;
                case 92:
                    inputChar = keyCode;
                    break;
                case 93:
                    inputChar = keyCode;
                    break;
                case 111:
                    inputChar = keyCode;
                    break;
                case 112:
                    inputChar = keyCode;
                    break;
                case 122:
                    inputChar = keyCode;
                    break;
                case 123:
                    inputChar = keyCode;
                    break;
                case 124:
                    inputChar = keyCode;
                    break;
                default:
                     ImGui::GetIO().AddInputCharacter(env->CallIntMethod(event, guc));
                    break;
            }
            return old_nativeInjectEvent(env, instance, event);
        }
        if(!env->IsInstanceOf(event, tchcls)){
            return old_nativeInjectEvent(env, instance, event);
        }
        jmethodID id_getAct = env->GetMethodID(tchcls, ozObfuscate("getActionMasked"), ozObfuscate("()I"));
        jmethodID id_getX = env->GetMethodID(tchcls, ozObfuscate("getX"), ozObfuscate("()F"));
        jmethodID id_getY = env->GetMethodID(tchcls, ozObfuscate("getY"), ozObfuscate("()F"));
        jmethodID id_getPs = env->GetMethodID(tchcls, ozObfuscate("getPointerCount"), ozObfuscate("()I"));
        HandleInputEvent(env, env->CallIntMethod(event, id_getAct),env->CallFloatMethod(event, id_getX), env->CallFloatMethod(event, id_getY), env->CallIntMethod(event, id_getPs));
        if (!ImGui::GetIO().MouseDownOwnedUnlessPopupClose[0]){
            return old_nativeInjectEvent(env, instance, event);
        }
        return false;
}

void SearchActivity(JNIEnv * globalEnv){
    jclass prcls = globalEnv->FindClass("com/unity3d/player/UnityPlayer");
    if(prcls != nullptr){
        jfieldID UnityPlayer_CurrentActivity_fid2 = globalEnv->GetStaticFieldID(prcls, "currentActivity","Landroid/app/Activity;");
        if(UnityPlayer_CurrentActivity_fid2 != nullptr){
            UnityPlayer_CurrentActivity_fid = globalEnv->NewGlobalRef(globalEnv->GetStaticObjectField(prcls, UnityPlayer_CurrentActivity_fid2));
        }
    }
}

void (*old_nativeDraw )(...);
void hook_nativeDraw(void*i1,void*i2){
    LOGI("nativeDraw");
    UpdateInput();
    // Open on-screen (soft) input if requested by Dear ImGui
    static bool WantTextInputLast = false;
    LOGI("nativeDraw2");
    ImGuiIO& io = ImGui::GetIO();
    if (io.WantTextInput && !WantTextInputLast){
        diplayKeyboard(nullptr);
    }
    LOGI("nativeDraw3");
    WantTextInputLast = io.WantTextInput;
    //Render();
    LOGI("nativeDraw4");
    old_nativeDraw(i1,i2);
    LOGI("nativeDraw5");
    LOGI("JNI Render Thread");

}
jint hook_RegisterNatives(JNIEnv* env, jclass destinationClass, JNINativeMethod* methods,
                          jint count){
    int i; // [sp+24h] [bp-2Ch]
    for ( i = 0; i < count; ++i )
    {
        if (!strcmp(methods[i].name, ozObfuscate("nativeInjectEvent")) ){
            LOGI("registern1");
            MSHookFunction(methods[i].fnPtr, (void*)hook_nativeInjectEvent, (void **)&old_nativeInjectEvent);
            LOGI("registern2");
        }
        if (!strcmp(methods[i].name, ozObfuscate("nativeRender")) ){
            LOGI("Native Render! It is on: %p", (methods[i].fnPtr));

            //MSHookFunction(methods[i].fnPtr, (void*)hook_nativeDraw, (void **)&old_nativeDraw);
            LOGI("registern3");
        }
    }
    LOGI("registern4");
    SearchActivtiy(env);
    LOGI("registern5");
    return old_RegisterNatives(env, destinationClass, methods, count);
}


extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    publicJVM = vm;
    JNIEnv *globalEnv;
    publicJVM->GetEnv((void **) &globalEnv, JNI_VERSION_1_6);
    sleep(2);
    InitMods();
    MSHookFunction((void*)globalEnv->functions->RegisterNatives, (void*)hook_RegisterNatives, (void **)&old_RegisterNatives);
    return JNI_VERSION_1_6;
}
