#include <stdio.h>
#include "Matrix.h"
#include "MatrixFactory.h"
#include "FrameBuffer.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cone.h"
#include <cmath>
#include <iostream>
#include <vector>
#include "RsTextureShader.h"

#include "RenderMan.h"

#define WIDTH  100
#define HEIGHT 100
#define N 8

Matrix projectionMatrix = MatrixFactory::createPerspectiveProjection(
  M_PI/3, 
  4.0f/4.0f,
  0.1,
  100
);

//void texture(int i) { (void) i;}

void TextureMap0()
{
  //texture(0);
}

void Earth()
{
	RiBegin(RI_NULL);
		//RiFormat(960, 720, 1.0);
		RiFormat(400, 300, 1.0);
		//RiFormat(200, 150, 1.0);
		RiDisplay("Earth.png", "file", "");
		RiPixelSamples(2,2);
		
		RiFrameBegin(0);
			/* set the perspective transformation */
			float fov = 45.0;
			RiProjection(RI_PERSPECTIVE, "fov", &fov);

			RiWorldBegin();
				RiTransformBegin();
					RiMakeTexture("earth.jpg", 0);
					void (*earthShader)(void) = TextureMap0;
					RiSurface(earthShader);
					RtColor blue = { 0, 0, 1 };
					RtColor opacity = { .9, .9, .9 };
					RiColor(blue);
					RiOpacity(opacity);
					//BUMP_AMPLITUDE = .02;
					//BUMP_MIN_FREQ_EXP = 14;
					//BUMP_MAX_FREQ_EXP = 16;
					//RiDisplacement(BUMPY);
					//RiRotate(-175, 0, 1, 0);
					//RiRotate(90, 1, 1, 1);
					RiTranslate(0, 0, 50.0);
					RiSphere(5, 5, 5, 2*M_PI);
				RiTransformEnd();
			RiWorldEnd();

		RiFrameEnd();

	RiEnd();
}


void myScene(void) { 
  RiBegin(RI_NULL);
 
  RiFormat(1024, 1024, 1.0); 
  RiFrameAspectRatio(4.0/4.0); 


  /* set the perspective transformation */ 
  float fov = 45.0;
  RiProjection(RI_PERSPECTIVE, "fov", &fov); 
  RiRotate(90, 1, 0, 0);
  RiRotate(180, 0, 0, 1);
  RiTranslate(0,0, 45.0); 

  RiSurface((RtShaderFunc)&RsTextureShader);
  
  for (int i=0; i<1; i++) {

    RiFrameBegin(i); 

    RiWorldBegin(); 
 
    RiTranslate(0,0, -45.0); 
    RiRotate(1, 0, 0, 1);
    RiTranslate(0,0, 45.0); 
    RiSphere(5.0, -5.0, 5.0, 2 * M_PI); 
    //RiSphere(2.5, 2.5, 2.5, 2 * M_PI);
    
    RiWorldEnd(); 
    RiFrameEnd(); 
  }
  RiEnd(); 
}; 

void SampleScene1(void) {
	int i;
	int nf;
	float slopex,slopey,slopez;
	char name[50];

	RtColor red={1,0,0};
	RtColor green={0,1,0};
	RtColor blue={0,0,1};
	RtColor white={1,1,1};


	RtPoint p1={30,0,100}; /* ball's initial position */
	RtPoint p2={0,20,100}; /* ball's final position  */


	RtFloat fov = 45;
	RtFloat intensity1=0.1;
	RtFloat intensity2=1.5;
	RtInt init=0,end=1;
	

	nf = 100; /* number of frames to output */
	slopex = (p2[0]-p1[0])/nf;
	slopey = (p2[1]-p1[1])/nf;
	slopez = (p2[2]-p1[2])/nf;
	
	RiBegin(RI_NULL);
		RiFormat(320,240,1);
		RiPixelSamples(2,2);
		RiShutter(0,1);

		/* loop through all the frames */
		for (i = 1; i <= nf; i++) {
			RiFrameBegin(i);
        sprintf(name,"image_%02d.tif", i-1);
				RiDisplay(name, "file", "rgb", RI_NULL);

				RiProjection("perspective", "fov", &fov, RI_NULL);
        
				RiTranslate(0,-5,60);
				RiRotate(-120,1,0,0);
				RiRotate(25,0,0,1);
        
				RiWorldBegin();
					RiColor(blue);
					RiTransformBegin();
						RiCylinder(1, 0, 20, 360, RI_NULL);
						RiTranslate(0, 0, 20);
						RiCone(2, 2, 360, RI_NULL);
					RiTransformEnd();

					RiColor(green);
					RiTransformBegin();
						RiRotate(-90, 1, 0, 0);
						RiCylinder(1, 0, 20, 360, RI_NULL);
						RiTranslate(0, 0, 20);
						RiCone(2, 2, 360, RI_NULL);
					RiTransformEnd();

					RiColor(red);
					RiTransformBegin();
						RiRotate(90, 0, 1, 0);
						RiCylinder(1, 0, 20, 360, RI_NULL);
						RiTranslate(0, 0, 20);
						RiCone(2, 2, 360, RI_NULL);
					RiTransformEnd();
          
        
					RiColor(white);
						RiTransformBegin();
						RiTranslate(p1[0] + slopex * (i-1), p1[1] + slopey * (i-1), p1[2] + slopez * (i-1));
						RiSphere(5, -5, 5, 360, RI_NULL);
					RiTransformEnd();
				RiWorldEnd();

			/* when you hit this command you should output the final image for this frame */
			RiFrameEnd();
		}
	RiEnd();
};


void renderExample();
int main(int argc, char *argv[]) {

  //Matrix m(1,2,3,1);
  //m.printPoint();
  //m.rotate(Z, M_PI/2);
  //m.printPoint();

  //FrameBuffer fb(10,10);
  //fb.flush(0);
  //SampleScene1();
  myScene();
  //Earth();
  //renderExample();

  return 0;
}


void renderExample() {

  Matrix translationVector(10, 0, 10);
  Matrix scaleVector(1, 1, 2);

  
  FrameBuffer fb(WIDTH, HEIGHT);
  
  for (int i=0; i<1; i++) {
    
    {
      Sphere s(1, 0, 1, 2*M_PI);
      s.setColor(0, 255, 0);
      s.setOpacity(0.2);
      Matrix t = MatrixFactory::createIdentity(4);
      //t.rotate(X, M_PI/2);
      //t.rotate(Z, M_PI/2);
      t.scale(2,2,2);
      t.translate(0, 0, 50);
      s.transform(t);
      s.projectOnto(projectionMatrix);
      s.homogenize();
      fb.draw(s);
    }

    {
      Sphere s(1, 0, 1, 2*M_PI);
      s.setColor(0, 255, 255);
      s.setOpacity(0.7);
      Matrix t = MatrixFactory::createIdentity(4);
      t.scale(20, 20, 20);
      //t.rotate(X, M_PI/4);
      t.translate(0,0,60);
      
      s.transform(t);
      s.projectOnto(projectionMatrix);
      s.homogenize();
      fb.draw(s);
    }    

    {
      Sphere s(1, 0, 1, 2*M_PI);
      s.setColor(255, 0, 0);
      s.setOpacity(0.3);
      Matrix t = MatrixFactory::createIdentity(4);
      t.scale(1,1,1);
      t.translate(1,1, 20);
      s.transform(t);
      s.projectOnto(projectionMatrix);
      s.homogenize();
      fb.draw(s);
    }    
    //fb.draw(&s);
    fb.flush(i);
  }


}
