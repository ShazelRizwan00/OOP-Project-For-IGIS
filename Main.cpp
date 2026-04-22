#include <string>
#include <vector>           //basically dynamic arrays
#include "raylib.h"
enum GameState {            //basically a way to give names to numbers, menu is 0 and so on
    MENU,
    INSTRUCTIONS,
    STORY,
    GAMEPLAY,
    ACCUSATION,
    RESULT,
    EXIT
};
struct Suspect {
    std::string name;
    std::string statement;
    bool visited;
};
struct Button {
    Rectangle bounds;
    std::string text;
};
std::vector<Suspect> suspects;
int score = 0;
std::string selectedSuspect;
std::string playerAccusation;
const std::string correctAnswer = "Owl";
GameState currentState = MENU;
std::string currentDialogue = "";
void showMenu();
void showInstructions();
void showStory();
void playGame();
void interrogateSuspect(int index);
void showAccusationScreen();
void checkResult();
void updateScore(bool correct);
void showResult();
void initGameData();
void initGameData() {
void drawButton(Button btn);
bool isButtonClicked(Button btn);
    suspects = {
        {"Cat (Velvet)", 
         "I heard a splash behind me, but I didn’t turn back. Curiosity is dangerous, you know.", 
         false},
        {"Dog (Bruno)", 
         "I was patrolling like always! I didn’t see anything… but I heard someone running near the reeds and then a splash. When I ran towards the pond, I discovered the body.", 
         false},
        {"Rabbit (Luna)", 
         "I saw shadows near the water… two shapes maybe… or one? I’m not sure… I got scared and ran to hide.", 
         false},
        {"Owl (Professor Hoot)", 
         "One voice will comfort you… another will confuse you… but only one is complete silence disguised as speech. I heard a splash and saw Bruno near the body.", 
         false},
        {"Crocodile (Mr. Victor)", 
         "Yes, I was in deeper water. I didn’t see anyone. When I surfaced, I saw the Mayor dead and Bruno standing there.", 
         false}
    };
    score = 0;
    selectedSuspect = "";
    playerAccusation = "";
}
int main() {
    InitWindow(800, 600, "Duck Detective");
    SetTargetFPS(60);
    initGameData();   // IMPORTANT: initialize your data
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (currentState) {
    case MENU:
        showMenu();
        break;
    case INSTRUCTIONS:
        showInstructions();
        break;
    case STORY:
        showStory();
        break;
    case GAMEPLAY:
        playGame();
        break;
    case ACCUSATION:
        showAccusationScreen();
        break;
    case RESULT:
        showResult();
        break;
    case EXIT:
        break;
}
// 🔽 TEMP input testing (still inside loop, AFTER drawing is fine)
        if (IsKeyPressed(KEY_ONE)) currentState = MENU;
        if (IsKeyPressed(KEY_TWO)) currentState = INSTRUCTIONS;
        if (IsKeyPressed(KEY_THREE)) currentState = STORY;
        if (IsKeyPressed(KEY_FOUR)) currentState = GAMEPLAY;
        if (IsKeyPressed(KEY_FIVE)) currentState = ACCUSATION;
        if (IsKeyPressed(KEY_SIX)) currentState = RESULT;

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
void showMenu() {
    DrawText("Duck Detective", 280, 150, 30, BLACK);
    Button startBtn = { {300, 250, 200, 50}, "Start" };
    Button exitBtn  = { {300, 320, 200, 50}, "Exit" };
    drawButton(startBtn);
    drawButton(exitBtn);
    if (isButtonClicked(startBtn)) {
        currentState = INSTRUCTIONS;
    }
    if (isButtonClicked(exitBtn)) {
        currentState = EXIT;
    }
}
void showInstructions() {
    DrawText("Instructions", 300, 80, 30, BLACK);
    DrawText("You are Detective Duck.", 200, 150, 20, DARKGRAY);
    DrawText("Investigate suspects and analyze their statements.", 200, 180, 20, DARKGRAY);
    DrawText("You may question multiple suspects.", 200, 210, 20, DARKGRAY);
    DrawText("When ready, make your final accusation.", 200, 240, 20, DARKGRAY);
    DrawText("Choose wisely to solve the mystery.", 200, 270, 20, DARKGRAY);
    Button nextBtn = { {300, 350, 200, 50}, "Continue" };
    drawButton(nextBtn);
    if (isButtonClicked(nextBtn)) {
        currentState = STORY;
    }
}
void showStory() {

    DrawText("The Silent Pond Case", 240, 60, 28, BLACK);

    DrawText("It was a quiet summer night...", 120, 120, 20, DARKGRAY);
    DrawText("The pond was unusually still. No ripples.", 120, 150, 20, DARKGRAY);
    DrawText("Something felt wrong.", 120, 180, 20, DARKGRAY);

    DrawText("Victim: Mayor Turtle", 120, 230, 20, BLACK);
    DrawText("Time: 11:47 PM", 120, 260, 20, BLACK);
    DrawText("Location: Silent Pond", 120, 290, 20, BLACK);

    DrawText("Four animals were present...", 120, 340, 20, DARKGRAY);
    DrawText("One of them is lying.", 120, 370, 20, RED);

    Button nextBtn = { {300, 450, 200, 50}, "Start Investigation" };

    drawButton(nextBtn);

    if (isButtonClicked(nextBtn)) {
        currentState = GAMEPLAY;
    }
}
void playGame() {
    DrawText("Investigation", 300, 50, 30, BLACK);
    // 🔹 Suspect Buttons
    for (int i = 0; i < suspects.size(); i++) {
        Button suspectBtn = {
            {100 + i * 120, 150, 100, 50},
            suspects[i].name
        };
        drawButton(suspectBtn);
        if (isButtonClicked(suspectBtn)) {
            interrogateSuspect(i);
        }
    }
    // 🔹 Dialogue Panel
    DrawRectangle(100, 250, 600, 100, LIGHTGRAY);
    DrawRectangleLines(100, 250, 600, 100, BLACK);
    DrawText(currentDialogue.c_str(), 110, 280, 18, BLACK);
    // 🔹 Accusation Button
    Button accuseBtn = { {300, 400, 200, 50}, "Make Accusation" };
    drawButton(accuseBtn);
    if (isButtonClicked(accuseBtn)) {
        currentState = ACCUSATION;
    }
}
void showAccusationScreen() {

    DrawText("Who is the culprit?", 260, 80, 30, BLACK);

    // 🔹 Suspect selection buttons
    for (int i = 0; i < suspects.size(); i++) {

        Button suspectBtn = {
            {100 + i * 120, 200, 100, 50},
            suspects[i].name
        };

        drawButton(suspectBtn);

        if (isButtonClicked(suspectBtn)) {
            playerAccusation = suspects[i].name;
        }
    }

    // 🔹 Show selected choice
    DrawText("Selected:", 100, 300, 20, BLACK);
    DrawText(playerAccusation.c_str(), 200, 300, 20, DARKBLUE);

    // 🔹 Submit button
    Button submitBtn = { {300, 400, 200, 50}, "Submit" };
    drawButton(submitBtn);

    if (isButtonClicked(submitBtn)) {

    if (playerAccusation == "") {
        DrawText("Please select a suspect first!", 220, 460, 20, RED);
    } else {
        checkResult();
        currentState = RESULT;
    }
}
}
void showResult() {

    bool won = (playerAccusation.find("Owl") != std::string::npos);

    if (won) {
        DrawText("Case Closed: Justice Delivered!", 180, 200, 25, DARKGREEN);
    } else {
        DrawText("Wrong choice. The culprit escaped.", 180, 200, 25, RED);
    }

    // 🔹 Score display
    DrawText(TextFormat("Score: %d", score), 320, 260, 20, BLACK);

    // 🔹 Replay button
    Button replayBtn = { {300, 350, 200, 50}, "Replay" };
    drawButton(replayBtn);

    if (isButtonClicked(replayBtn)) {
        initGameData();
        currentState = MENU;
    }
}
void drawButton(Button btn) {
    DrawRectangleRec(btn.bounds, LIGHTGRAY);
    DrawRectangleLinesEx(btn.bounds, 2, BLACK);
    int textWidth = MeasureText(btn.text.c_str(), 20);
    DrawText(
        btn.text.c_str(),
        btn.bounds.x + (btn.bounds.width - textWidth) / 2,
        btn.bounds.y + 10,
        20,
        BLACK
    );
}
bool isButtonClicked(Button btn) {
    return CheckCollisionPointRec(GetMousePosition(), btn.bounds)
           && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
void interrogateSuspect(int index) {
    currentDialogue = suspects[index].statement;
    suspects[index].visited = true;
}
void checkResult() {

    if (playerAccusation.find("Owl") != std::string::npos) {
        updateScore(true);
    } else {
        updateScore(false);
    }
}
void updateScore(bool correct) {
    if (correct) {
        score += 10;
    }
}