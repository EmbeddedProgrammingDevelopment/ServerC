#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>

#define EXIT_FAILURE -1

//prototype declaration
void pin_initialization();
void motor_ctrl( char );

//LED番号とwiringPiのピンを変換する配列
int MOTOR1_PIN[] = { 1, 4 };
int MOTOR2_PIN[] = { 5, 6 };

int main( int argc, char *argv[] ) {
	if( argc < 2 ) {
		printf("Usage: %s MOTOR_CMD\n", argv[0] );
		return EXIT_FAILURE;
	}

	//convert to int type
	char MOTOR_CMD = *argv[1];

	if( !( MOTOR_CMD == 'f' || MOTOR_CMD == 'b' || MOTOR_CMD == 'r' || MOTOR_CMD == 'l' || MOTOR_CMD == 's'  ) ) {
		printf("Error: Please read readme.md \n");
		return EXIT_FAILURE;
	}
	

	//wiringPi初期化
	if( wiringPiSetup() == -1 ) {
		printf("Error: setup failed.\n");
		return EXIT_FAILURE;
	}


	pin_initialization();	
	
	motor_ctrl( MOTOR_CMD );       
	
	
	return 0;
}



void pin_initialization() {	
	pinMode( MOTOR1_PIN[ 0 ], OUTPUT );
	pinMode( MOTOR1_PIN[ 1 ], OUTPUT );
	pinMode( MOTOR2_PIN[ 0 ], OUTPUT );
	pinMode( MOTOR2_PIN[ 1 ], OUTPUT );
}


void motor_ctrl( char motor_cmd ) {
	//motor control
	if( motor_cmd == 'f' ) {
		digitalWrite( MOTOR1_PIN[ 0 ], 1 );
		digitalWrite( MOTOR1_PIN[ 1 ], 0 );
		digitalWrite( MOTOR2_PIN[ 0 ], 1 );
		digitalWrite( MOTOR2_PIN[ 1 ], 0 );
	}
	else if( motor_cmd == 'b' ) {
		digitalWrite( MOTOR1_PIN[ 0 ], 0 );
		digitalWrite( MOTOR1_PIN[ 1 ], 1 );
		digitalWrite( MOTOR2_PIN[ 0 ], 0 );
		digitalWrite( MOTOR2_PIN[ 1 ], 1 );
	}
	else if( motor_cmd == 'r' ) {
		digitalWrite( MOTOR1_PIN[ 0 ], 0 );
		digitalWrite( MOTOR1_PIN[ 1 ], 1 );
		digitalWrite( MOTOR2_PIN[ 0 ], 1 );
		digitalWrite( MOTOR2_PIN[ 1 ], 0 );
	}
	else if( motor_cmd == 'l' ) {
		digitalWrite( MOTOR1_PIN[ 0 ], 1 );
		digitalWrite( MOTOR1_PIN[ 1 ], 0 );
		digitalWrite( MOTOR2_PIN[ 0 ], 0 );
		digitalWrite( MOTOR2_PIN[ 1 ], 1 );
	}
	else if( motor_cmd == 's' ) {
		digitalWrite( MOTOR1_PIN[ 0 ], 0 );
		digitalWrite( MOTOR1_PIN[ 1 ], 0 );
		digitalWrite( MOTOR2_PIN[ 0 ], 0 );
		digitalWrite( MOTOR2_PIN[ 1 ], 0 );
	}
}
