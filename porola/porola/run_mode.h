#ifndef RUN_MODE_H
#define RUN_MODE_H

#define MAIN_POROLA_MODE
//#define DEBUG_MOTOR_MODE
//#define DEBUG_TRAJ_MODE
//#define DEBUG_COMMUNICATION_WITH_ARDUINO_MODE

void main(void);

#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

#endif
