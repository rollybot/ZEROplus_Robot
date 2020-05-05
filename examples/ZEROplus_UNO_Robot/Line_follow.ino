////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
// QTR_LOGIC
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void Line_Follow_Move() {
  Setup_Calibration();   // only one time
  
  unsigned int position = qtra.readLine(sensorValues);
  int error = position - 1000;
  int motorSpeed = KP * error + KD * (error - lastError);  ///////// PID control
  lastError = error;  
  
  int m1Speed = LTRspeed + motorSpeed;   
  int m2Speed = LTRspeed - motorSpeed;
   
  if (m1Speed < 0)   m1Speed =    0;   
  if (m2Speed < 0)   m2Speed =    0;   
  if (m1Speed > 255) m1Speed =  255;   
  if (m2Speed > 255) m2Speed =  255;   
   
  motors.forward_diff(m2Speed,m1Speed); //////////////////  following the line
  if(!STATUS_Sonar_disabled) read_sonar_cm = sonar.ping_cm();
  
  Do_IF_LINE_end_of_line();
  #if defined(R_TURN_SENSOR_ENABLED)
     Do_IF_LINE_3ways_cross();
  #endif
  Do_IF_LINE_crossing_line();
  Do_IF_LINE_interrupt();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Setup_Calibration() {
  if (!STATUS_Calibration_setup) {     // first of all, calibrate the sensor 
    motors.brake(10); 
    QTR_Calibrate_rotate();
  }
}

void QTR_Calibrate_rotate() {        // for line tracing
  for (int i = 0; i < 50; i++) {     // make the calibration take about 10 seconds (before 220)
      qtra.calibrate();              // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
      motors.turnRight(130);
  }  
  for (int i = 0; i < 90; i++) {     // make the calibration take about 10 seconds (before 220)
      qtra.calibrate();              // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
      motors.turnLeft (130);
  }  
  do {                               // make sensor2 align with black line
      Batt_LED_status(LED_interval); // for batt status
      motors.turnRight(130);
      qtra.readCalibrated(sensorValues);
  }while(sensorValues[1] > QTR_CAL_thre);  
  motors.turnLeft(200,50);            // for braking with L293D
  
  STATUS_Calibration_setup = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Do IF LINE following
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Do_IF_LINE_end_of_line() {       // when linetracing mode , end of line case
  if (sensorValues[0] > QTR_CAL_thre && sensorValues[1] > QTR_CAL_thre && sensorValues[2] > QTR_CAL_thre ) {   // end of line
    motors.forward(LTRspeed,GAP_time);   
    motors.backward(150,30);          // for breaking with L293D   
    Do_LINE_rotate_align();           // rotating for aligning to black line , turn right
  } 
}

void Do_IF_LINE_3ways_cross() {       // when linetracing mode , 3 sensor meet black line at the same time
  sensorValue_R = read_QRED_distance(QTR5_PIN);   // 0~3000, black is high value , over 200
  if (sensorValue_R > 300 && sensorValues[1] < QTR_CAL_thre) {
    motors.forward(LTRspeed,GAP_time);// move a little
    motors.backward(150,30);          // for breaking with L293D   
    motors.turnRight(LTRspeed,200);
    Do_LINE_Rturn_align();            // rotating for aligning to black line , turn right
  }
}

void Do_IF_LINE_crossing_line() {       // when linetracing mode , end of line case
  if (sensorValues[0] < QTR_CAL_thre && sensorValues[1] < QTR_CAL_thre && sensorValues[2] < QTR_CAL_thre ) {   // end of line
    motors.brake(GAP_time);  
    motors.forward(LTRspeed,GAP_time); 
  } 
}

void Do_LINE_rotate_align() {          // rotate align to black line  (turn left a little and right)
    int r_counter = 0;
    do {                               // make sensor2 align with black line
        Batt_LED_status(LED_interval); // for batt status
        motors.turnLeft(130);
        qtra.readCalibrated(sensorValues);
        r_counter ++;
    }while(r_counter < 250 && sensorValues[1] > QTR_CAL_thre); 
    motors.turnRight(150,10);
        
    do {                               // make sensor2 align with black line
        Batt_LED_status(LED_interval); // for batt status
        motors.turnRight(130);
        qtra.readCalibrated(sensorValues);
    }while(sensorValues[1] > QTR_CAL_thre);  
    motors.turnLeft(150,10);           // for braking with L293D
}

void Do_LINE_Rturn_align() {           // right rotate align to black line  
  do {                                 // make sensor2 align with black line
      Batt_LED_status(LED_interval);   // for batt status
      motors.turnRight(130);
      qtra.readCalibrated(sensorValues);
  }while(sensorValues[1] > QTR_CAL_thre);  
  motors.turnLeft(150,10);             // for braking with L293D
}

void Do_IF_LINE_interrupt() {     
  if(STATUS_Sonar_disabled) return;    // ultrasonic sensor not installed
  if(COUNT_for_line_interrupt > 7) {
    COUNT_for_line_interrupt = 0;
    motors.turnRight(180,200);
    Do_LINE_Rturn_align();
  }
  if(read_sonar_cm < TRESHOLD && read_sonar_cm != 0) {  
    COUNT_for_line_interrupt++;
    motors.backward(150,50);
    motors.brake (100);
  }
}
