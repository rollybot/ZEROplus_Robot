////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
// QTR_LOGIC
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void Line_Follow_Move(int Mspeed, float Mkp, float Mkd) {
  Setup_Calibration();   // only one time
  
  unsigned int position = qtra.readLine(sensorValues);
  int error = position - 1000;
  int motorSpeed = Mkp * error + Mkd * (error - lastError); ///////// PID control
  lastError = error;  
  
  int m1Speed = Mspeed + motorSpeed;   
  int m2Speed = Mspeed - motorSpeed; 
  if (m1Speed < 0)   m1Speed = 0;   
  if (m2Speed < 0)   m2Speed = 0;   
   
  motors.forward_diff(m2Speed,m1Speed); //////////////////  following the line
  
  Do_IF_LINE_end_of_line();
  Do_IF_LINE_square_cross();   // for charging
}

void Setup_Calibration() {
  if (!STATUS_Calibration_setup) {     // first of all, calibrate the sensor 
    motors.brake(100); 
    QTR_Calibrate_rotate();
  }
}

void QTR_Calibrate_rotate() {    // for line tracing
  for (int i = 0; i < 70; i++) { // make the calibration take about 10 seconds (before 220)
      qtra.calibrate();          // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
      motors.turnRight(100,3);
  }  
  for (int i = 0; i < 140; i++) { // make the calibration take about 10 seconds (before 220)
      qtra.calibrate();          // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
      motors.turnLeft(100,3);
  }  
  Do_LINE_rotate_align();
  STATUS_Calibration_setup = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Do IF LINE following
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Do_IF_LINE_end_of_line() {       // when linetracing mode , end of line case
  //qtra.readCalibrated(sensorValues);
  if (sensorValues[0] > QTR_CAL_thre && sensorValues[1] > QTR_CAL_thre && sensorValues[2] > QTR_CAL_thre ) {   // end of line
    motors.forward(RUNspeed,QTR_GAP_time);  motors.brake(100);   // move straight a little for detecting the others   
    Do_LINE_rotate_align();           // rotating for aligning to black line , turn right
  } 
}

void Do_IF_LINE_square_cross() {       // 3 sensor meet black line at the same time, lead to charger
  if(sensorValues[0] < QTR_CAL_thre && sensorValues[1] < QTR_CAL_thre && sensorValues[2] < QTR_CAL_thre ) {
     motors.forward(MINspeed);      // move straight a little   
  }
}

void Do_LINE_rotate_align() {         // rotate align to black line  (turn right)
    do {                              // make sensor2 align with black line
        motors.turnRight(RUNspeed);
        qtra.readCalibrated(sensorValues);
    }while(sensorValues[1] > QTR_CAL_thre);  
    motors.brake(10);
}


