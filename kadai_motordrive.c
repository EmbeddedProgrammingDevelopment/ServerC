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
	/*
	if( argc < 2 ) {
		printf("Usage: %s MOTOR_CMD\n", argv[0] );
		return EXIT_FAILURE;
	}
	*/
	//convert to int type
	char MOTOR_CMD;
	FILE* input=NULL;
	
	input = fopen("/dev/ttyAMA0","r");
    if(input==NULL)
        printf("Input Stream is not correct.\n");
	
	//wiringPi初期化
	if( wiringPiSetup() == -1 ) {
		printf("Error: setup failed.\n");
		return EXIT_FAILURE;
	}

	pin_initialization();	     
	
    while(1){
		MOTOR_CMD = fgetc(fp);
		if(MOTOR_CMD!='q')
		{
			motor_ctrl( MOTOR_CMD );	
		}
		else
		{
			break;
		}
    }
    fclose(fp);
	
	return 0;
}



void pin_initialization() {	
	pinMode( MOTOR1_PIN[ 0 ], OUTPUT );
	pinMode( MOTOR1_PIN[ 1 ], OUTPUT );
	pinMode( MOTOR2_PIN[ 0 ], OUTPUT );
	pinMode( MOTOR2_PIN[ 1 ], OUTPUT );
}


void motor_ctrl( char motor_cmd ) {
	
	if( !( MOTOR_CMD == 'f' || MOTOR_CMD == 'b' || MOTOR_CMD == 'r' || MOTOR_CMD == 'l' || MOTOR_CMD == 's'  ) ) {
		printf("Error: Please read readme.md \n");
		return;
	}
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
