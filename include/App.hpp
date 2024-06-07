#ifndef APP_HPP
#define APP_HPP

#include <string>
#include "pch.hpp" // IWYU pragma: export
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Root.hpp"
#include "Util/Input.hpp"
#include "Util/Text.hpp"
#include "Util/SFX.hpp"
#include "BackgroundImage.hpp"
#include "Message.hpp"
#include "Base.hpp"
#include "Tube.hpp"
#include "Bird.hpp"
#include "Text.hpp"
#include "ON.hpp"
#include "OFF.hpp"
class App {
public:
    enum class State {
        START,
        UPDATE,
        LEVEL_1,
        LEVEL_2,
        LEVEL_3,
        LEVEL_4,
        LOSE,
        RESET,
        END,
    };

    App();
    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();
    void Level_1();
    void Level_2();
    void Level_3();
    void Level_4();

    void Lose();
    void Reset();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();
    void UpdateGame(int gameSpeed, int scoreThreshold, int X1, int Y1, int Y2, float tubeupMove, float tubedownMove);
private:
    State m_CurrentState = State::START;
    Util::Root m_Root;
    std::shared_ptr<Util::GameObject> t;
    std::shared_ptr<Message> m_Message;
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<Base> m_Base;
    std::vector<std::shared_ptr<Tube>> m_TubesUp;
    std::vector<std::shared_ptr<Tube>> m_TubesDown;
    std::vector<std::shared_ptr<Tube>> m_Pipe;
    std::shared_ptr<Bird> m_Bird;
    std::shared_ptr<Text> m_ScoreText;
    std::shared_ptr<Util::SFX> m_PointSFX;
    std::shared_ptr<Util::SFX> m_HitSFX;
    std::shared_ptr<Util::GameObject> m_GameOver;
    std::shared_ptr<ON> m_ON;
    std::shared_ptr<OFF> m_OFF;
    int m_Score = 0;
    int m_jumpCount = 0;
    int m_GameSpeed = 2;//遊戲速度
    int m_TubeInterval = 120;//水管之間的間隔
    static bool speedIncreased;
    bool collisionDetectionEnabled = true;
};

#endif