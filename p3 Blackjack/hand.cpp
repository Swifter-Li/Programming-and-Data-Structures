#include "card.h"
//#include "card.cpp"
#include "hand.h"
#include "deck.h"

Hand::Hand()
  // EFFECTS: establishes an empty blackjack hand.
{
    curValue.count=0;
    curValue.soft=0;
}

void Hand:: discardAll()
// MODIFIES: this
// EFFECTS: discards any cards presently held, restoring the state
// of the hand to that of an empty blackjack hand.
{
    curValue.count=0;
    curValue.soft=0;
}


void Hand::addCard(Card c)
// MODIFIES: this
// EFFECTS: adds the card "c" to those presently held.
{
     int p=c.spot;
     if (0<=p&&p<9)
     {
         p=p+2;
     }
     else if (8<p&&p<12)
     {
         p=10;
     }
     if (0<p&&p<11)
     {
        if (curValue.count+p<=21) curValue.count=curValue.count+p;
        else if (curValue.count+p>21)
        {
            if (curValue.soft==1)
            {
                curValue.count=curValue.count-10+p;
                curValue.soft=0;
            }
            else if (curValue.soft==0)
            {
                curValue.count=curValue.count+p;
            }
        }
     }
     else if (p==12)
     {
         if (curValue.count+11>21)
         {
             curValue.count=curValue.count+1;
         }
         else if (curValue.count+11<=21)
         {
             curValue.count=curValue.count+11;
             curValue.soft=1;
         }
     }
}


HandValue Hand::handValue() const
// EFFECTS: returns the present value of the blackjack hand.  The
// count field is the highest blackjack total possible without
// going over 21.  The soft field should be true if and only if at
// least one ACE is present, and its value is counted as 11 rather
// than 1.  If the hand is over 21, any value over 21 may be returned.
//
// Note: the const qualifier at the end of handValue means that
// you are not allowed to change any member variables inside
// handValue. Adding this prevents the accidental change by you.
{
    return curValue;
}
