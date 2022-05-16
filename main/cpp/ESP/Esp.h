#ifndef DESI_ESP_IMPORTANT_ESP_H
#define DESI_ESP_IMPORTANT_ESP_H
#include "CanvasVec.h"
bool espbox,espgradient, esphealth, espname, esptracer, esphpoutline, espnameoutline,esparmor,espweapon;
float esphpsize,  esphptextsize, espstroke = 1, espround;

float espnamesize = 22;
float espnameshadow = 0;

class ESP {
private:
    JNIEnv *_env;
    jobject _cvsView;
    jobject _cvs;


public:
    ESP() {
        _env = nullptr;
        _cvsView = nullptr;
        _cvs = nullptr;
    }

    ESP(JNIEnv *env, jobject cvsView, jobject cvs) {
        this->_env = env;
        this->_cvsView = cvsView;
        this->_cvs = cvs;
    }

    bool isValid() const {
        return (_env != nullptr && _cvsView != nullptr && _cvs != nullptr);
    }

    int getWidth() const {
        if (isValid()) {
            jclass canvas = _env->GetObjectClass(_cvs);
            jmethodID width = _env->GetMethodID(canvas, "getWidth", "()I");
            return _env->CallIntMethod(_cvs, width);
        }
        return 0;
    }

    int getHeight() const {
        if (isValid()) {
            jclass canvas = _env->GetObjectClass(_cvs);
            jmethodID width = _env->GetMethodID(canvas, "getHeight", "()I");
            return _env->CallIntMethod(_cvs, width);
        }
        return 0;
    }

    void DrawLine(Color color, float thickness, Vec22 start, Vec22 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawLine",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.x, start.y, end.x, end.y);
        }
    }
    void DrawLineGlow(Color color, float thickness, Vec22 start, Vec22 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawLineGlow",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.x, start.y, end.x, end.y);
        }
    }
    void DrawLineOutline(Color color, float thickness, Vec22 start, Vec22 end) {
        DrawLine(Color(0,0,0), thickness, Vec22(start.x, start.y - 1), Vec22(end.x,end.y + 1));
        DrawLine(Color(0,0,0), thickness, Vec22(start.x - 1, start.y - 1), Vec22(end.x - 1,end.y + 1));
        DrawLine(Color(0,0,0), thickness, Vec22(start.x + 1, start.y - 1), Vec22(end.x + 1,end.y + 1));
        DrawLine(color, thickness, start, end);
    }

    void DrawLineBot(Color color, float thickness, Vec22 start, Vec22 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawlinebot = _env->GetMethodID(canvasView, "DrawLineBot",
                                                      "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawlinebot, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.x, start.y, end.x, end.y);
        }
    }

    void DrawSkeleton(Color color, float thickness, Vec22 start, Vec22 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawskeleton = _env->GetMethodID(canvasView, "DrawSkeleton",
                                                       "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawskeleton, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.x, start.y, end.x, end.y);
        }
    }

    void DrawRect(Color color, float thickness, Vec22 start, Vec22 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawRect",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.x, start.y, end.x, end.y);
        }
    }

    void DrawRect2(Color color, float thickness, Vec22 start, Vec22 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawRect2",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.x, start.y, end.x, end.y);
        }
    }

    void DrawFilledRect3(Color color, Vec22 start, Vec22 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawFilledRect3",
                                                   "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 start.x, start.y, end.x, end.y);
        }
    }


    void DrawBox(Color color, float thickness, Vec22 start, Vec22 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawBox",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.x, start.y, end.x, end.y);
        }
    }

    void DrawFilledRect(Color color, Vec22 start, Vec22 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawFilledRect",
                                                   "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 start.x, start.y, end.x, end.y);
        }
    }

    void DrawEspBox1(Color color, Vec22 start, Vec22 end, float round, float stroke) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawEspBox",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 start.x, start.y, end.x, end.y, round, stroke);
        }
    }

    void DrawEspBoxGradient(Color color, Vec22 start, Vec22 end, float round, float stroke) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawEspBoxGradient",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 start.x, start.y, end.x, end.y, round, stroke);
        }
    }

    void DrawFilledRect2(Color color, Vec22 start, Vec22 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawFilledRect2",
                                                   "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 start.x, start.y, end.x, end.y);
        }
    }

    void DebugText(char * s){
        jclass cls = _env->GetObjectClass(_cvsView);
        jmethodID mid = _env->GetMethodID(cls, "DebugText", "(Ljava/lang/String;)V");
        jstring name = _env->NewStringUTF(s);
        _env->CallVoidMethod(_cvsView, mid, name);
        _env->DeleteLocalRef(name);
    }

    static jstring wcstojstr(JNIEnv *env, const wchar_t *input) {
        jobject bb = env->NewDirectByteBuffer((void *)input, wcslen(input) * sizeof(wchar_t));
        jstring UTF32LE = env->NewStringUTF("UTF-32LE");

        jclass charsetClass = env->FindClass("java/nio/charset/Charset");
        jmethodID forNameMethod = env->GetStaticMethodID(charsetClass, "forName", "(Ljava/lang/String;)Ljava/nio/charset/Charset;");
        jobject charset = env->CallStaticObjectMethod(charsetClass, forNameMethod, UTF32LE);

        jmethodID decodeMethod = env->GetMethodID(charsetClass, "decode", "(Ljava/nio/ByteBuffer;)Ljava/nio/CharBuffer;");
        jobject cb = env->CallObjectMethod(charset, decodeMethod, bb);

        jclass charBufferClass = env->FindClass("java/nio/CharBuffer");
        jmethodID toStringMethod = env->GetMethodID(charBufferClass, "toString", "()Ljava/lang/String;");
        jstring ret = (jstring)env->CallObjectMethod(cb, toStringMethod);

        env->DeleteLocalRef(bb);
        env->DeleteLocalRef(UTF32LE);
        env->DeleteLocalRef(charsetClass);
        env->DeleteLocalRef(charset);
        env->DeleteLocalRef(cb);
        env->DeleteLocalRef(charBufferClass);

        return ret;
    }

    void DrawTextShadow(Color color, const wchar_t *txt, Vec22 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawText",
                                                   "(Landroid/graphics/Canvas;IIIILjava/lang/String;FFF)V");
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 wcstojstr(_env, txt), pos.x, pos.y, size);
        }
    }

    void SetFps(int fps) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "SetFps",
                                                   "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawtext, fps);
        }
    }


    void DrawText(Color color, const char *txt, Vec22 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawText",
                                                   "(Landroid/graphics/Canvas;IIIILjava/lang/String;FFF)V");
            jstring s=_env->NewStringUTF(txt);
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 s, pos.x, pos.y, size);
            _env->DeleteLocalRef(s);
        }
    }

    void DrawPlayerList(const char *txt, int count) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawPlayerList",
                                                   "(Landroid/graphics/Canvas;Ljava/lang/String;I)V");
            jstring s=_env->NewStringUTF(txt);
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, s, count);
            _env->DeleteLocalRef(s);
        }
    }

    void DrawTextOutline(Color color, const char *txt, Vec22 pos, float size, int width) {
        DrawText(Color(0,0,0,255),txt,Vec22(pos.x,pos.y - width),size);
        DrawText(Color(0,0,0,255),txt,Vec22(pos.x - width,pos.y),size);
        DrawText(Color(0,0,0,255),txt,Vec22(pos.x,pos.y + width),size);
        DrawText(Color(0,0,0,255),txt,Vec22(pos.x + width,pos.y),size);
        DrawText(Color(0,0,0,255),txt,Vec22(pos.x - width,pos.y - width),size);
        DrawText(Color(0,0,0,255),txt,Vec22(pos.x + width,pos.y - width),size);
        DrawText(Color(0,0,0,255),txt,Vec22(pos.x - width,pos.y + width),size);
        DrawText(Color(0,0,0,255),txt,Vec22(pos.x + width,pos.y + width),size);
        DrawText(color,txt,pos,size);
    }

    void DrawEspBox(int x = 0, int x2 = 0, int y= 0, int y2= 0, int hp= 0,int armor= 0, const char *name = " ", std::string weapon = " ", Color color = Color(255,255,255,255), int ammo = 0) {
        Color hpcolor = Color(255 - (hp * 2.55),hp * 2.55, 100, 255);
        if (hpcolor.r < 100) {
            hpcolor.r = 100;
        }
        if (hpcolor.g < 100) {
            hpcolor.g = 100;
        }
        if (hpcolor.b < 100) {
            hpcolor.b = 100;
        }
        if (espbox) {
            //DrawLine(color, 2, Vec22(x - ((y - y2) / 4), getHeight() - y), Vec22(x + ((y - y2) / 4), getHeight() - y));
            //DrawLine(color, 2, Vec22(x - ((y - y2) / 4), getHeight() - y2), Vec22(x + ((y - y2) / 4), getHeight() - y2));
            //DrawLine(color, 2, Vec22(x - ((y - y2) / 4), getHeight() - y), Vec22(x - ((y - y2) / 4), getHeight() - y2));
            //DrawLine(color, 2, Vec22(x + ((y - y2) / 4), getHeight() - y), Vec22(x + ((y - y2) / 4), getHeight() - y2));
            if (espgradient) {
                DrawEspBoxGradient(color, Vec22(x + ((y - y2) / 4), getHeight() - y2), Vec22(x - ((y - y2) / 4),getHeight() - y), espround, espstroke);
            }
            else {
                DrawEspBox1(color, Vec22(x + ((y - y2) / 4), getHeight() - y2), Vec22(x - ((y - y2) / 4),getHeight() - y), espround, espstroke);
            }
        }
        if (esparmor) {
            DrawFilledRect(Color(255,255,255,255),  Vec22(x - esphpsize - 8 - esphpsize + ((y - y2) / 4), getHeight() - y + (y - y2) * (float(armor) / 100.0f)), Vec22(x - 8 - esphpsize + ((y - y2) / 4), getHeight() - y));

            if (esphpoutline) {
                DrawFilledRect(Color(0,0, 0, 100),  Vec22(x - esphpsize - 8 - esphpsize - 1  + ((y - y2) / 4), getHeight() - y2 - 1), Vec22(x - esphpsize - 8 + 1 + ((y - y2) / 4), getHeight() - y + 1));
                DrawTextOutline(Color(255,255, 255, 255), std::to_string(armor).c_str(), Vec22(x - esphpsize - 8 - (esphpsize/2) + ((y - y2) / 4), getHeight() - y + (y - y2) * (float(armor) / 100.0f)), 8 + esphptextsize, 1);
            }
            else {
                DrawText(Color(255,255, 255, 255), std::to_string(armor).c_str(), Vec22(x - esphpsize - 8 - (esphpsize/2) + ((y - y2) / 4), getHeight() - y + (y - y2) * (float(armor) / 100.0f)), 8 + esphptextsize);
            }
        }
        if (esphealth) {
            DrawFilledRect(hpcolor,  Vec22(x - esphpsize - 5  + ((y - y2) / 4), getHeight() - y + (y - y2) * (float(hp) / 100.0f)), Vec22(x - 5 + ((y - y2) / 4), getHeight() - y));

            if (esphpoutline) {
                DrawFilledRect(Color(0,0, 0, 100),  Vec22(x - esphpsize - 5 - 1  + ((y - y2) / 4), getHeight() - y2 - 1), Vec22(x  - 5 + 1 + ((y - y2) / 4), getHeight() - y + 1));
                DrawTextOutline(Color(255,255, 255, 255), std::to_string(hp).c_str(), Vec22(x - (esphpsize/2) - 5 + ((y - y2) / 4), getHeight() - y + (y - y2) * (float(hp) / 100.0f)), 8 + esphptextsize, 1);
            }
            else {
                DrawText(Color(255,255, 255, 255), std::to_string(hp).c_str(), Vec22(x - (esphpsize/2) - 5 + ((y - y2) / 4), getHeight() - y + (y - y2) * (float(hp) / 100.0f)), 8 + esphptextsize);
            }
        }
        if (esptracer) {
            DrawLine(Color(255,255, 255, 255), 2, Vec22(getWidth() / 2, getHeight()), Vec22(x, getHeight() - y));
        }
        if (espname) {
            if (espnameoutline) {
                DrawTextOutline(Color(255,255, 255, 255), name, Vec22(x, getHeight() - y2 - 5), 10 + espnamesize, 1);
            }
            else {
                DrawText(Color(255,255, 255, 255), name, Vec22(x, getHeight() - y2 - 5), 10 + espnamesize);
            }
        }
        if (espweapon) {
            DrawTextOutline(Color(255,255, 255, 255), (weapon + " | " + std::to_string(ammo)).c_str(), Vec22(x, getHeight() - y + 10 + espnamesize), 10 + espnamesize, 1);
        }
    }

    void DrawFilledRectGlowy(Color color, Vec22 start, Vec22 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawFilledRectGlowy",
                                                   "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 start.x, start.y, end.x, end.y);
        }
    }
    void Draw3dEspBox(Vec22 a, Vec22 b, Vec22 c, Vec22 d, Vec22 e, Vec22 f, Vec22 g, Vec22 h,  Vec22 down,Vec22 up, int hp, const char *name) {

        a.y = getHeight() - a.y;
        b.y = getHeight() - b.y;
        c.y = getHeight() - c.y;
        d.y = getHeight() - d.y;
        e.y = getHeight() - e.y;
        f.y = getHeight() - f.y;
        g.y = getHeight() - g.y;
        h.y = getHeight() - h.y;
        int x = down.x;
        int x2 = up.x;
        int y = down.y;
        int y2 = up.y;

        if (espbox) {
            DrawLine(Color(255,255, 255, 255), 5, a, b);
            DrawLine(Color(255,255, 255, 255), 5, b, c);
            DrawLine(Color(255,255, 255, 255), 5, c, d);
            DrawLine(Color(255,255, 255, 255), 5, d, a);

            DrawLine(Color(255,255, 255, 255), 5, e, f);
            DrawLine(Color(255,255, 255, 255), 5, f, g);
            DrawLine(Color(255,255, 255, 255), 5, g, h);
            DrawLine(Color(255,255, 255, 255), 5, h, e);

            DrawLine(Color(255,255, 255, 255), 5, a, e);
            DrawLine(Color(255,255, 255, 255), 5, b, f);
            DrawLine(Color(255,255, 255, 255), 5, c, g);
            DrawLine(Color(255,255, 255, 255), 5, d, h);
        }
        if (esphealth) {
            if (esphpoutline) {
                DrawFilledRect(Color(0,0, 0, 255),  Vec22(x - esphpsize - 5 - 1  + ((y - y2) / 4), getHeight() - y2 - 1), Vec22(x  - 5 + 1 + ((y - y2) / 4), getHeight() - y + 1));
                DrawTextOutline(Color(255 - (hp * 2.55),hp * 2.55, 0, 255), std::to_string(hp).c_str(), Vec22(x  - 15 - esphpsize + ((y - y2) / 4), getHeight() - y + (y - y2) * (float(hp) / 100.0f)), 8 + esphptextsize, 1);
            }
            else {
                DrawText(Color(255 - (hp * 2.55),hp * 2.55, 0, 255), std::to_string(hp).c_str(), Vec22(x  - 15 - esphpsize + ((y - y2) / 4), getHeight() - y + (y - y2) * (float(hp) / 100.0f)), 8 + esphptextsize);
            }
            DrawFilledRect(Color(255 - (hp * 2.55),hp * 2.55, 0, 255),  Vec22(x - esphpsize - 5  + ((y - y2) / 4), getHeight() - y + (y - y2) * (float(hp) / 100.0f)), Vec22(x - 5 + ((y - y2) / 4), getHeight() - y));
        }
        if (esptracer) {
            DrawLine(Color(255,255, 255, 255), 5, Vec22(getWidth() / 2, getHeight()), Vec22(x, getHeight() - y));
        }
        if (espname) {
            if (espnameoutline) {
                DrawTextOutline(Color(255,255, 255, 255), name, Vec22(x, getHeight() - y2 - 10), 8 + espnamesize, 1);
            }
            else {
                DrawText(Color(255,255, 255, 255), name, Vec22(x, getHeight() - y2 - 10), 8 + espnamesize);
            }
        }
    }

    void DrawBulletTracer(int x, int y, int x2, int y2) {
        DrawLine(Color(255,255, 255, 255), 5, Vec22(x, getHeight() - y), Vec22(x2, getHeight() - y2));
        DrawCrosshair(Color(77,111, 192, 255), Vec22(x2, getHeight() - y2), 100);
    }


    void DrawPoint(Color color, Vec22 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawfilledcircle = _env->GetMethodID(canvasView, "DrawPoint",
                                                           "(Landroid/graphics/Canvas;IIIIFFF)V");
            _env->CallVoidMethod(_cvsView, drawfilledcircle, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, pos.x, pos.y, radius);
        }
    }
    void DrawTextDistance(Color color, const char *txt, Vec22 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtextdistance = _env->GetMethodID(canvasView, "DrawTextDistance",
                                                           "(Landroid/graphics/Canvas;IIIILjava/lang/String;FFF)V");
            jstring s=_env->NewStringUTF(txt);
            _env->CallVoidMethod(_cvsView, drawtextdistance, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 s, pos.x, pos.y, size);
            _env->DeleteLocalRef(s);
        }
    }

    void DrawTextName(Color color, const char *txt, Vec22 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawTextName",
                                                   "(Landroid/graphics/Canvas;IIIILjava/lang/String;FFF)V");
            jstring s=_env->NewStringUTF(txt);
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 s, pos.x, pos.y, size);
            _env->DeleteLocalRef(s);
        }
    }

    void DrawTextAltert(Color color, const char *txt, Vec22 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtextalert = _env->GetMethodID(canvasView, "DrawTextAltert",
                                                        "(Landroid/graphics/Canvas;IIIILjava/lang/String;FFF)V");
            jstring s=_env->NewStringUTF(txt);
            _env->CallVoidMethod(_cvsView, drawtextalert, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 s, pos.x, pos.y, size);
            _env->DeleteLocalRef(s);
        }
    }
    void DrawTextAltert2(Color color, const char *txt, Vec22 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtextalert = _env->GetMethodID(canvasView, "DrawTextAltert2",
                                                        "(Landroid/graphics/Canvas;IIIILjava/lang/String;FFF)V");
            jstring s=_env->NewStringUTF(txt);
            _env->CallVoidMethod(_cvsView, drawtextalert, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 s, pos.x, pos.y, size);
            _env->DeleteLocalRef(s);
        }
    }

    void DrawWeapon(Color color, int wid,int ammo,int ammo2, Vec22 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawWeapon",
                                                   "(Landroid/graphics/Canvas;IIIIIIFFF)V");
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 wid,ammo,ammo2, pos.x, pos.y, size);
        }
    }
    void DrawName(Color color, const char *txt,int teamid, Vec22 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawName",
                                                   "(Landroid/graphics/Canvas;IIIILjava/lang/String;IFFF)V");
            jstring s=_env->NewStringUTF(txt);
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 s,teamid, pos.x, pos.y, size);
            _env->DeleteLocalRef(s);
        }
    }
    void DrawItems(const char *txt, float distance, Vec22 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawItems",
                                                   "(Landroid/graphics/Canvas;Ljava/lang/String;FFFF)V");
            jstring s=_env->NewStringUTF(txt);
            _env->CallVoidMethod(_cvsView, drawtext, _cvs,
                                 s,distance, pos.x, pos.y, size);
            _env->DeleteLocalRef(s);
        }
    }
    void DrawVehicles(const char *txt, float distance, Vec22 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawVehicles",
                                                   "(Landroid/graphics/Canvas;Ljava/lang/String;FFFF)V");
            jstring s=_env->NewStringUTF(txt);
            _env->CallVoidMethod(_cvsView, drawtext, _cvs,
                                 s ,distance, pos.x, pos.y, size);
            _env->DeleteLocalRef(s);
        }
    }
    void DrawFilledCircle(Color color, Vec22 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawfilledcircle = _env->GetMethodID(canvasView, "DrawFilledCircle",
                                                           "(Landroid/graphics/Canvas;IIIIFFF)V");
            _env->CallVoidMethod(_cvsView, drawfilledcircle, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, pos.x, pos.y, radius);
        }
    }
    void DrawHead(Color color, Vec22 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawhead = _env->GetMethodID(canvasView, "DrawHead",
                                                   "(Landroid/graphics/Canvas;IIIIFFF)V");
            _env->CallVoidMethod(_cvsView, drawhead, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, pos.x, pos.y, radius);
        }
    }

    void Drawcount() {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "Drawcount",
                                                   "(Landroid/graphics/Canvas;IFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs);
        }
    }

    void DrawCircle(Color color,float stroke, Vec22 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawcircle = _env->GetMethodID(canvasView, "DrawCircle",
                                                     "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawcircle, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,stroke, pos.x, pos.y, radius);
        }
    }

    void DrawCrosshair(Color clr, Vec22 center, float size = 10) {
        float x = center.x - (size / 2.0f);
        float y = center.y - (size / 2.0f);
        DrawLine(clr, 1, Vec22(x, center.y), Vec22(x + size, center.y));
        DrawLine(clr, 1, Vec22(center.x, y), Vec22(center.x, y + size));
    }

};


#endif //DESI_ESP_IMPORTANT_ESP_H
