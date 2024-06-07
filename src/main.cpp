#include "App.hpp"

#include "Core/Context.hpp"

int main(int, char **) {
    auto context = Core::Context::GetInstance();
    App app;

    while (!context->GetExit()) {
        switch (app.GetCurrentState()) {
            case App::State::START:
                app.Start();
                break;

            case App::State::UPDATE:
                app.Update();
                break;

            case App::State::LEVEL_1:
                app.Level_1();
                break;

            case App::State::LEVEL_2:
                app.Level_2();
                break;

            case App::State::LEVEL_3:
                app.Level_3();
                break;

            case App::State::LEVEL_4:
                app.Level_4();
                break;

            case App::State::LOSE:
                app.Lose();
                break;

            case App::State::END:
                app.End();
                context->SetExit(true);
                break;
        }
        context->Update();
    }
    return 0;
}
