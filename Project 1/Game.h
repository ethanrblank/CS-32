#ifndef Game_h
#define Game_h

#include "Arena.h"
#include <string>

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRats);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    
    // Helper functions
    std::string takePlayerTurn();
};



#endif /* Game_h */
