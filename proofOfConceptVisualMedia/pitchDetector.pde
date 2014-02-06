class SpecturmFeature{
  // some features need to be converted to dB scale
  FFT fft;
  int sampleRate;
  int binLength;
  int harmonicSize;
  int fftLength;
  float[][] step;
  float[] frame;
  float maxfrequency;
  void setFrame(float[] frame){
    this.frame=frame;
    fft.forward(frame);
  }
  SpecturmFeature(int fftLength,int sampleRate,int harmonicSize){
    fft=new FFT(fftLength,sampleRate);
    maxfrequency=fft.specSize()*fft.getBandWidth();

    this.fftLength=fftLength;
    this.sampleRate=sampleRate;
    this.binLength=fft.specSize();
    //this.fftLength=fftLength;
    this.harmonicSize=harmonicSize;
    step=new float[harmonicSize][];
    for(int i=0;i<harmonicSize;i++){
      step[i]=new float[binLength];
    }
    fft.window(fft.HAMMING);
  }
  float pitchDetect(){
    //downsample
      for(int i=0;i<binLength;i++){
        for(int j=1;j<=harmonicSize;j++){
           if(i%j==0)( step[j-1])[i/j]=fft.getBand(i);
        }
      }
     // println(fft.specSize());
    //HSP
      int index=0;
      float max;
      max=0;
      float tmp;;
      for(int i=0;i<binLength;i++){
        tmp=1;
        for(int j=0;j<harmonicSize;j++){
          tmp*=step[j][i];
        }
        //println(tmp);
        if(tmp>max){
          max=tmp;
          index=i;
        }
      }
       if(index==0)return 1.0;
      // println( index*fft.getBandWidth());
      return index*fft.getBandWidth();
   

  }
  float centroid(){
    float wSum=0;
    float aSum=0;
     for(int i=1;i<binLength;i++){
          wSum+=i*fft.getBand(i);
          aSum+=fft.getBand(i);
     }
     //println((wSum/aSum)*fft.getBandWidth());
     return wSum/aSum*fft.getBandWidth();
  }
  float spread(){
    float sc=centroid()/fft.getBandWidth();
     float wSum=0;
    float aSum=0;
     for(int i=1;i<binLength;i++){
        
          wSum+=((i-sc)*(i-sc))*fft.getBand(i);
          aSum+=fft.getBand(i);
     }
     //println((wSum/aSum)*fft.getBandWidth());
     float result=wSum/aSum*fft.getBandWidth()*fft.getBandWidth()/binLength/binLength/binLength;
    // println(result);
     return result;
     
  }
  
  float ZCR(){
    int zeros=0;
     for(int i=0;i<frame.length-1;i++){
       if(frame[i]*frame[i+1]<0) zeros++;
     }
    // println( (float)zeros/2/frame.length);
     return (float)zeros/2/frame.length;
  }
  float power(){
    float power=0;
     for(int i=0;i<frame.length;i++){
       power+=frame[i]*frame[i];
     }
     return (power/frame.length);
  }
  float flatness(){
    //stub?unit
    float logsum=0;
    float sum=0;
     for(int i=1;i<binLength;i++){
      logsum+=log( fft.getBand(i));
      sum+=fft.getBand(i);
     }
     float result=exp(logsum/binLength)/sum*binLength;
     //println(result);
     return result;
  }
  float mel2freq(float freq){
    return 1127.01028*log(1+freq/700);
  }
  float freq2mel(float mel){
    return 700*(exp(mel/1127.01028)-1);
  }
  float[] Hamming(int n){
     float[] result=new float[n];
     for(int i=0;i<n;i++){
       result[i]=0.5f*(1.0f-cos(2.0f*(float)PI*i/(n-1)));
     }
     return result;
  }


 
}

