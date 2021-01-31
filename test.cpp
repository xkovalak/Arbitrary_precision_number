/* You can put any private test cases into this file. It will *not* be part of
 * the submission. */

#include "number.hpp"
#include <cassert>
#include <iostream>
#include <chrono>

int main()
{
    /*number a( 10 ), b( 25 ), h(100);
    number c = a + b;
    number d = c / a;
    number e = d * a;

    assert( e == a + b );
    assert( e != a );
    assert( c > a );
    assert( a < b );
    assert( c.power( 2 ) > c );
    c = number( 10 ).power( -5 );
    assert( c > c.power( 2 ) );

    number s = number( 145 ).sqrt( 3 );
    number lower = number( 120415 ) * number( 10 ).power( -4 );
    number upper = number( 120425 ) * number( 10 ).power( -4 );
    assert( s > lower );
    assert( s < upper );

    auto start = std::chrono::high_resolution_clock::now();
    number(1337).sqrt(53);
    auto finish = std::chrono::high_resolution_clock::now();

    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);

    std::cout << (double)microseconds.count()/1000000 << "s" << std::endl;
 *//*
    auto start = std::chrono::high_resolution_clock::now();
    number m( 0 );
    number s = number( 10 ).power( -5 ); // scale = -5
    m = m + number( 331662 ) * s;           // chunk = 331662
    s = number( 10 ).power( -11 ); // scale = -11
    m = m + number( 479035 ) * s;            // chunk = 479035
    s = number( 10 ).power( -17 ); // scale = -17
    m = m + number( 539984 ) * s;           // chunk = 539984
    s = number( 10 ).power( -23 ); // scale = -23
    m = m + number( 911493 ) * s;           // chunk = 911493
    s = number( 10 ).power( -29 ); // scale = -29
    m = m + number( 273667 ) * s;            // chunk = 273667
    s = number( 10 ).power( -35 ); // scale = -35
    m = m + number( 68668 ) * s;            // chunk = 68668
    s = number( 10 ).power( -41 ); // scale = -41
    m = m + number( 392708 ) * s;            // chunk = 392708
    s = number( 10 ).power( -47 ); // scale = -47
    m = m + number( 854558 ) * s;            // chunk = 854558
    s = number( 10 ).power( -53 ); // scale = -53
    m = m + number( 935359 ) * s;            // chunk = 935359
    s = number( 10 ).power( -59 ); // scale = -59
    m = m + number( 705868 ) * s;            // chunk = 705868
    s = number( 10 ).power( -65 ); // scale = -65
    m = m + number( 214611 ) * s;            // chunk = 214611
    s = number( 10 ).power( -71 ); // scale = -71
    m = m + number( 648464 ) * s;            // chunk = 648464
    s = number( 10 ).power( -77 ); // scale = -77
    m = m + number( 260904 ) * s;            // chunk = 260904
    s = number( 10 ).power( -83 ); // scale = -83
    m = m + number( 384670 ) * s;            // chunk = 384670
    s = number( 10 ).power( -89 ); // scale = -89
    m = m + number( 884339 ) * s;            // chunk = 884339
    s = number( 10 ).power( -95 ); // scale = -95
    m = m + number( 912829 ) * s;            // chunk = 912829
    s = number( 10 ).power( -101 ); // scale = -101
    m = m + number( 65090 ) * s;            // chunk = 65090
    s = number( 10 ).power( -107 ); // scale = -107
    m = m + number( 424242 ) * s;            // chunk = 424242 ;
    number n = number(11).sqrt(71);
    number error = m - n > 0 ? m - n : n - m;
    assert(error < number(10).power(-70));
    auto finish = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);

    std::cout << (double)microseconds.count()/1000000 << "s" << std::endl;
*/
    auto start = std::chrono::high_resolution_clock::now();
    number(1000).power(1000);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "pow 1000^1000 " << duration.count() << " milisec \n";

    start = std::chrono::high_resolution_clock::now();
    (number(1000) / number(31)).power(1000);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "pow (1000/31)^1000 " << duration.count() << " milisec \n";

    start = std::chrono::high_resolution_clock::now();
    number testedNum = number(10).power(18) * number(4453);;
    testedNum.sqrt(3);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "time of sqrt should be less than 20 sec " << duration.count() << " milisec \n";

    start = std::chrono::high_resolution_clock::now();
    testedNum = number(3);
    testedNum.sqrt(300);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "3.sqrt(300) " << duration.count() << " milisec \n";

    start = std::chrono::high_resolution_clock::now();
    testedNum = number(3) / number(66);
    testedNum.sqrt(300);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "3/66.sqrt(299) very small num sqrt" << duration.count() << " milisec \n";
}
