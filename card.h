#ifndef CARD_H
#define CARD_H

#include <string>

enum Color{
    RED, GREEN, YELLOW, BLUE, NONE
};
enum Index{
    ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, SKIP, REVERSE, DRAW_TWO, WILD, WILD_DRAW_FOUR
};

struct Card{
    Color color;
    Index index;
    Card(Color c, Index i): color(c), index(i){}
};
const int CARD_COUNT = 15;
const int CARD_HEIGHT = 14;
const std::string card_display_array[CARD_COUNT][CARD_HEIGHT] = {

    {
        "********************",
        "*                  *",
        "*     OOOOOOOO     *",
        "*    OOOOOOOOOO    *",
        "*   OOOO    OOOO   *",
        "*   OOOO    OOOO   *",
        "*   OOOO    OOOO   *",
        "*   OOOO    OOOO   *",
        "*   OOOO    OOOO   *",
        "*   OOOO    OOOO   *",
        "*    OOOOOOOOOO    *",
        "*     OOOOOOOO     *",
        "*                  *",
        "********************",

    },

    {
        "********************",
        "*                  *",
        "*         OO       *",
        "*       OOOO       *",
        "*     OOOOOO       *",
        "*        OOO       *",
        "*        OOO       *",
        "*        OOO       *",
        "*        OOO       *",
        "*        OOO       *",
        "*        OOO       *",
        "*     OOOOOOOOO    *",
        "*                  *",
        "********************",

    },

    {
        "********************",
        "*                  *",
        "*     OOOOOOOO     *",
        "*    OOOOOOOOOO    *",
        "*   OOOO    OOOO   *",
        "*   OOO    OOOOO   *",
        "*         OOOOO    *",
        "*        OOOOO     *",
        "*       OOOOO      *",
        "*      OOOOO       *",
        "*    OOOOOOOOOOO   *",
        "*   OOOOOOOOOOOO   *",
        "*                  *",
        "********************",

    },

    {
        "********************",
        "*                  *",
        "*     OOOOOOOO     *",
        "*    OOOOOOOOOO    *",
        "*   OOOO    OOOO   *",
        "*   OOO     OOOO   *",
        "*        OOOOOO    *",
        "*        OOOOOO    *",
        "*   OOO     OOOO   *",
        "*   OOOO    OOOO   *",
        "*    OOOOOOOOOO    *",
        "*     OOOOOOOO     *",
        "*                  *",
        "********************",

    },

    {
        "********************",
        "*                  *",
        "*   OOOO    OOOO   *",
        "*   OOOO    OOOO   *",
        "*   OOOO    OOOO   *",
        "*   OOOO    OOOO   *",
        "*   OOOOOOOOOOOO   *",
        "*   OOOOOOOOOOOO   *",
        "*           OOOO   *",
        "*           OOOO   *",
        "*           OOOO   *",
        "*           OOOO   *",
        "*                  *",
        "********************",

    },
    {
        "********************",
        "*                  *",
        "*   OOOOOOOOOOOO   *",
        "*   OOOOOOOOOOOO   *",
        "*   OOOO           *",
        "*   OOOO           *",
        "*   OOOOOOOOOO     *",
        "*    OOOOOOOOOO    *",
        "*           OOOO   *",
        "*           OOOO   *",
        "*   OOOOOOOOOOO    *",
        "*    OOOOOOOOO     *",
        "*                  *",
        "********************",

    },

    {
        "********************",
        "*                  *",
        "*     OOOOOOOO     *",
        "*    OOOOOOOOO     *",
        "*   OOOO           *",
        "*   OOOO           *",
        "*   OOOOOOOOOO     *",
        "*   OOOOOOOOOOO    *",
        "*   OOOO    OOOO   *",
        "*   OOOO    OOOO   *",
        "*    OOOOOOOOOO    *",
        "*     OOOOOOOO     *",
        "*                  *",
        "********************",

    },

    {
        "********************",
        "*                  *",
        "*   OOOOOOOOOOOO   *",
        "*   OOOOOOOOOOOO   *",
        "*         OOOOO    *",
        "*        OOOOO     *",
        "*       OOOOO      *",
        "*      OOOOO       *",
        "*     OOOOO        *",
        "*    OOOOO        *",
        "*   OOOOO          *",
        "*   OOOO           *",
        "*                  *",
        "********************",

    },
    {
        "********************",
        "*                  *",
        "*     OOOOOOOO     *",
        "*    OOOOOOOOOO    *",
        "*   OOOO    OOOO   *",
        "*   OOOO    OOOO   *",
        "*     OOOOOOOO     *",
        "*    OOOOOOOOOO    *",
        "*   OOOO    OOOO   *",
        "*   OOOO    OOOO   *",
        "*    OOOOOOOOOO    *",
        "*     OOOOOOOO     *",
        "*                  *",
        "********************",

    },
    {
        "********************",
        "*                  *",
        "*     OOOOOOOO     *",
        "*    OOOOOOOOOO    *",
        "*   OOOO    OOOO   *",
        "*   OOOO    OOOO   *",
        "*    OOOOOOOOOOO   *",
        "*     OOOOOOOOOO   *",
        "*           OOOO   *",
        "*           OOOO   *",
        "*     OOOOOOOOO    *",
        "*     OOOOOOOO     *",
        "*                  *",
        "********************",

    },
    {
        "********************",
        "*                  *",
        "*                  *",
        "*   OOO      OOO   *",
        "*    OOO    OOO    *",
        "*     OOO  OOO     *",
        "*      OOOOOO      *",
        "*       OOOO       *",
        "*      OOOOOO      *",
        "*     OOO  OOO     *",
        "*    OOO    OOO    *",
        "*   OOO      OOO   *",
        "*                  *",
        "********************",
    },
    {
        "********************",
        "*                  *",
        "*        OOOO      *",
        "*       OOOOOO     *",
        "*      OOOOOOOO    *",
        "*       OOO        *",
        "*      OOOO        *",
        "*        OOOO      *",
        "*        OOO       *",
        "*    OOOOOOOO      *",
        "*     OOOOOO       *",
        "*      OOOO        *",
        "*                  *",
        "********************",

    },
    {
        "********************",
        "* +2               *",
        "*                  *",
        "*       OOOOOOOO   *",
        "*       O      O   *",
        "*   OOOOOOOO   O   *",
        "*   O   O  O   O   *",
        "*   O   O  O   O   *",
        "*   O   OOOOOOOO   *",
        "*   O      O       *",
        "*   OOOOOOOO       *",
        "*                  *",
        "*               +2 *",
        "********************",

    },
    {
        // Wild
        "********************",
        "*                  *",
        "*    \e[41m     \e[44m     \e[0m    *",
        "*   \e[41m      \e[44m      \e[0m   *",
        "*  \e[41m       \e[44m       \e[0m  *",
        "*  \e[41m       \e[44m       \e[0m  *",
        "*  \e[41m       \e[44m       \e[0m  *",
        "*  \e[43m       \e[42m       \e[0m  *",
        "*  \e[43m       \e[42m       \e[0m  *",
        "*  \e[43m       \e[42m       \e[0m  *",
        "*   \e[43m      \e[42m      \e[0m   *",
        "*    \e[43m     \e[42m     \e[0m    *",
        "*                  *",
        "********************",
    },


    {
        // Wild Draw Four
        "********************",
        "* +4               *",
        "*      \e[44m      \e[0m      *",
        "*  \e[41m    \e[44m      \e[0m      *",
        "*  \e[41m    \e[44m    \e[42m      \e[0m  *",
        "*  \e[41m    \e[44m    \e[42m      \e[0m  *",
        "*  \e[41m    \e[43m    \e[42m      \e[0m  *",
        "*  \e[41m    \e[43m    \e[42m      \e[0m  *",
        "*      \e[43m    \e[42m      \e[0m  *",
        "*      \e[43m      \e[0m      *",
        "*      \e[43m      \e[0m      *",
        "*               +4 *",
        "********************",
    }

};



#endif
