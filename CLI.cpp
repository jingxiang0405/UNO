#include <iostream>
#include <unordered_map>
#include "CLI.h"

std::unordered_map<Color, std::string> color_map = {
    {RED, "\e[41;30m"},
    {GREEN, "\e[42;30m"},
    {YELLOW, "\e[43;30m"},
    {BLUE, "\e[44;30m"},
    {NONE, "\e[0m"}
};


void print_hand_cards(std::vector<Card> cards){

    for(int h = 0; h < CARD_HEIGHT; ++h){
        for(int i = 0; i < cards.size(); ++i){
            std::cout << color_map[cards[i].color] << card_display_array[cards[i].index][h] << "\e[0m ";
        }
        std::cout << std::endl;
    }

}
void print_round(){

}

void print_end(){

}

//test
int main(){
    Card c1(RED, ONE);
    
    Card c2(NONE, WILD);
    Card c3(GREEN, FOUR);
    Card c4(YELLOW , ONE);
    Card c5(BLUE, TWO);
    std::vector<Card> v = {c1, c2, c3, c4, c5};
    print_hand_cards(v);
}


