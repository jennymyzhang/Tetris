#include "board.h"
#include "block.h"
#include "cell.h"
#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include <vector>

const int rows = 20;
const int cols = 11;

Board::Board(int level, int score, int blockCount, bool isBlind, bool isHeavy, bool isForce,
             Board* opponentBoard, Block* currBlock, Block* nextBlock, Level* currLevel) :
             level{level}, score{score}, blockCount{blockCount}, isBlind{isBlind}, isHeavy{isHeavy}, isForce{isForce},
             opponentBoard{opponentBoard}, currBlock{currBlock}, nextBlock{nextBlock}, currLevel{currLevel} {
    std::vector<std::vector<Cell*>> cells; 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cells[i][j] = new Cell{' ', i, j};
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (cells[i][j]->getX() != 0) {
                cells[i][j]->setNeighbour('t', cells[i - 1][j]);
            } else if (cells[i][j]->getX() != rows - 1) {
                cells[i][j]->setNeighbour('b', cells[i + 1][j]);
            } else if (cells[i][j]->getY() != 0) {
                cells[i][j]->setNeighbour('l', cells [i][j - 1]);
            } else if (cells[i][j]->getY() != cols - 1) {
                cells[i][j]->setNeighbour('r', cells[i][j + 1]);
            }
        }
    }
    this->cells = cells;
}


void Board::right(bool isHeavy) {
    currBlock->right(isHeavy);
}


void Board::left(bool isHeavy) {
    currBlock->left(isHeavy);
}


bool Board::down() {
    currBlock->down();
}


void Board::rotate(bool clockwise) {
    currBlock->rotate(clockwise);
}


void Board::drop() {
    
}


void Board::levelDown() {
    if(level > 0) {
        level--;
        Level *tmp = currLevel;
        if (level == 1) {
            currLevel = new Level1{cells};
        } else if (level == 2) {
            currLevel = new Level2{cells};
        } else if (level == 3) {
            currLevel = new Level3{cells};
        } else if (level == 4) {
            currLevel = new Level4{cells};
        }
        delete tmp;
    }
}

void Board::levelUp() {
    if(level < 4) {
        level++;
        Level *tmp = currLevel;
        if (level == 0) {
            currLevel = new Level1{cells};
        } else if (level == 1) {
            currLevel = new Level2{cells};
        } else if (level == 2) {
            currLevel = new Level3{cells};
        } else if (level == 3) {
            currLevel = new Level4{cells};
        }
        delete tmp;
    }
}

void Board::setBlind() {
    isBlind = true;
}

void Board::setHeavy() {
    isHeavy = true;
}


void Board::setForce(char blockType) {
    setCurrBlock(blockType);
    isForce = true;
}


int Board::getScore() {
    return score;
}


char Board::charAt(int row, int col) {
    return cells[row][col]->getChar(isBlind);
}


int Board::checkClear() {
    int clear = 0;
    bool rowClear;
    for (int i = 0; i < rows - 2; i++) {
        rowClear = true;
        for (int j = 0; j < cols; j++) {
            if (cells[i][j]->getBlock() == nullptr) {
                rowClear = false;
                break;
            }
        }
        if (rowClear) {
            clear += 1;
            for (int i2 = i; i2 > 0; i2--) {
                for (int j2 = 0; j2 < cols; j2++) {
                    if (i2 == i) {
                        Block *currBlock = cells[i2][j2]->getBlock();
                        if (currBlock->getAlive() == 1) {
                            delete currBlock;
                            cells[i2][j2]->setBlock(nullptr);
                        } else {
                            currBlock->setAlive(currBlock->getAlive() - 1);
                        }
                        cells[i2][j2]->setChar(' ');
                    }
                    if (i2 != 0) {
                        cells[i2][j2]->setBlock(cells[i2 - 1][j2]->getBlock());
                        cells[i2][j2]->setChar(cells[i2 - 1][j2]->getChar(false));
                    }
                }
            }
        }
    }
}



void Board::addstar() {

}

