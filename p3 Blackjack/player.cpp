#include "hand.h"
#include "player.h"

class simpleplayer: public Player
{
public:
    //simpleplayer();
    int bet(unsigned int bankroll, unsigned int minimum); 
    // REQUIRES: bankroll >= minimum
    // EFFECTS: returns the player's bet, between minimum and bankroll 
    // inclusive
   
    bool draw(Card dealer, const Hand &player);// Player's current hand
    // EFFECTS: returns true if the player wishes to be dealt another
    // card, false otherwise.

     void expose(Card c);
    // EFFECTS: allows the player to "see" the newly-exposed card c.
    // For example, each card that is dealt "face up" is expose()d.
    // Likewise, if the dealer must show his "hole card", it is also
    // expose()d.  Note: not all cards dealt are expose()d---if the
    // player goes over 21 or is dealt a natural 21, the dealer need
    // not expose his hole card.

     void shuffled();
    // EFFECTS: tells the player that the deck has been re-shuffled.
      ~simpleplayer();
    //Effect: leave the player alone
};
     int simpleplayer::bet( unsigned int bankroll, unsigned int minimum) 
    // REQUIRES: bankroll >= minimum
    // EFFECTS: returns the player's bet, between minimum and bankroll 
    // inclusive
    {
        return (int) minimum;
    }
    // EFFECTS: returns true if the player wishes to be dealt another
    // card, false otherwise.
    bool simpleplayer::draw(Card dealer, const Hand &player)// Player's current hand
    // EFFECTS: returns true if the player wishes to be dealt another
    // card, false otherwise.
    { 
        HandValue current=player.handValue();
        if (current.soft==0)//situation for soft hand
        {
            if ( current.count<=11) return 1;
            else if (current.count==12)
            {
                int p=dealer.spot;
                //transformation
                if (0<=p&&p<9)
                {
                    p=p+2;
                }
                else if (8<p&&p<12)
                {
                    p=10;
                }
                //statement 2 for simple player
                if (3<p&&p<7)
                {
                    return 0;
                }
                else return 1;
            }
            else if (12<current.count&&current.count<17)
            {
                int p=dealer.spot;
                //transformation
                if (0<=p&&p<9)
                {
                    p=p+2;
                }
                else if (8<p&&p<12)
                {
                    p=10;
                }
                //statement 3 for simple player
                if (1<p&&p<7)
                {
                    return 0;
                }
                else return 1;
            }
            else  return 0;
        }
        else if (current.soft==1)
        {
            int p=dealer.spot;
            //transformation
            if (0<=p&&p<9)
            {
                p=p+2;
            }
            else if (8<p&&p<12)
            {
                p=10;
            }
            if(current.count<=17) return 1;
            else if (current.count==18)
            {
                if (p==2||p==7||p==8) return 0;
                else return 1;
            }
            else return 0;
        }
        return 0;
    }
     void simpleplayer:: expose(Card c){}
    // EFFECTS: allows the player to "see" the newly-exposed card c.
    // For example, each card that is dealt "face up" is expose()d.
    // Likewise, if the dealer must show his "hole card", it is also
    // expose()d.  Note: not all cards dealt are expose()d---if the
    // player goes over 21 or is dealt a natural 21, the dealer need
    // not expose his hole card.

     void simpleplayer:: shuffled() {}
    // EFFECTS: tells the player that the deck has been re-shuffled.
      simpleplayer::~simpleplayer() {}
    //Effect: leave the player alone
    
class countingplayer: public Player
{
    int count;
public:
    int bet(unsigned int bankroll,unsigned int minimum); 
    // REQUIRES: bankroll >= minimum
    // EFFECTS: returns the player's bet, between minimum and bankroll 
    // inclusive

    // EFFECTS: returns true if the player wishes to be dealt another
    // card, false otherwise.
    bool draw(Card dealer, const Hand &player);// Player's current hand
    // EFFECTS: returns true if the player wishes to be dealt another
    // card, false otherwise.
     

    void expose(Card c);
    // EFFECTS: allows the player to "see" the newly-exposed card c.

    void shuffled();
    //Effects:tell shuffled

    ~countingplayer() ;
    //Effect: leave the player alone
};
 int countingplayer::bet(unsigned int bankroll,unsigned int minimum) 
    // REQUIRES: bankroll >= minimum
    // EFFECTS: returns the player's bet, between minimum and bankroll 
    // inclusive
    {
        if (count>=2)
        {
            if (bankroll>=2*minimum)
            {
                return int (2*minimum);
            }
            else return (int) minimum;
        }
        else return (int) minimum;
    }
    bool countingplayer::draw(Card dealer, const Hand &player)// Player's current hand
    // EFFECTS: returns true if the player wishes to be dealt another
    // card, false otherwise.
    { 
        HandValue current=player.handValue();
        if (current.soft==0)//situation for soft hand
        {
            if ( current.count<=11) return 1;
            else if (current.count==12)
            {
                int p=dealer.spot;
                //transformation
                if (0<=p&&p<9)
                {
                    p=p+2;
                }
                else if (8<p&&p<12)
                {
                    p=10;
                }
                //statement 2 for simple player
                if (3<p&&p<7)
                {
                    return 0;
                }
                else return 1;
            }
            else if (12<current.count&&current.count<17)
            {
                int p=dealer.spot;
                //transformation
                if (0<=p&&p<9)
                {
                    p=p+2;
                }
                else if (8<p&&p<12)
                {
                    p=10;
                }
                //statement 3 for simple player
                if (1<p&&p<7)
                {
                    return 0;
                }
                else return 1;
            }
            else  return 0;
        }
        else 
        {
            int p=dealer.spot;
            //transformation
            if (0<=p&&p<9)
            {
                p=p+2;
            }
            else if (8<p&&p<12)
            {
                p=10;
            }
            if(current.count<=17) return 1;
            else if (current.count==18)
            {
                if (p==2||p==7||p==8) return 0;
                else return 1;
            }
            else return 0;
        }
    }
    void countingplayer:: expose(Card c)
    // EFFECTS: allows the player to "see" the newly-exposed card c.
    {
        int p=c.spot;
        if (0<=p&&p<5)
        {
            count++;
        }
        if (8<=p)
        {
            count--;
        }
    }
    void countingplayer::shuffled()
    {
        count=0;
    }
    countingplayer::~countingplayer() {}
    //Effect: leave the player alone

Player *get_Simple()
// EFFECTS: returns a pointer to a "simple player", as defined by the
// project specification
{
    simpleplayer* sim=new simpleplayer;
    return sim;
}
// EFFECTS: returns a pointer to a "counting player", as defined by
// the project specification
Player *get_Counting()
// EFFECTS: returns a pointer to a "counting player", as defined by
// the project specification.
{
    countingplayer* cou=new countingplayer;
    return cou;
}