#include <iostream>
#include <vector>

#include "common.h"
#include "glm/glm.hpp"
#include "Application.h"
#include "Components/GameObject.h"
#include "Components/Component.h"
#include <assert.h>


int main() {
    Logger::init();
    WindowSetting setting = {
        1600,
        900,
        0,
        "Material Editor",
        false,
        false,
        false
    };
    Application* app = new Application(setting);
    app->Run();
    system("pause");
    Logger::clean();
    return 0;
}
