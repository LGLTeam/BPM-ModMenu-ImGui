#ifndef DESI_ESP_IMPORTANT_HACKS_H
#define DESI_ESP_IMPORTANT_HACKS_H
#include <thread>
#include <sys/uio.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <stdio.h>
#include <sys/un.h>
#include <time.h>
#include <ctype.h>
#include <iostream>
static bool drawaim1;
static bool drawaim2;

static bool drawcircle;
static bool drawcrosschair;

static bool drawcircle2;
static bool drawcrosschair2;
static int circlestroke2 = 3;
static int circlesize2 = 45;

static int crosschairsize = 30;
static int circlestroke = 3;
static int circlesize = 45;
static int vel = 45;

Vec22 a1,b1,c1,d1,e1,f1,g1,h1,up1,down1;
Vec22 a2,b25,c2,d2,e2,f2,g25,h2,up2,down2;
Vec22 a3,b3,c3,d3,e3,f3,g3,h3,up3,down3;
Vec22 a4,b4,c4,d4,e4,f4,g4,h4,up4,down4;
Vec22 a5,b5,c5,d5,e5,f5,g5,h5,up5,down5;
Vec22 a6,b6,c6,d6,e6,f6,g6,h6,up6,down6;
Vec22 a7,b7,c7,d7,e7,f7,g7,h7,up7,down7;
Vec22 a8,b8,c8,d8,e8,f8,g8,h8,up8,down8;
Vec22 a9,b9,c9,d9,e9,f9,g9,h9,up9,down9;
Vec22 a10,b10,c10,d10,e10,f10,g10,h10,up10,down10;

static int bulletstart1 = 45;
static int bulletstart2 = 45;
static int bulletend1 = 45;
static int bulletend2 = 45;

static bool esp3d;

static bool esp1;
static int x1tracer = 45;
static int y1tracer = 45;
static int x1tracer2 = 45;
static int y1tracer2 = 45;
static int hpesp1 = 100;
const char *nameesp1 = "unconnected";

static bool esp2;
static int x2tracer = 45;
static int y2tracer = 45;
static int x2tracer2 = 45;
static int y2tracer2 = 45;
static int hpesp2 = 100;
const char *nameesp2 = "unconnected";

static bool esp3;
static int x3tracer = 45;
static int y3tracer = 45;
static int x3tracer2 = 45;
static int y3tracer2 = 45;
static int hpesp3 = 100;
const char *nameesp3 = "unconnected";

static bool esp4;
static int x4tracer = 45;
static int y4tracer = 45;
static int x4tracer2 = 45;
static int y4tracer2 = 45;
static int hpesp4 = 100;
const char *nameesp4 = "unconnected";

static bool esp5;
static int x5tracer = 45;
static int y5tracer = 45;
static int x5tracer2 = 45;
static int y5tracer2 = 45;
static int hpesp5 = 100;
const char *nameesp5 = "unconnected";

static bool esp6;
static int x6tracer = 45;
static int y6tracer = 45;
static int x6tracer2 = 45;
static int y6tracer2 = 45;
static int hpesp6 = 100;
const char *nameesp6 = "unconnected";

static bool esp7;
static int x7tracer = 45;
static int y7tracer = 45;
static int x7tracer2 = 45;
static int y7tracer2 = 45;
static int hpesp7 = 100;
const char *nameesp7 = "unconnected";

static bool esp8;
static int x8tracer = 45;
static int y8tracer = 45;
static int x8tracer2 = 45;
static int y8tracer2 = 45;
static int hpesp8 = 100;
const char *nameesp8 = "unconnected";

static bool esp9;
static int x9tracer = 45;
static int y9tracer = 45;
static int x9tracer2 = 45;
static int y9tracer2 = 45;
static int hpesp9 = 100;
const char *nameesp9 = "unconnected";

static bool esp10;
static int x10tracer = 45;
static int y10tracer = 45;
static int x10tracer2 = 45;
static int y10tracer2 = 45;
static int hpesp10 = 100;
const char *nameesp10 = "unconnected";

static int espscale = 45;

static std::string playername1 = "unconnected";
static int health1 = 0;
static int ammo1 = 0;
static bool plalive1;
static bool pldraw1;

static std::string playername2 = "unconnected";
static int health2 = 0;
static int ammo2 = 0;
static bool plalive2;
static bool pldraw2;

static std::string playername3 = "unconnected";
static int health3 = 0;
static int ammo3 = 0;
static bool plalive3;
static bool pldraw3;

static std::string playername4 = "unconnected";
static int health4 = 0;
static int ammo4 = 0;
static bool plalive4;
static bool pldraw4;

static std::string playername5 = "unconnected";
static int health5 = 0;
static int ammo5 = 0;
static bool plalive5;
static bool pldraw5;

static std::string playername6 = "unconnected";
static int health6 = 0;
static int ammo6 = 0;
static bool plalive6;
static bool pldraw6;

static std::string playername7 = "unconnected";
static int health7 = 0;
static int ammo7 = 0;
static bool plalive7;
static bool pldraw7;

static std::string playername8 = "unconnected";
static int health8 = 0;
static int ammo8 = 0;
static bool plalive8;
static bool pldraw8;

static std::string playername9 = "unconnected";
static int health9 = 0;
static int ammo9 = 0;
static bool plalive9;
static bool pldraw9;

static std::string playername10 = "unconnected";
static int health10 = 0;
static int ammo10 = 0;
static bool plalive10;
static bool pldraw10;

const char *Weapon1 = "unconnected";
const char *Weapon2 = "unconnected";
const char *Weapon3 = "unconnected";
const char *Weapon4 = "unconnected";
const char *Weapon5 = "unconnected";
const char *Weapon6 = "unconnected";
const char *Weapon7 = "unconnected";
const char *Weapon8 = "unconnected";
const char *Weapon9 = "unconnected";
const char *Weapon10 = "unconnected";






float x,y;
char extra[30];
int botCount,playerCount;
Color clr,clrHealth;
int cfd;
int recbytes;
int sin_size;
struct sockaddr_in s_add, c_add;
unsigned short portnum = 443;
#define PI 3.141592653589793238
float px;
float py;
struct D3DXVECTOR4
{
    float X;
    float Y;
    float Z;
    float W;
};
struct D3DXMATRIX
{
    float _11;
    float _12;
    float _13;
    float _14;
    float _21;
    float _22;
    float _23;
    float _24;
    float _31;
    float _32;
    float _33;
    float _34;
    float _41;
    float _42;
    float _43;
    float _44;
};


#endif //kolarubin870
