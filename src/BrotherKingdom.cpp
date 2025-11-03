#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "globals.h"
#include "entities/creatures/hero/hero.h"
#include "client/ui/ui.h"


int main()
{
    SetTargetFPS(60);
    Hero hero = Hero("Doberman", 100, 100, 10, 50, 100, Vector2{ 800, 800 });
    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        ui.Update();
        world.Update();
        
        world.Move();

        world.Draw();
        ui.Draw();

        EndDrawing();
    }
}