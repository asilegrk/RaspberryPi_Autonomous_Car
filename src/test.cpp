#include <opencv2/opencv.hpp>
#include "raspicam_cv.h"
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
using namespace cv;
using namespace raspicam;

Mat frame , frame1;
RaspiCam_Cv Camera;

Point2f Source[]={Point2f(50,200),Point2f(280,200),Point2f(0,240),Point2f(360,240)};
// point degerleri olusturulacak track e duzenleme yapilacak
//ekranda olusacak seklin yan taraflari track uzerindeki line a paralel olmali


 void Setup ( int argc,char **argv, RaspiCam_Cv &Camera )
  {
    Camera.set ( CAP_PROP_FRAME_WIDTH,  ( "-w",argc,argv,360) );
    Camera.set ( CAP_PROP_FRAME_HEIGHT,  ( "-h",argc,argv,240 ) );
    Camera.set ( CAP_PROP_BRIGHTNESS, ( "-br",argc,argv,50 ) );
    Camera.set ( CAP_PROP_CONTRAST ,( "-co",argc,argv,50 ) );
    Camera.set ( CAP_PROP_SATURATION,  ( "-sa",argc,argv,50 ) );
    Camera.set ( CAP_PROP_GAIN,  ( "-g",argc,argv ,50 ) );
    Camera.set ( CAP_PROP_FPS,  ( "-fps",argc,argv,0));

}

void Perspective(){
	line(frame,Source[0],Source[1], Scalar(0,0,255),2);
	line(frame,Source[1],Source[3], Scalar(0,0,255),2);
	line(frame,Source[3],Source[2], Scalar(0,0,255),2);
	line(frame,Source[2],Source[0], Scalar(0,0,255),2);
}

void Capture(){
	
	Camera.grab();
	Camera.retrieve( frame);
	cvtColor(frame, frame,COLOR_BGR2RGB);
}

int main(int argc, char **argv){
	
	Setup(argc,argv, Camera);
	cout<<"Connecting to Camera"<<endl;
	if(!Camera.open()){
		cout<<"Failed to Connect"<<endl;
		return -1;
	}
	
	cout<<"Camera ID = "<<Camera.getId()<<endl;
	
	while(1){
		
	
		auto start = std::chrono::system_clock::now();
		
		Capture();
		Perspective();
		
		namedWindow("original", WINDOW_KEEPRATIO);
		moveWindow("original",50,100);
		resizeWindow("original",640,480);					
		imshow("original", frame);
		
		//namedWindow("RGB", WINDOW_KEEPRATIO);
		//moveWindow("RGB",700,100);
		//resizeWindow("RGB",640,480);					
		//imshow("RGB", frame1);
		
		
		
		waitKey(1);
		
		auto end = std::chrono::system_clock::now();
	  

		std::chrono::duration<double> elapsed_seconds = end-start;
		
		float t = elapsed_seconds.count();
		int FPS = 1/t;
		cout<<"FPS = "<<FPS<<endl;
		
	}
	return 0;
}
