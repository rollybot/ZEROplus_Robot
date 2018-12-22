

import processing.serial.*; //Importing the Serial library.
import static javax.swing.JOptionPane.*;

Serial myPort; // Creating a port variable.
final boolean debug = true;
int r,g,b; // initializing colours.
String T0= "ZEROplus Robot Keyboard Control"; 
String T00="by rollybot.com"; 
String T1= "UP";
String T2= "DOWN";
String T3= "RIGHT";
String T4= "LEFT";

void setup()
{
  String COMx, COMlist = "";
  try {
    if(debug) printArray(Serial.list());
    int i = Serial.list().length;
    if (i != 0) {
      if (i >= 2) {
        // need to check which port the inst uses -
        // for now we'll just let the user decide
        for (int j = 0; j < i;) {
          COMlist += char(j+'a') + " = " + Serial.list()[j];
          if (++j < i) COMlist += ",  ";
        }
        COMx = showInputDialog("Which COM port is correct? (a,b,..):\n"+COMlist);
        if (COMx == null) exit();
        if (COMx.isEmpty()) exit();
        i = int(COMx.toLowerCase().charAt(0) - 'a') + 1;
      }
      String portName = Serial.list()[i-1];
      if(debug) println(portName);
      myPort = new Serial(this, portName, 9600); // change baud rate to your liking
      myPort.bufferUntil('\n'); // buffer until CR/LF appears, but not required..
    }
    else {
      showMessageDialog(frame,"Device is not connected to the PC");
      exit();
    }
  }
  catch (Exception e)
  { //Print the type of error
    showMessageDialog(frame,"COM port is not available (may\nbe in use by another program)");
    println("Error:", e);
    exit();
  }
  
  size(600,600); // Creating the display window and defining its' size.
  r = 0; // Setting up the colours.
  g = 0;
  b = 0;
}
 
void draw()
{
   
  background(0,0,0); // Setting up the background's colour- Yellow.

  fill (255,255,255); // Painting the Arrows White.
  rect(width/2-50, height/2-50, 100, 100,7); // Up arrow
  rect(width/2-50, height/2+60, 100, 100,7); // Down arrow
  rect(width/2-160, height/2+60, 100, 100,7); // Down arrow
  rect(width/2+60, height/2+60, 100, 100,7); // Down arrow
  textAlign(CENTER);
  textSize(32); // Defining the headline's size- 32
  fill (0,0,255); // painting the headline blue.
  text(T0,  width/2, 50 );  // placing the headline in a specific location
  text(T00, width/2, 100);
  
  textSize (20); // The arrow keys text size- 20
  fill (0,0,0); // painting it green.
  text(T1, width/2, height/2+10); //UP
  text(T2, width/2, height/2+120);//DOWN
  text(T3, width/2+110, height/2+120); //RIGHT
  text(T4, width/2-110, height/2+120);//LEFT
}
 
void keyPressed()
{
   switch (keyCode) { //Switch case: Sending different signals and filling different arrows red according to which button was pressed.   
    case UP: //In case the UP button was pressed:
      myPort.write('1'); // Send the signal 1
      println("UP!"); // + Print "UP!" (Debugging only) 
      fill(255,0,0); // + Fill the up triangle with red.
      rect(width/2-50, height/2-50, 100, 100,7);
      break;
    case DOWN:
      myPort.write('2');
      println("DOWN!");
      fill(255,0,0);
      rect(width/2-50, height/2+60, 100, 100,7);
      break; 
    case LEFT:
      myPort.write('3');
      println("LEFT!");
      fill(255,0,0);
      rect(width/2-160, height/2+60, 100, 100,7);
      break;
    case RIGHT:
      myPort.write('4');
      println("RIGHT!");
      fill(255,0,0);
      rect(width/2+60, height/2+60, 100, 100,7);
      break;
    default:
      break;
  }
}

void keyReleased(){
  myPort.write ('5');
}