
class WaveformRenderer implements AudioListener
{
  

Brush brush=new Brush();
  float prev=0;
   float prev2=0;
  float prev3=0;
 float freq=0;
  private float[] left;
  private float[] right;
  float partialCount;
  int sampleRate;
  SpecturmFeature feature;
  WaveformRenderer(SpecturmFeature feature,int sampleRate)
  {
    left = null;
    right = null;
    this.feature=feature;
    this.sampleRate=sampleRate;
  }
  
  synchronized void samples(float[] samp){
    left=samp;
  }

  synchronized void samples(float[] sampL, float[] sampR)
  {
    
     feature.setFrame(sampL);
    freq=freq*0.3+0.7*feature.pitchDetect();

    left = sampL;
    right = sampR;
  }
  float maxH=0;
  float maxS=0;
  float maxB=0;
    float minH=300;
  float minS=300;
  float minB=300;
  float pL=0;
  float pP=0;
  synchronized void draw()
  {
  
      float m=0;
    // we've got a stereo signal if right or left are not null
    if ( left != null && right != null )
    {
     for ( int i = 0; i < left.length; i++ )
     {
       if(abs(left[i])>m)m=abs(left[i]);
     }
     

     if(m<0.03){
     //brush.pull(0,0,0.3);
    // return;
   }

     // noFill();
      stroke(0);
      float tmp=0;
      float tmp2=0;
      float []xxx=new float[left.length];
      float []yyy=new float[left.length];
      for ( int i = 0; i < left.length; i++ )
      {
        tmp=left[i]-prev;
        tmp2=tmp-prev2;
         xxx[i]=left[i]*600/m;
        yyy[i]=200*(tmp)/m/freq/PI*sampleRate;
        
        //point(left[i]*600/m,200*(tmp)/m/freq/PI*sampleRate);
        prev2=tmp;
        prev3=tmp2;
        prev=left[i];
        
      }
      float p=(12*log(freq/440)+69);
      
      float l=10*log(feature.power()/1e-12)*log(2)/log(10);
      l=norm(l,40,85);
     // p=norm(p,20,90);
     p=norm(p,20,90);
     // p=(feature.ZCR()*30);
      brush.pull(width/2+l*20,height-height*p,1);
      message1=l;
      message2=p;
      //brush.pull(10*cos(frameCount/100.0),10*sin(frameCount/100.0),1);
     // ellipse(l*width,height-height*p,5,5);
      //println(height*p);
      float H=sqrt(feature.spread())*360;
      float S=feature.flatness();
      float B=feature.centroid()/feature.maxfrequency;
      if(H>maxH)maxH=H;
      if(S>maxS)maxS=S;
      if(B>maxB)maxB=B;
       if(H<minH)minH=H;
      if(S<minS)minS=S;
      if(B<minB)minB=B;
      H=(H)%360;
      S=(S*2);
      B=(B*2);
      //println(m);

      brush.draw(H,S,B,m*2);

     // println(maxH+"   "+maxS+"   "+ maxB);
      // println(minH+"   "+minS+"   "+ minB);
    }
  }
  
  

}

