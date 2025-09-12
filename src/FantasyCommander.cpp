#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "globals.h"
#include "client/ui/ui.h"


int main()
{
    SetTargetFPS(60);
    ui = UI();
    Creature c = Creature({ 120.0f, 100.0f }, Creature::WARRIOR);
    Creature c2 = Creature({ 150.0f, 100.0f }, Creature::WARRIOR);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        ClearBackground(DARKGREEN);
        
        // Update
        ui.Update();
        world.Update();
        

        //should be moved to Update in world
        world.Move();

        //Draw
        world.Draw();
        ui.Draw();

        EndDrawing();
    }
}