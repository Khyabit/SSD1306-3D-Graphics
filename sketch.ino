class float3 {
public:
    float x, y, z;

    float3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float3() {}

    float3 operator -(float3 a) {
        return float3(x-a.x, y-a.y, z-a.z);
    }


    float get_length() {
        return sqrt((x*x) + (y*y) + (z*z));
    }
    float3 normalize(float3 a);
};

class float4 {

public:
    float x, y, z, w;
    
    float4(float x, float y, float z, float w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    float4() {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }

    float4(float3 a, float w) {
        x = a.x;
        y = a.y;
        z = a.z;
        this->w = w;
    }

    float4 operator *(float a) {
        return float4(x*a, y*a, z*a, w*a);
    }
};


class float4x4 {
public:
    float4 row0, row1, row2, row3;

    float4x4(float4 r1, float4 r2, float4 r3, float4 r4) {
        row0 = r1;
        row1 = r2;
        row2 = r3;
        row3 = r4;
    }

    float4x4() {
        row0 = float4();
        row1 = float4();
        row2 = float4();
        row3 = float4();
    }

    float4x4 operator *(float4x4 a) {

        float4 r0 = float4(row0.x*a.row0.x + row0.y*a.row1.x + row0.z*a.row2.x + row0.w*a.row3.x, 
                           row0.x*a.row0.y + row0.y*a.row1.y + row0.z*a.row2.y + row0.w*a.row3.y, 
                           row0.x*a.row0.z + row0.y*a.row1.z + row0.z*a.row2.z + row0.w*a.row3.z,
                           row0.x*a.row0.w + row0.y*a.row1.w + row0.z*a.row2.w + row0.w*a.row3.w);

        float4 r1 = float4(row1.x*a.row0.x + row1.y*a.row1.x + row1.z*a.row2.x + row1.w*a.row3.x, 
                           row1.x*a.row0.y + row1.y*a.row1.y + row1.z*a.row2.y + row1.w*a.row3.y, 
                           row1.x*a.row0.z + row1.y*a.row1.z + row1.z*a.row2.z + row1.w*a.row3.z,
                           row1.x*a.row0.w + row1.y*a.row1.w + row1.z*a.row2.w + row1.w*a.row3.w);

        float4 r2 = float4(row2.x*a.row0.x + row2.y*a.row1.x + row2.z*a.row2.x + row2.w*a.row3.x, 
                           row2.x*a.row0.y + row2.y*a.row1.y + row2.z*a.row2.y + row2.w*a.row3.y, 
                           row2.x*a.row0.z + row2.y*a.row1.z + row2.z*a.row2.z + row2.w*a.row3.z,
                           row2.x*a.row0.w + row2.y*a.row1.w + row2.z*a.row2.w + row2.w*a.row3.w);

        float4 r3 = float4(row3.x*a.row0.x + row3.y*a.row1.x + row3.z*a.row2.x + row3.w*a.row3.x, 
                           row3.x*a.row0.y + row3.y*a.row1.y + row3.z*a.row2.y + row3.w*a.row3.y, 
                           row3.x*a.row0.z + row3.y*a.row1.z + row3.z*a.row2.z + row3.w*a.row3.z,
                           row3.x*a.row0.w + row3.y*a.row1.w + row3.z*a.row2.w + row3.w*a.row3.w);
        
        return float4x4(r0, r1, r2, r3);
    }

    float4 operator *(float4 a) {
        return float4(
          row0.x * a.x + row0.y * a.y + row0.z * a.z + row0.w * a.w,
        -(row1.x * a.x + row1.y * a.y + row1.z * a.z + row1.w * a.w),
          row2.x * a.x + row2.y * a.y + row2.z * a.z + row2.w * a.w,
          row3.x * a.x + row3.y * a.y + row3.z * a.z + row3.w * a.w
        );
    }

    float4x4 lookAt(float3 view_position, float3 view_target, float3 up);
};

float3 normalize(float3 a) {
    float scale = 1.0/a.get_length();
    return float3(a.x * scale, a.y * scale, a.z * scale);
}

float3 cross(float3 a, float3 b) {
    return float3(
      (a.y * b.z) - (a.z * b.y),
      (a.z * b.x) - (a.x * b.z),
      (a.x * b.y) - (a.y * b.x));
}


float4x4 lookAt(float3 view_position, float3 view_target, float3 up) {
    float3 z = normalize(view_position - view_target);
    float3 x = normalize(cross(up, z));
    float3 y = normalize(cross(x, z));

    float x_eye = -((x.x * view_position.x) + (x.y * view_position.y) + (x.z * view_position.z));
    float y_eye = -((y.x * view_position.x) + (y.y * view_position.y) + (y.z * view_position.z));
    float z_eye = -((z.x * view_position.x) + (z.y * view_position.y) + (z.z * view_position.z));

    return float4x4(float4(x.x, y.x, z.x, 0),
                    float4(x.y, y.y, z.y, 0),
                    float4(x.z, y.z, z.z, 0),
                    float4(x_eye, y_eye, z_eye, 1));
}

float4x4 identity(float scale) {
    return float4x4(float4(scale, 0, 0, 0),
                    float4(0, scale, 0, 0),
                    float4(0, 0, scale, 0),
                    float4(0, 0, 0,     1));
}

float4x4 perspectiveProjection(float fovRadians, float aspect, float zNear, float zFar) {
    float yScale = 1.0 / tan(fovRadians * 0.5);
    float xScale = yScale / aspect;
    float zRange = zFar - zNear;
    float zScale = -(zFar + zNear) / zRange;
    float wzScale = -2.0 * zFar * zNear / zRange;

    float xx = xScale;
    float yy = yScale;
    float zz = zScale;
    float zw = -1.0;
    float wz = wzScale;

    return float4x4(float4(xx, 0, 0, 0),
                    float4( 0,yy, 0, 0),
                    float4( 0, 0,zz,zw),
                    float4( 0, 0,wz, 0));
}


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


float3 coords[] = {
    float3(-1, 1, 1),
    float3(-1,-1, 1),
    float3( 1,-1, 1),
    float3( 1, 1, 1),
    float3(-1, 1,-1),
    float3(-1,-1,-1),
    float3( 1,-1,-1),
    float3( 1, 1,-1),
};

float3 eye = float3(0,0,0);
float yrot = 0, xrot = 0;

void setup() {

    float4x4 projection = perspectiveProjection(radians(90), 1.0, 0.1, 1000.0);
    float4x4 view = lookAt(float3(0,0,0), float3(0,0,1), float3(0,1,0));
    float4x4 model = identity(50);

    float4x4 MVP = projection * view * model;

    float4 screenPositions[] = {
        MVP * float4(coords[0], 1.0),
        MVP * float4(coords[1], 1.0),
        MVP * float4(coords[2], 1.0),
        MVP * float4(coords[3], 1.0)
    };

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay(); 

    for (int i = 0; i < 4; i++) {
        int x = int(floor(screenPositions[i].x));
        int y = int(floor(screenPositions[i].y));

        display.drawPixel(x, y, WHITE);
    }
    display.drawLine(int(floor(screenPositions[0].x)), int(floor(screenPositions[0].y)), int(floor(screenPositions[1].x)), int(floor(screenPositions[1].y)), WHITE);
    display.drawLine(int(floor(screenPositions[0].x)), int(floor(screenPositions[0].y)), int(floor(screenPositions[2].x)), int(floor(screenPositions[2].y)), WHITE);
    display.drawLine(int(floor(screenPositions[1].x)), int(floor(screenPositions[1].y)), int(floor(screenPositions[2].x)), int(floor(screenPositions[2].y)), WHITE);
    display.drawLine(int(floor(screenPositions[1].x)), int(floor(screenPositions[1].y)), int(floor(screenPositions[3].x)), int(floor(screenPositions[3].y)), WHITE);
    display.drawLine(int(floor(screenPositions[2].x)), int(floor(screenPositions[2].y)), int(floor(screenPositions[3].x)), int(floor(screenPositions[3].y)), WHITE);
    
    display.display();
}

void loop() { 

    float4x4 projection = perspectiveProjection(radians(90), 1.0, 0.1, 1000.0);
    float4x4 view = lookAt(float3(0,0,10), float3(eye.x,eye.y,eye.z+10), float3(0,1,0));
    float4x4 model = identity(10);

    float4x4 MVP = projection * view * model;

    float4 screenPositions[] = {
        MVP * float4(coords[0], 1.0) * 2,
        MVP * float4(coords[1], 1.0) * 2,
        MVP * float4(coords[2], 1.0) * 2,
        MVP * float4(coords[3], 1.0) * 2,
        MVP * float4(coords[4], 1.0) * 2,
        MVP * float4(coords[5], 1.0) * 2,
        MVP * float4(coords[6], 1.0) * 2,
        MVP * float4(coords[7], 1.0) * 2
    };

    eye = normalize(float3(
        cos(radians(xrot)) * cos(radians(yrot)),
        sin(radians(xrot)),
        cos(radians(xrot)) * sin(radians(yrot))
      ));

    yrot+=5;
    xrot+=2;

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay(); 

    display.drawLine(int(floor(screenPositions[0].x)+64), int(floor(screenPositions[0].y)+32), int(floor(screenPositions[1].x)+64), int(floor(screenPositions[1].y)+32), WHITE);
    display.drawLine(int(floor(screenPositions[3].x)+64), int(floor(screenPositions[3].y)+32), int(floor(screenPositions[2].x)+64), int(floor(screenPositions[2].y)+32), WHITE);
    display.drawLine(int(floor(screenPositions[0].x)+64), int(floor(screenPositions[0].y)+32), int(floor(screenPositions[3].x)+64), int(floor(screenPositions[3].y)+32), WHITE);
    display.drawLine(int(floor(screenPositions[0].x)+64), int(floor(screenPositions[0].y)+32), int(floor(screenPositions[4].x)+64), int(floor(screenPositions[4].y)+32), WHITE);
    display.drawLine(int(floor(screenPositions[5].x)+64), int(floor(screenPositions[5].y)+32), int(floor(screenPositions[4].x)+64), int(floor(screenPositions[4].y)+32), WHITE);
    display.drawLine(int(floor(screenPositions[7].x)+64), int(floor(screenPositions[7].y)+32), int(floor(screenPositions[4].x)+64), int(floor(screenPositions[4].y)+32), WHITE);
    display.drawLine(int(floor(screenPositions[1].x)+64), int(floor(screenPositions[1].y)+32), int(floor(screenPositions[5].x)+64), int(floor(screenPositions[5].y)+32), WHITE);
    display.drawLine(int(floor(screenPositions[1].x)+64), int(floor(screenPositions[1].y)+32), int(floor(screenPositions[2].x)+64), int(floor(screenPositions[2].y)+32), WHITE);
    display.drawLine(int(floor(screenPositions[6].x)+64), int(floor(screenPositions[6].y)+32), int(floor(screenPositions[5].x)+64), int(floor(screenPositions[5].y)+32), WHITE);
    display.drawLine(int(floor(screenPositions[6].x)+64), int(floor(screenPositions[6].y)+32), int(floor(screenPositions[2].x)+64), int(floor(screenPositions[2].y)+32), WHITE);
    display.drawLine(int(floor(screenPositions[6].x)+64), int(floor(screenPositions[6].y)+32), int(floor(screenPositions[7].x)+64), int(floor(screenPositions[7].y)+32), WHITE);
    display.drawLine(int(floor(screenPositions[3].x)+64), int(floor(screenPositions[3].y)+32), int(floor(screenPositions[7].x)+64), int(floor(screenPositions[7].y)+32), WHITE);
    
    display.display();
    delay(1);
}
