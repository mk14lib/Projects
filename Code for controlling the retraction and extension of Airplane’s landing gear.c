/*
*   Title : Implement the Code for controlling the retraction and extension of Airplane’s landing gear
*   Author: Koona MaheswaraRao
*   Date  : 04/01/2023 
*/


//preprocessor directives included
#include<stdio.h> // for printf(), scanf()
#include<stdlib.h>// for exit()
#include<time.h> //for clock_t, clock()

//all possible system states
typedef enum{
    GEAR_DOWN,
    CHECKING_BEFORE_TAKE_OFF,
    RAISING_GEAR,
    GEAR_UP,
    CHECKING_BEFORE_LANDING,
    LOWERING_GEAR
}state_type;

state_type current_state;

//pilot lever states
typedef enum{
    RISING,
    UP,
    FALLING,
    DOWN
}pilot_lever_status;

pilot_lever_status pilot_lever;

//limit switches, squat switches states
typedef enum{
    OPEN,
    CLOSE
}switch_state;

switch_state limit_switch, squat_switch;

//hydraulic mechanism status flags
typedef enum{
    DISABLED,
    ENABLED
}hydraulic_mechanism;

hydraulic_mechanism landing_control;

//state transitions
typedef struct states{
	char* present_state;
	char* light_status;
    char* direction_valve_status;
    char* hydraulics_status;
    char* spring_status;
}states;

//state transition table
                    //cuurent state, light_status, direction_valve_status, hydraulic_status, spring_status
states state_table[] = {{"GEAR DOWN", "GREEN", "DOWN", "ENABLED", "DISABLED"},
	{"CHECK BEFORE TAKE OFF", "RED", "UP", "ENABLED", "DISABLED"},
	{"RAISING GEAR", "RED", "UP", "ENABLED", "DISABLED"},
	{"GEAR UP", "OFF","UP", "DISABLED", "DISABLED"},
	{"CHECK BEFORE LANDING", "RED", "DOWN", "ENABLED", "DISABLED"},
	{"LOWERING_GEAR", "GREEN", "DOWN", "ENABLED", "ENABLED"}};

//recommended inputs are:
//0 0
//1 0
//1 1
//2 
//3
//0 3 

//time delay function
void delay(int seconds)
{
    int ms = 1000*seconds; //time in milliseconds
    clock_t time = clock(); //start time
    while(clock() > time + ms); //iterates till required time 
}

//initization states machine for the first time
void INIT_SM()
{
	current_state = GEAR_DOWN;
	printf("State Machine is initialized\nProgram is in %s State\nLight Status: %s\n\n",state_table[current_state].present_state, state_table[current_state].light_status);
}

//gear down function
void GR_DWN()
{
    printf("Enter the Pilot's Lever Position and Squat Switch Status: ");
    fflush(stdout);
    scanf("%d %d", &pilot_lever, &squat_switch);
    if(pilot_lever == RISING && squat_switch == OPEN)
    {
        current_state = CHECKING_BEFORE_TAKE_OFF;
        printf("\nCurrent State is %s\nLight Status: %s\n\n", state_table[current_state].present_state, state_table[current_state].light_status);
    }
}

//check before take off function
void CHK_BFR_TKFF()
{
    printf("Enter the Pilot's Lever Position, Squat Switch Status: ");
    fflush(stdout);
    scanf("%d %d", &pilot_lever, &squat_switch);
    if (pilot_lever == UP && squat_switch == OPEN)
    {
        printf("\nWait for 3 secs\n");
        delay(3); //creates 3 seconds delay 
        current_state = RAISING_GEAR;
        printf("\nCurrent State: %s\nLight Status: %s\nDirection Valve Status: %s\nFlight Status: Take off in progress..\n\n", state_table[current_state].present_state, state_table[current_state].light_status, state_table[current_state].direction_valve_status);
    }
    else
    {
        GR_DWN();
    }
}

//raising gear function
void RSING_GR(){
    printf("Enter the Limit Switch Status, Pilot's Lever Position: ");
    fflush(stdout);
    scanf("%d %d", &limit_switch, &pilot_lever);
    if (limit_switch == CLOSE && pilot_lever == UP)
    {
        current_state = GEAR_UP;
        printf("\nCurrent State: %s\nLight Status: %s\nHydraulic Control for Landing Gear Status: %s\nFlight Status: Airborne\n\n", state_table[current_state].present_state, state_table[current_state].light_status, state_table[current_state].hydraulics_status);
    }
    else if(limit_switch == CLOSE && pilot_lever == UP)
    {
        printf("Wait for 1 sec\n");
        current_state = CHECKING_BEFORE_LANDING;
        printf("\nCurrent State: %s\nLight Status: %s\nHydraulic Control for Landing Gear Status: %s\n\n", state_table[current_state].present_state, state_table[current_state].light_status, state_table[current_state].hydraulics_status);
    }
}

//gear up function
void GR_UP()
{

    printf("Enter the Pilot's Lever Position: ");
    fflush(stdout);
    scanf("%d", &pilot_lever);
    if (pilot_lever == FALLING)
    {
        current_state = CHECKING_BEFORE_LANDING;
        printf("\nCurrent State: %s\nLight Status: %s\nHydraulic Control for Landing Gear Status: %s\n\n", state_table[current_state].present_state, state_table[current_state].light_status, state_table[current_state].hydraulics_status);
    }
}

//check before landing function
void CHK_BFR_LANDING()
{
    printf("Enter the Pilot's Lever Position: ");
    fflush(stdout);
    scanf("%d", &pilot_lever);
    if(pilot_lever == DOWN)
    {
        current_state = LOWERING_GEAR;
        printf("\nCurrent State : %s\nLight Status: %s\nDirection Valve Status: %s\nGas Pressurized Spring System Status: %s\nFlight Status: Landing in progress..\n\n", state_table[current_state].present_state, state_table[current_state].light_status,state_table[current_state].direction_valve_status, state_table[current_state].spring_status);
    }
}

//lowering gear function
void LWRING_GR()
{
    printf("Enter the Limit_Switch Status, Pilot_Lever Status: ");
    fflush(stdout);
    scanf("%d %d", &limit_switch, &pilot_lever);
    if (limit_switch == CLOSE && pilot_lever == RISING)
    {
        current_state = CHECKING_BEFORE_TAKE_OFF;
        printf("\nCurrent State: %s\nLight Status: %s\n\n", state_table[current_state].present_state, state_table[current_state].light_status);
    }
    else if(limit_switch == OPEN && pilot_lever == DOWN)
    {
        current_state = GEAR_DOWN;
        printf("\nCurrent State: %s\nLight Status: %s\nFlight Status: Landed and Parked at Bay\n\n", state_table[current_state].present_state, state_table[current_state].light_status);
    }
    exit(0);
}

//function pointer array named as state machine
static void (*state_machine[])(void) = {GR_DWN, CHK_BFR_TKFF,  RSING_GR, GR_UP, CHK_BFR_LANDING, LWRING_GR};


//execution begins from here
int main()
{
	INIT_SM(); //calling function
    while(1) //forever loop
    {
        state_machine[current_state](); //calls respective function based on current state 
    }
	return 0; //returns 0 on successful execution
}
