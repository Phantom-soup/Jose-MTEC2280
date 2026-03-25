let serial; // declare variable for an instance of the serialport library
let portName = 'COM3';  // fill in your serial port name here
let options = { baudRate: 9600}; // change the baud rate to match your Arduino code

let inData = 0; // variable for storing incoming serial data
let sensors = [0, 0, 0, 0]; // array to hold sensor values: [button1, button2, pot1, pot2]

// Variables
let button1 = 0;
let button2 = 0;
let potVal = 0;

let lightLevel = 0;

let uno;
let dos;
backlight = 0;

function setup() //setup function runs once at beginning
{
  //P5 SerialPort Setup
  serial = new p5.SerialPort();             // make a new instance of the serialport library

  serial.on('list', printList);             // set a callback function for the serialport list event
  serial.on('connected', serverConnected);  // set callback for connecting to the server
  serial.on('open', portOpen);              // set callback for the port opening
  serial.on('data', serialEvent);           // set callback for when new data received
  serial.on('error', serialError);          // set callback for errors
  serial.on('close', portClose);            // set callback for closing the port

  serial.list();                            // list the serial ports
  serial.open(portName, options);           // open a serial port

  //TYPICAL P5.JS SETUP
  createCanvas(800, 800); //set size of canvas
  textSize(64); // set text size
  textAlign(CENTER, CENTER);  // set text alignment
  strokeWeight(10); // set stroke weight
  stroke(0); // set stroke color
  rectMode(CENTER);
  angleMode(DEGREES);

  uno = new spotLight(0,height, -40, 20);
  dos = new spotLight(width, height, 240, 310);
}

function draw() //  draw function loops forever at frame rate
{
  background(backlight);
  button1 = sensors[0];
  button2 = sensors[1];
  potVal = map(sensors[2], 0,1023, 0,150);
  background(potVal,potVal,100+potVal,60);

  if(sensors[0]){
    uno.show();
    lightLevel = 1;
  }
  if(sensors[1]){
    dos.show();
    lightLevel = 1;
  }

  if(sensors[0] && sensors[1]){
    lightLevel = 2;
  }
  if(sensors[0] == 0 && sensors[1] == 0) {
    lightLevel = 0;
  }

  if(lightLevel == 1){
    backlight = 150;
  }
  else if (lightLevel == 2){
    backlight = 255;
  }
  else {
    backlight = 0;
  }
  print(button1, button2);
}

class spotLight{
  constructor(x, y, ancL, ancR){
    this.x = x;
    this.y = y;
    this.ancL = ancL;
    this.ancR = ancR;
  }

  show() {
    push();

    translate(this.x, this.y);
    rotate(map(sensors[3], 0,1023, this.ancL,this.ancR));

    strokeWeight(2);
    fill('orange');
    triangle(0,0, width,-height+200, width-200,-height);

    pop();
  }
}


function printList(portList) // gets called when the serial.list() function is called
{
  print("List of Available Serial Ports: ");
  for (var i = 0; i < portList.length; i++) 
  {
    print(i + portList[i]); //print list of available serial ports to console
  }
}

function serverConnected() //gets called when we connect to the serial server
{
  print("CONNECTED TO SERVER");
}
 
function portOpen() //gets called when the serial port opens
{
  print("SERIAL PORT OPEN");
}
 
function serialEvent() //gets called when new data arrives
{
  let inString = serial.readStringUntil('\n'); // read until newline character
  if (inString.length > 0) //if there's data in the string
  {
    sensors = split(inString, ','); // split the string at commas and store in array
    
    for (let i = 0; i < sensors.length; i++) 
    {
      // Number() function converts string to number
      sensors[i] = Number(sensors[i]); // convert every element in array to numbers

      // You can also use parseInt() function, which takes a second argument for the base (radix).
      // A base of 10 is for decimal numbers, base of 16 is for hexadecimal, base of 2 is for binary.
      // sensors[i] = parseInt(sensors[i], 10); // converts every element in array to decimal number
    }
    //print(sensors);
  } 
}
 
function serialError(err) //gets called when there's an error
{
  print('ERROR: ' + err);
}
 
function portClose() //gets called when the serial port closes
{
  print("*____SERIAL PORT CLOSED");
}