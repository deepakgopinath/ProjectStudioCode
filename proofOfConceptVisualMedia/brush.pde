
class Brush{
Particle[] particle;
Particle particleM=new Particle(random(0,width/2),random(0,height),random(0,100),0.3);
Brush(){
  
particle=new Particle[500];
  for(int i=0;i<particle.length;i++){
    particle[i]=new Particle(random(0,width/2),random(0,height),random(0,1000),random(0.1,5));
    particle[i].setV(random(0,100),random(0,100),0);
  }
}
  void draw(float H,float S,float B,float m){
    //colorMode(HSB, 360, 1, 1);
   // stroke(H,S,B,3);
   stroke(255*noise(frameCount/200.0*0.2),255*noise(frameCount/200.0*0.6),255*noise(frameCount/200.0*0.86),5*param1);
   //stroke(255*noise(frameCount/200.0*0.86),5);
  strokeWeight(1);
 // particleM.X+=(0.03*(mouseX-particleM.X));
 // particleM.Y+=(0.03*(mouseY-particleM.Y));
    for(int i=0;i<particle.length;i++){  
    particle[i].applyForce(0.03*m*(particleM.X-particle[i].X),0.03*m*(particleM.Y-particle[i].Y),0);
    particle[i].draw();
     // rotate(PI);
    }
  }
  void setPosition(float X,float Y){
    particleM.X=X;
    particleM.Y=Y;
  }
  void applyForce(float X,float Y,float force){
    particleM.X+=force*(X-width/2)/width;
    particleM.Y+=force*(Y-height/2)/height;
    particleM.X=constrain(particleM.X,0,width);
    particleM.Y=constrain(particleM.Y,0,height);
  }
  void pull(float X,float Y,float force){
    particleM.X+=force*(X-particleM.X);
    particleM.Y+=force*(Y-particleM.Y);
  }
}
class Particle{
  float X;
  float Y;
  float Z;
  float Vx;
  float Vy;
  float Vz;
  float damp=0.98;
  float M;
  Particle(float X,float Y,float Z,float M){
    this.X=X;
    this.Y=Y;
    this.Z=Z;
    this.M=M;
  }
  void setV(float Vx,float Vy,float Vz){
    this.Vx=Vx;
    this.Vy=Vy;
    this.Vz=Vz;
  }
  void applyForce(float Fx,float Fy,float Fz){
    Vx*=damp;
    Vy*=damp;
    Vx+=Fx/M;
    Vy+=Fy/M;
    Vz+=Fz/M;
  }
  void draw(){

    X+=Vx;
    Y+=Vy;
    Z+=Vz;
    line(X,Y,X-Vx,Y-Vy);
    
   // line(width-X,Y,width-(X-Vx),Y-Vy);
  }
  
}
