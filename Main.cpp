#include <string>
#include <vector>           //basically dynamic arrays
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
std::vector<Suspect> suspects;
int score = 0;
std::string selectedSuspect;
std::string playerAccusation;
const std::string correctAnswer = "Owl";
GameState currentState = MENU;
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