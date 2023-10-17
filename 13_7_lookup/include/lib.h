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
get_5hand_rank takes a type Card array of length 5 and the two flush and nonflush lookup arrays as arguments,
checks if the hand represents a flush and returns the hand rank of the hand-representing array.
*/
int get_5hand_rank(Card cards[], int flush_lookup[], int nonflush_lookup[]);

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
init_deck takes initiates an array of type Card and size 52, fills that array
with all 52 possible Texas-Holdem Cards and returns a pointer to that array.
*/
Card* init_deck();