

import ddf.minim.*;
import ddf.minim.analysis.*;
import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;

Minim minim;
AudioPlayer groove;
AudioInput in;
WaveformRenderer waveform;
PShape trollface;
PShape trollface2;
PShape trollface3;
PShape trollface4;
void setup()
{
  size(800 , 600);
  
  minim = new Minim(this);
    in = minim.getLineIn(Minim.STEREO, 1024,44100);
SpecturmFeature feature=new SpecturmFeature(1024,44100,3);
 // groove = minim.loadFile("groove.mp3", 512);
 waveform = new WaveformRenderer(feature,8000);
    in.addListener(waveform);
 background(255);smooth();
 trollface=loadShape("Trollface.svg");
 trollface2=loadShape("Trollface.svg");
 trollface2.disableStyle();
  trollface3=loadShape("herp.svg");
 trollface4=loadShape("herp.svg");
  trollface4.disableStyle();
  //groove.addListener(waveform);
   oscP5 = new OscP5(this,1234);
 
 /* myRemoteLocation is a NetAddress. a NetAddress takes
  * an ip address and a port number. myRemoteLocation is
  * oscP5.send() when sending osc packets to another com
  * application. usage see below. for testing purposes t
  * and the port of the remote location address are the 
  * send messages back to this sketch.
  */
 myRemoteLocation = new NetAddress("128.61.44.45",1234);
}
float scal=0.5;
 void keyPressed(){
   {
    if( (key == '+' || key=='='))
    scal*=1.2f;
    if( (key == '-' || key=='_'))
    scal/=1.2f;
  }
 }
void draw()
{

//ellipse(particleM.X,particleM.Y,5,5);
 translate(width/2,height/2);
 rotate(frameCount/100.0);
 translate(-width/2,-height/2);
  waveform.draw();
 
  color(0,0,0,255);
  if(param2<10000){
  shape(trollface2,width/2,height/2,150,150);
  shape(trollface,width/2,height/2,150,150);
  }
  else{
    shape(trollface4,width/2,height/2,150,150);
    shape(trollface3,width/2,height/2,150,150);
  }
   /* create a new osc message object */
  OscMessage myMessage = new OscMessage("/trollface");
  
  myMessage.add(message1); /* add an int to the osc message */
  myMessage.add(message2); /* add a float to the osc message */
  message3= noise(frameCount/100.0);
  myMessage.add(message3); 
 // myMessage.add("some text"); /* add a string to the osc message */

  /* send the message */
  oscP5.send(myMessage, myRemoteLocation); 
}

void stop()
{
  // always close Minim audio classes when you are done with them
  //groove.close();
  // always stop Minim before exiting.
 // minim.stop();
 // super.stop();
}
void mouseClicked()
{
   saveFrame("frame-######.jpg");
}

float message1=0;
float message2=0;
float message3=0;
void mousePressed() {
 
}

float param1=1;
float param2=0;
void oscEvent(OscMessage theOscMessage) {
  /* check if theOscMessage has the address pattern we are looking for. */
  print("haha");
  if(theOscMessage.checkAddrPattern("/test")==true) {
    /* check if the typetag is the right one. */
    if(theOscMessage.checkTypetag("ifs")) {
      /* parse theOscMessage and extract the values from the osc message arguments. */
      int firstValue = theOscMessage.get(0).intValue();  
      float secondValue = theOscMessage.get(1).floatValue();
      String thirdValue = theOscMessage.get(2).stringValue();
      print("### received an osc message /test with typetag ifs.");
      println(" values: "+firstValue+", "+secondValue+", "+thirdValue);
      return;
    }  
  } 
  println("### received an osc message. with address pattern "+theOscMessage.addrPattern());
     param1 = theOscMessage.get(0).floatValue();  
     param2 = theOscMessage.get(1).floatValue(); 
     println(param1);
     println(param2);
}

