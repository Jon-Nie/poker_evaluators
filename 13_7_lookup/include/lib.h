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
check_flush takes an array of type Card and the number of elements in that array as arguments
and returns the integer representation of the suit (0: clubs, 1: diamonds, 2: hearts, 3: spades)
if the hand is a flush and -1 else.
*/
char check_flush(Card cards[], int no_elements);

/*
print_cards prints the string representation of each card in an array.
The parameters have to be the card array of type Card and the number of elements in that array.
*/
void print_cards(Card cards[], int no_elements);

/*
init_deck takes an array of type Card and size 52 as the argument
and fills that array with all 52 possible Texas-Holdem Cards.
*/
void init_deck(Card deck[]);