#include "App.hpp"

App::App() {
    srand(time(NULL));
    m_Background = std::make_shared<BackgroundImage>(RESOURCE_DIR"/Image/Background/background-day.png");
    m_Root.AddChild(m_Background);
    m_Base = std::make_shared<Base>();
    m_Root.AddChild(m_Base);
    m_Base->SetPosition({0.5f, -209.5f});
    m_Message = std::make_shared<Message>();
    m_Root.AddChild(m_Message);
    m_ON = std::make_shared<ON>();
    m_Root.AddChild(m_ON);
    m_ON->SetPosition({100, 200});
    m_ON->SetVisible(false);
    m_OFF = std::make_shared<OFF>();
    m_Root.AddChild(m_OFF);
    m_OFF->SetPosition({100, 200});
}

void App::Start() {
    LOG_TRACE("Start");
    if (Util::Input::IsKeyPressed(Util::Keycode::SPACE)) {
        m_Message->SetVisible(false);
        //Green Tube
        for (int i = 0; i < 3; i++) {
            std::shared_ptr<Tube> tempTubeUp;
            std::shared_ptr<Tube> tempTubeDown;
            int r = rand() % 110 - 20;
            tempTubeUp = std::make_shared<Tube>(RESOURCE_DIR"/Image/Character/tube_up.png");
            tempTubeDown = std::make_shared<Tube>(RESOURCE_DIR"/Image/Character/tube.png");
            tempTubeUp->SetPosition({170 + i * 180, r + 160 + m_TubeInterval / 2});
            tempTubeDown->SetPosition({170 + i * 180, r - 160 - m_TubeInterval / 2});
            m_TubesUp.push_back(tempTubeUp);
            m_TubesDown.push_back(tempTubeDown);
            m_Root.AddChild(tempTubeUp);
            m_Root.AddChild(tempTubeDown);
        }
        //Red Tube
        m_Bird = std::make_shared<Bird>();
        m_Root.AddChild(m_Bird);
        m_Bird->SetPosition({-90, 20});

        m_ScoreText = std::make_shared<Text>();
        m_ScoreText->SetText("0");
        m_ScoreText->SetPosition({0, 200});
        m_ScoreText->SetZIndex(99);
        m_Root.AddChild(m_ScoreText);

        m_GameOver = std::make_shared<Util::GameObject>();
        m_GameOver->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Image/gameover.png"));
        m_GameOver->SetZIndex(98);
        m_GameOver->SetVisible(false);
        m_Root.AddChild(m_GameOver);

        m_PointSFX = std::make_shared<Util::SFX>(RESOURCE_DIR"/audio/point.wav");
        m_HitSFX = std::make_shared<Util::SFX>(RESOURCE_DIR"/audio/hit.wav");
        m_CurrentState = State::UPDATE;
    }
    m_Root.Update();
}
void App::UpdateGame(int gameSpeed, int scoreThreshold, int X1, int Y1, int Y2, float tubeupMove, float tubedownMove) {


    if (Util::Input::IsKeyUp(Util::Keycode::T) || Util::Input::IfExit()) {
        collisionDetectionEnabled = false; // 當按下‘X’鍵時禁用碰撞檢測
        m_ON->SetVisible(true);
        m_OFF->SetVisible(false);
    }
    if (Util::Input::IsKeyUp(Util::Keycode::F) || Util::Input::IfExit()) {
        collisionDetectionEnabled = true; // 當按下‘X’鍵時禁用碰撞檢測
        m_ON->SetVisible(false);
        m_OFF->SetVisible(true);
    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
        return;
    }
    if (Util::Input::IsKeyUp(Util::Keycode::N)) {
        m_CurrentState = static_cast<State>(static_cast<int>(m_CurrentState) + 1);
    }
    // Update tube positions
    for (auto &tubeUp : m_TubesUp) {
        tubeUp->SetPosition({tubeUp->GetPosition().x - gameSpeed, tubeUp->GetPosition().y});
    }
    for (auto &tubeDown : m_TubesDown) {
        tubeDown->SetPosition({tubeDown->GetPosition().x - gameSpeed, tubeDown->GetPosition().y});
    }

    if (Util::Input::IsKeyDown(Util::Keycode::SPACE)) {
        m_jumpCount = 15 / gameSpeed;
    }

    if (m_jumpCount != 0) {
        m_Bird->SetPosition({m_Bird->GetPosition().x, m_Bird->GetPosition().y + 2 * gameSpeed});
        m_jumpCount--;
    } else {
        m_Bird->SetPosition({m_Bird->GetPosition().x, m_Bird->GetPosition().y - 1});
    }

    for (int i = 0; i < 3; i++) {
        if (collisionDetectionEnabled) { // 只有在啟用碰撞檢測時才檢查碰撞
            if (m_Bird->isOverlap(m_TubesUp[i]) || m_Bird->isOverlap(m_TubesDown[i])) {
                m_GameOver->SetVisible(true);
                m_HitSFX->Play(0);
                m_CurrentState = State::LOSE;
                return;
            }
        }

//        if (m_Bird->isOverlap(m_TubesUp[i]) || m_Bird->isOverlap(m_TubesDown[i])) {
//            m_GameOver->SetVisible(true);
//            m_HitSFX->Play(0);
//            m_CurrentState = State::LOSE;
//            return;
//        }

        if (m_Bird->GetPosition().x == m_TubesUp[i]->GetPosition().x) {
            m_Score++;
            if (m_Score == scoreThreshold) {
                m_CurrentState = static_cast<State>(static_cast<int>(m_CurrentState) + 1);
            }
            m_ScoreText->SetText(std::to_string(m_Score));
            m_PointSFX->Play(0);
        }

        if (m_TubesUp[i]->GetPosition().x <= -170 && m_Score < scoreThreshold - 2) {
            int r = rand() % 110 - 20;
            m_TubesUp[i]->SetPosition({m_TubesUp[(i + 2) % 3]->GetPosition().x + 180, r + 160 + m_TubeInterval / 2});
            m_TubesDown[i]->SetPosition({m_TubesUp[(i + 2) % 3]->GetPosition().x + 180, r - 160 - m_TubeInterval / 2});
        }

        if (m_TubesUp[i]->GetPosition().x <= X1 && m_TubesUp[i]->GetPosition().y <= Y1 && m_TubesUp[i]->GetPosition().y >= Y2) {
            m_TubesUp[i]->SetPosition({m_TubesUp[i]->GetPosition().x, m_TubesUp[i]->GetPosition().y - tubeupMove});
            m_TubesDown[i]->SetPosition({m_TubesDown[i]->GetPosition().x, m_TubesDown[i]->GetPosition().y - tubedownMove });
        }
    }

    m_Root.Update();
}

//關卡0
void App::Update(){
    if (Util::Input::IsKeyUp(Util::Keycode::A) || Util::Input::IfExit()) {
        m_CurrentState = State::LEVEL_1;
    }
    UpdateGame(2, 10, 0, 0, 0, 0, 0);
}
//關卡1-加速
void App::Level_1() {
    if (Util::Input::IsKeyUp(Util::Keycode::B) || Util::Input::IfExit()) {
        m_CurrentState = State::LEVEL_2;
    }
    m_Background->SetDrawable(std::make_unique<Util::Image>(RESOURCE_DIR"/Image/Background/background-night.jpg"));
    UpdateGame(4, 20, 0, 0, 0, 0, 0);
}
//關卡2-水管下移
void App::Level_2() {
    if (Util::Input::IsKeyUp(Util::Keycode::C) || Util::Input::IfExit()) {
        m_CurrentState = State::LEVEL_3;
    }
    UpdateGame(3, 30, 60, 280, 120, 0.6, 0.6);
}
//關卡3-水管上移
 void App::Level_3() {
    if (Util::Input::IsKeyUp(Util::Keycode::D) || Util::Input::IfExit()) {
        m_CurrentState = State::LEVEL_4;
    }
    UpdateGame(3, 40, 70, 350, 220, -0.6, -0.6);
}
//關卡4
void App::Level_4() {
    LOG_TRACE("Level_4");
    m_GameSpeed=3;


    if (Util::Input::IsKeyUp(Util::Keycode::T) || Util::Input::IfExit()) {
        collisionDetectionEnabled = false; // 當按下‘X’鍵時禁用碰撞檢測
        m_ON->SetVisible(true);
        m_OFF->SetVisible(false);
    }
    if (Util::Input::IsKeyUp(Util::Keycode::F) || Util::Input::IfExit()) {
        collisionDetectionEnabled = true; // 當按下‘X’鍵時禁用碰撞檢測
        m_ON->SetVisible(false);
        m_OFF->SetVisible(true);
    }
    m_Background->SetDrawable(std::make_unique<Util::Image>(RESOURCE_DIR"/Image/Background/background-day.png"));
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    for (auto &i: m_TubesUp) {
        i->SetPosition({i->GetPosition().x - m_GameSpeed, i->GetPosition().y});
    }
    for (auto &i: m_TubesDown) {
        i->SetPosition({i->GetPosition().x - m_GameSpeed, i->GetPosition().y});
    }
    if (Util::Input::IsKeyDown(Util::Keycode::SPACE)) {
        m_jumpCount = 15 / m_GameSpeed;
    }

    if (m_jumpCount != 0) {
        m_Bird->SetPosition({m_Bird->GetPosition().x, m_Bird->GetPosition().y + 2 * m_GameSpeed});
        m_jumpCount--;
    } else {
        m_Bird->SetPosition({m_Bird->GetPosition().x, m_Bird->GetPosition().y - 1});
    }
    for (int i = 0; i < 3; i++) {
        if (collisionDetectionEnabled) { // 只有在啟用碰撞檢測時才檢查碰撞
            if (m_Bird->isOverlap(m_TubesUp[i]) || m_Bird->isOverlap(m_TubesDown[i])) {
                m_GameOver->SetVisible(true);
                m_HitSFX->Play(0);
                m_CurrentState = State::LOSE;
                return;
            }
        }
        if (m_Bird->GetPosition().x == m_TubesUp[i]->GetPosition().x ||
            m_Bird->GetPosition().x == m_TubesUp[i]->GetPosition().x+1||
            m_Bird->GetPosition().x == m_TubesUp[i]->GetPosition().x+2){
            m_Score++;
            if(m_Score==51){
                m_CurrentState = State::LOSE;
            }
            m_ScoreText->SetText(std::to_string(m_Score));
            m_PointSFX->Play(0);
        }
        if(m_TubesUp[i]->GetPosition().x <= -170) {
            int r = rand() % 110 - 20;
            m_TubesUp[i]->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Image/Character/tube_up.png"));
            m_TubesDown[i]->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Image/Character/tube.png"));
            m_TubesUp[i]->SetPosition({m_TubesUp[(i + 2) % 3]->GetPosition().x + 180, r + 160 + m_TubeInterval / 2});
            m_TubesDown[i]->SetPosition({m_TubesUp[(i + 2) % 3]->GetPosition().x + 180, r - 160 - m_TubeInterval / 2});

        }
        if(m_TubesUp[i]->GetPosition().x <= 110 && m_TubesUp[i]->GetPosition().y<=310 && m_TubesUp[i]->GetPosition().y>=120) {
            m_TubesUp[i]->SetPosition({m_TubesUp[i]->GetPosition().x, m_TubesUp[i]->GetPosition().y - 0.3});
            m_TubesDown[i]->SetPosition({m_TubesDown[i]->GetPosition().x, m_TubesDown[i]->GetPosition().y + 0.3});
        }
    }
//    m_Background->SetDrawable(std::make_unique<Util::Image>(RESOURCE_DIR"/Image/Background/background-night.jpg"));
    m_Root.Update();
}

void App::Lose() {
    LOG_TRACE("Start");
    m_GameOver->SetVisible(true);
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::SPACE)) {
        Reset();
        m_CurrentState = State::UPDATE;
    }

    m_Root.Update();
}
void App::Reset() {
    m_Message->SetVisible(false);
    //Green Tube
    for (int i = 0; i < 3; i++) {
        int r = rand() % 110 - 20;
        m_TubesUp[i]->SetPosition({170 + i * 180, r + 160 + m_TubeInterval / 2});
        m_TubesDown[i]->SetPosition({170 + i * 180, r - 160 - m_TubeInterval / 2});
    }

    m_Bird->SetPosition({-90, 20});
    m_ScoreText->SetText("0");
    m_ScoreText->SetPosition({0, 200});
    m_Score=0;
    m_ScoreText->SetZIndex(99);
    m_GameOver->SetZIndex(98);
    m_GameOver->SetVisible(false);
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
