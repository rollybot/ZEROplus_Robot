void Palm_control_Move() {
  qtra.read(sensorValues); 
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
   
  motors.forward_diff(m2Speed,m1Speed);    //////////////////  following the line
  no_palm_detecting();
}

void no_palm_detecting() {       // when linetracing mode , end of line case
  if (sensorValues[0] < 20 && sensorValues[1] < 20 && sensorValues[2] < 20 ) {   // no palm detect
    motors.brake(10);
  } 
}
