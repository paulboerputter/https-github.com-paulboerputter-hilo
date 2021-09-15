//
//  main.cpp
//  hilo
//
// This program plkays a game of HighCard, where two cards are drawn from a deck of cards, and the highest card wins.
//
// Iyt uses a number of command line arguments and options to calculate the chanves of the possible outcomes
//
//  Created by Paul-Boer Putter on 2021/09/10.
//

#include <iostream>
#include <random>
#include <vector>
#include "cxxopts.hpp"
#include "highcard.hpp"
#include "tests.hpp"

using namespace HighCard;

#ifdef DEBUG

using namespace UnitTest;

#endif /* DEBUG */

int main(int argc, const char * argv[] ) {
    
    
    // Process the command line
    
    cxxopts::Options options("hilo", "A very silly card game");

    options.add_options()
        // Number of decks used
        ( "d,decks", "Number of decks to use", cxxopts::value<int>()->default_value( "1" ) )
        // Number of catds per suit
        ( "c,cards", "Number of cards per suit", cxxopts::value<int>()->default_value( "13" ) )
        // Number of hands to play
        ( "n,hands", "Number of hands to play", cxxopts::value<int>()->default_value( "1" ))
        // Option to ignore the ranking of suits
        ( "s,suits", "Ignore suits", cxxopts::value<bool>()->default_value("false") )
        // Option to breal ties by drawing more cards
        ( "t,ties", "Break ties", cxxopts::value<bool>()->default_value("false") )
        // Option to use wildcards
        ( "w,wild", "Wild card", cxxopts::value<bool>()->default_value("false") )
        // Print the help for the program
        ( "h,help", "Print usage" )

    
        
#ifdef DEBUG
        ( "u,test", "Unit tests" )
#endif /* DEBUG */
    ;

    auto result = options.parse(argc, argv);
    
    // Show the help if asked

    if (result.count("help"))
    {
        
      std::cout << options.help() << std::endl;
      exit(0);
    
    }
    
#ifdef DEBUG
    
    // Do the unit tests, if asked to

    if (result.count("test"))
    {
    
        UnitTests();
        exit(0);

    }

#endif /* DEBUG */
    
    // Create the random generator
    unsigned seed = static_cast< unsigned >( std::chrono::system_clock::now().time_since_epoch().count() );
    std::default_random_engine generator (seed);
    
    // Calculate the distibution using the given parameters
    auto distribution = GetDistribution(
                                        
        result["decks"].as<int>(),
        result["cards"].as<int>(),
        result["suits"].as<bool>(),
        result["ties"].as<bool>(),
        result["wild"].as<bool>()
    
                                        );
    // Bind the distribution to the generator
    auto play = std::bind ( distribution, generator );

    
    int hands = result["hands"].as<int>();
    if ( hands > 1 ){
        std::vector< int > counts( 3, 0 );
        for ( int i = 0; i < hands; ++i ){
            counts[ play() ]++;
        }
        auto prob = distribution.probabilities();
        std::cout << "Wins: " << counts[ win ] << "(" << (int)floor( hands * prob[ win ] + 0.5 ) << ")\n";
        std::cout << "Losses: " << counts[ lose ] << "(" << (int)floor( hands * prob[ lose ] + 0.5 ) << ")\n";
        if( prob.size() > 2 ){
            std::cout << "Ties: " << counts[ tie ] << "(" << (int)floor( hands * prob[ tie ] + 0.5 ) << ")\n";
        }
        std::cout << hands << " hands played\n";
    }
    else{
        // Play one hand
        switch ( play() ){
        
            case win:
                std::cout << "win\n";
                break;
            
            case lose:
                std::cout << "lose\n";
                break;
            
            default:
                std::cout << "tie\n";
                break;
        }
    }
    return 0;
}

