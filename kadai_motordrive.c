#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>

#define EXIT_FAILURE -1
#define MAX_TIME 85

//prototype declaration
void pin_initialization();
void motor_ctrl( char );
void send_properties(FILE*);

//wiringPiのピンを変換する配列
int MOTOR1_PIN[] = { 1, 4 };
int MOTOR2_PIN[] = { 5, 6 };
int DHT11_PIN = 3;

//DHT11関係
int dht11_val[5] = { 0, 0, 0, 0, 0 };

int main( int argc, char *argv[] ) {
	/*
	if( argc < 2 ) {
		printf("Usage: %s MOTOR_CMD\n", argv[0] );
		return EXIT_FAILURE;
	}
	*/
	//convert to int type	
	FILE* input = NULL;
	
	input = fopen("/dev/ttyAMA0","r+");
	if( input == NULL ) {
		printf("Input Stream is not correct.\n");
		return EXIT_FAILURE;
	}
	
	//wiringPi初期化
	if( wiringPiSetup() == -1 ) {
		printf("Error: setup failed.\n");
		return EXIT_FAILURE;
	}

	pin_initialization();	     
	
	//motor_ctrl('f');
	
	while( 1 ) {
		char MOTOR_CMD = fgetc( input );
		putchar( MOTOR_CMD );

		if( MOTOR_CMD == 'g' ) {
			send_properties(input);
		}
		else if( MOTOR_CMD != 'q' ) {
			motor_ctrl( MOTOR_CMD );	
		}		
		else {
			break;
		}
	}
	
	fclose( input );
	
	return 0;
}


void send_properties( FILE* fp ) {

	unsigned char lststate = HIGH;
	unsigned char counter = 0;
	unsigned char i, j = 0;

	for( i = 0; i < 5; i++ )
		dht11_val[i] = 0;

	pinMode( DHT11_PIN, OUTPUT );
	digitalWrite( DHT11_PIN, LOW );
	delay( 18 );
	digitalWrite( DHT11_PIN, HIGH );
	delayMicroseconds( 40 );
	pinMode( DHT11_PIN, INPUT );
	
	for( i = 0; i < MAX_TIME; i++ )
	{
		counter = 0;
		while( digitalRead( DHT11_PIN ) == lststate ) {
			counter++;
			delayMicroseconds( 1 );
			if( counter == 255 )
 				break;
		}
		lststate = digitalRead( DHT11_PIN );
		if( counter == 255 )
			break;
		// top 3 transistions are ignored
		if( ( i >= 4 ) && ( i % 2 == 0 ) ) {
			dht11_val[ j / 8 ] <<= 1;
			if( counter > 16 )
				dht11_val[ j / 8 ] |= 1;
			j++;
		}
	}
	// verify cheksum and print the verified data
	if( ( j >= 40 ) && ( dht11_val[4] == ( ( dht11_val[0] + dht11_val[1] + dht11_val[2] + dht11_val[3] ) & 0xFF ) ) ) {
		float humidity = ( float )( dht11_val[0] ) + ( float )( dht11_val[1] ) * 0.01;
		float temperature = ( float )( dht11_val[2] ) + ( float )( dht11_val[3] ) * 0.01;
		fprintf( fp, "%f,%f|", temperature, humidity ); //気温, 湿度の順で書き込むこと
	}
	else{
		fprintf( fp, "NODATA,NODATA|");
	}

  	
	fflush( fp );
}


void pin_initialization() {	
	pinMode( MOTOR1_PIN[ 0 ], OUTPUT );
	pinMode( MOTOR1_PIN[ 1 ], OUTPUT );
	pinMode( MOTOR2_PIN[ 0 ], OUTPUT );
	pinMode( MOTOR2_PIN[ 1 ], OUTPUT );	
}


void motor_ctrl( char motor_cmd ) {
	
	if( !( motor_cmd == 'f' || motor_cmd == 'b' || motor_cmd == 'r' || motor_cmd == 'l' || motor_cmd == 's'  ) ) {
		printf("Error: Please read readme.md \n");
		return;
	}
	//motor control
	if( motor_cmd == 'f' ) {
		//puts("front roll.");
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
