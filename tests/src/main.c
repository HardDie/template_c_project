#include <iostream>
#include <gtest/gtest.h>

#include <test_func.h>

TEST( test_func, add ) { ASSERT_EQ( add( 3, 7 ), 10 ) << "sum is not 10"; }
TEST( test_func, subtract ) {
	ASSERT_EQ( subtract( 17, 2 ), 15 ) << "subtract is not 15";
}
TEST( test_func, multiply ) {
	ASSERT_EQ( multiply( 3, 4 ), 12 ) << "multply is not 12";
}
TEST( test_func, divide ) {
	ASSERT_EQ( divide( 15, 3 ), 5 ) << "divide is not 5";
}

int main( int argc, char *argv[] ) {
	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}
