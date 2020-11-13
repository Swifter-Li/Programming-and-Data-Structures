#include "card.h"
//#include "card.cpp"
#include "deck.h"


    Deck::Deck()
    // EFFECTS: constructs a "newly opened" deck of cards.  first the
    // spades from 2-A, then the hearts, then the clubs, then the
    // diamonds.  The first card dealt should be the 2 of Spades.
    {
        this->reset();
    }
    void Deck:: reset()
    // EFFECTS: resets the deck to the state of a "newly opened" deck
    // of cards:
    {
        for (int i=0;i<13;i++)
        {
            deck[i].suit=SPADES;
        }
        for (int i=13;i<26;i++)
        {
            deck[i].suit=HEARTS;
        }
        for (int i=26;i<39;i++)
        {
            deck[i].suit=CLUBS;
        }   
        for (int i=39;i<52;i++)
        {
            deck[i].suit=DIAMONDS;
        }  
        for (int i=0;i<52;i=i+13)
        {
            deck[i].spot=TWO;
            deck[i+1].spot=THREE;
            deck[i+2].spot=FOUR;
            deck[i+3].spot=FIVE;
            deck[i+4].spot=SIX;
            deck[i+5].spot=SEVEN;
            deck[i+6].spot=EIGHT;
            deck[i+7].spot=NINE;
            deck[i+8].spot=TEN;
            deck[i+9].spot=JACK;
            deck[i+10].spot=QUEEN;
            deck[i+11].spot=KING;
            deck[i+12].spot=ACE;
        }
    }

    void Deck::shuffle(int n)
    // REQUIRES: n is between 0 and 52, inclusive.

    // MODIFIES: this

    // EFFECTS: cut the deck into two segments: the first n cards,
    // called the "left", and the rest called the "right".  Note that
    // either right or left might be empty.  Then, rearrange the deck
    // to be the first card of the right, then the first card of the
    // left, the 2nd of right, the 2nd of left, and so on.  Once one
    // side is exhausted, fill in the remainder of the deck with the
    // cards remaining in the other side.  Finally, make the first
    // card in this shuffled deck the next card to deal.  For example,
    // shuffle(26) on a newly-reset() deck results in: 2-clubs,
    // 2-spades, 3-clubs, 3-spades ... A-diamonds, A-hearts.
    //
    // Note: if shuffle is called on a deck that has already had some
    // cards dealt, those cards should first be restored to the deck
    // in the order in which they were dealt, preserving the most
    // recent post-shuffled/post-reset state.
    {
        Card left[n];
        Card right[DeckSize-n];
        for (int i=0;i<n;i++)
        {
            left[i]=deck[i];
        }
        for (int i=0;i<DeckSize-n;i++)
        {
            right[i]=deck[n+i];
        }
        int min;
        int pin=0;
        if (n<26) {
            min=n;
            pin=1;
        }
        else {
            min=DeckSize-n;
            pin=0;
        }
        if (min==0) {
            next=0;
            return;
        }
        for (int i=0;i<min;i++)
        {
            deck[2*i]=right[i];
        }
        for (int i=0;i<min;i++)
        {
            deck[2*i+1]=left[i];
        }
        for (int i=0;i<DeckSize-2*min;i++)
        {
            if (pin==1)
            {
                deck[2*min+i]=right[min+i];
            }
            else 
            {
                deck[2*min+i]=left[min+i];
            }
        }
        next=0;
        return;
    }
    Card Deck::deal()    // MODIFIES: this
    // EFFECTS: returns the next card to be dealt.  If no cards
    // remain, throws an instance of DeckEmpty.
    {
        if (next==DeckSize)
        {
            DeckEmpty error;
            throw error;
        }
        return deck[next++];
    }


    int Deck::cardsLeft()
    // EFFECTS: returns the number of cards in the deck that have not
    // been dealt since the last reset/shuffle.
    {
        return DeckSize-next;
    }


