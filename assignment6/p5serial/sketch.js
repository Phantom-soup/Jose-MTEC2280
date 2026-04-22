let serial; // variable for instance of the serialport library
let portName = 'COM3'; // fill in your serial port name
let options = { baudRate: 9600}; // change the baud rate to match your Arduino code

let rxFlag = false; // flag to indicate when new data has been received
let firstContact = false; // flag to indicate when the first contact has been made with the serial port
let sensors = [0, 0]; // declare array to hold incoming sensor data, and initialize with zeros
let button1 = 0; // variable to hold button value
let button2 = 0; // variable to hold button value


let x = 0;


function setup() 
{
  //P5 Sketch Setup
  createCanvas(500, 500);
  textAlign(CENTER, CENTER);
  textSize(24);
  strokeWeight(4);
  stroke(127);
  rectMode(CENTER);

  x = width/2;

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
}

function draw() 
{
  background(255);
  stroke(127);

  if (!firstContact)  //if we have not yet received any data...
  {
    fill(100);
    noStroke();
    text("Click to Begin", width/2, height/3);
  }
  else  //if we have established contact with the serial port, show main sketch...
  {
    // spot 1
    if (x > width - 125) // if the player circle goes over the shape
    {
      fill(255, 40, 40);
      strokeWeight(0);
      rect(width - 100, height/2 , 100);
    }
    else
    {
      fill(40, 255, 40);
      strokeWeight(2);
      circle(width - 100, height/2 , 75);
    }

    // spot 2
    if (x < 125) // same thing, but on the other side
    {
      fill(255, 40, 40);
      strokeWeight(0);
      rect(100, height/2, 100);
    }
    else
    {
      fill(40, 255, 40);
      strokeWeight(2);
      circle(100, height/2, 75);
    }

    // "Player" control
    if(button1 == 1)
    {
      x -= 10;
    }
    if(button2 == 1)
    {
      x += 10;
    }
    constrain(x, 0, width);

    fill(0, 0, 255);
    strokeWeight(0);
    circle(x, height/2, 30);

    if (rxFlag) // if rxFlag is true, we are receiving data, so...
    {
      fill(0);
      noStroke();
      text("Pause to click", width/2, height/2 - 100);  // display "PAUSE RX" on the button
    }
    else  //if rxFlag is false, we are not receiving data, so...
    {
      fill(0);
      noStroke();
      text("PAUSED", width/2, height/2 - 100);  //display "PAUSED" on the button
    }
  }
}

function mousePressed() //if mouse is pressed...
{
    rxFlag = !rxFlag; // toggle the rxFlag

    if (rxFlag) //if rxFlag is true, we want to receive data, so...
    {
      serial.write('A'); // send 'A' to the serial port to indicate that we want to receive data
    }
    else  //if rxFlag is false, we want to pause receiving data, so...
    {
      serial.write('B'); // send 'B' to the serial port to indicate that we want to pause receiving data
    }
}

function portOpen() //gets called when the serial port opens
{
  print("SERIAL PORT OPEN");
}

function portClose() //gets called when the serial port closes
{
  print("SERIAL PORT CLOSED");
}

function printList(portList) // gets called when the serial.list() function is called
{
  print("List of Available Serial Ports: ");
  for (var i = 0; i < portList.length; i++) 
  {
    print(i + portList[i]); //print list of available serial ports to console
  }
}

function serialEvent() // gets called when new serial data arrives
{
  if (!firstContact)  //if we have not yet received any data, this is our first contact with the serial port, so...
  {
    print("FIRST CONTACT"); //print "FIRST CONTACT" to the console
    firstContact = true;  //set firstContact flag to true
  }
  
  if(rxFlag)  //if rxFlag is true, we want to receive data, so...
  {
    let inString = serial.readStringUntil('\n'); // read the incoming string until you get a newline character
    if (inString.length > 0) 
    {
      print("Rx String: " + inString); // print the incoming string to the console
      sensors = split(inString, ','); // split the string into an array of sensor values
    
      if(sensors.length >= 2) // check if we have all 4 sensor values before trying to access them
      {
        print(sensors); // print the array of sensor values to the console

        button1 = Number(sensors[0]); // convert the first sensor value to an integer

        button2 = Number(sensors[1]); // convert the second sensor value to an integer

        //now that we're done processing the incoming data, we can "call out" to our microcontroller, which respond with latest sensor data.
        serial.write('A');  // send 'A' to the serial port to indicate that we want the latest sensor data
      }
    }
  }
  else
  {
    let inString = serial.readStringUntil('\n'); // read the incoming string until you get a newline character
    print(inString); // print the incoming string to the console
  }
}

function serialError(err) //gets called when there's an error
{
  print('SERIAL ERROR: ' + err);
}

function serverConnected() //gets called when we connect to the serial server
{
  print("CONNECTED TO SERIAL SERVER");
}