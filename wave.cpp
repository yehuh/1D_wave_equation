#include<iostream>
#include<fstream>
#include <string>
#include<windows.h>
#include<gl\glut.h>
#include<gl\gl.h>
#include<cmath>
//#include "stlinput.H"
//#include "four_bar.H"
using namespace std;
   const GLdouble pi = 3.141592654;                //       no unit
   const GLdouble Gr = 980;                        //       cm/s^2
   const GLdouble omega = 1.2025;                  //       1/s
   const GLdouble line = 50;                       //       cm
   const GLdouble w    = pi;                     //       1/s
   const GLint x_interval    = 15;              //       total grids in x axis
   const GLint t_interval    = 10000;              //       total grids in t axis
         GLfloat position_x = 0;                  //       cm   x
	   //GLfloat position_y = 0;                  //       cm
		 GLdouble ctrlPoints[x_interval][3] = {0.0};    //       cm   
		 GLdouble u[x_interval][t_interval] = {0.0};             //       u(x,t)
         GLdouble time  =0;                        //       sec  
		 GLdouble time2 =0;                        //       sec 
		 GLdouble step = 0.005;                     //       sec  =>delta t = 0.005
		 GLdouble delta_x = line/(x_interval);       //       cm   delta x
		 GLdouble timevary  = 0;                   //       no unit
         GLfloat ob_angle_x =0;                   //       degree
         GLfloat ob_angle_y =0;                   //       degree
		 GLfloat ob_angle_z =0;                   //       degree

		 GLfloat ob_x =0;                         //       degree
         GLfloat ob_y =0;                         //       degree
		 GLfloat ob_z =0;                         //       degree

		 GLfloat length = 0;                      //       cm   =>length of shape function
		 //GLfloat temp1  = 0;                      //      temperary caculate1
         //GLfloat temp2  = 0;                      //      temperary caculate2
		 //GLfloat temp3  = 0;                      //      temperary caculate3
		 GLfloat tencmpoint = 0;                  //      the point which length is equal to 10 cm

		 //int j = 0;
		 int a = 0;                               //      temp storage

		    
		  GLfloat wing_output_rad(GLfloat t1)
		 {
			 GLfloat temp = 0;
		    temp = pi/4*cos(6*t1);
			return temp;
		 };

		 GLfloat wing_output_deg(GLfloat t1)
		 {
			 GLfloat temp = 0;
		    temp = 45*cos(6*t1);
			return temp;
		 };



   void SetupRC(void)
   {

	GLfloat ambientLight[]={0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat diffuseLight[]={0.7f, 0.7f, 0.7f, 1.0f};

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_CCW);

	glEnable(GL_LIGHTING);

	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glEnable(GL_LIGHT0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    //stlinput("base120x14.7x7mm.STL",base);
	
	

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   }

   void ChangeSize(GLsizei w,GLsizei h)
   { 
	GLfloat lightPos[]={100.0f, 100.0f, 100.0f, 1.0f};
	if(h==0)
		h=1;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    if(w<=h)
      glOrtho(-200.0f*w/h,200.0f*w/h, -200.0f, 200.f, -200.0f, 200.0f); //顯示範圍
    else
	  glOrtho(-200.0f,200.0f, -200.0f*h/w, 200.f*h/w, -200.0f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

   } 


   void SpecialKeyHandler(int key, int x, int y)
   {  


	if(key == GLUT_KEY_LEFT)
	{
		ob_angle_y = ob_angle_y+10.0f;

		if (ob_angle_y<-180.0f)
			ob_angle_y = ob_angle_y+360.0f;
	}

	if(key == GLUT_KEY_RIGHT)
	{
		ob_angle_y = ob_angle_y-10.0f;

		if (ob_angle_y>360.0f)
			ob_angle_y = ob_angle_y-360.0f;
	}
	     

	if(key == GLUT_KEY_UP)
	{
		ob_angle_x = ob_angle_x-10.0f;

		if (ob_angle_x>360.0f)
			ob_angle_x = ob_angle_x-360.0f;
	}

	if(key == GLUT_KEY_DOWN)
	{
		ob_angle_x = ob_angle_x+10.0f;

		if (ob_angle_y<-180.0f)
			ob_angle_y = ob_angle_y+360.0f;
	}




	if(key == GLUT_KEY_LEFT && glutGetModifiers() == GLUT_ACTIVE_CTRL)
	{
		ob_x = ob_x-10.0f;
		ob_angle_y = ob_angle_y-10.0f;

		if (ob_angle_y<-180.0f)
			ob_angle_y = ob_angle_y+360.0f;

	}

	if(key == GLUT_KEY_RIGHT && glutGetModifiers() == GLUT_ACTIVE_CTRL)
	{
		ob_x = ob_x+10.0f;
		ob_angle_y = ob_angle_y+10.0f;

		if (ob_angle_y>360.0f)
			ob_angle_y = ob_angle_y-360.0f;
	}
	     

	if(key == GLUT_KEY_UP && glutGetModifiers() == GLUT_ACTIVE_CTRL)
	{
		ob_y = ob_y+10.0f;
		ob_angle_x = ob_angle_x+10.0f;

		if (ob_angle_x>360.0f)
			ob_angle_x = ob_angle_x-360.0f;
	}

	if(key == GLUT_KEY_DOWN && glutGetModifiers() == GLUT_ACTIVE_CTRL)
	{
		ob_y = ob_y-10.0f;
		ob_angle_x = ob_angle_x-10.0f;

		if (ob_angle_y<-180.0f)
			ob_angle_y = ob_angle_y+360.0f;
	}

	if(key == GLUT_KEY_PAGE_UP)
	{
		ob_angle_z = ob_angle_z+10.0f;

		while(ob_angle_z>360.0f)
			ob_angle_z = ob_angle_z - 360.0f;
	}

	if(key == GLUT_KEY_PAGE_DOWN)
	{
		ob_angle_z = ob_angle_z-10.0f;

		while(ob_angle_z < 0.0f)
			ob_angle_z = ob_angle_z + 360.0f;
	}


   }
 
    
   void TimerFunc(int value)
   {
	  
	



	   
	   //if(time*omega*sqrt(Gr/line)>pi*2)
       //time = time-pi*2/(omega*sqrt(Gr/line));
		 
	   //if (time2>pi*2)
		//	 time2 = time2 -pi*2;

    glutPostRedisplay();
    glutTimerFunc(10, TimerFunc, 1);  // call timerfunc once per 0.005 sec glutTimerFunc(10, TimerFunc, 1)
    time = time+step;	
	      
     /*      j = (time-0.0001)/0.005; 
		  u[0][j] = 5*sin(w*time);          //boundary condition u(0,t)=sin(w*t)
		  u[x_interval][j] = 0;             //boundary condition utt(L,t) = 0;

		 for(int i = 0; i < x_interval ; i++)              //initial condition u(x,0) = 0
		 {
			 u[i][0] = 0;
		 }

		 for(i = 1 ; i < x_interval-1; i++)              // the wave eqution solving
		 {		                       
				 if(j == 0)
				 {
				 }

				 if(j == 1)
				 pde_result(u[i][j], u[i][j-1], u[i-1][j-1], u[i+1][j-1], 0, i);

				 if(j>1)
				 {
					 pde_result(u[i][j], u[i][j-1], u[i-1][j-1], u[i+1][j-1], u[i+1][j-2], i);
				 }	  
		 }


		 for(i = 0; i < x_interval; i++)
		 {
			 ctrlPoints[i][0] = u[i][j];                      // u(x,t)
			 ctrlPoints[i][1] = -i/x_interval*line;            // x
			 ctrlPoints[i][2] = 0;
			 
		 }*/

   }

 

   void changesize2(GLsizei w1,GLsizei h1)
   {
	   if(h1==0)
		   h1=1;

		glViewport(0,0,w1,h1);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if(w1<=h1)
         glOrtho(-40.0f*w1/h1,40.0f*w1/h1,        -100.0f,       2.0f, -1.0, 1.0); //顯示範圍
        else
	     glOrtho(      -40.0f,      40.0f,  -100.0f*h1/w1, 2.0f*h1/w1, -1.0, 1.0);

        glMatrixMode(GL_MODELVIEW);
		glLoadIdentity;
   }

    GLdouble pde_result(GLdouble u11, GLdouble u01, GLdouble u21, GLdouble u10, GLint x)
   {
	   GLdouble temp = 0;
	   GLdouble temp1 = 0;
	   GLdouble temp2 = 0;
	   GLdouble temp3 = 0;
	   GLdouble u12 = 0;

	   temp  = 2*u11*(1/pow(step, 2) - Gr*(line-x*delta_x)/pow(delta_x, 2));
	   temp1 = Gr*u01*((line-x*delta_x)/pow(delta_x, 2) + 0.5/delta_x );
	   temp2 = Gr*u21*((line-x*delta_x)/pow(delta_x, 2) - 0.5/delta_x );
	   temp3 = u10/pow(step, 2);
	   u12 = (temp+temp1+temp2-temp3)*pow(step, 2);
	   return u12;
   }

   void diagramdisplay()
   {
	   glClear(GL_COLOR_BUFFER_BIT);
	     /*glColor3f(0.0f,0.0f,0.0f);   //標示x軸為黑色
		 glLineWidth(1.0f);
		 glBegin(GL_LINES);
		 glVertex3f(0.0f,0.0f,0.0f);
         glVertex3f(2.0f,0.0f,0.0f);
		 glEnd();*/

		 /*glColor3f(0.0f,0.0f,0.0f);   //標示y軸為黑色
		 glLineWidth(1.0f);
		 glBegin(GL_LINES);
		 glVertex3f(0.0f,0.0f,0.0f);
         glVertex3f(0.0f,-10.0f,0.0f);
		 glEnd();*/
         
		 

          //j = (time-0.0001)/0.005;


		 /*for(i = 1; i < 10; i++)           //length calculate
		 {
			 temp1 = ((i)-(i-1))*line/10;                      
			 //delta y 
             temp2 = u[i][j] - u[i-1][j];
			 //delta x
			 temp3 = sqrt(powf(temp1,2)+powf(temp2,2));  
			 //delta length;
			 length = length + temp3;
			 if (length > 10 && length <12)
			 {
				 tencmpoint = i*line/10;
			 }
		 }*/

	     a = (time / step) - 1;
         int i =0;
		 glColor3f(0.0f,0.0f,1.0f);
		 for(i = 0; i < x_interval; i++)
		 {
		 	 glPointSize(5.0f);
			 glBegin(GL_POINTS);
		     glVertex2f(u[i][a],-(i*line)/(x_interval-1));
			 glEnd();
		 }
		 for(i = 0; i < x_interval; i++)
		 {
			 ctrlPoints[i][0] = u[i][a];                      // u(x,t)
			 ctrlPoints[i][1] = -(i*line)/9;                   // x
			 ctrlPoints[i][2] = 0;
			 
		 }

		 /*for(j = 0; j<t_interval-2 ;j++)                  //boundary conition utt(L,t) = 0;
		 {
		   (ctrlPoints[100][j+2] - 2*ctrlPoints[100][j+1] + (ctrlPoints[100][j])/pow(step,2));
		 }*/


		/*glColor3f(1.0f,0.0f,0.0f);
		 glLineWidth(1.0f);
			 glBegin(GL_LINES);
		     glVertex2f(0,0);
			 glVertex2f(0,-10);
			 glEnd();*/

		 
		/*glColor3f(0.0f,0.0f,0.0f);
		 glMap1d(GL_MAP1_VERTEX_3,         //type of data
			     0.0,                     //lower u range
				 100.0,                     //Upper u range
				 3,                        //distance between points in the data
				 30,                        //number of contrl points
				 &ctrlPoints[0][0]);       //address of contrl points*/
         //glPointSize(4.0f);
		 //glColor3f(0.0f,0.0f,1.0f);
		 
		 //glVertex3f(time2,sin(time2),0);
        /*glEnable(GL_MAP1_VERTEX_3);
		 glMapGrid1d(100,0.0,100.0);
		 glEvalMesh1(GL_LINE,0,100);*/


		 glEnd();

		 // Draw control points
		 //glPointSize(5.0f);
		 /*glBegin(GL_POINTS);
		 for(i = 0; i < 10; i++)
		 {
			 glVertex2fv(ctrlPoints[i]);
		 }
		 glEnd();*/

          glutSwapBuffers();
		  glFlush();
   }

   void backgroundset()
   {
	   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   }


int main()
{
	//cout<<" CTRL+ORIENT -> move   the object"<<endl;
	//cout<<" ORIENT      -> evolve the object"<<endl;
    //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//glutCreateWindow("Simple Homonic Motion");
	//glutReshapeFunc(ChangeSize);
	//glutSpecialFunc(SpecialKeyHandler);
	//glutDisplayFunc(RenderScene);
	//glutTimerFunc(500, TimerFunc, 1);
	//SetupRC();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Diagram of Accelation/Velacity versus time");
	glutReshapeFunc(changesize2);
	double b = 0;
		for(int j = 0; j < t_interval; j++)
		 {
		  b = w*j*step;
		  while (b > pi/4)
		  {
            b = b-pi/4;
		  }
			  
		  u[0][j] = 30*cos(wing_output_rad(j*step));//wing_output_rad(GLfloat t1)          //boundary condition u(0,t)=sin(w*t)
		  //u[x_interval-1][j] = 0;             //boundary condition utt(L,t) = 0;
		 }

		 for(int i = 1; i < x_interval ; i++)              //initial condition u(x,0) = 0
		 {
			 u[i][0] = 30*cos(wing_output_rad(0));
		 }

	     for(int j = 1; j < t_interval; j++)
		 {
		  for(int i = 1 ; i < x_interval; i++)              // the wave eqution solving
		  {		                       
				 if(j == 1)
				 {
				 u[i][j] = pde_result(u[i][j-1], u[i-1][j-1], u[i+1][j-1], 30*cos(wing_output_rad(0)), i);
				 }

				 else
				 {
         		 u[i][j] = pde_result(u[i][j-1], u[i-1][j-1], u[i+1][j-1], u[i][j-2], i);
				 }	  
		  }
		 }
	glutDisplayFunc(diagramdisplay);
	glutTimerFunc(10, TimerFunc, 1);
	backgroundset();


	glutMainLoop();
   return 0;
}