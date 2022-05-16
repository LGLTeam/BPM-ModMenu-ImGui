#ifndef STANDOFF0171_FUNC_H
#define STANDOFF0171_FUNC_H

#include "defines.h"
#include "tools.h"
#include "hooks.h"
#include "xx.h"
#include "ByNameModding.h"
#include "drawer.h"
#include "field_offsets.h"
#include "opengl.h"


#include <list>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <chrono>
#include <dlfcn.h>
#include <sstream>
#include <codecvt>
#include <iostream>


Field<bool> inAirF;
Field<bool> inAttackKeyF;
Field<bool> inFreezeF;
Field<bool> inZoomF;
Field<bool> inJumpKeyF;
Field<float> freezetimeF;
Field<monoString*> playernameF;
Field<monoString*> signF;
Field<monoString*> gameidF;
Field<monoString*> gamekeyF;
Field<monoArray<void**>*> playersF;

#define FIELDFUNCTION(a,b,c) (*(a*) ((uint64_t) b + c))
#define InitField(offset,name_space,classs,field) (offset = LoadClass(name_space, classs).GetFieldOffset(field))

bool drawaim1;
bool drawaim2;

bool drawcircle;
bool drawcrosschair;

bool drawcircle2;
bool drawcrosschair2;
int circlestroke2 = 3;
int circlesize2 = 45;

int crosschairsize = 30;
int circlestroke = 3;
float circlesize = 10;
float circlesize22 = 10;
int vel = 45;


int idtoset = 0;
void* checkPlayer;

bool ovFakelags = false;

std::vector<char> StdStringToStdVector(std::string string) {
    std::vector<char> v(string.begin(), string.end());
    return v;
}

std::string StdVectorToStdString(std::vector<char> string) {
    std::string s(string.begin(), string.end());
    return s;
}

void procrypt(std::string &data) {
    const std::string key = "JIJJIJIJIIJJIJIJIJIJIIJJIJJ";
    for (size_t i = 0; i != data.size(); i++) {
        data[i] ^= key[i % key.size()];
    }
}
void* (*AddComponent)(void* position, void* text);
bool watermark = false;
bool debbuger = false;
bool indicators = false;
bool fakelagOnPeek;
bool fakelagOnMove;
bool fakelagOnStand;
bool fakelagOnAir;
monoArray<void**>*playerss;
int customWidth = 100;
int customHeight = 100;
int fireDelay = 0;
int maxDelay = 0;
bool AutoStop = false;
bool AimHead = false;
bool AimArms = false;
bool AimBody = false;
bool third = false;
bool AimLegs = false;
bool espprev = false;
Vector3 Camerapos = Vector3(0,0,0);
monoString *CreateMonoString(const char *str) {
    //private unsafe string CreateString(sbyte* value)
    return CreateMonoString(str,monoString::CreateMethod::C_LIKE);
}
void* RealCamera;
void (*Camera$$set_backgroundColor)(uintptr_t, Color);
void (*Camera$$set_nearClipPlane)(uintptr_t, float);
void (*SetActiveConsole)(bool);
void* espinst;
int scopeValue = 0;
struct circle_info {
public:
    Vector3 pos1 = Vector3(0,0,0);
    Vector3 pos2 = Vector3(0,0,0);

    Vector3 w2s1 = Vector3(0,0,0);
    Vector3 w2s2 = Vector3(0,0,0);
};
deque<circle_info> circle_data;
void*testTransform;
struct hit_log {
public:
    void* player;
    int hitbox;
    int animation;
    bool miss;
    int AimedHitBox;
};
deque<hit_log> hit_logs;
struct enemy_t {
    void *object;
    bool isVisible = false;
    int health = 0;
    int armor = 0;
    int ammo = 0;
    std::string name = " ";
    std::string weapon = " ";
    Vector3 pos = Vector3(0,0,0);
    Vector3 rot = Vector3(0,0,0);
    Vector3 wts1 = Vector3(0,0,0);
    Vector3 wts2 = Vector3(0,0,0);
};
class ESPManager {
public:
    std::vector<enemy_t *> *enemies;
    ESPManager() {
        enemies = new std::vector<enemy_t *>();
    }
    bool isEnemyPresent(void *enemyObject) {
        if (!enemies->empty()) {
            for (std::vector<enemy_t *>::iterator it = enemies->begin();
                 it != enemies->end(); it++) {
                if ((*it)->object == NULL) {
                    removeEnemyGivenObject((*it)->object);
                    return false;
                }
                if ((*it)->object == enemyObject) {
                    return true;
                }
            }
        }
        return false;
    }
    void tryAddEnemy(void *enemyObject,bool isVis) {
        if (isEnemyPresent(enemyObject)) {
            return;
        }
        if (enemyObject == NULL) {
            enemies->clear();
            return;
        }
        enemy_t *newEnemy = new enemy_t();
        newEnemy->object = enemyObject;
        enemies->push_back(newEnemy);
    }
    void updateEnemies() {
        if (!enemies->empty()) {
            for (int i = 0; i < enemies->size(); i++) {
                enemy_t *current = (*enemies)[i];
                if (current->object == NULL) {
                    enemies->erase(enemies->begin() + i);
                }
            }
        }
    }
    void removeEnemyGivenObject(void *enemyObject) {
        if (!enemies->empty()) {
            for (int i = 0; i < enemies->size(); i++) {
                if ((*enemies)[i]->object == enemyObject) {
                    enemies->erase(enemies->begin() + i);
                }
            }
            return;
        }
        return;
    }
};
ESPManager *espManager;
bool checkkk = false;
void (*PlayDefuseEnd)();
void (*PlayDefuseStart)();
void (*PlayHitMark)();
void (*PlayHitMarkObj)();
void (*PlayHitSelf)();
void (*PlayMiss)();
void (*PlayRoundEnd)();
void (*send_hardtosoftt)(void*);
void (*send_spawn)(void*);
bool materialEnabled = false;
int materialGlossiness = 0;
int materialGlossinessScale = 0;
int materialMetallic = 0;
int materialCutoff = 0;
int materialSpecular = 0;
int materialReflections = 0;
int materialBump = 0;
int materialOcclusion = 0;
bool materialPulseTex = false;
bool materialRainbowTex = false;
int materialRedTex = 0;
int materialGreenTex = 0;
int materialBlueTex = 0;
bool materialPulseEmission = false;
bool materialRainbowEmission = false;
int materialRedEmission = 0;
int materialGreenEmission = 0;
int materialBlueEmission = 0;
void (*CreatePlayerObject)(void*,void*,int,int);
void (*SetResolution)(int width, int height, bool fullscreen);
void (*UnityText)(Rect position, monoString* text);
void (*DrawTexture)(Rect position, void* image);
void* (*Texture2D)(Il2CppObject *,int width, int height,int,bool);
void (*SetPixel)(void* t, int x, int y, Color color);
void (*Apply)(void* t);
Il2CppObject *(*FindObjectOfType)( Il2CppClass* typeStr);
void*(*GetType2)( monoString* typeStr);
monoArray<void**>*(*GetComponent)( void*,void*,bool);
monoArray<void**>*(*FindObjectsOfType)( void*);
void*(*GetMaterial)( void*);
void(*SetMaterial)( void*,void*);
void(*SetShader)( void*,void*);
void*(*FindShader)( monoString*);
void(*SetIntMaterial)( void*,monoString*,float);
void(*SetColorMaterial)( void*,monoString*,Color);
void(*SetTextureMaterial)( void*,monoString*,void*);
void(*DisableCollider)( void*,bool);
monoList<void* *> *attackList;
int rgbSpeed = 1;
int pulseSpeed = 1;
Vector3 (*_GetForward)(void *players);
void *(*_Camera_main)(void *nuls);
static Vector3 get_forward(void *player) {
    return _GetForward(player);
}
static void *get_main() {
    return _Camera_main(NULL);
}
uintptr_t (*Camera$$get_main)();
Vector3 (*world2screen)(void *camera, Vector3 pos, int test);
Vector3 (*GetPlayerPos)();
Vector3 (*GetPlayerCameraPos)();
Vector3 (*GetPlayerSpeed)();
float (*GetWeaponSpeed)(void*);
Quaternion (*GetPlayerRot)(void *);
float (*get_deltaTime)();
float (*GetSpread)(void*);
int (*get_screen_width)();
int (*get_screen_height)();
void (*SetVisible)(void*,void*, bool);
bool infFov = false;
bool damagePr = false;
void (*Camera$$set_clearFlags)(uintptr_t, int32_t);
void (*Camera$$set_clearFlags2)(uintptr_t, int32_t);
bool aimbot, aimsmooth = false;
int vR,vG,vB = 0;
int invR,invG,invB = 0;
const char * ise[2];
const char * kolan[2];
const char * altfy[2];
const char * seekbar[2];
void (*Transform_SetRotation)(void *transform, Quaternion newRotation);
void (*SetFollow)(void *transform, void*testt);
void* (*GetFollowTransform)(void *transform);
void (*SetCharacterActive)(bool);
void (*SetProgressActive)(bool);
void (*SetWeaponActive)(bool);
void (*SetAnimatorActive)(bool);
void (*set_ambient)(int);
void (*SetDist)(void *transform, float testt);
void* camera;
void (*set_timeScale)(float send_pos);
void (*SetFov)(float, float);
void *instancee;
bool (*RaycastPlayer)(void*po, Vector3 pos, float maxdist);
bool (*RaycastPlayerFixed)(Vector3 pos, Vector3 pos1, RaycastHit &maxdist);
void (*AddPrimeItems)(void*,void *);
Quaternion (*get_rotation)(void*);
void (*EnableFog)(bool);
void (*SetFogColor)(Color);
void (*SetFogMode)(int);
void* (*get_collider)(RaycastHit);
monoString* (*get_name)(void*);
void* (*GetItem)(int,int);
bool autofire;
bool autoscope;
void (*StartDefuse)(int slot, int uid);
void *(*get_transformCamera)(void *component);
void (*Camera$$set_farClipPlane)(uintptr_t, float);
void (*Camera$$set_fieldOfView)(uintptr_t, float);
Quaternion lookRotation;
void (*Transform_get_position)(void *transform, Vector3 *out);
Vector3 get_position(void *player) {
    Vector3 pos;
    Transform_get_position(player, &pos);
    return pos;
}
Quaternion GetRotationToLocation(Vector3 targetLocation, float y_bias, Vector3 myLoc){
    return Quaternion::LookRotation((targetLocation + Vector3(0, y_bias, 0)) - myLoc, Vector3(0, 1, 0));
}
bool bulletTracer;
bool hitMarker;
bool playerList;
bool radar;
int hitMarkerR;
int hitMarkerG;
int hitMarkerB;
int bulletTracerR;
int bulletTracerG;
int bulletTracerB;
int radarZoom = 3;
int radarScale = 100;
int SpeedValue = 1;
int JumpValue = 1;
bool playerCircle;
bool drawvel = false;
bool playerLine = false;
bool skins = false;
bool characters = false;
bool weapons = false;
bool detect, feature1, spam,lerp1, spinbot, setweap, masskill, feature2, featureHookToggle, feature3, feature4, feature5, feature6,Respawn, feature7, feature8, feature9, feature10, feature11, feature12, feature14, feature15, feature16, feature13, feature20, feature21, feature22, feature23, weappos,espenable,visible, feature24, feature25, feature26, feature27, feature28, feature29, feature30,ctknife,tknife, feature31, feature32,rrgb1,rrgb2,rrgb3, wwh1, wwh2, wwh3, bhop, strafe, aimlock = false;
int sliderValue = 0, sliderValue1 = 1, sliderValue2 = 1, sliderValue3 = 1, sliderValue4 = 7,  dmgmul = 1, sound = 0, defmul = 1, skymode = 1, skycolorr = 0, skycolorg = 0, skycolorb = 0, valueFromInput, XPOS, YPOS, ZPOS, NEAR, FAR, ctId = 1, tId = 1,tKnife = 0,ctKnife = 0;
void (*AddMoneyExample)(void *instance, int amount);
void*itemtest;
void (*old_send_name)(void *instance, monoString* newname);
void send_name(void *instance, monoString* newname) {
    old_send_name(instance, newname);
}
Vector3 enemypos = Vector3(0,0,0);
Vector3 aimedplayerpos2 = Vector3(0,0,0);
int slote;
void *WeaponInst;
bool aiming2 = false;
bool aiming = false;
bool playerInFov = false;
void *AddWeaponinst;
void (*old_AddWeapon1)(void *instance, int slot, int itemid, int uid, int skinid, int muzzleid, int foregripid, int magazineid, int scopeid, int stockid);
void AddWeapon1(void *instance, int slot, int itemid, int uid, int skinid, int muzzleid, int foregripid, int magazineid, int scopeid, int stockid){
    LOGD(("slot: %d | itemid: = %d | uid: = %d | skinid: %d | muzzleid: = %d | foregripid: = %d | magazineid: = %d | scopeid: = %d | stockid: = %d"), slot,  itemid,  uid,  skinid,  muzzleid,  foregripid,  magazineid,  scopeid,  stockid);
    if (instance) {
        AddWeaponinst = instance;
    }
    if (slot == 14 && tKnife != 0) {
        old_AddWeapon1(instance, tKnife,  itemid,  tId,  skinid,  muzzleid,  foregripid,  magazineid,  scopeid,  stockid);
    }
    else if (slot == 31 && ctKnife != 0) {
        old_AddWeapon1(instance, ctKnife,  itemid,  ctId,  skinid,  muzzleid,  foregripid,  magazineid,  scopeid,  stockid);
    }
        /*else if (slot == 69) {
            old_AddWeapon1(instance, 69,  itemid,  tId + 76,  skinid,  muzzleid,  foregripid,  magazineid,  scopeid,  stockid);
        }
        else if (slot == 1) {
            old_AddWeapon1(instance, slot,  itemid,  76,  skinid,  muzzleid,  foregripid,  magazineid,  scopeid,  stockid);
        }
        else if (slot == 32) {
            old_AddWeapon1(instance, slot,  itemid,  39,  skinid,  muzzleid,  foregripid,  magazineid,  scopeid,  stockid);
        }*/
    else {
        old_AddWeapon1(instance, slot,  itemid,  uid,  skinid,  muzzleid,  foregripid,  magazineid,  scopeid,  stockid);
    }
}
void (*old_setfov)(void *instance, float p);
void setfov(void *instance, float p){
    if (instance) {
        p *= float(sliderValue1 + 49) / 50;
    }
    old_setfov(instance, p);
}
void (*old_SetWeapon)(void *instance, int v, void* it, int slot);
void SetWeapon(void *instance, int v, void* it, int slot) {
    if (instance) {

        int idddd = FIELDFUNCTION(int,it,GameClass$BaseItemInfo$id);
        slote = idddd;
        if (idddd == 14) {
            FIELDFUNCTION(int,it,GameClass$BaseItemInfo$id) = ctKnife;
        }
        if (idddd == 31) {
            FIELDFUNCTION(int,it,GameClass$BaseItemInfo$id) = tKnife;
        }

    }
    old_SetWeapon(instance, v, it, slot);
}
monoArray<int*>*buyArray;
void (*old_AddPrimeItems)(void *instance, monoArray<int*>* b);
void _AddPrimeItems(void *instance, monoArray<int*>* b) {
    buyArray = b;
    old_AddPrimeItems(instance, b);
}
int bulletanimation = 255;
struct hit_info {
public:
    Vector3 w2s;
    Vector3 pos;

    Vector3 w2sCamera;
    Vector3 posCamera;

    int animation;

};
bool setWeapon = false;
deque<hit_info>hit_data;
int aimedHitBoxId = 0;
bool logs1 = false;
bool doubletap = false;
bool doubletap1 = false;
void (*old_send_attack)(void *instance,monoList<void* *> *players);
void send_attack(void *instance,monoList<void* *> *players) {
    ovFakelags = true;
    doubletap1 = !doubletap1;
    bulletanimation = 255;
    attackList = players;
    if (camera && instance) {

        for (int i = 0; i < players->getSize(); i++) {


            void* hitdata = attackList->getItems()[i];
            if (hitdata) {
                Vector3 hitPos = FIELDFUNCTION(Vector3,hitdata,GameClass$HitData$p);

                if (hitPos != Vector3()) {

                    int id = FIELDFUNCTION(int,hitdata,GameClass$HitData$id);
                    int vbox = FIELDFUNCTION(int,hitdata,GameClass$HitData$hb);
                    void* playerr;
                    if (playerss != NULL) {
                        for (int e = 0; e < playerss->getLength(); e++) {
                            if (playerss->getPointer()[e]) {
                                int plId = FIELDFUNCTION(int,playerss->getPointer()[e],GameClass$PlayerData$id);
                                if (id == plId) {
                                    playerr = playerss->getPointer()[e];
                                }
                            }
                        }

                        if (hit_logs.size() > 10) {
                            hit_logs.pop_front();
                        }
                        hit_logs.push_back({ playerr, vbox, 255, false, aimedHitBoxId });
                    }

                    Vector3 positionScreen = world2screen(camera, hitPos,2);
                    Vector3 positionScreenCam = world2screen(camera, Camerapos, 2);

                    hit_data.push_back({ positionScreen, hitPos, positionScreenCam, Camerapos, 255});

                    if (hit_data.size() > 50) {
                        hit_data.pop_front();
                    }
                }
            }
        }
        if (players == NULL || players->getSize() == 0) {
            if (hit_logs.size() > 10) {
                hit_logs.pop_front();
            }
            hit_logs.push_back({ NULL, 0, 255, true, aimedHitBoxId });

        }
    }
    old_send_attack(instance,players);
}
Vector3 Forw;
float minimalangle = 999;
float minimalangle2 = 999;
bool visibletest;
bool testtt;
Color color;
struct velo_info {
public:
    int velocity;
    bool on_ground;
};
deque<velo_info>velocity_data;
struct position_info {
public:
    bool visible;
    Vector3 w2s;
    Vector3 pos;
    bool on_ground;
    Color color;
};
deque<position_info>position_data;
Vector3 Vel;
bool slide;
bool fakelagRandom;
int fakelagValue;

int PitchValue;
int YawValue;

int PitchValue1;
int YawValue1;
#define BYTE uint8_t
static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
static inline bool is_base64(BYTE c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}
std::string base64_encode(BYTE const* buf, unsigned int bufLen) {
    std::string ret;
    int i = 0;
    int j = 0;
    BYTE char_array_3[3];
    BYTE char_array_4[4];

    while (bufLen--) {
        char_array_3[i++] = *(buf++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for(i = 0; (i <4) ; i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while((i++ < 3))
            ret += '=';
    }

    return ret;
}

std::vector<BYTE> base64_decode(std::string const& encoded_string) {
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    BYTE char_array_4[4], char_array_3[3];
    std::vector<BYTE> ret;

    while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret.push_back(char_array_3[i]);
            i = 0;
        }
    }

    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;

        for (j = 0; j <4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) ret.push_back(char_array_3[j]);
    }

    return ret;
}
int PitchSpeed;
int YawSpeed;
bool randomslide;
bool fakeduck;
bool inAir;
int bitmaskkk = 0;
bool SkyRender = false;
bool RgbSky = false;
bool SkyColor = false;
bool SkyPulse = false;
int SkyColorR = 0;
int SkyColorG = 0;
int SkyColorB = 0;
bool antiaim = false;
bool desync = false;
bool randomYaw = false;
bool spinbot1Yaw = false;
bool spinbot2Yaw = false;
bool randomPitch = false;
bool spinbot1Pitch = false;
bool spinbot2Pitch = false;

bool randomm = false;
bool Scopee = false;
bool freezetime = false;
int circleanimation = 0;
int screen_width;
int screen_height;
Vector3 playerRottt = Vector3(0,0,0);
Vector3 playerPosss = Vector3(0,0,0);
void *WeaponObject;
bool drawingCircle = false;
std::string playername = "";

void* (*old_CreateItem)(void *instance, int type, int wid, int uid, int menu, monoString* sign, int cat);
void* CreateItem(void *instance, int type, int wid, int uid, int menu, monoString* sign, int cat) {
    LOGI(" type: %d, wid: %d, uid: %d, menu: %d, cat: %d, sign: %s", type,wid,uid,menu,cat,sign->get_string().c_str());

    if (type == 0 && wid == 31 && weapons) {
        for (int i = 1; i < 150; i++) {
            old_CreateItem(instance,  type,  i,  uid,  menu,  sign,  cat);
        }
    }

    if (type == 2 && skins) {
        //old_CreateItem(instance,  type,  wid,  uid,  menu,  sign,  cat);
        for (int i = 1; i <= 79; i++) {
            old_CreateItem(instance,  type,  i, 777,  menu,  CreateMonoString("_"),  cat);
        }
    }

    if (type == 1 && characters) {
        old_CreateItem(instance,  type,  2,  777,  menu,  CreateMonoString("_"),  cat);
        old_CreateItem(instance,  type,  3,  777,  menu,  CreateMonoString("_"),  cat);
        old_CreateItem(instance,  type,  4,  777,  menu,  CreateMonoString("_"),  cat);
        old_CreateItem(instance,  type,  5,  777,  menu,  CreateMonoString("_"),  cat);
    }
    for (int i = 0; i < 100; i++) {
        old_CreateItem(instance,  3,  1,  777,  2,  CreateMonoString(""),  2);
        old_CreateItem(instance,  3,  2,  777,  2,  CreateMonoString(""),  2);
        old_CreateItem(instance,  3,  3,  777,  2,  CreateMonoString(""),  2);
        old_CreateItem(instance,  3,  4,  777,  2,  CreateMonoString(""),  2);
        old_CreateItem(instance,  3,  5,  777,  2,  CreateMonoString(""),  2);
        old_CreateItem(instance,  3,  6,  777,  2,  CreateMonoString(""),  2);
    }
    return old_CreateItem(instance,  type,  wid,  uid,  menu,  sign,  cat);
}
std::string t;
void (*old_Weapon)(void *lol1);
void _Weapon(void *lol1) {
    bool loaded = true;
    if (lol1 != NULL)
    {
        WeaponInst = lol1;
        WeaponObject = FIELDFUNCTION(void*,lol1,$Shooter$currweapon);
        if (WeaponObject != NULL) {
            if (feature15) {
                FIELDFUNCTION(float,WeaponObject,GameClass$WeaponObject$recoilhorizontal) = 0;
                FIELDFUNCTION(float,WeaponObject,GameClass$WeaponObject$recoilvertical) = 0;
            }
            if (feature12) {
                FIELDFUNCTION(float,WeaponObject,GameClass$WeaponObject$spread) = 0;
            }
            if (featureHookToggle) {
                FIELDFUNCTION(float,WeaponObject,GameClass$WeaponObject$firerate) = 0;
            }
            if (feature29) {
                FIELDFUNCTION(int,WeaponObject,GameClass$WeaponObject$_clip) = 228;
            }
        }
        if (!third) {
            if (weappos) {
                FIELDFUNCTION(Vector3,lol1,$Shooter$vOffsetPos) = Vector3(float(XPOS) / 50, float(YPOS) / 50, float(ZPOS) / 50);
            }
            else {
                FIELDFUNCTION(Vector3,lol1,$Shooter$vOffsetPos) = Vector3(0,0,0);
            }
        }
        else {
            FIELDFUNCTION(Vector3,lol1,$Shooter$vOffsetPos) = Vector3(0,0,999);
        }

    }
    old_Weapon(lol1);
}
bool jumploaded = true;
void* espTexture;
static void RectFilled(float x, float y, float width, float height, void* text)
{
    DrawTexture(Rect(x, y, width, height), text);
}
static void RectOutlined(float x, float y, float width, float height, void* text, float thickness = 1.0f)
{
    RectFilled(x, y, thickness, height, text);
    RectFilled(x + width - thickness, y, thickness, height, text);
    RectFilled(x + thickness, y, width - thickness * 2.0f, thickness, text);
    RectFilled(x + thickness, y + height - thickness, width - thickness * 2.0f, thickness, text);
}
static void Box(float x, float y, float width, float height, void* text, float thickness = 1.0f)
{
    RectOutlined(x - width / 2.0f, y - height, width, height, text, thickness);
}


int updatefps = 20;
void (*old_Jump_Update)(void *Jump);
void Jump_Update(void *Jump) {
    LOGI("JUMP1");
    old_Jump_Update(Jump);
    updatefps--;
    checkPlayer = Jump;
    if (Jump != NULL) {
        LOGI("JUMP2");
        if (updatefps <= 1) {
            vel = 1 / get_deltaTime();

            camera = get_main();
            inAir = inAirF;
            updatefps = 20;
        }
        LOGI("JUMP3");
        if (materialEnabled) {
            
            
            monoArray<void**>*objArray = FindObjectsOfType(GetType2(CreateMonoString("UnityEngine.SkinnedMeshRenderer, UnityEngine")));
            if (objArray) {
                for (int i = 0; i < objArray->getLength(); i++) {
                    void* obj = objArray->getPointer()[i];
                    if(obj) {
                        //auto test = LoadClass("UnityEngine", "Material", false);
                        //monoString *t1 = CreateMonoString(R"(Shader "Custom/Cham"{\tSubShader \t{\t\tPass \t\t{\t\t\tZTest Less\t\t\tZWrite On\t\t\tColor (0,255,255,1) \t\t}\t\tPass \t\t{\t\t\tZTest Greater\t\t\tZWrite Off\t\t\tColor (0,255,255,1)\t\t}\t}})");
                        //void* args[] = {&t1};
                        //void* chamsMaterial = test.CreateNewClass(args, 1, {"contents"});
                        //monoArray<void**>*comp = GetComponent(obj,GetType2(CreateMonoString("UnityEngine.MeshCollider, UnityEngine.PhysicsModule")), true);
                        SetShader(GetMaterial(obj),FindShader(CreateMonoString("Standard")));
                        //SetIntMaterial(GetMaterial(obj),CreateMonoString("_ZTest"), 8);
                        SetColorMaterial(GetMaterial(obj),CreateMonoString("_EmissionColor"), Color(1,1,1));
                        SetColorMaterial(GetMaterial(obj),CreateMonoString("_Color"), Color(float(materialRedTex)/1000,float(materialGreenTex)/1000, float(materialBlueTex)/1000,0.5));
                        //SetColorMaterial(GetMaterial(obj),CreateMonoString("_MainTex"), Color(1,1, 1));

                        if (materialPulseTex) {
                            SetTextureMaterial(GetMaterial(obj),CreateMonoString("_MainTex"), NULL);
                            SetTextureMaterial(GetMaterial(obj),CreateMonoString("_MetallicGlossMap"), NULL);

                        }


                        SetIntMaterial(GetMaterial(obj),CreateMonoString("_Cutoff"), (float)materialCutoff/10);
                        SetIntMaterial(GetMaterial(obj),CreateMonoString("_Glossiness"), (float)materialGlossiness/10);
                        SetIntMaterial(GetMaterial(obj),CreateMonoString("_GlossMapScale"), (float)materialGlossinessScale/10);
                        SetIntMaterial(GetMaterial(obj),CreateMonoString("_Metallic"), (float)materialMetallic/100);
                        SetIntMaterial(GetMaterial(obj),CreateMonoString("_SpecularHighlights"), (float)materialSpecular/10);
                        SetIntMaterial(GetMaterial(obj),CreateMonoString("_GlossyReflections"), (float)materialReflections/10);
                        SetIntMaterial(GetMaterial(obj),CreateMonoString("_BumpScale"), (float)materialBump/10);
                        SetIntMaterial(GetMaterial(obj),CreateMonoString("_OcclusionStrength"), (float)materialOcclusion/10);
                        //SetMaterial(obj,chamsMaterial);
                    }
                }
            }
        }

        if (freezetime) {
            inFreezeF = false;
            freezetimeF = 0;
        }
        //DrawSphere(GetPlayerPos(), 10);
        //FieldBN(bool, 0, "", "Controll", "developer",1) = true;
        //FieldBN(bool, 0, "", "Controll", "killcam",1) = true;
        LOGI("JUMP4");
        screen_width = get_screen_width();
        screen_height = get_screen_height();
        LOGI("JUMP5");
        if (scopeValue > 0) {
            bool scoped = inZoomF;
            if (scoped) {
                SetFov(scopeValue, 200);
            }
        }
        LOGI("JUMP6");
        Vel = GetPlayerSpeed();
        LOGI("JUMP7");
        if (camera) {
            LOGI("CAMERA0");
            if (!espManager->enemies->empty()) {
                for (std::vector<enemy_t *>::iterator e = espManager->enemies->begin();
                     e < espManager->enemies->end(); e++) {
                    if ((*e)->object != NULL) {
                        void *player = (*e)->object;
                        if (player != NULL) {
                            LOGI("CAMERA1");
                            void *plobj = FIELDFUNCTION(void*,player,GameClass$PlayerData$po);
                            if (plobj) {
                                (*e)->isVisible = RaycastPlayer(plobj, Camerapos, 100);
                                if (true) {
                                    Vector3 pos = FIELDFUNCTION(Vector3,player,GameClass$PlayerData$lerpPos);
                                    Vector3 rot = FIELDFUNCTION(Vector3,player,0x94);

                                    (*e)->pos = pos;
                                    (*e)->rot = rot;

                                    Vector3 PosNew = Vector3(0, 0, 0);
                                    Vector3 PosNeww = Vector3(0, 0, 0);
                                    if (true) {
                                        PosNew = world2screen(camera, pos, 2);
                                        PosNeww = world2screen(camera,
                                                               Vector3(pos.x, pos.y + 2, pos.z),
                                                               2);

                                        (*e)->wts1 = PosNew;
                                        (*e)->wts2 = PosNeww;
                                    }

                                }
                                LOGI("CAMERA2");
                                (*e)->name = (FIELDFUNCTION(monoString*,player,GameClass$PlayerData$playername))->get_string();
                                (*e)->health = FIELDFUNCTION(int,player,GameClass$PlayerData$health);
                                if (true) {
                                    (*e)->armor = FIELDFUNCTION(int,player,GameClass$PlayerData$armor);
                                }
                                if (true) {
                                    void* weap1 = FIELDFUNCTION(void*,player,GameClass$PlayerData$currwpn);
                                    if (weap1 != NULL) {
                                        void* weap2 = FIELDFUNCTION(void*,weap1,GameClass$PlayerWeaponObject$it);
                                        if (weap2 != NULL) {
                                            monoString* weap3 = FIELDFUNCTION(monoString*,weap2,GameClass$BaseItemInfo$localname);
                                            if (weap3 != NULL) {
                                                (*e)->weapon = weap3->get_string();
                                            }
                                        }
                                    }
                                }
                                if ((*e)->armor == 0) {
                                    (*e)->armor = 100;
                                }

                                if (masskill) {
                                    FIELDFUNCTION(Vector3,player,GameClass$PlayerData$lerpPos) = Vector3(
                                            GetPlayerPos().x + 2, GetPlayerPos().y,
                                            GetPlayerPos().z);
                                    FIELDFUNCTION(Vector3,player,GameClass$PlayerData$prevPos) = Vector3(
                                            GetPlayerPos().x + 2, GetPlayerPos().y,
                                            GetPlayerPos().z);
                                    FIELDFUNCTION(Vector3,player,GameClass$PlayerData$Pos) = Vector3(
                                            GetPlayerPos().x + 2, GetPlayerPos().y,
                                            GetPlayerPos().z);
                                }
                                LOGI("CAMERA3");
                            }
                        }
                    }
                }
            }
            if (camera) {
                LOGI("CAMERA4");
                if (SkyColor) {
                    if (camera) {
                        if (SkyRender == false) {
                            Camera$$set_clearFlags2(Camera$$get_main(), 2);
                            if (RgbSky) {
                                if (SkyPulse) {
                                    Camera$$set_backgroundColor(Camera$$get_main(),
                                                                Color(float(red) / 255.0f *
                                                                      float(pulsevalue) / 100.0f,
                                                                      float(green) / 255.0f *
                                                                      float(pulsevalue) / 100.0f,
                                                                      float(blue) / 255.0f *
                                                                      float(pulsevalue) / 100.0f));
                                } else {
                                    Camera$$set_backgroundColor(Camera$$get_main(),
                                                                Color(float(red) / 255.0f,
                                                                      float(green) / 255.0f,
                                                                      float(blue) / 255.0f));
                                }
                            } else {
                                if (SkyPulse) {
                                    Camera$$set_backgroundColor(Camera$$get_main(),
                                                                Color(float(SkyColorR) / 255.0f *
                                                                      float(pulsevalue) / 100.0f,
                                                                      float(SkyColorG) / 255.0f *
                                                                      float(pulsevalue) / 100.0f,
                                                                      float(SkyColorB) / 255.0f *
                                                                      float(pulsevalue) / 100.0f));
                                } else {
                                    Camera$$set_backgroundColor(Camera$$get_main(),
                                                                Color(float(SkyColorR) / 255.0f,
                                                                      float(SkyColorG) / 255.0f,
                                                                      float(SkyColorB) / 255.0f));
                                }
                            }
                        } else {
                            Camera$$set_clearFlags2(Camera$$get_main(), 3);
                        }
                    }
                } else {
                    LOGI("CAMERA5");
                    Camera$$set_clearFlags2(Camera$$get_main(), 1);
                    LOGI("CAMERA6");
                }
            }
            LOGI("CAMERA7");
            Forw = get_forward(get_transformCamera(camera)) * 100.0f;
            Vector3 positionScreen = Vector3(0,0,0);
            if (playerLine) {
                positionScreen = world2screen(camera, GetPlayerPos(),2);
            }

            position_data.push_back({ false, positionScreen, GetPlayerPos(), inAir, Color(red,green,blue) });
            if (position_data.size() > 255) {
                position_data.pop_front();
            }
            for (auto i = 0; i < position_data.size(); i++)
            {
                if (playerLine) {
                    RaycastHit cast;
                    position_data[i].visible = true;
                    position_data[i].w2s = world2screen(camera, position_data[i].pos, 2);
                }
            }

            if (hitMarker || bulletTracer) {
                for (auto i = 0; i < hit_data.size(); i++)
                {
                    hit_data[i].w2s = world2screen(camera, hit_data[i].pos, 2);
                    hit_data[i].w2sCamera = world2screen(camera, hit_data[i].posCamera, 2);
                    hit_data[i].animation = hit_data[i].animation - 1;
                    if (hit_data[i].animation < 0) {
                        hit_data[i].animation = 0;
                    }
                }
            }


            for (auto i = 0; i < hit_logs.size(); i++)
            {
                hit_logs[i].animation = hit_logs[i].animation - 1;
                if (hit_logs[i].animation < 0) {
                    hit_logs[i].animation = 0;
                    hit_logs.erase(hit_logs.begin() + i);
                }
            }
            LOGI("CAMERA8");
        }
        else {
            espManager->enemies->clear();
        }
        LOGI("JUMP8");
        void *Example = FIELDFUNCTION(void*,Jump,KinematicCharacterController$ExamplePlayer$Character);
        void *Camera = FIELDFUNCTION(void*,Jump,KinematicCharacterController$ExamplePlayer$CharacterCamera);
        RealCamera = GetFollowTransform(Camera);
        if (Camera) {
            //set_ambient(3);
            if (third) {
                SetDist(Camera,3);
                //monoList<void**>*coll = *(monoList<void**>**) ((uint664_t) Camera + 0x54);
                //for (int i = 0; i < coll->getSize(); i++) {
                //    coll->getItems()[i] = NULL;
                //}
                //FieldBN(bool, 0, "", "Controll", "showbody",1) = true;
                //FieldBN(bool, 0, "", "Controll", "thirdperson",1) = true;
            }
            else {
                SetDist(Camera,0);
                //FieldBN(bool, 0, "", "Controll", "showbody",1) = false;
                //FieldBN(bool, 0, "", "Controll", "thirdperson",1) = false;
            }
        }
        if (aiming2 && aimbot && Camera && testTransform) {
            aiming2 = false;
            Quaternion lerped = Quaternion::Slerp(get_rotation(get_transformCamera(camera)),GetRotationToLocation(
                    aimedplayerpos2, 0,
                    GetPlayerCameraPos()), 0.5);


            if (aimsmooth) {

                //SetFollow(Camera, get_transformCamera(Example));
                //SetDist(Camera,5);
                //Transform_SetRotation(get_transformCamera(camera),lerped);
                //Transform_SetRotation(get_transformCamera(Camera),lerped);
            }
            else {
                //SetFollow(Camera, get_transformCamera(Example));
                // SetDist(Camera,5);

                //Transform_SetRotation(get_transformCamera(camera),lerped);
                //Transform_SetRotation(get_transformCamera(Camera),lerped);
            }
        }
        if (Example != NULL) {
            espinst = Example;
            if (feature23) {
                FIELDFUNCTION(bool,Example,KinematicCharacterController$ExampleCharacterController$_jumpConsumed) = false;
                FIELDFUNCTION(float,Example,KinematicCharacterController$ExampleCharacterController$_timeSinceLastAbleToJump) = 0;
            }
            if (bhop) {
                if (!FIELDFUNCTION(bool,Example,KinematicCharacterController$ExampleCharacterController$_jumpRequested) && !FIELDFUNCTION(bool,Example,KinematicCharacterController$ExampleCharacterController$_jumpedThisFrame)) {
                    if (inJumpKeyF) {
                        FIELDFUNCTION(bool,Example,KinematicCharacterController$ExampleCharacterController$_jumpRequested) = true;
                        FIELDFUNCTION(bool,Example,KinematicCharacterController$ExampleCharacterController$_jumpedThisFrame) = true;
                        FIELDFUNCTION(float,Example,KinematicCharacterController$ExampleCharacterController$JumpScalableForwardSpeed) = sliderValue3;
                    }
                }
            }
            if (strafe) {
                FIELDFUNCTION(float,Example,KinematicCharacterController$ExampleCharacterController$AirAccelerationSpeed) = 100.0f;
            }

            //*(float *) ((uint664_t) Example + 0x30) = JumpValue + 6;

            //float speed = *(float *) ((uint664_t) Example + 0x10);
            if (playerInFov && AutoStop && !inAir) {
                FIELDFUNCTION(float,Example,KinematicCharacterController$ExampleCharacterController$MaxStableMoveSpeed) = 1.5;
            }
            else {
                FIELDFUNCTION(float,Example,KinematicCharacterController$ExampleCharacterController$MaxStableMoveSpeed) = 5.5f;
            }
        }
    }
}
bool CheckStepValidity;

void* hitcollider;
bool (*old_get_fieldOfView)(void *instance, int nbStepHits, Vector3 characterPosition, Quaternion characterRotation, Vector3 innerHitDirection, Vector3 stepCheckStartPos, void* hitCollider);
bool get_fieldOfView(void *instance, int nbStepHits, Vector3 characterPosition, Quaternion characterRotation, Vector3 innerHitDirection, Vector3 stepCheckStartPos, void* hitCollider) {
    if (instance != NULL) {
        if (feature32) {
            return true;
        }
        /*
        if (old_get_fieldOfView(instance,  nbStepHits,  characterPosition,  characterRotation,  innerHitDirection,  stepCheckStartPos,  hitCollider) == true) {
            if (detect) {
                HitmarkObj();
                return false;
            }
            if (sound == 1) {
                PlayDefuseEnd();
                return false;
            }
            if (sound == 2) {
                PlayDefuseStart();
                return false;
            }
            if (sound == 3) {
                PlayHitMark();
                return false;
            }
            if (sound == 4) {
                PlayHitMarkObj();
                return false;
            }
            if (sound == 5) {
                PlayHitSelf();
                return false;
            }
            if (sound == 6) {
                PlayMiss();
                return false;
            }
            if (sound == 7) {
                PlayRoundEnd();
                return false;
            }
        }*/
    }
    return old_get_fieldOfView(instance,  nbStepHits,  characterPosition,  characterRotation,  innerHitDirection,  stepCheckStartPos,  hitCollider);
}

int clipe = 1;
monoString* backpacke;

void (*old_setammo)(void *instance, int clip, monoString* backpack);
void setammo(void *instance, int clip, monoString* backpack) {
    if (instance) {
        instancee = instance;
        clipe = clip;
        backpacke = backpack;
    }
    old_setammo(instance, clip, backpack);
}

void (*old_BulletHitScann)(void *instance, float bx, float by, float dist);
void BulletHitScann(void *instance, float bx, float by, float dist) {

    if (feature20) {
        dist = 999;
    }
    old_BulletHitScann(instance,  bx,  by,  dist);
}

void (*old_FixMovement)(void *instance,  Vector3 currentVelocity, float deltaTime);
void FixMovement(void *instance,  Vector3 currentVelocity, float deltaTime) {


    old_FixMovement(instance,  currentVelocity,  0);
}

void* (*old_ctorTexture2D)(void *instance, int width, int height, int textureFormat, bool mipChain);
void* ctorTexture2D(void *instance, int width, int height, int textureFormat, bool mipChain) {

    //espTexture = Texture2D(instance,2,2,5,false);
    return old_ctorTexture2D(instance, width, height, textureFormat, mipChain);
}

float (*old_fogDensity)();
float fogDensity() {

    return 10;
}

void *instanced;
float rxd;
float ryd;
float rzd;
float lxd;
float lyd;
unsigned char bitmaskd;
Vector3 Pos;

bool spinSideYaw = false;
bool spinSidePitch = false;

int spinvalueYaw = -180;
int spinvaluePitch = -90;

int fakelag1 = 0;
bool micro1 = false;
void (*old_sendpos)(void *instance, float rx, float ry, float rz, float lx, float ly, unsigned char bitmask);
void sendpos(void *instance, float rx, float ry, float rz, float lx, float ly, unsigned char bitmask) {

    int velocity = sqrt(Vel.x * Vel.x + Vel.z * Vel.z) * 50;

    bool stand = velocity < 1 && !inAir && fakelagOnStand;
    bool move = velocity > 1 && !inAir && fakelagOnMove;
    bool air = inAir && fakelagOnAir;
    bool peek = (aiming || playerInFov) && fakelagOnPeek;

    lx = ToEulerRad(GetPlayerRot(get_transformCamera(camera))).x;
    ly = ToEulerRad(GetPlayerRot(get_transformCamera(camera))).y;

    if (ovFakelags) {
        if (desync) {
            old_sendpos(instance, rx, ry, rz, lx - 180, ly - 180, bitmask);
        }
        old_sendpos(instance, rx, ry, rz, lx, ly, bitmask);
        ovFakelags = false;
    }
    else {
        if (instance) {
            
            if (randomslide) {
                if (fakeduck) {
                    int randomvalue = rand() % 64 + 79;
                    bitmask = randomvalue;
                }
                else {
                    int randomvalue = rand() % 30 + 0;
                    bitmask = randomvalue;
                }
            }
            else if (slide) {
                if (bitmask == 4) {
                    bitmask = 0;
                }
            }

            if (fakeduck) {
                if (bitmask < 10) {
                    bitmask = bitmask + 64;
                }
            }



            {
                if (spinbot2Yaw) {
                    spinvalueYaw = spinvalueYaw + YawSpeed;
                    if (spinvalueYaw >= 180) {
                        spinvalueYaw = -180;
                    }
                }

                if (spinbot1Yaw) {
                    if (spinSideYaw) {
                        spinvalueYaw = spinvalueYaw + YawSpeed;
                        if (spinvalueYaw >= 180) {
                            spinvalueYaw = 180;
                            spinSideYaw = false;
                        }
                    } else {
                        spinvalueYaw = spinvalueYaw - YawSpeed;
                        if (spinvalueYaw <= -180) {
                            spinvalueYaw = -180;
                            spinSideYaw = true;
                        }
                    }
                }
            }





            instanced = instance;
            rxd = rx;
            ryd = ry;
            rzd = rz;
            lxd = lx;
            lyd = ly;

            if (camera && feature28) {
                if (antiaim == false) {


                    lx = ToEulerRad(GetPlayerRot(get_transformCamera(camera))).x;
                    ly = ToEulerRad(GetPlayerRot(get_transformCamera(camera))).y;
                }
            }
            Pos = Vector3(rxd,ryd,rzd);
        }
        if (antiaim) {

            if (randomYaw) {
                ly += float(rand() % 360 + -360) * (float(YawValue) / 180.0f) + YawValue1;
            }
            else {
                ly = ly + float(spinvalueYaw) * (float(YawValue) / 180.0f) + YawValue1;
            }

            lx = lx + PitchValue1;

            if (lx >= 90) {
                lx = 90;
            }
            if (lx <= -90) {
                lx = -90;
            }
        }
        Pos = Vector3(rx,ry,rz);

        if (feature6) {
            rx = FLT_MAX;
            ry = FLT_MAX;
            rz = FLT_MAX;
        }
        if (move||peek||stand||air) {
            fakelag = true;
            if (fakelagRandom) {
                int randValue = rand() % fakelagValue + 0;
                if (randValue == 0) {
                    if (desync) {
                        old_sendpos(instance, rx, ry, rz, lx, ly - 180, bitmask);
                    }
                    old_sendpos(instance, rx, ry, rz, lx, ly, bitmask);
                }
            }
            else {
                if (fakelag1 >= fakelagValue) {
                    if (desync) {
                        old_sendpos(instance, rx, ry, rz, lx, ly - 180, bitmask);
                    }
                    old_sendpos(instance, rx, ry, rz, lx, ly, bitmask);
                    fakelag1 = 0;
                }
                else {
                    fakelag1 = fakelag1 + 1;
                }
            }
        }
        else {
            fakelag = false;
            if (desync) {
                old_sendpos(instance, rx, ry, rz, lx, ly - 180, bitmask);
            }
            old_sendpos(instance, rx, ry, rz, lx, ly, bitmask);
        }
    }

}

int localplayerteam;

void (*old_AddWeapon)(void *instance, int slot);
void AddWeapon(void *instance, int slot) {
    if (instance) {
        localplayerteam = slot;
    }
    old_AddWeapon(instance, slot);
}

void (*old_Damage)(void *instance, int id, int vid, int vbox);
void Damage(void *instance, int id, int vid, int vbox) {


    old_Damage(instance,  id,  vid,  vbox);
}

void (*old_SetCapsuleDimensions)(void *instance,float radius, float height, float yOffset);
void SetCapsuleDimensions(void *instance,float radius, float height, float yOffset) {
    if (feature27) {
        old_SetCapsuleDimensions(instance, 0,  height,  yOffset);
    }
    else {
        old_SetCapsuleDimensions(instance, radius,  height,  yOffset);
    }
}
void (*old_GetItemWeapon)(void *instance, void *instance1, int id);
void GetItemWeapon(void *instance, void *instance1, int id) {
    old_GetItemWeapon(instance, instance1, id);
}
void (*old_OpenAttach)(void *instance,void *instance1);
void OpenAttach(void *instance,void *instance1) {
    old_OpenAttach(instance,instance1);
    if (itemtest) {
        old_OpenAttach(instance,itemtest);
    }
}
void (*old_send_selectweapon)(void *instance,int w0, int w1, int w2, int w3, int w4);
void send_selectweapon(void *instance,int w0, int w1, int w2, int w3, int w4) {
    if (instance) {

    }

    old_send_selectweapon(instance, w0,  w1,  w2,  w3,  w4);
}
void (*old_client_upd)(void *instance);
void client_upd(void *instance) {

    if (instance) {
        //send_spawn(instance);
        instancee = instance;
        std::string textspam;
        const char *texts;
        if (spam && instancee) {
            old_setammo(instancee, clipe, CreateMonoString("t.me/Alvinmods"));
        }
        if (buyArray && setWeapon) {
            for (int i = 0; i < buyArray->getLength(); i++) {
                *(buyArray->getPointer()[i]) = idtoset;
            }
            old_AddPrimeItems(instance,buyArray);
            //old_send_selectweapon(instance, 1,1,1,1,1);
            setWeapon = false;
        }
        Pos = Vector3(rxd,ryd,rzd);
    }
    old_client_upd(instance);
}
void (*old_UpdateAnimator2)(void *instance,void*t);
void UpdateAnimator2(void *instance,void*t) {
    old_UpdateAnimator2(instance,t);
}
bool thth = true;
Vector3 hitpos;
void *localplayer;
int localTeam = 0;
void* aimedPos;
void (*old_UpdateAnimator)(void *instance);
void UpdateAnimator(void *instance) {
    old_UpdateAnimator(instance);
    if (instance && checkPlayer) {
        LOGI("PLAYER");
        espManager->updateEnemies();
        if (playerss == NULL) {
            playerss = playersF;
        }
        LOGI("PLAYER0");
        Vector3 playerPos = GetPlayerPos();
        if (RealCamera) {
            Camerapos = get_position(RealCamera);
        }
        LOGI("PLAYER1");
        minimalangle = 999;
        minimalangle2 = 999;
        if (instance && playerss != NULL) {
            if (!espManager->enemies->empty()) {
                LOGI("PLAYER1");
                for (std::vector<enemy_t *>::iterator e = espManager->enemies->begin();
                     e < espManager->enemies->end(); e++) {
                    void *player = (*e)->object;
                    void *plobj = *(void **) ((uint64_t) player + 0x14);
                    Vector3 pos = *(Vector3 *) ((uint64_t) player +
                                                0x60);
                    LOGI("PLAYER2");
                    Vector3 PlayerPos = pos;
                    Vector3 target = PlayerPos - playerPos;
                    float aimAngle = Vector3::Angle(target, Forw);
                    if (minimalangle > aimAngle && RaycastPlayer(plobj, Camerapos, 250)) {
                        minimalangle = aimAngle;
                    }
                    LOGI("PLAYER3");
                }
            }
            for (int i = 0; i < playerss->getLength(); i++) {
                void *pl = playerss->getPointer()[i];
                if (pl) {
                    LOGI("PLAYER4");
                    void *plobj = *(void **) ((uint64_t) pl + 0x14);
                    if (plobj) {
                        if (lerp1) {
                            *(Vector3 *) ((uint64_t) pl + 0x60) = *(Vector3 *) ((uint64_t) pl + 0x54);
                            *(Vector3 *) ((uint64_t) pl + 0x48) = *(Vector3 *) ((uint64_t) pl + 0x54);

                            *(monoArray<float *> **) ((uint64_t) pl +
                                                      0x7C) = *(monoArray<float *> **) (
                                    (uint64_t) pl + 0x78);
                            *(monoArray<float *> **) ((uint64_t) pl +
                                                      0x74) = *(monoArray<float *> **) (
                                    (uint64_t) pl + 0x78);
                        }
                        bool isLocal = *(bool *) ((uint64_t) pl + 0x10);
                        int healthhh = *(int *) ((uint64_t) pl + 0x30);
                        int team = *(int *) ((uint64_t) pl + 0x1C);
                        if (isLocal) {
                            SetVisible(instance, plobj, true);
                            espManager->removeEnemyGivenObject(pl);
                            LOGI("PLAYER5");
                            if (third) {
                                void *plgameobj = *(void **) ((uint64_t) plobj + 0x18);
                                if (plgameobj && GetType2(CreateMonoString(
                                        "UnityEngine.Collider, UnityEngine.PhysicsModule"))) {
                                    monoArray<void **> *comp = GetComponent(plgameobj,
                                                                            GetType2(CreateMonoString(
                                                                                    "UnityEngine.Collider, UnityEngine.PhysicsModule")),
                                                                            false);
                                    if (comp) {
                                        for (int i = 0; i < comp->getLength(); i++) {
                                            if (comp->getPointer()[i]) {
                                                DisableCollider(comp->getPointer()[i], false);
                                            }
                                        }
                                    }
                                }

                                *(Vector3 *) ((uint64_t) pl + 0x60) = playerPos;
                                *(Vector3 *) ((uint64_t) pl + 0x54) = playerPos;
                                *(Vector3 *) ((uint64_t) pl + 0x48) = playerPos;

                                if (fakelag) {
                                    *(monoArray<float *> **) ((uint64_t) pl +
                                                              0x7C) = *(monoArray<float *> **) (
                                            (uint64_t) pl + 0x78);
                                    *(monoArray<float *> **) ((uint64_t) pl +
                                                              0x74) = *(monoArray<float *> **) (
                                            (uint64_t) pl + 0x78);
                                }

                                *(void **) ((uint64_t) plobj + 0x24) = NULL;

                            } else {
                                *(Vector3 *) ((uint64_t) pl + 0x60) = Vector3(0,-999,0);
                                *(Vector3 *) ((uint64_t) pl + 0x54) = Vector3(0,-999,0);
                                *(Vector3 *) ((uint64_t) pl + 0x48) = Vector3(0,-999,0);
                            }
                        }
                        LOGI("PLAYER6");
                        if (healthhh < 1 || healthhh == NULL) {
                            espManager->removeEnemyGivenObject(pl);
                            continue;
                        }
                        if (isLocal && healthhh < 1) {
                            espManager->enemies->clear();
                            break;
                        }
                        if (camera && espinst) {
                            checkkk = true;
                            LOGI("PLAYER7");
                            playerPosss = playerPos;
                            playerRottt = Quaternion::ToEuler(
                                    GetPlayerRot(get_transformCamera(camera)));
                            LOGI("PLAYER8");
                            if (isLocal == false) {
                                if (team != localTeam) {
                                    void *plgameobj = *(void **) ((uint64_t) plobj + 0x18);
                                    LOGI("PLAYER9");
                                    if (third) {
                                        if (plgameobj && GetType2(CreateMonoString(
                                                "UnityEngine.Collider, UnityEngine.PhysicsModule"))) {

                                            monoArray<void **> *comp = GetComponent(plgameobj,
                                                                                    GetType2(CreateMonoString(
                                                                                            "UnityEngine.Collider, UnityEngine.PhysicsModule")),
                                                                                    false);
                                            LOGI("PLAYER10");
                                            if (comp) {

                                                for (int i = 0; i < comp->getLength(); i++) {
                                                    if (comp->getPointer()[i]) {
                                                        DisableCollider(comp->getPointer()[i], true);

                                                    }
                                                }
                                            }
                                            LOGI("PLAYER11");
                                        }
                                    }


                                    espManager->tryAddEnemy(pl, false);
                                    LOGI("PLAYER12");




                                } else if (false) {
                                    void *plgameobj = *(void **) ((uint64_t) plobj + 0x18);

                                    if (plgameobj && GetType2(CreateMonoString(
                                            "UnityEngine.Collider, UnityEngine.PhysicsModule"))) {

                                        monoArray<void **> *comp = GetComponent(plgameobj,
                                                                                GetType2(CreateMonoString(
                                                                                        "UnityEngine.Collider, UnityEngine.PhysicsModule")),
                                                                                false);

                                        if (comp) {

                                            for (int i = 0; i < comp->getLength(); i++) {
                                                if (comp->getPointer()[i]) {

                                                    DisableCollider(comp->getPointer()[i], false);

                                                }
                                            }
                                        }
                                    }
                                    espManager->removeEnemyGivenObject(pl);
                                    continue;
                                }
                                else {
                                    espManager->removeEnemyGivenObject(pl);
                                    continue;
                                }
                            } else {
                                localTeam = team;
                                espManager->removeEnemyGivenObject(pl);
                                continue;
                            }

                            Vector3 PlayerPos = *(Vector3 *) ((uint64_t) pl +0x60);
                            Vector3 target = PlayerPos - playerPos;
                            float aimAngle = Vector3::Angle(target, Forw);
                            if (minimalangle == aimAngle) {
                                if (healthhh > 0) {
                                    if (playerCircle) {
                                        for (int i = 0; i < 100; i++) {

                                            if (i < 100) {
                                                Vector3 pos1 = Vector3(
                                                        float((double) PlayerPos.x + 1 *
                                                                                     cos((double) i *
                                                                                         (PI *
                                                                                          2) /
                                                                                         (double) 100)),
                                                        float((double) PlayerPos.y),
                                                        float((double) PlayerPos.z + 1 *
                                                                                     sin((double) i *
                                                                                         (PI *
                                                                                          2) /
                                                                                         (double) 100)));
                                                Vector3 pos2 = Vector3(
                                                        float((double) PlayerPos.x + 1 *
                                                                                     cos((double) (
                                                                                             i +
                                                                                             1) *
                                                                                         (PI *
                                                                                          2) /
                                                                                         (double) 100)),
                                                        float((double) PlayerPos.y),
                                                        float((double) PlayerPos.z + 1 *
                                                                                     sin((double) (
                                                                                             i +
                                                                                             1) *
                                                                                         (PI *
                                                                                          2) /
                                                                                         (double) 100)));
                                                Vector3 ScreenPos1 = world2screen(camera, pos1,
                                                                                  2);
                                                Vector3 ScreenPos2 = world2screen(camera, pos2,
                                                                                  2);
                                                circle_data.push_back(
                                                        {pos1, pos2, ScreenPos1,
                                                         ScreenPos2});

                                                if (circle_data.size() > 100) {
                                                    circle_data.pop_front();
                                                }
                                            }
                                        }
                                        for (auto i = 0; i < circle_data.size(); i++) {
                                            circle_data[i].w2s1 = world2screen(camera,
                                                                               circle_data[i].pos1,
                                                                               2);
                                            circle_data[i].w2s2 = world2screen(camera,
                                                                               circle_data[i].pos2,
                                                                               2);
                                        }
                                    }
                                    monoArray<void **> *plHead = *(monoArray<void **> **) (
                                            (uint64_t) plobj + 0x80);
                                    if (plHead) {
                                        bool headVis = false;
                                        bool bodyVis = false;
                                        bool legsVis = false;
                                        bool armsVis = false;
                                        int headId = 99;
                                        int bodyId = 99;
                                        int legId = 99;
                                        int armId = 99;
                                        for (int b = 0; b < plHead->getLength(); b++) {
                                            if (plHead->getPointer()[b]) {
                                                if (!damagePr) {
                                                    for (int u = 0;
                                                         u < plHead->getLength(); u++) {
                                                        if (
                                                                (u == 0 && AimBody) ||
                                                                (u == 1 && AimBody) ||
                                                                (u == 2 && AimBody) ||
                                                                (u == 7 && AimBody) ||
                                                                (u == 13 && AimBody) ||

                                                                (u == 10 && AimArms) ||
                                                                (u == 11 && AimArms) ||
                                                                (u == 12 && AimArms) ||

                                                                (u == 4 && AimArms) ||
                                                                (u == 5 && AimArms) ||
                                                                (u == 6 && AimArms) ||

                                                                (u == 3 && AimHead) ||

                                                                (u == 8 && AimLegs) ||
                                                                (u == 14 && AimLegs)

                                                                ) {
                                                            if (plHead->getPointer()[u]) {

                                                                Vector3 PlayerPos = get_position(
                                                                        plHead->getPointer()[u]);

                                                                RaycastHit tes;
                                                                if (RaycastPlayerFixed(
                                                                        Camerapos,
                                                                        PlayerPos,
                                                                        tes)) {
                                                                    if ((int) tes.FaceID ==
                                                                        -1 ||
                                                                        (int) tes.FaceID ==
                                                                        30) {
                                                                        Vector3 target =
                                                                                PlayerPos -
                                                                                Camerapos;
                                                                        float aimAngle = Vector3::Angle(
                                                                                target,
                                                                                Forw);

                                                                        if (minimalangle2 >
                                                                            aimAngle) {
                                                                            minimalangle2 = aimAngle;
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }

                                                if (!damagePr) {
                                                    if (                                                                (b == 0 && AimBody) ||
                                                                                                                        (b == 1 && AimBody) ||
                                                                                                                        (b == 2 && AimBody) ||
                                                                                                                        (b == 7 && AimBody) ||
                                                                                                                        (b == 13 && AimBody) ||

                                                                                                                        (b == 10 && AimArms) ||
                                                                                                                        (b == 11 && AimArms) ||
                                                                                                                        (b == 12 && AimArms) ||

                                                                                                                        (b == 4 && AimArms) ||
                                                                                                                        (b == 5 && AimArms) ||
                                                                                                                        (b == 6 && AimArms) ||

                                                                                                                        (b == 3 && AimHead) ||

                                                                                                                        (b == 8 && AimLegs) ||
                                                                                                                        (b == 14 && AimLegs)) {
                                                        Vector3 PlayerPos = get_position(
                                                                plHead->getPointer()[b]);
                                                        Vector3 target = PlayerPos - Camerapos;
                                                        float aimAngle = Vector3::Angle(target,
                                                                                        Forw);
                                                        if (minimalangle2 == aimAngle) {

                                                            if (aimAngle <=
                                                                float(float(circlesize) /
                                                                      700.0f) ||
                                                                infFov) {
                                                                //LOGI("hit collider: %d",
                                                                //     (int) tes.FaceID);


                                                                aimedPos = plHead->getPointer()[b];
                                                                aiming = true;
                                                                playerInFov = true;
                                                                aimedHitBoxId = b;


                                                            }
                                                        }

                                                    }
                                                } else {
                                                    Vector3 PlayerPos = get_position(
                                                            plHead->getPointer()[b]);
                                                    if ((b == 3 && AimHead) && !headVis) {
                                                        RaycastHit tes;
                                                        if (RaycastPlayerFixed(Camerapos,
                                                                               PlayerPos,
                                                                               tes)) {
                                                            //LOGI("hit collider: %d",
                                                            //     (int) tes.FaceID);

                                                            headVis =
                                                                    (int) tes.FaceID == -1 ||
                                                                    (int) tes.FaceID == 30;
                                                            if (headVis) {
                                                                headId = b;
                                                            }
                                                            //aimedPos = PlayerPos;
                                                        }
                                                    }
                                                    if ((b == 0 && AimBody) ||
                                                        (b == 1 && AimBody) ||
                                                        (b == 2 && AimBody) ||
                                                        (b == 7 && AimBody) ||
                                                        (b == 13 && AimBody) && !bodyVis && !headVis) {
                                                        RaycastHit tes;
                                                        if (RaycastPlayerFixed(Camerapos,
                                                                               PlayerPos,
                                                                               tes)) {
                                                            //LOGI("hit collider: %d",
                                                            //     (int) tes.FaceID);

                                                            bodyVis =
                                                                    (int) tes.FaceID == -1 ||
                                                                    (int) tes.FaceID == 30;
                                                            if (bodyVis) {
                                                                bodyId = b;
                                                            }
                                                            //aimedPos = PlayerPos;
                                                        }
                                                    }
                                                    if ((b == 8 && AimLegs) ||
                                                        (b == 14 && AimLegs) && !legsVis && !bodyVis && !headVis && !armsVis) {
                                                        RaycastHit tes;
                                                        if (RaycastPlayerFixed(Camerapos,
                                                                               PlayerPos,
                                                                               tes)) {
                                                            //LOGI("hit collider: %d",
                                                            //     (int) tes.FaceID);

                                                            legsVis =
                                                                    (int) tes.FaceID == -1 ||
                                                                    (int) tes.FaceID == 30;
                                                            if (legsVis) {
                                                                legId = b;
                                                            }
                                                            //aimedPos = PlayerPos;
                                                        }
                                                    }
                                                    if (                                                                (b == 10 && AimArms) ||
                                                                                                                        (b == 11 && AimArms) ||
                                                                                                                        (b == 12 && AimArms) ||

                                                                                                                        (b == 4 && AimArms) ||
                                                                                                                        (b == 5 && AimArms) ||
                                                                                                                        (b == 6 && AimArms) && !armsVis && !bodyVis && !headVis) {
                                                        RaycastHit tes;
                                                        if (RaycastPlayerFixed(Camerapos,
                                                                               PlayerPos,
                                                                               tes)) {
                                                            //LOGI("hit collider: %d",
                                                            //     (int) tes.FaceID);

                                                            armsVis =
                                                                    (int) tes.FaceID == -1 ||
                                                                    (int) tes.FaceID == 30;
                                                            if (armsVis) {
                                                                armId = b;
                                                            }
                                                            //aimedPos = PlayerPos;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        if (damagePr) {
                                            if (headVis) {
                                                aiming = true;
                                                playerInFov = true;
                                                aimedHitBoxId = headId;
                                                aimedPos =
                                                        plHead->getPointer()[headId];
                                            } else if (bodyVis) {
                                                aiming = true;
                                                playerInFov = true;
                                                aimedHitBoxId = bodyId;
                                                aimedPos =
                                                        plHead->getPointer()[bodyId];
                                            } else if (armsVis) {
                                                aiming = true;
                                                playerInFov = true;
                                                aimedHitBoxId = armId;
                                                aimedPos =
                                                        plHead->getPointer()[armId];
                                            } else if (legsVis) {
                                                aiming = true;
                                                playerInFov = true;
                                                aimedHitBoxId = legId;
                                                aimedPos =
                                                        plHead->getPointer()[legId];
                                            }
                                        }
                                    }
                                }
                            }

                        }
                    } else {
                        espManager->removeEnemyGivenObject(pl);
                    }
                } else {
                    espManager->removeEnemyGivenObject(pl);
                }
            }
        } else {
            checkkk = false;
        }
    }
    else {
        checkkk = false;
    }
}
void (*old_set_PlanarDirection)(void *instance,void* currentRotation);
void set_PlanarDirection(void *instance,void*  currentRotation) {

    micro1 = !micro1;
    if (micro1) {
        Quaternion rotation = *(Quaternion *) ((uint64_t) currentRotation + 0x8);
        Vector3 rot = Quaternion::ToEuler(rotation);
        rot.y = rot.y + 0.00001;
        *(Quaternion *) ((uint64_t) currentRotation + 0x8) = Quaternion::FromEuler(rot);
    }
    else {
        Quaternion rotation = *(Quaternion *) ((uint64_t) currentRotation + 0x8);
        Vector3 rot = Quaternion::ToEuler(rotation);
        rot.y = rot.y - 0.00001;
        *(Quaternion *) ((uint64_t) currentRotation + 0x8) = Quaternion::FromEuler(rot);
    }
    //old_set_PlanarDirection(instance, currentRotation);
    if (feature28 && instance && currentRotation) {
        if (aiming) {
            //lookRotation =
            //LOGI("hit collider: %d",
            //     (int) tes.FaceID);


            *(Quaternion *) ((uint64_t) currentRotation + 0x8) = GetRotationToLocation(get_position(aimedPos), 0,Camerapos);
            //old_set_PlanarDirection(instance, currentRotation);
            if (autoscope) {
                if (inZoomF == false) {
                    inZoomF = true;
                }
            }
            if (autofire) {
                if (fireDelay >= maxDelay) {
                    //old_set_PlanarDirection(instance, currentRotation);
                    //checkhit->Point = tes.Point;

                    inAttackKeyF = true;
                    old_set_PlanarDirection(instance, currentRotation);
                }
                else {
                    fireDelay = fireDelay + 1;
                }
            }




            //aimedPos = PlayerPos;

            aiming = false;
        }
        else {
            fireDelay = 0;
            if (autofire) {
                inAttackKeyF = false;
            }
        }
    }
    old_set_PlanarDirection(instance, currentRotation);
}




void inj() {
    do {
        sleep(2);
    } while (!isLibraryLoaded(targetLibName) && mlovinit());
    sleep(2);
    LOGD("il2cpp loaded");


    //MS("0xB83204", service2, service_list2);
    //AntiO("0x8F3B9C");
    // MS("0xA7E358",stts12, old_stts12);

    //CreateMonoString = (monoString *(*)( const char *))getAbsoluteAddress("libil2cpp.so", 0x156933C);
/*
    hexPatches.recv_pos = MemoryPatch::createWithHex(targetLibName,
                                                     string2Offset(OBFUSCATE_KEY("0xEFE27C", '-')),
                                                     OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.Kill_LocalPlayer = MemoryPatch::createWithHex(targetLibName,
                                                             string2Offset(OBFUSCATE_KEY("0x104B058", '-')),
                                                             OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.Flash1 = MemoryPatch::createWithHex(targetLibName,
                                                   string2Offset(OBFUSCATE_KEY("0x11BE0D4", '-')),
                                                   OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.Flash2 = MemoryPatch::createWithHex(targetLibName,
                                                   string2Offset(OBFUSCATE_KEY("0x11C2978", '-')),
                                                   OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.Spawn = MemoryPatch::createWithHex(targetLibName,
                                                  string2Offset(OBFUSCATE_KEY("0xF113B0", '-')),
                                                  OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.recv_buyzone = MemoryPatch::createWithHex(targetLibName,
                                                         string2Offset(OBFUSCATE_KEY("0xF000CC", 'g')),
                                                         OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.recv_buytime = MemoryPatch::createWithHex(targetLibName,
                                                         string2Offset(OBFUSCATE_KEY("0xF01848", 'd')),
                                                         OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.UpdateSmoke = MemoryPatch::createWithHex(targetLibName,
                                                        string2Offset(OBFUSCATE_KEY("0x11BBE80", 'f')),
                                                        OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.recv_chatmsg = MemoryPatch::createWithHex(targetLibName,
                                                         string2Offset(OBFUSCATE_KEY("0xEFE788", 'h')),
                                                         OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.send_pos = MemoryPatch::createWithHex(targetLibName,
                                                     string2Offset(OBFUSCATE_KEY("0xEFC448", 'j')),
                                                     OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.isLockedAttach = MemoryPatch::createWithHex(targetLibName,
                                                           string2Offset(OBFUSCATE_KEY("0x10226C0", 'k')),
                                                           OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.RemoveWeapon = MemoryPatch::createWithHex(targetLibName,
                                                         string2Offset(OBFUSCATE_KEY("0x11063C8", 'k')),
                                                         OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.CalcBulletSpread = MemoryPatch::createWithHex(targetLibName,
                                                             string2Offset(OBFUSCATE_KEY("0x1108428", 'k')),
                                                             OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.CreateHole = MemoryPatch::createWithHex(targetLibName,
                                                       string2Offset(OBFUSCATE_KEY("0xFC50FC", 'k')),
                                                       OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.Blood1 = MemoryPatch::createWithHex(targetLibName,
                                                   string2Offset(OBFUSCATE_KEY("0xFC43DC", 'k')),
                                                   OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.Blood2 = MemoryPatch::createWithHex(targetLibName,
                                                   string2Offset(OBFUSCATE_KEY("0xFC593C", 'k')),
                                                   OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.isLockedAttach2 = MemoryPatch::createWithHex(targetLibName,
                                                            string2Offset(OBFUSCATE_KEY("0x10226C0", 'k')),
                                                            OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.UpdateFov = MemoryPatch::createWithHex(targetLibName,
                                                      string2Offset(OBFUSCATE_KEY("0xF12658", 'k')),
                                                      OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.CreateHole1 = MemoryPatch::createWithHex(targetLibName,
                                                        string2Offset(OBFUSCATE_KEY("0xFC33FC", 'k')),
                                                        OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.CreateHoleLocal = MemoryPatch::createWithHex(targetLibName,
                                                            string2Offset(OBFUSCATE_KEY("0xFC33FC", 'k')),
                                                            OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.UpdateCameraOffset = MemoryPatch::createWithHex(targetLibName,
                                                               string2Offset(OBFUSCATE_KEY("0x10F84E0", 'k')),
                                                               OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.StopDefuse = MemoryPatch::createWithHex(targetLibName,
                                                       string2Offset(OBFUSCATE_KEY("0x110B710", 'k')),
                                                       OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.BulletHitScan = MemoryPatch::createWithHex(targetLibName,
                                                          string2Offset(OBFUSCATE_KEY("0xFB7B44", 'k')),
                                                          OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));




    hexPatches.SpeedHackAC = MemoryPatch::createWithHex(targetLibName,
                                                        string2Offset(OBFUSCATE_KEY("0x1314460", 'k')),
                                                        OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.SpeedHackAC.Modify();

    hexPatches.SpeedHackAC = MemoryPatch::createWithHex(targetLibName,
                                                        string2Offset(OBFUSCATE_KEY("0x13210E8", 'k')),
                                                        OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.SpeedHackAC.Modify();
    hexPatches.SpeedHackAC = MemoryPatch::createWithHex(targetLibName,
                                                        string2Offset(OBFUSCATE_KEY("0x121FCAC", 'k')),
                                                        OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.SpeedHackAC.Modify();
    hexPatches.SpeedHackAC = MemoryPatch::createWithHex(targetLibName,
                                                        string2Offset(OBFUSCATE_KEY("0x1314704", 'k')),
                                                        OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.SpeedHackAC.Modify();
    hexPatches.SpeedHackAC = MemoryPatch::createWithHex(targetLibName,
                                                        string2Offset(OBFUSCATE_KEY("0x13210E8", 'k')),
                                                        OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.SpeedHackAC.Modify();
    hexPatches.SpeedHackAC = MemoryPatch::createWithHex(targetLibName,
                                                        string2Offset(OBFUSCATE_KEY("0x1314460", 'k')),
                                                        OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.SpeedHackAC.Modify();
    hexPatches.SpeedHackAC = MemoryPatch::createWithHex(targetLibName,
                                                        string2Offset(OBFUSCATE_KEY("0xEFD9B8", 'k')),
                                                        OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.SpeedHackAC.Modify();
    hexPatches.SpeedHackAC = MemoryPatch::createWithHex(targetLibName,
                                                        string2Offset(OBFUSCATE_KEY("0xEFDE40", 'k')),
                                                        OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.SpeedHackAC.Modify();



    hexPatches.Shake1 = MemoryPatch::createWithHex(targetLibName,
                                                   string2Offset(OBFUSCATE_KEY("0x10F84E0", 'k')),
                                                   OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    hexPatches.Shake2 = MemoryPatch::createWithHex(targetLibName,
                                                   string2Offset(OBFUSCATE_KEY("0x10F8BC0", 'k')),
                                                   OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));




    hexPatches.Scope = MemoryPatch::createWithHex(targetLibName,
                                                  string2Offset(OBFUSCATE_KEY("0x11C5310", 'k')),
                                                  OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));*/

    /*InitResolveFunc(_Camera_main, "UnityEngine.Camera::get_main()");
    InitResolveFunc(_GetForward, "UnityEngine.Transform::get_forward()");
    InitResolveFunc(get_transformCamera, "UnityEngine.Component::get_transform()");
    InitResolveFunc(set_timeScale, "UnityEngine.Time::set_timeScale(System.Single)");
    InitResolveFunc(get_deltaTime, "UnityEngine.Time::get_deltaTime()");
    InitResolveFunc(get_collider, "UnityEngine.RaycastHit::get_collider()");
    InitResolveFunc(GetPlayerRot, "UnityEngine.Transform::get_rotation()");
    InitResolveFunc(world2screen, "UnityEngine.Camera::WorldToScreenPoint(UnityEngine.Vector3, UnityEngine.Camera.MonoOrStereoscopicEye)");
    InitResolveFunc(Camera$$set_backgroundColor, "UnityEngine.Camera::set_backgroundColor(UnityEngine.Color)");
    InitResolveFunc(Camera$$set_nearClipPlane, "UnityEngine.Camera::set_nearClipPlane(System.Single)");
    InitResolveFunc(Camera$$set_clearFlags, "UnityEngine.Camera::set_nearClipPlane(System.Single)");
    InitResolveFunc(Camera$$set_clearFlags2, "UnityEngine.Camera::set_clearFlags(UnityEngine.CameraClearFlags)");
    InitResolveFunc(Camera$$get_main, "UnityEngine.Camera::get_main()");
    InitResolveFunc(Camera$$set_farClipPlane, "UnityEngine.Camera::set_farClipPlane(System.Single)");
    InitResolveFunc(Camera$$set_fieldOfView, "UnityEngine.Camera::set_fieldOfView(System.Single)");
    InitResolveFunc(get_screen_width, "UnityEngine.Screen::get_width()");
    InitResolveFunc(get_screen_height, "UnityEngine.Screen::get_height()");
    InitResolveFunc(SetResolution, "UnityEngine.Screen::SetResolution(System.Int32,System.Int32,System.Boolean)");*/





    LOGI("HOOKED start");
    InitField(GameClass$BaseItemInfo$id,"GameClass","BaseItemInfo","id");
    LOGI("HOOKED test");
    InitField(GameClass$HitData$p,"GameClass","HitData","p");
    InitField(GameClass$HitData$id,"GameClass","HitData","id");
    InitField(GameClass$HitData$hb,"GameClass","HitData","hb");
    InitField(GameClass$PlayerData$id,"GameClass","PlayerData","id");
    InitField($Shooter$currweapon,"","Shooter","currweapon");
    InitField(GameClass$WeaponObject$recoilhorizontal,"GameClass","WeaponObject","recoilhorizontal");
    InitField(GameClass$WeaponObject$recoilvertical,"GameClass","WeaponObject","recoilvertical");
    InitField(GameClass$WeaponObject$spread,"GameClass","WeaponObject","spread");
    InitField(GameClass$WeaponObject$firerate,"GameClass","WeaponObject","firerate");
    InitField(GameClass$WeaponObject$_clip,"GameClass","WeaponObject","_clip");
    InitField($Shooter$vOffsetPos,"","Shooter","vOffsetPos");
    InitField($Controll$inAir,"","Controll","inAir");
    InitField($Controll$inFreeze,"","Controll","inFreeze");
    InitField($Controll$freezetime,"","Controll","freezetime");
    InitField($Controll$inZoom,"","Controll","inZoom");
    InitField(GameClass$PlayerData$po,"GameClass","PlayerData","po");
    InitField(GameClass$PlayerData$lerpPos,"GameClass","PlayerData","lerpPos");
    InitField(GameClass$PlayerData$Dir,"GameClass","PlayerData","Dir");
    InitField(GameClass$PlayerData$playername,"GameClass","PlayerData","playername");
    InitField(GameClass$PlayerData$health,"GameClass","PlayerData","health");
    InitField(GameClass$PlayerData$armor,"GameClass","PlayerData","armor");
    InitField(GameClass$PlayerData$currwpn,"GameClass","PlayerData","currwpn");
    InitField(GameClass$PlayerWeaponObject$it,"GameClass","PlayerWeaponObject","it");
    InitField(GameClass$BaseItemInfo$localname,"GameClass","BaseItemInfo","localname");
    InitField(GameClass$PlayerData$prevPos,"GameClass","PlayerData","prevPos");
    InitField(GameClass$PlayerData$Pos,"GameClass","PlayerData","Pos");
    InitField(KinematicCharacterController$ExamplePlayer$Character,"KinematicCharacterController.Examples","ExamplePlayer","Character");
    InitField(KinematicCharacterController$ExamplePlayer$CharacterCamera,"KinematicCharacterController.Examples","ExamplePlayer","CharacterCamera");
    InitField(KinematicCharacterController$ExampleCharacterController$_jumpConsumed,"KinematicCharacterController.Examples","ExampleCharacterController","_jumpConsumed");
    InitField(KinematicCharacterController$ExampleCharacterController$_timeSinceLastAbleToJump,"KinematicCharacterController.Examples","ExampleCharacterController","_timeSinceLastAbleToJump");
    InitField(KinematicCharacterController$ExampleCharacterController$_jumpRequested,"KinematicCharacterController.Examples","ExampleCharacterController","_jumpRequested");
    InitField(KinematicCharacterController$ExampleCharacterController$_jumpedThisFrame,"KinematicCharacterController.Examples","ExampleCharacterController","_jumpedThisFrame");
    InitField($ControllTouch$inJumpKey,"","ControllTouch","inJumpKey");
    InitField(KinematicCharacterController$ExampleCharacterController$JumpScalableForwardSpeed,"KinematicCharacterController.Examples","ExampleCharacterController","JumpScalableForwardSpeed");
    InitField(KinematicCharacterController$ExampleCharacterController$AirAccelerationSpeed,"KinematicCharacterController.Examples","ExampleCharacterController","AirAccelerationSpeed");
    InitField(KinematicCharacterController$ExampleCharacterController$MaxStableMoveSpeed,"KinematicCharacterController.Examples","ExampleCharacterController","MaxStableMoveSpeed");
    InitField($PLH$player,"","PLH","player");
    InitField($ControllTouch$inAttackKey,"","ControllTouch","inAttackKey");
    InitField($Main$playername,"","Main","playername");
    InitField($Main$sign,"","Main","sign");
    InitField($Main$gameid,"","Main","gameid");
    InitField($Main$gamekey,"","Main","gamekey");
    LOGI("HOOKED1");
    /*
     Field<bool> inAirF;
Field<bool> inAttackKeyF;
Field<bool> inFreezeF;
Field<bool> inZoomF;
Field<bool> inJumpKeyF;
Field<float> freezetimeF;
Field<monoString*> playernameF;
Field<monoString*> signF;
Field<monoString*> gameidF;
Field<monoString*> gamekeyF;
Field<monoArray<void**>*> playersF;
     */


    LOGI("HOOKED1");
    InitFunc(_Camera_main,LoadClass("UnityEngine", "Camera").GetMethodOffsetByName("get_main", 0));
    InitFunc(Camera$$get_main,LoadClass("UnityEngine", "Camera").GetMethodOffsetByName("get_main", 0));
    InitFunc(get_screen_width,LoadClass("UnityEngine", "Screen").GetMethodOffsetByName("get_width", 0));
    InitFunc(get_screen_height,LoadClass("UnityEngine", "Screen").GetMethodOffsetByName("get_height", 0));
    InitFunc(GetPlayerRot,LoadClass("UnityEngine", "Transform").GetMethodOffsetByName("get_rotation", 0));
    InitFunc(get_collider,LoadClass("UnityEngine", "RaycastHit").GetMethodOffsetByName("get_collider", 0));
    InitFunc(get_deltaTime,LoadClass("UnityEngine", "Time").GetMethodOffsetByName("get_deltaTime", 0));
    InitFunc(_GetForward,LoadClass("UnityEngine", "Transform").GetMethodOffsetByName("get_forward", 0));
    InitFunc(get_transformCamera,LoadClass("UnityEngine", "Component").GetMethodOffsetByName("get_transform", 0));
    LOGI("HOOKED2");
    InitFunc(set_timeScale,LoadClass("UnityEngine", "Time").GetMethodOffsetByName("set_timeScale", {"value"}));
    InitFunc(world2screen,LoadClass("UnityEngine", "Camera").GetMethodOffsetByName("WorldToScreenPoint", {"position","eye"}));
    InitFunc(Camera$$set_backgroundColor,LoadClass("UnityEngine", "Camera").GetMethodOffsetByName("set_backgroundColor", {"value"}));
    InitFunc(Camera$$set_nearClipPlane,LoadClass("UnityEngine", "Camera").GetMethodOffsetByName("set_nearClipPlane", {"value"}));
    InitFunc(Camera$$set_clearFlags,LoadClass("UnityEngine", "Camera").GetMethodOffsetByName("set_nearClipPlane", {"value"}));
    InitFunc(Camera$$set_clearFlags2,LoadClass("UnityEngine", "Camera").GetMethodOffsetByName("set_clearFlags", {"value"}));
    InitFunc(Camera$$set_farClipPlane,LoadClass("UnityEngine", "Camera").GetMethodOffsetByName("set_farClipPlane", {"value"}));
    InitFunc(Camera$$set_fieldOfView,LoadClass("UnityEngine", "Camera").GetMethodOffsetByName("set_fieldOfView", {"value"}));
    InitFunc(SetResolution,LoadClass("UnityEngine", "Screen").GetMethodOffsetByName("SetResolution", {"width", "height", "fullscreen"}));
    LOGI("HOOKED3");
    InitFunc(SetFov,LoadClass("", "Controll").GetMethodOffsetByName("SetFov", 2));
    InitFunc(RaycastPlayer,LoadClass("", "PLHUtil").GetMethodOffsetByName("RaycastPlayer", {"po", "pos", "maxdist"}));
    InitFunc(RaycastPlayerFixed,LoadClass("UnityEngine", "Physics").GetMethodOffsetByName("Linecast", {"start", "end", "hitInfo"}));
    InitFunc(GetPlayerSpeed,LoadClass("", "Controll").GetMethodOffsetByName("GetPlayerSpeed", 0));
    InitFunc(GetPlayerPos,LoadClass("", "Controll").GetMethodOffsetByName("GetPlayerPos", 0));
    InitFunc(GetPlayerCameraPos,LoadClass("", "Controll").GetMethodOffsetByName("GetPlayerCameraPos", 0));
    InitFunc(GetType2,LoadClass("System", "Type").GetMethodOffsetByName("GetType", {"typeName"}));
    InitFunc(GetComponent,LoadClass("UnityEngine", "Component").GetMethodOffsetByName("GetComponentsInChildren", {"type","includeInactive"}));
    InitFunc(FindObjectsOfType,LoadClass("UnityEngine", "Object").GetMethodOffsetByName("FindObjectsOfType", {"type"}));
    InitFunc(DisableCollider,LoadClass("UnityEngine", "Collider").GetMethodOffsetByName("set_enabled", {"value"}));
    InitFunc(SetColorMaterial,LoadClass("UnityEngine", "Material").GetMethodOffsetByName("SetColor", {"name","value"}));
    InitFunc(SetTextureMaterial,LoadClass("UnityEngine", "Material").GetMethodOffsetByName("SetTexture", {"name","value"}));
    InitFunc(SetIntMaterial,LoadClass("UnityEngine", "Material").GetMethodOffsetByName("SetFloat", {"name","value"}));
    InitFunc(GetMaterial,LoadClass("UnityEngine", "Renderer").GetMethodOffsetByName("get_material", 0));
    InitFunc(SetShader,LoadClass("UnityEngine", "Material").GetMethodOffsetByName("set_shader", {"value"}));
    InitFunc(FindShader,LoadClass("UnityEngine", "Shader").GetMethodOffsetByName("Find", {"name"}));
    InitFunc(SetVisible,LoadClass("", "PLH").GetMethodOffsetByName("SetVisible", {"po","val"}));
    InitFunc(Transform_get_position,LoadClass("UnityEngine", "Transform").GetMethodOffsetByName("get_position_Injected", {"ret"}));
    InitFunc(Transform_SetRotation,LoadClass("UnityEngine", "Transform").GetMethodOffsetByName("set_rotation", {"value"}));
    InitFunc(GetFollowTransform,LoadClass("KinematicCharacterController.Examples", "ExampleCharacterCamera").GetMethodOffsetByName("get_FollowTransform", 0));
    InitFunc(SetDist,LoadClass("KinematicCharacterController.Examples", "ExampleCharacterCamera").GetMethodOffsetByName("set_TargetDistance", {"value"}));
    InitFunc(get_rotation,LoadClass("UnityEngine", "Transform").GetMethodOffsetByName("get_rotation", 0));
    LOGI("HOOKED4");
    //UnityText = (void (*)(Rect position, monoString* text)) getAbsoluteAddress(targetLibName, 0xAB33DC);
    //DrawTexture = (void (*)(Rect position, void* image)) getAbsoluteAddress(targetLibName, 0xAB39E4);
    //Texture2D = (void* (*)(Il2CppObject *,int width, int height,int,bool)) getAbsoluteAddress(targetLibName, 0x92D7F4);
    //SetPixel = (void (*)(void* t, int x, int y, Color color)) getAbsoluteAddress(targetLibName, 0x92E548);
    //Apply = (void (*)(void* t)) getAbsoluteAddress(targetLibName, 0x92EA10);

    HOOK(LoadClass("KinematicCharacterController", "KinematicCharacterMotor").GetMethodOffsetByName("CheckStepValidity", {"nbStepHits", "characterPosition", "characterRotation", "innerHitDirection", "stepCheckStartPos", "hitCollider"}),get_fieldOfView,old_get_fieldOfView);
    LOGI("HOOKED45");
    //HOOK(0x764AEC,set_PlanarDirection,old_set_PlanarDirection);
    LOGI("HOOKED46");
    //HOOK(0xEFC38C,AddWeapon,old_AddWeapon)
    HOOK(LoadClass("", "HUDWeapon").GetMethodOffsetByName("SetWeapon", {"v", "it", "slot"}),SetWeapon,old_SetWeapon);
    LOGI("HOOKED47");
    HOOK(LoadClass("", "Client").GetMethodOffsetByName("send_buy", {"b"}),_AddPrimeItems,old_AddPrimeItems);
    LOGI("HOOKED48");
    //HOOK(0xEFDD44,send_selectweapon,old_send_selectweapon)
    HOOK(LoadClass("", "Client").GetMethodOffsetByName("send_attack", {"list"}),send_attack,old_send_attack);
    LOGI("HOOKED49");
    HOOK(LoadClass("", "HUDInv").GetMethodOffsetByName("AddWeapon", {"slot", "itemid", "uid", "skinid", "muzzleid", "foregripid", "magazineid", "scopeid", "stockid"}),AddWeapon1,old_AddWeapon1);
    LOGI("HOOKED410");
    //HOOK(0x127B578,Damage,old_Damage)
    HOOK(LoadClass("UnityEngine", "Camera").GetMethodOffsetByName("set_fieldOfView", {"value"}),setfov,old_setfov);
    LOGI("HOOKED411");
    //HOOK(0x1207EE4,OpenAttach,old_OpenAttach)
    //HOOK(0x12C55C4,send_name,old_send_name)
    HOOK(LoadClass("", "Camera").GetMethodOffsetByName("AddItem", {"type", "wid", "uid", "menu", "sign", "cat"}),CreateItem,old_CreateItem);

    LOGI("HOOKED412");//HOOK(0x121C8E8,UpdateFov,old_UpdateFov)
    // HOOK(0xBB5E70,fogDensity,old_fogDensity)
    HOOK(LoadClass("", "Shooter").GetMethodOffsetByName("BulletHitScan", {"bx", "by", "dist"}),BulletHitScann,old_BulletHitScann);
    //HOOK(0x1213A78,OnGUI,old_OnGUI)

    LOGI("HOOKED5");
    //HOOK(0xCA9844,ctorTexture2D,old_ctorTexture2D)
    MSHookFunction((void *)LoadClass("", "Client").GetMethodOffsetByName(
            "send_chatmsg", 2), (void *) setammo, (void **) &old_setammo);
    MSHookFunction((void *)LoadClass("", "Client").GetMethodOffsetByName(
            "UpdatePing", 0), (void *) client_upd, (void **) &old_client_upd);
    MSHookFunction((void *)LoadClass("","Client").GetMethodOffsetByName(
            "send_pos", 6), (void *) sendpos, (void **) &old_sendpos);
    MSHookFunction((void *)LoadClass("KinematicCharacterController","KinematicCharacterMotor").GetMethodOffsetByName(
            "SetCapsuleDimensions", 3), (void *) SetCapsuleDimensions, (void **) &old_SetCapsuleDimensions);
    MSHookFunction((void *)LoadClass("", "Shooter").GetMethodOffsetByName(
            "Update", 0), (void *) _Weapon, (void **) &old_Weapon);
    MSHookFunction((void *)LoadClass("KinematicCharacterController.Examples", "ExamplePlayer").GetMethodOffsetByName(
            "Update", 0), (void *) Jump_Update, (void **) &old_Jump_Update);
    MSHookFunction((void *)LoadClass("", "PLH").GetMethodOffsetByName(
            "Update", 0), (void *) UpdateAnimator, (void **) &old_UpdateAnimator);
    LOGI("HOOKED6");


    MS(0xD11A3C,set_PlanarDirection,old_set_PlanarDirection);
    //SetCharacterActive = (void (*)(bool))getAbsoluteAddress("libil2cpp.so", 0xF2BA80);
    //SetProgressActive = (void (*)(bool))getAbsoluteAddress("libil2cpp.so", 0xF2EBC4);
    //SetWeaponActive = (void (*)(bool))getAbsoluteAddress("libil2cpp.so", 0xF39E40);
    //SetAnimatorActive = (void (*)(bool))getAbsoluteAddress("libil2cpp.so", 0x108C308);


    setShader("unity_SHC");
    LogShaders();
    Wallhack();
    espManager = new ESPManager();
    LOGI("HOOKED7");

    inAirF = FieldBN(bool,0,"","Controll","inAir");
    inAttackKeyF = FieldBN(bool,0,"","ControllTouch","inAttackKey");
    inFreezeF = FieldBN(bool,0,"","Controll","inFreeze");
    inZoomF = FieldBN(bool,0,"","Controll","inZoom");
    inJumpKeyF = FieldBN(bool,0,"","ControllTouch","inJumpKey");
    freezetimeF = FieldBN(float,0,"","Controll","freezetime");
    playernameF = FieldBN(monoString*,0,"","Main","playername");
    signF = FieldBN(monoString*,0,"","Main","sign");
    gameidF = FieldBN(monoString*,0,"","Main","gameid");
    gamekeyF = FieldBN(monoString*,0,"","Main","gamekey");
    playersF = FieldBN(monoArray<void **>*,0,"","PLH","player");


}




#endif //STANDOFF0171_TOOLS_H
/*
switch (feature) {



case 4224:
switch (value) {
case 0:
spinbot1Yaw = true;
randomYaw = false;
spinbot2Yaw = false;
break;
case 1:
spinbot1Yaw = false;
randomYaw = false;
spinbot2Yaw = true;
break;
case 2:
spinbot1Yaw = false;
randomYaw = true;
spinbot2Yaw = false;
break;
}
break;
case 42241:
switch (value) {
case 0:
ctKnife = 0;
break;
case 1:
ctKnife = 3;
break;
case 2:
ctKnife = 68;
break;
case 3:
ctKnife = 69;
break;
case 4:
ctKnife = 72;
break;
case 5:
ctKnife = 76;
break;
case 6:
ctKnife = 86;
break;
}
break;
case 42242:
switch (value) {
case 0:
tKnife = 0;
break;
case 1:
tKnife = 3;
break;
case 2:
tKnife = 68;
break;
case 3:
tKnife = 69;
break;
case 4:
tKnife = 72;
break;
case 5:
tKnife = 76;
break;
case 6:
tKnife = 86;
break;
}
break;
case 8914:
drawcrosschair = boolean;
break;
case 8915:
crosschairsize = value;
break;
case 8916:
drawcircle = boolean;
break;
case 668:
drawcircle2 = boolean;
break;
case 8917:
circlestroke = value;
break;
case 8918:
circlesize = value * 10;
break;
case 669:
circlestroke2 = value;
break;
case 667:
circlesize2 = value * 10;
break;
case 1:
if (boolean) {
hexPatches.recv_pos.Modify();
} else {
hexPatches.recv_pos.Restore();
}
break;
case 2:
freezetime = boolean;
if (boolean) {
//hexPatches.recv_buyzone.Modify();
} else {
// hexPatches.recv_buyzone.Restore();
}
break;
case 3:
freezetime = boolean;
if (boolean) {
//hexPatches.recv_buytime.Modify();
} else {
//hexPatches.recv_buytime.Restore();
}
break;
case 75757:
Scopee = boolean;
if (boolean) {
hexPatches.Scope.Modify();
} else {
hexPatches.Scope.Restore();
}
break;
case 777555:
if (boolean) {
hexPatches.Shake1.Modify();
hexPatches.Shake2.Modify();
} else {
hexPatches.Shake1.Restore();
hexPatches.Shake2.Restore();
}
break;
case 771:
featureHookToggle = boolean;
break;
case 772:
feature12 = boolean;
break;
case 773:
feature20 = boolean;
break;
case 4:
if (boolean) {
hexPatches.UpdateSmoke.Modify();
} else {
hexPatches.UpdateSmoke.Restore();
}
break;
case 5:
if (boolean) {
hexPatches.recv_chatmsg.Modify();
} else {
hexPatches.recv_chatmsg.Restore();
}
break;
case 6:
feature6 = boolean;
break;
case 5252:
if (boolean) {
hexPatches.Kill_LocalPlayer.Modify();
hexPatches.Spawn.Modify();
} else {
hexPatches.Spawn.Restore();
hexPatches.Kill_LocalPlayer.Restore();
}
break;
case 7:
if (value >= 1) {
sliderValue = value;
set_timeScale(sliderValue);
}
break;
case 8:
if (value >= 1) {
sliderValue1 = value;
}
break;
case 1200:
XPOS = value;

break;
case 1201:
YPOS = value;

break;
case 1202:
ZPOS = value;

break;
case 1203:
feature31 = boolean;
break;
case 775:
sliderValue3 = value;
break;
case 4415:
SpeedValue = value;
break;
case 4416:
JumpValue = value;
break;
case 9090900:
weappos = boolean;
break;
case 8888:
SkyRender = boolean;
break;
case 88880:
RgbSky = boolean;
break;
case 88881:
SkyColorR = value;
break;
case 88882:
SkyColorG = value;
break;
case 88883:
SkyColorB = value;
break;
case 88884:
SkyColor = boolean;
break;
case 88885:
SkyPulse = boolean;
break;
case 75754:
if (boolean) {
hexPatches.Flash1.Modify();
hexPatches.Flash2.Modify();
}
else {
hexPatches.Flash1.Restore();
hexPatches.Flash2.Restore();
}
break;
case 778:
bhop = boolean;
break;
case 779:
strafe = boolean;
break;
case 91:
espenable = boolean;
break;
case 90:
visible = boolean;
break;
case 92:
espbox = boolean;
break;
case 93:
esphealth = boolean;
break;
case 94:
esptracer = boolean;
break;
case 95:
espname = boolean;
break;
case 969696:
randomslide = boolean;
break;

case 9119:
bitmaskkk = value;
break;

case 9641:
watermark = boolean;
break;
case 9642:
debbuger = boolean;
break;
case 9643:
indicators = boolean;
break;

case 9696981:
fakelagOnPeek = boolean;
break;
case 9696982:
fakelagOnStand = boolean;
break;
case 9696983:
fakelagOnMove = boolean;
break;
case 9696984:
fakelagOnAir = boolean;
break;

case 969699:
fakelagValue = value;
break;
case 9696100:
fakelagRandom = boolean;
break;

case 5969699:
PitchSpeed = value;
break;
case 6969699:
YawSpeed = value;
break;

case 3969699:
YawValue = value;
break;
case 1969699:
PitchValue = value;
break;

case 7969699:
YawValue1 = value;
break;
case 8969699:
PitchValue1 = value;
break;


case 969697:
slide = boolean;
break;
case 969695:
fakeduck = boolean;
break;
case 96:
esp3d = boolean;
break;
case 99:
playerCircle = boolean;
break;
case 10011:
bulletTracer = boolean;
break;
case 10012:
hitMarker = boolean;
break;
case 30011:
playerList = boolean;
break;

case 300121:
{
LoadClass GameObject;
LoadClass ExampleClass;
GameObject = LoadClass("UnityEngine", "GameObject");
void *new_GameObject = GameObject.CreateNewClass({}, 0); // No args
AddComponent(new_GameObject, GetType2(CreateMonoString("UnityEngine.TrailRenderer, UnityEngine")));
}
break;

case 20011:
radar = boolean;
break;
case 200111:
radarScale = value;
break;
case 200112:
radarZoom = value;
break;
case 100121:
hitMarkerR = value;
break;
case 100122:
hitMarkerG = value;
break;
case 100123:
hitMarkerB = value;
break;
case 100111:
bulletTracerR = value;
break;
case 100112:
bulletTracerG = value;
break;
case 100113:
bulletTracerB = value;
break;
case 91117:
doubletap = boolean;
break;
case 97:
esparmor = boolean;
break;
case 98:
espweapon = boolean;
break;
case 9981:
esphpoutline = boolean;
break;
case 9982:
espnameoutline = boolean;
break;
case 991:
esphpsize = value;
break;
case 992:
esphptextsize = boolean;
break;
case 994:
espgradient = boolean;
break;
case 995:
espstroke = value;
break;
case 996:
espround = value;
break;
case 993:
espnamesize = boolean;
break;
case 9090901:
XPOS = value;

break;
case 9090902:
YPOS = value;

break;
case 9090908:
if (value >= 1) {
rgbSpeed = value;
}
break;
case 9090909:
if (value >= 1) {
pulseSpeed = value;
}
break;
case 9090903:
ZPOS = value;
break;
case 77666:
if (value >= 1) {
if (camera){
Camera$$set_nearClipPlane(Camera$$get_main(),float(value)/100);
}
break;
}
break;
case 776:
if (value >= 1) {
sliderValue4 = value;
}
break;
case 777:
if (value >= 1) {
if (camera){
Camera$$set_farClipPlane(Camera$$get_main(),float(value)/100);
}
}
break;
case 9:
feature7 = boolean;
break;
case 10:
if (boolean) {
hexPatches.isLockedAttach.Modify();
} else {
hexPatches.isLockedAttach.Restore();
}
break;
case 410:
weapons = boolean;

break;
case 510:
skins = boolean;

break;

case 610:
characters = boolean;

break;

case 54:
if (boolean) {
hexPatches.CalcBulletSpread.Modify();
} else {
hexPatches.CalcBulletSpread.Restore();
}
break;
case 999:
SetWallhack(boolean);
break;
case 559:
WallhackOn(boolean);
break;
case 228337:
SetActiveConsole(boolean);
break;

case 22837:
SetProgressActive(boolean);
break;
case 22836:
SetAnimatorActive(boolean);
break;
case 22835:
SetWeaponActive(boolean);
break;
case 22834:
SetCharacterActive(boolean);
break;

case 2283326:
lerp1 = boolean;
break;

case 228336:
spam = boolean;
break;
case 757514:
logs1 = boolean;
break;

case 228331:
antiaim = boolean;
break;

case 2283300:
desync = boolean;
break;

case 1228332:
spinbot1Pitch = boolean;
break;
case 1228333:
spinbot2Pitch = boolean;
break;
case 1228334:
randomPitch = boolean;
break;

case 228332:
spinbot1Yaw = boolean;
break;

case 228333:
spinbot2Yaw = boolean;
break;
case 228334:
randomYaw = boolean;
break;



case 54545454:
masskill = boolean;
break;
case 545454541:
setweap = boolean;
break;
case 545454544:
feature28 = boolean;
drawaim1 = boolean;
break;

case 54545414:
AutoStop = boolean;
break;

case 54545424:
AimHead = boolean;
break;
case 54545434:
AimBody = boolean;
break;
case 54544341:
AimArms = boolean;
break;
case 54545444:
AimLegs = boolean;
break;
case 9021:
third = boolean;
break;
case 4535:
infFov = boolean;
break;

case 4536:
damagePr = boolean;
break;

case 444:
autofire = boolean;
break;
case 445:
autoscope = boolean;
break;
case 665:
aimbot = boolean;
//drawaim2 = boolean;
break;
case 666:
aimsmooth = boolean;
break;
case 228338:
sound = value;
break;
case 228339:
feature32 = boolean;
break;
case 71:
feature23 = boolean;
break;
case 72:
feature27 = boolean;
break;
case 337228:
feature29 = boolean;
break;
case 55:
if (boolean) {
hexPatches.Blood1.Modify();
hexPatches.Blood2.Modify();
} else {
hexPatches.Blood1.Restore();
hexPatches.Blood2.Restore();
}
break;
case 56:
if (boolean) {
hexPatches.CreateHole.Modify();
hexPatches.CreateHoleLocal.Modify();
} else {
hexPatches.CreateHole.Restore();
hexPatches.CreateHoleLocal.Restore();
}
break;
case 57:
if (boolean) {
hexPatches.UpdateCameraOffset.Modify();
} else {
hexPatches.UpdateCameraOffset.Restore();
}
break;
case 888:
StartDefuse(1, 69);
break;
case 12:
if (camera){
Camera$$set_fieldOfView(Camera$$get_main(), 50);
}
break;
case 56565656:
if (value >= 0) {
ctId = value;
}
break;
case 156565656:
ctknife = boolean;
break;
case 56565657:
if (value >= 0) {
tId = value;
}
break;
case 156565657:
tknife = boolean;
break;
case 5564:
SetR(float(value));
break;
case 5566:
SetG(float(value));
break;
case 5567:
SetB(float(value));
break;
case 55649:
SetR2(float(value));
break;
case 55669:
SetG2(float(value));
break;
case 55679:
SetB2(float(value));
break;
case 88941:
RemoveSet(boolean);
break;
case 5569:
SetA(float(value));
break;
case 9991:
SetWireframe(boolean);
break;
case 55641:
SetRw(float(value));
break;
case 55661:
SetGw(float(value));
break;
case 55671:
SetBw(float(value));
break;
case 228335:
detect = boolean;
break;
case 89141:
set_nightmode(boolean);
break;
case 5568441:
PulseT1Set(boolean);
break;
case 5568442:
PulseT2Set(boolean);
break;
case 5568443:
PulseWSet(boolean);
break;
case 5568444:
PulseGSet(boolean);
break;
case 556844:
Rgb0(boolean);
break;
case 5568:
Rgb1(boolean);
break;
case 55569:
Rgb2(boolean);
break;
case 55568:
Rgb3(boolean);
break;
case 6565651:
darkmode1set(boolean);
break;
case 6565654:
darkmode2set(boolean);
break;
case 6565652:
Wh2(boolean);
break;

case 242424:
SetShading(boolean);
break;
case 2424240:
SetWs(boolean);
break;
case 2424241:
SetRs(boolean);
break;
case 2424242:
SetGs(boolean);
break;
case 2424243:
SetBs(boolean);
break;

case 6565653:
Wh3(boolean);
break;
case 9992:
SetGlow(boolean);
break;
case 99925:
set_nightmode(boolean);
break;
case 99990:
set_arms(boolean);
break;
case 99991:
PulseASet(boolean);
break;
case 99992:
Rgb5(boolean);
break;
case 99993:
darkmode4set(boolean);
break;
case 99994:
SetRa(float(value));
break;
case 99995:
SetGa(float(value));
break;
case 99996:
SetBa(float(value));
break;
case 555685:
Rgb4(boolean);
break;
case 555686:
darkmode3set(boolean);
break;
case 556425:
SetRn(float(value));
break;
case 556625:
SetGn(float(value));
break;
case 556725:
SetBn(float(value));
break;
case 999213:
drawvel = boolean;
break;
case 92935:
espprev = boolean;
break;
case 9992131:
playerLine = boolean;
break;
case 55642:
SetRg(float(value));
break;
case 55662:
SetGg(float(value));
break;
case 55672:
SetBg(float(value));
break;
case 87876:
scopeValue = value;
break;
case 64:
vR = value;
break;
case 65:
vG = value;
break;
case 66:
vB = value;
break;
case 67:
invR = value;
break;
case 68:
invG = value;
break;
case 69:
invB = value;
break;
case 525252:
maxDelay = value;
break;

case 9921:
customWidth = value;
break;
case 9922:
customHeight = value;
break;
case 9923:
SetResolution(customWidth, customHeight, true);
break;

case 264:
if (value >= 1) {
SetWidthG(value);
}
break;
case 566:
if (value >= 1) {
if (camera){
Camera$$set_clearFlags(Camera$$get_main(), value);
}
}
break;
case 556:
feature12 = boolean;
break;
case 51:
if (boolean) {
hexPatches.RemoveWeapon.Modify();
} else {
hexPatches.RemoveWeapon.Restore();
}
break;
case 52:
feature15 = boolean;
break;
case 5152:
setWeapon = true;
break;
case 51523:
idtoset = value;
break;
case 53:
if (boolean) {
hexPatches.RemoveWeapon.Restore();
} else {
hexPatches.RemoveWeapon.Modify();
}
break;




case 8880:
materialEnabled = boolean;
break;
case 8881:
materialGlossiness = value;
break;
case 8882:
materialGlossinessScale = value;
break;
case 8883:
materialMetallic = value;
break;
case 8884:
materialCutoff = value;
break;
case 8885:
materialSpecular = value;
break;
case 8886:
materialReflections = value;
break;
case 8887:
materialBump = value;
break;
case 8889:
materialOcclusion = value;
break;

case 3330:
materialPulseTex = boolean;
break;
case 3331:
materialRainbowTex = boolean;
break;
case 3332:
materialRedTex = value;
break;
case 3333:
materialGreenTex = value;
break;
case 3334:
materialBlueTex = value;
break;

case 3335:
materialPulseEmission = boolean;
break;
case 3336:
materialRainbowEmission = boolean;
break;
case 3337:
materialRedEmission = value;
break;
case 3338:
materialGreenEmission = value;
break;
case 3339:
materialBlueEmission = value;
break;
*/