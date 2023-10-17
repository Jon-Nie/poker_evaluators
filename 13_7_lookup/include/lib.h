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