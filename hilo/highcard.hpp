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
    
    // Calculates the distribution according to the given arguments
    Distribution GetDistribution(
            int decks,
            int cardsPerSuit,
            bool ignoreSuits,
            bool breakTies,
            bool useWildCards )
    {
        
        if ( breakTies ) {
            // if there are no ties allowed the game is always coin flip
            return Distribution{ 1, 1 };
        } else {
            
            // Unique cards
            int uniqueCards = cardsPerSuit;

            // Number of copies of each unique card
            int copiesOfCards = decks;
            
            // Adjust the appropriate value depending on whether suits are ranked or not
            if ( ignoreSuits ){
                copiesOfCards *= 4;
            }
            else{
                uniqueCards *= 4;
            }

            // Total cards available
            int totalCards = uniqueCards * copiesOfCards;


            // Calculate the possible ties
            int ties;
            
            // Wildcards only have an effect if suits are not ranked
            if ( useWildCards && ignoreSuits ){
            
                // Number of wildcards
                int wildCards = decks;
            
            
                // Number of cards with same face value but different suits as the wild card
                int sameValueAsWildCard = wildCards * 3;

                ties = ( uniqueCards - 1 ) * copiesOfCards * (copiesOfCards - 1) + // normal cards
                    sameValueAsWildCard * ( sameValueAsWildCard - 1 ) + // same value as wildcard
                    wildCards * ( wildCards - 1 ); // wildcards

            }
            else{
                ties = uniqueCards * copiesOfCards * (copiesOfCards - 1);
            }
            
            // Wins/losses are half of what is left after ties are calculated
            auto winOrLoseCards = (float)( totalCards * ( totalCards  - 1 ) - ties ) / 2.0;
            
            // Return the distribution
            if ( ties > 0 ){
//                std::cout << winOrLoseCards << ": " << ties << " (" << 2 * winOrLoseCards + ties << ")\n";
                return Distribution{ winOrLoseCards, winOrLoseCards, ( float )ties };
            }
            else {
                return Distribution{ 1, 1 };
            }
        }
    }

};



#endif /* highcard_h */
