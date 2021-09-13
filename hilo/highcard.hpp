//
//  highcard.hpp
//  hilo
//
//  Defines types needed for playing hilo
//
//  Created by Paul-Boer Putter on 2021/09/13.
//

#ifndef highcard_h
#define highcard_h

namespace HighCard{

    // The possible outcopmes of a game
    typedef enum { win, lose, tie } Outcome;
    
    // The random distribution that is used to generate outcomes
    typedef std::discrete_distribution< Outcome > Distribution;
    
    // Claculates the distribution according to the given arguments
    Distribution GetDistribution(
            int decks,
            int cardsPerSuit,
            bool ignoreSuits,
            bool breakTies,
            bool useWildCards )
    {
        
#ifdef DEBUG
        std::cout << decks << " decks " << cardsPerSuit << " cards " << (ignoreSuits ? "no suits " : "") << ( breakTies ? "break ties " : "" ) << ( useWildCards ? "wild cards\n" : "\n" );

#endif
        
        if ( breakTies ) {
            // if there are no ties allowed the game is always coin flip
            return Distribution{ 1, 1 };
        } else {
            // Unique cards depend on wheter suits are ranked or not
            int uniqueCards = ignoreSuits? cardsPerSuit : cardsPerSuit * 4;
            
            // Number of copies of each unique card
            int copiesOfCards = ignoreSuits? decks * 4 : decks;
            
            // Number of wildcards
            int wildCards = useWildCards ? decks : 0;
            
            // Total cards available
            int totalCards = uniqueCards * copiesOfCards;
            
            // Number of catds with same face value but different suits as the wild card
            int sameValueAsWildCard = ignoreSuits && useWildCards ? decks * 3 : 0;
            
            // Number of ties possible
            int ties = ( uniqueCards - 1 ) * (copiesOfCards - 1) + // normal cards
                    sameValueAsWildCard * ( sameValueAsWildCard - 1 ) + // same value as wildcard
                    wildCards * ( wildCards - 1 ); // wildcards
            
            // Wins/losses are half of what is left after ties are calculated
            auto winOrLoseCards = (float)( totalCards * ( totalCards  - 1 ) - ties ) / 2.0;
            
            // Return the distribution
            if ( ties > 0 ){
                return Distribution{ winOrLoseCards, winOrLoseCards, ( float )ties };
            }
            else {
                return Distribution{ 1, 1 };
            }
        }
    }

};



#endif /* highcard_h */
