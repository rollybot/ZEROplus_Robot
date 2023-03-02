void Autonomous_Move() {
  if(STATUS_Sonar_disabled) {playsong_No_sensor(100); return; }     // ultrasonic sensor not installed
  read_sonar_cm = scan_average_cm(3);
  if(read_sonar_cm < TRESHOLD && read_sonar_cm != 0) {  
    motors.brake (100);
    motors.backward (RUNspeed,400);   // move backward a little
    motors.brake (100);
    
    motors.turnRight(RUNspeed,400);   // move right to see block
    motors.brake (100);
    long temp = scan_average_cm(3);
    
    motors.turnLeft (RUNspeed,800);  // move left to see block
    motors.brake (100);
    if (scan_average_cm(3) < temp) motors.turnRight(RUNspeed,800); // turn to the way value is hig   
  }
  #if defined(BLACKline_ENABLED)
     if(int check = Check_Darkness_inFloor()) { 
       if(check == 1) { motors.backward(RUNspeed,500); motors.turnRight(RUNspeed,1000); }
       if(check == 2) { motors.backward(RUNspeed,500); motors.turnRight(RUNspeed,1000); }
       if(check == 3) { motors.backward(RUNspeed,500); motors.turnLeft (RUNspeed,1000); }
       }    
  #endif
  motors.forward(RUNspeed);
}
