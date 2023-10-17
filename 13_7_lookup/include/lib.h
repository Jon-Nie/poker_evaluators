#ifndef LIB_DECLARATIONS
    #define LIB_DECLARATIONS

    typedef struct {
        unsigned int value;
        unsigned int suit;
    } Card;

    enum VALUES {
        TWO = 0,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        ACE
    };

    enum SUITS {
        CLUBS=0,
        DIAMONDS,
        HEARTS,
        SPADES
    };
#endif

/*
print_cards prints the string representation of each card in an array.
The parameters have to be the card array of type Card and the number of elements.
*/
void print_cards(Card cards[], int no_elements);