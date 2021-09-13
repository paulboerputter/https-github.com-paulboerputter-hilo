//
//  tests.hpp
//  hilo
//
//  Performs Unit tests by checking the calculated dustributions against a few known values calculated mostrly by hand
//
//  Created by Paul-Boer Putter on 2021/09/13.
//

#ifndef tests_h
#define tests_h

#ifdef DEBUG

#include "highcard.hpp"

using namespace HighCard;

namespace UnitTest{

    
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
            float wins,
            float loses,
            float ties,
            int decks = 1,
            int cardsPerSuit = 13,
            bool ignoreSuits = false,
            bool breakTies = false,
            bool useWildCards = false)

    {
        
        auto test = GetDistribution( decks, cardsPerSuit, ignoreSuits, breakTies, useWildCards );
        auto given = ties > 0 ? Distribution{ wins, loses, ties } : Distribution{ wins, loses };
        
        if ( test.probabilities() == given.probabilities() ){
            std::cout << message << ": passed\n";
        }
        else{
            std::cout << "========================================\n";
            std::cout << message << ": failed\n";
            printVector( "Expected", given.probabilities() );
            printVector( "Calculated", test.probabilities() );
            std::cout << "========================================\n";
        }
    }

    void UnitTests(){
    

        UnitTest( "No ties A", 1, 1, 0, 1, 13, false, true, false );
        UnitTest( "No ties B", 1, 1, 0, 4, 20, true, true, true );


        UnitTest( "Eight card deck with suits", 1, 1, 0,  1, 2, false, false, false );
        UnitTest( "Eight card deck without suits", 53, 53, 6,  1, 2, true, false, false );
        UnitTest( "Eight card deck with suits with wildcard", 1, 1, 0,  1, 2, false, false, true );
        UnitTest( "Eight card deck without suits with wildcard", 47, 47, 18,  1, 2, true, false, true );

        UnitTest( "Two Eight card decks with suits", 233, 233, 14,  2, 2, false, false, false );
        UnitTest( "Two Eight card deck without suits", 233, 233, 14,  2, 2, true, false, false );
        UnitTest( "Four Eight card decks with suits", 971, 971, 42,  4, 2, false, false, false );
        UnitTest( "Four Eight card deck without suits", 977, 977, 30,  4, 2, true, false, false );

        UnitTest( "Twelve card deck with suits", 1, 1, 0,  1, 3, false, false, false );
        UnitTest( "Twelve card deck without suits", 63, 63, 6,  1, 3, true, false, false );
        UnitTest( "Twelve card deck with suits with wildcard", 1, 1, 0,  1, 3, false, false, true );
        UnitTest( "Twelve card deck without suits with wildcard", 60, 60, 12,  1, 3, true, false, true );

        UnitTest( "One standard deck with suits", 1, 1, 0,  1, 13, false, false, false );
        UnitTest( "One standard deck without suits", 1308, 1308, 36,  1, 13, true, false, false );
        UnitTest( "One standard deck with suits with wildcard", 1, 1, 0,  1, 13, false, false, true );
        UnitTest( "One standard deck without suits with wildcard", 1305, 1305, 42, 1, 13, true, false, true );
    }

};

#endif /* DEBUG */

#endif /* tests_h */
