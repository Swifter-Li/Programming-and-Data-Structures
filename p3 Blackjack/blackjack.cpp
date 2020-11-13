#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "deck.h"
//#include "deck.cpp"
#include "rand.h"
//#include "rand.cpp"
#include "hand.h"
//#include "hand.cpp"
#include "player.h"
//#include "player.cpp"
#include "card.h"
//#include "card.cpp"
using namespace std;
const int bankmin=5;
//Requires: Deck of 52 cards
//Effect: Shuffle the deck for 7 times
void shuffle(Deck &deck);

//Requires: Deck of 52 cards
//Effect: Deal cards, return the face up card of the dealer
Card dealfourcards(Hand& play,Hand& deal,Player* player, Deck& deck);

 
//Effect: the wanted type player 
Player* getPlayer(const string& name);


//Effect: print the result 
void printresult(const int& thishand,const int& bankroll );


//Effect: print the result when hand is 0
void printresult2 (const int& bankroll);

//Requires: line is "simple" or "counting"
//Effect: the blackjack driver
void sim_player (const int& bankrol,const int& hand,const string&line);


//Effect: the main function
int main(int argc, char* argv[]) 
{
    
    //string bank=argv[1];
    int bankroll=atoi(argv[1]);
    //string han=argv[2];
    int hand=atoi(argv[2]);
    string line=argv[3];
    sim_player(bankroll,hand,line);
    
    
}
//Requires: Deck of 52 cards
//Effect: Shuffle the deck for 7 times
void shuffle(Deck &deck)
{
        cout<<"Shuffling the deck\n";
        for (int i=0;i<7;i++)
        {
            int cut=get_cut();
            deck.shuffle(cut);
            cout<<"cut at "<<cut<<endl;
        }
}
//Requires: Deck of 52 cards
//Effect: Deal cards, return the face up card of the dealer
Card dealfourcards(Hand& play,Hand& deal,Player* player, Deck& deck)
{
    Card c;
    c=deck.deal();
    play.addCard(c);
    cout<<"Player dealt "<<SpotNames[c.spot]<<" of "<<SuitNames[c.suit]<<endl;
    player->expose(c);
    c=deck.deal();
    Card d=c;
    deal.addCard(c);
    cout<<"Dealer dealt "<<SpotNames[c.spot]<<" of "<<SuitNames[c.suit]<<endl;
    player->expose(c);
    c=deck.deal();
    play.addCard(c);
    cout<<"Player dealt "<<SpotNames[c.spot]<<" of "<<SuitNames[c.suit]<<endl;
    player->expose(c);
    //c=deck.deal();
    //deal.addCard(c);
    return d;
}
 
//Effect: the wanted type player 
Player* getPlayer(const string& name)
{
    if (name == "simple") {
        return get_Simple();
    } else if (name == "counting") {
        return get_Counting();
    }
    // just for safety.
    return nullptr;
}

//Effect: print the result 
void printresult(const int& thishand,const int& bankroll )
{
        cout<<"Player has "<<bankroll
    <<" after "<<thishand-1<<" hands\n";
}

//Effect: print the result when hand is 0
void printresult2 (const int& bankroll)
{
    cout<<"Player has "<<bankroll
    <<" after "<<0<<" hands\n";
}
//Requires: line is "simple" or "counting"
//Effect: the blackjack driver
void sim_player (const int& bankrol,const int& hand,const string&line)
{
    Player* player;
    if (line=="simple") player=get_Simple();
    else  player=get_Counting();
    int bankroll=bankrol;
    Deck deck;     
    shuffle(deck);
    player->shuffled();
    if (bankroll<bankmin)
    {
        cout<<"Player has "<<bankroll
        <<" after "<<0<<" hands\n";
        return;
    }
    int thishand=1;
    while (bankroll>=5&&thishand<=hand)
    {
        Hand play;
        Hand deal;
        cout<<"Hand "<<thishand<<" bankroll "<<bankroll<<endl;
        if (deck.cardsLeft()<20) 
        {
            shuffle(deck);
            player->shuffled();
        }
        int wager=player->bet(bankroll,bankmin);
        cout<<"Player bets "<<wager<<endl;
       // bankroll=bankroll-player->bet(bankroll,bankmin);

        Card dealercard=dealfourcards(play,deal,player,deck);
        Card holecard=deck.deal();
        deal.addCard(holecard);

        if (play.handValue().count==21)
        {
            int wager2=wager*3/2;
            bankroll= bankroll+wager2;
            cout<<"Player dealt natural 21\n";
            thishand++;
        }
        else 
        {
            while (player->draw(dealercard,play)&&play.handValue().count<=21)
            {
                Card c=deck.deal();
                play.addCard(c);
                cout<<"Player dealt "<<SpotNames[c.spot]<<" of "<<SuitNames[c.suit]<<endl;
                player->expose(c);
            }
            int player_count=play.handValue().count;
            cout<<"Player's total is "<<player_count<<endl;
            if (play.handValue().count>21)
            {
                cout<<"Player busts\n";
                bankroll=bankroll-wager;
                thishand++;
            }
            else 
            {
                //Card c=deck.deal();
                //deal.addCard(c);
                player->expose(holecard);
                cout<<"Dealer's hole card is "<<SpotNames[holecard.spot]<<" of "<<SuitNames[holecard.suit]<<endl;
                while (deal.handValue().count<17)
                {
                    Card c=deck.deal();
                    deal.addCard(c);
                    player->expose(c);
                    cout<<"Dealer dealt "<<SpotNames[c.spot]<<" of "<<SuitNames[c.suit]<<endl;
                }
                int dealer_count=deal.handValue().count;
                cout<<"Dealer's total is "<<dealer_count<<endl;
                if (deal.handValue().count>21)
                {
                    cout <<"Dealer busts\n";
                    bankroll=bankroll+wager;
                    thishand++;
                }
                else 
                {
                    if (dealer_count>player_count) 
                    {
                        bankroll=bankroll-wager;
                        cout<<"Dealer wins\n";
                        thishand++;
                    }
                    else if (dealer_count<player_count) 
                    {
                        bankroll=bankroll+wager;
                        cout<<"Player wins\n";
                        thishand++;
                    }
                    else 
                    {
                        cout<<"Push\n";
                        thishand++;
                    }
                }
            }
        }
        
    }
    cout<<"Player has "<<bankroll
    <<" after "<<thishand-1<<" hands\n";
    return;
}
