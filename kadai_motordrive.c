#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>

#define EXIT_FAILURE -1

//prototype declaration
void pin_initialization();
void motor1_ctrl( int );
void motor2_ctrl( int );

//LED番号とwiringPiのピンを変換する配列
int MOTOR1_PIN[] = { 1, 4 };
int MOTOR2_PIN[] = { 5, 6 };

int main( int argc, char *argv[] ) {
	if( argc < 3 ) {
		printf("Usage: %s MOTOR_IN1 MOTOR_IN2\n", argv[0] );
		return EXIT_FAILURE;
	}

	//convert to int type
	int MOTOR1_MOVE = atoi( argv[1] );
	int MOTOR2_MOVE = atoi( argv[2] );	

	if( !( MOTOR1_MOVE >= 0 && MOTOR1_MOVE < 4 ) ) {
		printf("Error: MOTOR_IN1 must be specified to 0 or 1.\n");
		return EXIT_FAILURE;
	}

	if( !( MOTOR2_MOVE >= 0 && MOTOR2_MOVE < 4 ) ) {
		printf("Error: MOTOR_IN2 must be specified to 0 or 1.\n");
		return EXIT_FAILURE;
	}

	//wiringPi初期化
	if( wiringPiSetup() == -1 ) {
		printf("Error: setup failed.\n");
		return EXIT_FAILURE;
	}


	pin_initialization();	

	motor1_ctrl( MOTOR1_MOVE );
	
	motor2_ctrl( MOTOR2_MOVE );		
	
	
	return 0;
}



void pin_initialization() {	
	pinMode( MOTOR1_PIN[ 0 ], OUTPUT );
	pinMode( MOTOR1_PIN[ 1 ], OUTPUT );
	pinMode( MOTOR2_PIN[ 0 ], OUTPUT );
	pinMode( MOTOR2_PIN[ 1 ], OUTPUT );
}


void motor1_ctrl( int motor1 ) {
	//motor1 control
	if( motor1 == 0 ) {
		digitalWrite( MOTOR1_PIN[ 0 ], 0 );
		digitalWrite( MOTOR1_PIN[ 1 ], 0 );
	}
	else if( motor1 == 1 ) {
		digitalWrite( MOTOR1_PIN[ 0 ], 1 );
		digitalWrite( MOTOR1_PIN[ 1 ], 0 );
	}
	else if( motor1 == 2 ) {
		digitalWrite( MOTOR1_PIN[ 0 ], 0 );
		digitalWrite( MOTOR1_PIN[ 1 ], 1 );
	}
	else if( motor1 == 3 ) {
		digitalWrite( MOTOR1_PIN[ 0 ], 1 );
		digitalWrite( MOTOR1_PIN[ 1 ], 1 );
	}
}


void motor2_ctrl( int motor2 ) {
	//motor2 control
	if( motor2 == 0 ) {
		digitalWrite( MOTOR2_PIN[ 0 ], 0 );
		digitalWrite( MOTOR2_PIN[ 1 ], 0 );
	}
	else if( motor2 == 1 ) {
		digitalWrite( MOTOR2_PIN[ 0 ], 1 );
		digitalWrite( MOTOR2_PIN[ 1 ], 0 );
	}
	else if( motor2 == 2 ) {
		digitalWrite( MOTOR2_PIN[ 0 ], 0 );
		digitalWrite( MOTOR2_PIN[ 1 ], 1 );
	}
	else if( motor2 == 3 ) {
		digitalWrite( MOTOR2_PIN[ 0 ], 1 );
		digitalWrite( MOTOR2_PIN[ 1 ], 1 );
	}
}
