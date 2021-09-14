//
//  tests.hpp
//  hilo
//
//  Performs Unit tests by checking the calculated dustributions against an independent calculation
//
//  Created by Paul-Boer Putter on 2021/09/13.
//

#ifndef tests_h
#define tests_h

#ifdef DEBUG

#include "highcard.hpp"

using namespace HighCard;

namespace UnitTest{

    // Calculates the control distribution according to the given arguments
    Distribution GetDistributionControl(
            int decks,
            int cardsPerSuit,
            bool ignoreSuits,
            bool breakTies,
            bool useWildCards )
    {
        
        if ( breakTies ){
            return Distribution{ 1, 1 };
        }
        
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

        // Create the deck, an array of card counts
        std::vector< unsigned > cards( uniqueCards, copiesOfCards );
        
        // Wildcards only have an effect if suits are not ranked
        if ( useWildCards && ignoreSuits ){
            
            // Add the wildcards to the deck
            cards.back() = 3 * decks;
            cards.push_back( decks );
        
        }
        
        
        // Calculate the ties
        int ties = 0;
        for ( auto i : cards ){
            ties += i * ( i - 1 );
        }
        
        // Calculate the wins
        int wins = 0;
        for ( int i = 0; i < cards.size(); ++i ){
            for ( int j = i + 1; j < cards.size(); ++j ){
                    wins += cards[ i ] * cards[ j ];
            }
        }
        
        if ( ties > 0 ){
//            std::cout << wins << ": " << ties << " (" << 2 * wins + ties << ")\n";
            return Distribution{ ( double )wins, ( double )wins, ( double )ties };
        }
        else {
            return Distribution{ 1, 1 };
        }
        
    }


    // Helper function to print information about a vector
    template< class T >
    void printVector( std::string message, std::vector< T > v ){
        std::cout << message << ": ";
        for ( auto i: v ){
            std::cout << i <<  " ";
        }
        std::cout << "\n";
    }

    // Checks a calculated distribution agains a given set of values
    void UnitTest(
                  
            std::string message,
            int decks = 1,
            int cardsPerSuit = 13,
            bool ignoreSuits = false,
            bool breakTies = false,
            bool useWildCards = false)

    {
        
        auto test = GetDistribution( decks, cardsPerSuit, ignoreSuits, breakTies, useWildCards );
        auto control = GetDistributionControl( decks, cardsPerSuit, ignoreSuits, breakTies, useWildCards );
        
        if ( test.probabilities() == control.probabilities() ){
            printVector( message + " passed", control.probabilities() );
        }
        else{
            std::cout << "========================================\n";
            std::cout << message << ": failed\n";
            printVector( "Expected", control.probabilities() );
            printVector( "Calculated", test.probabilities() );
            std::cout << "========================================\n";
        }
    }

    void UnitTests(){
    

        UnitTest( "No ties A", 1, 13, false, true, false );
        UnitTest( "No ties B", 4, 20, true, true, true );


        UnitTest( "Eight card deck with suits",  1, 2, false, false, false );
        UnitTest( "Eight card deck without suits",  1, 2, true, false, false );
        UnitTest( "Eight card deck with suits with wildcard",  1, 2, false, false, true );
        UnitTest( "Eight card deck without suits with wildcard",  1, 2, true, false, true );

        UnitTest( "Two Eight card decks with suits", 2, 2, false, false, false );
        UnitTest( "Two Eight card deck without suits", 2, 2, true, false, false );
        UnitTest( "Four Eight card decks with suits",  4, 2, false, false, false );
        UnitTest( "Four Eight card deck without suits", 4, 2, true, false, false );

        UnitTest( "Twelve card deck with suits", 1, 3, false, false, false );
        UnitTest( "Twelve card deck without suits", 1, 3, true, false, false );
        UnitTest( "Twelve card deck with suits with wildcard", 1, 3, false, false, true );
        UnitTest( "Twelve card deck without suits with wildcard", 1, 3, true, false, true );

        UnitTest( "One standard deck with suits", 1, 13, false, false, false );
        UnitTest( "One standard deck without suits", 1, 13, true, false, false );
        UnitTest( "One standard deck with suits with wildcard", 1, 13, false, false, true );
        UnitTest( "One standard deck without suits with wildcard",  1, 13, true, false, true );
    }

};

#endif /* DEBUG */

#endif /* tests_h */
