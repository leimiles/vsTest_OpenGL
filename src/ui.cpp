#include "users/ui.h"

ui::ui(/* args */)
{
    ImGui::Text("Hello, world %d", 123);
    if (ImGui::Button("Save"))
    {
    }
}

ui::~ui()
{
}