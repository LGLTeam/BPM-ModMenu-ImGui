#ifndef FWD_ASSAULT_CHAMS_H
#define FWD_ASSAULT_CHAMS_H
#include "gl2.h"
#include <dlfcn.h>
#include "Substrate/SubstrateHook.h"
#include "Substrate/CydiaSubstrate.h"

static void *handle;
static const char* shaderName;
static bool enableWallhack, isRGB;
static bool enableWallhackW;
static bool nightmode;

static bool wh1;
static bool wh2;
static bool wh3 = true;

static bool rgb0;
static bool rgb1;
static bool rgb2;
static bool rgb3;

static bool arms;

static bool rgb4;
static bool rgb5;

static bool enableWireframe;
static bool enableGlow;
static bool enableShading;
static bool wallhack;
static bool fakelag;
static bool darkmode1;
static bool darkmode3;
static bool remove1;
static bool darkmode2;
static bool darkmode4;
static float r = 0;
static float g = 0;
static float b = 0;

static float armsR = 0;
static float armsG = 0;
static float armsB = 0;

static float nightvalR = 0;
static float nightvalG = 0;
static float nightvalB = 0;

static float r2 = 0;
static float g2 = 0;
static float b2 = 0;

static bool rS = false;
static bool gS = false;
static bool bS = false;
static bool whSh = false;

static float a = 0;
static float rw = 0;
static float gw = 0;
static float bw = 0;
static float rg = 0;
static float gg = 0;
static float bg = 0;
static int widthw = 1;
static int widthg = 1;
static bool PulseT1;
static bool PulseT2;
static bool PulseW;
static bool PulseG;
static bool PulseA;
static int red = 255, green = 0, blue = 255, rgb = 1, pulsesw = 0, pulsevalue = 0;
static bool rF = true, gF, bF = true, rF_, gF_, bF_;

void PulseT1Set(bool enable) {
    PulseT1 = enable;
}
void PulseT2Set(bool enable) {
    PulseT2 = enable;
}
void PulseWSet(bool enable) {
    PulseW = enable;
}
void PulseGSet(bool enable) {
    PulseG = enable;
}
void PulseASet(bool enable) {
    PulseA = enable;
}

void performRGBChange(){
    switch (rgb) {
        case 0: {
            if (gF) {
                green--;
                if (!green) {
                    gF = !gF;
                    rF_ = !rF_;
                }
                break;
            }

            if (red < 255 && rF_) red++;
            else {
                rgb++;
                red = 255;
                rF = !rF;
                rF_ = !rF_;
            }
            break;
        }
        case 1: {
            if (bF) {
                blue--;
                if (!blue) {
                    bF = !bF;
                    gF_ = !gF_;
                }
                break;
            }

            if (green < 255 && gF_) green++;
            else {
                rgb++;
                green = 255;
                gF = !gF;
                gF_ = !gF_;
            }
            break;
        }
        case 2: {
            if (rF) {
                red--;
                if (!red) {
                    rF = !rF;
                    bF_ = !bF_;
                }
                break;
            }

            if (blue < 255 && bF_) blue++;
            else {
                rgb = 0;
                blue = 255;
                bF = !bF;
                bF_ = !bF_;
            }
        }
    }
}

void perfPulse(){
    switch (pulsesw) {
        case 0: {
            if (pulsevalue < 100) {
                pulsevalue++;
            }
            else {
                pulsesw++;
            }
            break;
        }
        case 1: {
            if (pulsevalue > 0) {
                pulsevalue--;
            }
            else {
                pulsesw--;
            }
            break;
        }
    }
}

void SetRGB(bool enable) {
    rgb1 = enable;
}
void Rgb0(bool enable) {
    rgb0 = enable;
}
void Rgb1(bool enable) {
    rgb1 = enable;
}
void Rgb2(bool enable) {
    rgb2 = enable;
}
void Rgb3(bool enable) {
    rgb3 = enable;
}

void Rgb4(bool enable) {
    rgb4 = enable;
}
void Rgb5(bool enable) {
    rgb5 = enable;
}

void Wh1(bool enable) {
    wh1 = enable;
}

void darkmode1set(bool enable) {
    darkmode1 = enable;
}
void darkmode3set(bool enable) {
    darkmode3 = enable;
}
void RemoveSet(bool enable) {
    remove1 = enable;
}
void darkmode2set(bool enable) {
    darkmode2 = enable;
}
void darkmode4set(bool enable) {
    darkmode4 = enable;
}
void Wh2(bool enable) {
    wh2 = enable;
}
void Wh3(bool enable) {
    wh3 = enable;
}

void setShader(const char* s) {
    handle = dlopen("libGLESv2.so", RTLD_LAZY);
    shaderName = s;
}
const char* getShader() {
    return shaderName;
}

void SetWallhack(bool enable){
    enableWallhack = enable;
}

void SetWallhackW(bool enable){
    enableWallhackW = enable;
}

void WallhackOn(bool enable){
    wallhack = enable;
}

void SetWireframe(bool enable){
    enableWireframe = enable;
}

void SetGlow(bool enable){
    enableGlow = enable;
}

void SetShading(bool enable){
    enableShading = enable;
}

void SetR(int set){
    r = set;
}

void SetR2(int set){
    r2 = set;
}

void SetG2(int set){
    g2 = set;
}

void SetB2(int set){
    b2 = set;
}

void SetRs(bool set){
    rS = set;
}
void SetGs(bool set){
    gS = set;
}
void SetBs(bool set){
    bS = set;
}
void SetWs(bool set){
    whSh = set;
}




void SetRn(int set){
    nightvalR = set;
}

void SetGn(int set){
    nightvalG = set;
}

void SetBn(int set){
    nightvalB = set;
}




void SetWidth(int set){
    widthw = set;
}

void SetWidthG(int set){
    widthg = set;
}

void SetG(int set){
    g = set;
}

void SetB(int set){
    b = set;
}

void SetA(int set){
    a = set;
}

void SetRw(int set){
    rw = set;
}

void SetGw(int set){
    gw = set;
}

void SetBw(int set){
    bw = set;
}

void SetRg(int set){
    rg = set;
}

void SetGg(int set){
    gg = set;
}

void SetBg(int set){
    bg = set;
}


void SetRa(int set){
    armsR = set;
}

void SetGa(int set){
    armsG = set;
}

void SetBa(int set){
    armsB = set;
}

bool getWallhackEnabled(){
    return enableWallhack;
}

void set_nightmode(bool enable){
    nightmode = enable;
}

bool get_nightmode(){
    return nightmode;
}

void set_arms(bool enable){
    arms = enable;
}

bool get_arms(){
    return arms;
}

bool getWallhackOn(){
    return wallhack;
}

bool getWireframeEnabled(){
    return enableWireframe;
}
bool getGlowEnabled(){
    return enableGlow;
}
bool getShadingChams(){
    return enableShading;
}

int (*old_glGetUniformLocation)(GLuint, const GLchar *);
GLint new_glGetUniformLocation(GLuint program, const GLchar *name) {
    //Log name to find used shaders.
    LOGI("New shader found: %s", name);
    return old_glGetUniformLocation(program, name);
}

bool isCurrentShader(const char *shader) {
    GLint currProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
    return old_glGetUniformLocation(currProgram, shader) != -1;
}
#define _DRAW_RGB_ 12,0,28 // Color
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
const void *indices1;

void (*old_glDrawElements)(GLenum mode, GLsizei count, GLenum type, const void *indices);
void new_glDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices) {
    //if (count < 20) return;
    GLint currProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
    GLint id = old_glGetUniformLocation(currProgram, getShader());
    if (id != -1) {
        if (mode != GL_TRIANGLES || count < 100) {
            if (remove1 == false) {
                old_glDrawElements(mode, count, type, indices);
            }
            if (get_arms()) {
                glLineWidth(3);
                //old_glDrawElements(GL_TRIANGLES, count, type, indices);
                glBlendColor(GLfloat(armsR/100), GLfloat(armsG/100), GLfloat(armsB/100), 1);
                if (PulseA) {
                    glBlendColor(GLfloat(armsR/100) * GLfloat(float(pulsevalue)/100), GLfloat(armsG/100) * GLfloat(float(pulsevalue)/100), GLfloat(armsB/100) * GLfloat(float(pulsevalue)/100), 1);
                }
                if (rgb5) {
                    if (PulseA) {
                        glBlendColor(GLfloat(float(red)/255) * GLfloat(float(pulsevalue)/100), GLfloat(float(green)/255) * GLfloat(float(pulsevalue)/100), GLfloat(float(blue)/255) * GLfloat(float(pulsevalue)/100), 1);
                    }
                    else {
                        glBlendColor(GLfloat(float(red)/255), GLfloat(float(green)/255), GLfloat(float(blue)/255), 1);
                    }
                }

                glColorMask(1, 1, 1, 1);
                glEnable(GL_BLEND);

                if (darkmode4) {
                    glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_ALPHA, GL_ONE, GL_ONE);
                }
                else {
                    glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
                }
                old_glDrawElements(GL_LINES, count, type, indices);
                old_glDrawElements(GL_TRIANGLES, count, type, indices);
                glDepthRangef(0.5, 1);
                glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
                glDisable(GL_BLEND);
            }
            else {
                old_glDrawElements(mode, count, type, indices);
            }
            return;
        }
        if (!remove1) {
            old_glDrawElements(mode, count, type, indices);
        }
        if (getShadingChams()) {
            if (whSh) {
                glDepthRangef(1, 0.5);
            }
            else {
                glDepthRangef(0.5, 1);
            }
            glEnable(GL_BLEND);
            glBlendColor(0, 0, 0, 0);
            glColorMask(!rS, !gS, !bS, 1);
            glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
            old_glDrawElements(GL_TRIANGLES, count, type, indices);
        }
        if (getWallhackEnabled()) {


            //glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);

            glEnable(GL_CULL_FACE);
            glFrontFace(GL_CW);
            glBlendColor(GLfloat(r/100), GLfloat(g/100), GLfloat(b/100), 1);
            glColorMask(1, 1, 1, 1);
            glEnable(GL_BLEND);
            glEnable(GL_STENCIL_TEST);

            glStencilMask(0);

            if (PulseT1) {
                glBlendColor(GLfloat(r/100) * GLfloat(float(pulsevalue)/100), GLfloat(g/100) * GLfloat(float(pulsevalue)/100), GLfloat(b/100) * GLfloat(float(pulsevalue)/100), 1);
            }
            if (rgb0) {
                if (PulseT1) {
                    glBlendColor(GLfloat(float(red)/255) * GLfloat(float(pulsevalue)/100), GLfloat(float(green)/255) * GLfloat(float(pulsevalue)/100), GLfloat(float(blue)/255) * GLfloat(float(pulsevalue)/100), 1);
                }
                else {
                    glBlendColor(GLfloat(float(red)/255), GLfloat(float(green)/255), GLfloat(float(blue)/255), 1);
                }
            }
            glDepthMask(true);
            //glCullFace(GL_FRONT_FACE);
            glDepthFunc(GL_EQUAL);
            if (wh1) {
                glDepthRangef(1, 0.5);
            }
            else {
                glDepthRangef(0.5, 1);
            }
            if (darkmode1) {

                glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_ALPHA, GL_ONE, GL_ONE);
            }
            else {
                glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
            }
            old_glDrawElements(GL_TRIANGLES, count, type, indices);
            //glEnable(GL_CULL_FACE);
            //glFrontFace(GL_CW);
            //glCullFace(GL_BACK);
            glEnable(GL_BLEND);
            glDepthFunc(GL_NOTEQUAL);
            //glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT,GL_FUNC_SUBTRACT);
            if (darkmode2) {
                glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_ALPHA, GL_ONE, GL_ONE);
            }
            else {
                glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
            }
            glBlendColor(GLfloat(r2/100), GLfloat(g2/100), GLfloat(b2/100), 1);
            if (PulseT2) {
                glBlendColor(GLfloat(r2/100) * GLfloat(float(pulsevalue)/100), GLfloat(g2/100) * GLfloat(float(pulsevalue)/100), GLfloat(b2/100) * GLfloat(float(pulsevalue)/100), 1);
            }
            if (rgb1) {
                if (PulseT2) {
                    glBlendColor(GLfloat(float(red)/255) * GLfloat(float(pulsevalue)/100), GLfloat(float(green)/255) * GLfloat(float(pulsevalue)/100), GLfloat(float(blue)/255) * GLfloat(float(pulsevalue)/100), 1);
                }
                else {
                    glBlendColor(GLfloat(float(red)/255), GLfloat(float(green)/255), GLfloat(float(blue)/255), 1);
                }
            }
            old_glDrawElements(GL_TRIANGLES, count, type, indices);
            //glDepthMask(true);
            //glClearDepthf(1);


            glDepthMask(true);
            glDepthFunc(GL_LESS);
        }




        if (getWireframeEnabled()) {
            if (wh2) {
                glDepthRangef(1, 0.5);
            }
            else {
                glDepthRangef(0.5, 1);
            }
            glEnable(GL_BLEND);
            glBlendColor(GLfloat(rw/100), GLfloat(gw/100), GLfloat(bw/100), 1);
            glColorMask(1, 1, 1, 1);
            glEnable(GL_BLEND);
            glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
            glLineWidth(1);
            if (PulseW) {
                glBlendColor(GLfloat(rw/100) * GLfloat(float(pulsevalue)/100), GLfloat(gw/100) * GLfloat(float(pulsevalue)/100), GLfloat(bw/100) * GLfloat(float(pulsevalue)/100), 1);
            }
            if (rgb2) {
                if (PulseW) {
                    glBlendColor(GLfloat(float(red)/255) * GLfloat(float(pulsevalue)/100), GLfloat(float(green)/255) * GLfloat(float(pulsevalue)/100), GLfloat(float(blue)/255) * GLfloat(float(pulsevalue)/100), 1);
                }
                else {
                    glBlendColor(GLfloat(float(red)/255), GLfloat(float(green)/255), GLfloat(float(blue)/255), 1);
                }
            }
            old_glDrawElements(GL_LINES, count, type, indices);
        }

        if (getGlowEnabled()) {




            glDepthRangef(1, 0);

            glLineWidth(20.0f);
            //glBlendFunc(GL_SRC_ALPHA, 0x1);
            //glBlendColor(rg, gg, bg, 0);
            //glColorMask(0, 0, 0, 0);
            glEnable(GL_BLEND);
            glColorMask(1, 1, 1, 1);
            glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
            glBlendColor(0, 0, 0, 1);
            old_glDrawElements(GL_TRIANGLES, count, type, indices);
            glBlendColor(GLfloat(rg/100), GLfloat(gg/100), GLfloat(bg/100), 1);
            if (wh3) {
                glDepthRangef(1, 0.5);
            }
            else {
                glDepthRangef(0.5, 1);
            }
            if (PulseG) {
                glBlendColor(GLfloat(rg/100) * GLfloat(float(pulsevalue)/100), GLfloat(gg/100) * GLfloat(float(pulsevalue)/100), GLfloat(bg/100) * GLfloat(float(pulsevalue)/100), 1);
            }
            if (rgb3) {
                if (PulseG) {
                    glBlendColor(GLfloat(float(red)/255) * GLfloat(float(pulsevalue)/100), GLfloat(float(green)/255) * GLfloat(float(pulsevalue)/100), GLfloat(float(blue)/255) * GLfloat(float(pulsevalue)/100), 1);
                }
                else {
                    glBlendColor(GLfloat(float(red)/255), GLfloat(float(green)/255), GLfloat(float(blue)/255), 1);
                }
            }
            old_glDrawElements(GL_LINES, count, type, indices);
            glDepthRangef(0.5, 1);
            glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
            glDisable(GL_BLEND);



        }
        glDepthRangef(0.5, 1);
        glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
        glDisable(GL_BLEND);
    }
    else {
        old_glDrawElements(mode, count, type, indices);
    }
    GLint currProgram2;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);

    GLint id2 = old_glGetUniformLocation(currProgram, "_MainTex");
    if (id2 != -1 && id == -1) {
        if (mode != GL_TRIANGLES || count < 300) return;
        if (get_nightmode()) {
            //old_glDrawElements(GL_TRIANGLES, count, type, indices);
            glBlendColor(GLfloat(nightvalR/100), GLfloat(nightvalG/100), GLfloat(nightvalB/100), 1);
            if (rgb4) {
                glBlendColor(GLfloat(float(red)/255), GLfloat(float(green)/255), GLfloat(float(blue)/255), 1);
            }

            glColorMask(1, 1, 1, 1);
            glEnable(GL_BLEND);

            if (darkmode3) {
                glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_ALPHA, GL_ONE, GL_ONE);
            }
            else {
                glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
            }
            old_glDrawElements(GL_TRIANGLES, count, type, indices);
        }
    }
}

bool mlovinit(){
    handle = dlopen("libGLESv2.so", RTLD_LAZY);
    if(!handle){
        LOGE("Cannot open library: %s", dlerror());
        return false;
    }
    return true;
}

void LogShaders(){
    auto p_glGetUniformLocation = (const void*(*)(...))dlsym(handle, "glGetUniformLocation");
    const char *dlsym_error = dlerror();
    if(dlsym_error){
        LOGE("Cannot load symbol 'glGetUniformLocation': %s", dlsym_error);
        return;
    }else{
        MSHookFunction(reinterpret_cast<void*>(p_glGetUniformLocation), reinterpret_cast<void*>(new_glGetUniformLocation), reinterpret_cast<void**>(&old_glGetUniformLocation));
    }
}
void Wallhack(){
    handle = dlopen("libGLESv2.so", RTLD_LAZY);
    auto p_glDrawElements = (const void*(*)(...))dlsym(handle, "glDrawElements");
    const char *dlsym_error = dlerror();
    if(dlsym_error){
        LOGE("Cannot load symbol 'glDrawElements': %s", dlsym_error);
        return;
    }else{
        MSHookFunction(reinterpret_cast<void*>(p_glDrawElements), reinterpret_cast<void*>(new_glDrawElements), reinterpret_cast<void**>(&old_glDrawElements));
    }
}


#endif //FWD_ASSAULT_CHAMS_H
