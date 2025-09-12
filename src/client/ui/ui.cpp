#include "ui.h"
#include "../../globals.h"
#include "../../entities/buildings/building.h"
#include "components/button/button.h"

UI::UI()
{
    menuPosition = { 0, (float)GetScreenHeight() - 100 };
    menuSize = { (float)GetScreenWidth(), 100 };

    const char* text = "Base";
    Vector2 buttonPosition = { 5, (float)GetScreenHeight() - 90 };
    Vector2 buttonSize = { 100, 25 };

    Button baseButton = Button(buttonPosition, buttonSize, LIGHTGRAY, text);
    baseButton.SetOnClickEvent
    (
        []()
        {
            if (!world.IsAnyBuildingInBuildMode())
            {
                world.AddBuilding(Building(Building::BASE));
            }
        }
    );

    buttons.push_back(baseButton);
}

void UI::DrawResources()
{
    Vector2 position = { 0, 0 };
    Vector2 size = { (float)GetScreenWidth(), 100 };

    DrawRectangleV(position, size, GRAY);

    std::string wood = "Wood: ";
    std::string stone = "Stone: ";
    std::string iron = "Iron: ";
    std::string money = "Money: ";

    uint16_t textPosX = 10;
    uint16_t textPosY = 10;
    uint16_t margin = 0;
    uint8_t fontSize = 20;

    const char* resourcesTextToDisplay[4] =
    {
        wood.append(std::to_string(player.GetWood())).c_str(),
        stone.append(std::to_string(player.GetStone())).c_str(),
        iron.append(std::to_string(player.GetIron())).c_str(),
        money.append(std::to_string(player.GetMoney())).c_str()
    };

    for (const char* text : resourcesTextToDisplay)
    {
        DrawText(text, textPosX, textPosY + margin, fontSize, WHITE);
        margin += 20;
    }
}

void UI::DrawShop()
{
    DrawRectangleV(menuPosition, menuSize, GRAY);
}

void UI::OpenBuildingMenu(Building::BuildingType type)
{
    const int fontSize = 20;
    const char* text = "Add creature";
    float margin = 10;
    Vector2 buttonPosition = { margin, (float)(GetScreenHeight() - 60) };
    
    DrawRectangleV(menuPosition, menuSize, GRAY);
    switch (type)
    {
    case Building::BASE:
        break;
    case Building::SAWMILL:
        break;
    default:
        break;
    }
}

void UI::Update()
{
    for (auto& button : buttons)
    {
        button.OnClick();
    }
}

void UI::Draw()
{
    DrawResources();
    DrawShop();
    
    for (auto& button : buttons)
    {
        button.Draw();
    }
}


