#include "raylib.h"
#include <math.h>

#define SCREEN_HEIGHT 500
#define SCREEN_WIDTH 500
#define PI 3.1415926

float dist(int x1, int y1, int x2, int y2){
    return sqrt(pow((float)x1 - x2, 2) + pow((float)y1 - y2, 2));
}

float mouseXVel = 0;
float mouseYVel = 0;
int pastMouseX = 0;
int pastMouseY = 0;

class Ball{
    public:
        int x, y, radius;
        float xVel = 0, yVel = 0;
        Color color;
        bool moving = false;
        
        Ball(int _x, int _y, int _radius, Color _color){
            x = _x;
            y = _y;
            radius = _radius;
            color = _color;
        }
        
        void draw(){
            DrawCircle(x, y, radius, color);
        }
        
        void drag(){
            float increment = 0.1;
            // Drag on the xVel
            if (xVel >= increment){
                xVel -= increment;
            } else if (xVel <= -increment){
                xVel += increment;
            } else {
                xVel = 0;
            }
            
            // Drag on the yVel
            if (yVel >= increment){
                yVel -= increment;
            } else if (yVel <= -increment){
                yVel += increment;
            } else {
                yVel = 0;
            }
        }
        
        bool ballInBounds(){
            return (x + xVel >= radius && x + xVel <= SCREEN_WIDTH - radius) && (y + yVel >= radius && y + yVel <= SCREEN_HEIGHT - radius);
        }
        
        void move(){
            if (dist(x, y, GetMouseX(), GetMouseY()) <= radius && IsMouseButtonPressed(0)){ // On click
                moving = true;
            }
            if (IsMouseButtonReleased(0)){
                moving = false;
                xVel = mouseXVel/5;
                yVel = mouseYVel/5;
            }
            if (moving){
                if (GetMouseX() > radius && GetMouseX() < SCREEN_WIDTH - radius)
                    x = GetMouseX();
                if (GetMouseY() > radius && GetMouseY() < SCREEN_HEIGHT - radius)
                    y = GetMouseY();
            } else {
                x += xVel;
                if (x < radius || x > SCREEN_WIDTH - radius){
                    xVel *= -1;
                    x += xVel;
                }
                    
                y += yVel;
                if (y < radius || y > SCREEN_HEIGHT - radius){
                    yVel *= -1;
                    y += yVel;
                }
                drag();
                if (y >= SCREEN_HEIGHT - radius * 1.2){
                    y = SCREEN_HEIGHT - radius;
                }
            }
        }
};

Ball ball(250, 250, 20, RED);

void updateMouseVel(){
    mouseXVel = GetMouseX() - pastMouseX;
    mouseYVel = GetMouseY() - pastMouseY;
    pastMouseX = GetMouseX();
    pastMouseY = GetMouseY();
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bouncing ball");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(WHITE);
        
        updateMouseVel();
        
        ball.draw();
        ball.move();
        
        ball.yVel += 0.3;
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}