#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Motor,  port2,           dm_n,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           dm_s,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           dm_w,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           dm_e,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           cpm_l,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           cpm_r,         tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*

Motor mappings:

1. RESERVED
2. dm_n Drive Motor North
3. dm_s Drive Motor South
4. dm_w Drive Motor West
5. dm_e Drive Motor East
-----------------------------
6. cpm_l Catapault Motor Left
7. cpm_r Catapault Motor Right

*/
int speedLimit = 127;
int tInc = 0;
int tickRate = 30;

int mathNegative(int input) {
	if (input > 0) {
		return input - (input * 2);
	} else if (input == 0) {
		return 0;
	} else if (input < 0) {
		return input;
	}
	return 1;
}

int returnIfPositive(int input) {
	if (input > 0) {
		return input;
		} else if (input < 0) {
		return 0;
		} else if (input == 0) {
		return input;
	}
	return 1;
}

int evalSpeedLimit(int input) {
	if (input > 0 || input < speedLimit) {
		return input;
	} else if (input < 0 || input > mathNegative(speedLimit)) {
		return input;
	} else if (input == speedLimit || input == mathNegative(speedLimit)) {
		return speedLimit;
	}
	return 0;
}

int returnIfNegative(int input) {
	if (input > 0) {
		return 0;
		} else if (input < 0) {
		return input;
		} else if (input == 0) {
		return input;
	}
	return 0;
}

void moveDriveMotor() {
	motor[dm_n] = evalSpeedLimit(vexRT[Ch4]);
	motor[dm_s] = evalSpeedLimit(vexRT[Ch4]);
	motor[dm_w] = evalSpeedLimit(vexRT[Ch3]);
	motor[dm_e] = evalSpeedLimit(vexRT[Ch3]);
}

bool areButtonsActive() {
	if (vexRT[Btn8L] == 1 || vexRT[Btn8R] == 1) {
		return true;
	} else {
		return false;
	}
}
void rotateDriveMotor() {
	if (vexRT[Btn8L] == 1){
		motor[dm_n] = 127;
		motor[dm_s] = 127;
		motor[dm_w] = 127;
		motor[dm_e] = 127;
	} else if (vexRT[Btn8R] == 1) {
		motor[dm_n] = -127;
		motor[dm_s] = -127;
		motor[dm_w] = -127;
		motor[dm_e] = -127;
	}
}
void moveLeverMotor() {

}
void tick() {
	clearTimer(T1);
	while(time1[T1] <= 1000 / tickRate) {
		if (areButtonsActive() == true) {
			rotateDriveMotor();
		} else if (areButtonsActive() == false) {
			moveDriveMotor();
		} else {
		moveDriveMotor();
		}
		moveLeverMotor();
		sleep(30 - time1[T1]);
		tInc++;
	}
}

task main() {
	while(true) {
		tick();
	}
}
