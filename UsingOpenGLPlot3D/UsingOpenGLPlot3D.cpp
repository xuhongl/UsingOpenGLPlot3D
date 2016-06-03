#include <GL/glut.h>
#include <fstream>
#include<GL/gl.h>
#include<GL/glu.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glfw3.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <complex>
#include <iostream>
using namespace std;
 
bool plot = true;


float normal_vector[512][3];
//int XCrossValue[4096];
int FFT_InputArray[512];


//This function is used to calculate the x coordinates of the normal vector
//in order to better visulization, the normal vector is normalized to 100 pixel longitude
float NormalVector0(float x1, float y1, float z1, float x2, float y2, float z2)
{
	int multiple = 100;
	float normal[3];

	normal[0] = y1*z2 - z1*y2;
	normal[1] = z1*x2 - x1*z2;
	normal[2] = x1*y2 - y1*x2;

	normal[0] = multiple*normal[0] / sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
	normal[1] = multiple*normal[1] / sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
	normal[2] = multiple*normal[2] / sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);

	return normal[0];

	
}
//This function is used to calculate the y coordinates of the normal vector
float NormalVector1(float x1, float y1, float z1, float x2, float y2, float z2)
{
	int multiple = 100;
	float normal[3];

	normal[0] = y1*z2 - z1*y2;
	normal[1] = z1*x2 - x1*z2;
	normal[2] = x1*y2 - y1*x2;

	normal[0] = multiple*normal[0] / sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
	normal[1] = multiple*normal[1] / sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
	normal[2] = multiple*normal[2] / sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);

	return normal[1];


}

//This function is used to calculate the z coordinates of the normal vector
float NormalVector2(float x1, float y1, float z1, float x2, float y2, float z2)
{
	int multiple = 100;
	float normal[3];

	normal[0] = y1*z2 - z1*y2;
	normal[1] = z1*x2 - x1*z2;
	normal[2] = x1*y2 - y1*x2;

	normal[0] = multiple*normal[0] / sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
	normal[1] = multiple*normal[1] / sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
	normal[2] = multiple*normal[2] / sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);

	return normal[2];



}

//This function is used to adjust the Normal Vector Sphere visulization
void reshape(int w, int h)
{
	glViewport(0, 0, 500, 500);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, (GLfloat)(500 / 500), -500.0, 500.0);//the first parameter in this function can be used to "see" the object closly or farly
	glMatrixMode(GL_MODELVIEW);

	//this section is used to show x cross-sections-----
	//glViewport(0, 0, 500, 1000);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0, 500, 0, 1000, 0, -1 * 4500);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//--------------------------------------------------

}


//This function is used to reconstruct the 3D environment for the normal vector sphere
void renderScene(void)
{
	glLoadIdentity();
	gluLookAt(700.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glBegin(GL_LINES);// z axis is blue
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 600);
	glEnd();

	glBegin(GL_LINES);// y axis is green
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, 0);
	//glVertex3f(0, 600, 0);
	glVertex3f(0, 500, 0);
	glEnd();

	glBegin(GL_LINES);// x axis is red
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0);
	//glVertex3f(600, 0, 0);
	glVertex3f(300, 0, 0);
	glEnd();



	for (int i = 0; i < 256; i++)
	{
		glColor3f(1.0, 0.0, 1.0);
		glLineWidth(2.0f);

		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(normal_vector[i][0], normal_vector[i][1], normal_vector[i][2]);
		glEnd();
	}


	//this sections is used to draw X axis cross-sections---------------------
	//glClearColor(1.0, 1.0, 1.0, 0.0);
	//glClearDepth(1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glBegin(GL_LINES);// y axis is green
	//glColor3f(0.0, 1.0, 0.0);
	//glVertex3f(0, 0, 0);
	//glVertex3f(0, 500, 0);
	//glEnd();

	//glBegin(GL_LINES);// x axis is red
	//glColor3f(1.0, 0.0, 0.0);
	//glVertex3f(0, 0, 0);
	//glVertex3f(300, 0, 0);
	//glEnd();

	//glColor3f(0.0, 0.0, 0.0);
	//glBegin(GL_LINES);
	//glVertex3f(199, 0, 0);
	//glVertex3f(200, XCrossValue[0], 0);
	//glEnd();

	//for (int i = 0; i < 4096; i++)
	//{
	//		

	//		if (XCrossValue[i + 1] == 0) break;
	//		glBegin(GL_LINES);

	//		glVertex3f(i+200, XCrossValue[i], 0);
	//		glVertex3f(i+201, XCrossValue[i+1], 0);
	//		glEnd();


	//		
	//}
	//------------------------------------------------------


	glFlush();

}


//the 3D environment set up for plotting those 3d point cloud
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}



int main(int argc, char *argv[])
{

	ifstream depthDataFile;
	depthDataFile.open("OneFrame.txt");

	//open the txt file and read the depth data into an array 
	int temporary[217088];

	if (depthDataFile.is_open())
	{

		for (long i = 0; i < 217088; i++)
		{
			long a;
			depthDataFile >> a;
			temporary[i] = a;
		}
	}

	//// do the 3*3 median filter~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//typedef int element;
	//int M = 424;
	//int N = 512;


	////   Allocate memory for signal extension
	//element* extension = new element[(N + 2) * (M + 2)];

	////   Create image extension
	//for (int i = 0; i < M; ++i)
	//{
	//	memcpy(extension + (N + 2) * (i + 1) + 1, temporary + N * i, N * sizeof(element));
	//	extension[(N + 2) * (i + 1)] = temporary[N * i];
	//	extension[(N + 2) * (i + 2) - 1] = temporary[N * (i + 1) - 1];
	//}

	////   Fill first line of image extension
	//memcpy(extension, extension + N + 2, (N + 2) * sizeof(element));

	////   Fill last line of image extension
	//memcpy(extension + (N + 2) * (M + 1), extension + (N + 2) * M, (N + 2) * sizeof(element));

	////   Call median filter implementation
	//M = M + 2;
	//N = N + 2;
	//for (int m = 1; m < M - 1; ++m)
	//	for (int n = 1; n < N - 1; ++n)
	//	{
	//		//   Pick up window elements
	//		int k = 0;
	//		element  window[9];
	//		for (int j = m - 1; j < m + 2; ++j)
	//			for (int i = n - 1; i < n + 2; ++i)
	//				window[k++] = extension[j * N + i];
	//		//   Order elements (only half of them)
	//		for (int j = 0; j < 5; ++j)
	//		{
	//			//   Find position of minimum element
	//			int min = j;
	//			for (int l = j + 1; l < 9; ++l)
	//				if (window[l] < window[min])
	//					min = l;
	//			//   Put found minimum element in its place
	//			const element  temp = window[j];
	//			window[j] = window[min];
	//			window[min] = temp;
	//		}
	//		//   Get result - the middle element
	//		temporary[(m - 1) * (N - 2) + n - 1] = window[4];
	//	}

	////   Free memory
	//delete[] extension;
	
	//Using threshold and average filter~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//for (int i = 0; i < 424; i++)
	//{
	//	for (int j = 0; j < 512; j++)
	//	{
	//		if ((2500 - temporary[i * 512 + j] <= 140) || (2500 - temporary[i * 512 + j] >= 330)) //140z&330 is the parameter for original "one frame"
	//		{
	//			temporary[i * 512 + j] = temporary[i * 512 + j - 1] + temporary[i * 512 + j] + temporary[i * 512 + j + 1] + temporary[i * 512 + j - 1 + 512] + temporary[i * 512 + j + 512] + temporary[i * 512 + j + 1 + 512] + temporary[i * 512 + j - 1-512] + temporary[i * 512 + j-512] + temporary[i * 512 + j + 1-512];
	//			temporary[i * 512 + j] = temporary[i * 512 + j] / 9;
	//		}
	//	}
	//}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	//from now on, we start to plot these 3D points in space
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(800, 600, "3D SURFACE", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);


	while (!glfwWindowShouldClose(window))
	{

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, 800, 600);

		glClearDepth(0.0f);
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);

		glLoadIdentity();
		//gluLookAt(0.0, 0.0, 1500.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //use to see the cross-sections
		//gluLookAt(1200.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	    gluLookAt(700.0, 700.0, 1000.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//use to see the whole

		
		// draw the x-y-z axis
		//glLineWidth(3.0f);
		glBegin(GL_LINES);// z axis is blue
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 600);
		glEnd();

		//glBegin(GL_LINES);
		//glColor3f(0.0, 0.0, 1.0);
		//glVertex3f(0, 400, 0);
		//glVertex3f(0, 400, 100);
		//glEnd();

		glBegin(GL_LINES);// y axis is green
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 600, 0);
		glEnd();

		//glBegin(GL_LINES);// y axis is green
		//glColor3f(0.0, 1.0, 0.0);
		//glVertex3f(0, 400, 0);
		//glVertex3f(0, 300, 0);
		//glEnd();

		glBegin(GL_LINES);// x axis is red
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0, 0, 0);
		glVertex3f(600, 0, 0);
		glEnd();

		//glBegin(GL_LINES);// x axis is red
		//glColor3f(1.0, 0.0, 0.0);
		//glVertex3f(0, 400, 0);
		//glVertex3f(100, 400, 0);
		//glEnd();
		//glLineWidth(1.0f);

		//glBegin(GL_LINE_LOOP);
		//glColor3f(0.0, 0.0, 0.0);
		//glVertex3f(0, 100, 0);
		//glVertex3f(0, 100, 300);
		//glVertex3f(400, 100, 300);
		//glVertex3f(400, 100, 0);
		//glEnd();
		
		float x, y, z;

//画出整个切吧切吧的体系~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//for (int i = 0; i < 500; i += 16){
		////for (int i = 0; i < 500; i++){

		//	if (i == 240||i==336){
		//	//if (i == 170 ){
		//		glLineWidth(3.0f);


		//		glBegin(GL_LINES);
		//		glColor3f(0.0, 1.0, 0.0);
		//		glVertex3f(i, 0, 0);
		//		glVertex3f(i, 500, 0);
		//		glEnd();

		//		glBegin(GL_LINES);
		//		glVertex3f(i, 500, 0);
		//		glVertex3f(i, 500, 500);
		//		glEnd();

		//		glBegin(GL_LINES);
		//		glVertex3f(i, 500, 500);
		//		glVertex3f(i, 0, 500);
		//		glEnd();

		//		glBegin(GL_LINES);
		//		glVertex3f(i, 0, 0);
		//		glVertex3f(i, 0, 500);
		//		glEnd();
		//	}
		//	else {
		//		glLineWidth(1.0f);
		//	}

		//	
		//}

		//for (int i = 0; i < 500; i += 16){
		//	
		//	if (i == 240 || i == 336){
		//		glLineWidth(3.0f);
		//		glBegin(GL_LINES);
		//		glColor3f(1.0, 0.0, 0.0);
		//		glVertex3f(0, 0, i);
		//		glVertex3f(500, 0, i);
		//		glVertex3f(500, 500, i);
		//		glVertex3f(0, 500, i);
		//		glEnd();

		//		glBegin(GL_LINES);
		//		glVertex3f(500, 0, i);
		//		glVertex3f(500, 500, i);
		//		glEnd();

		//		glBegin(GL_LINES);
		//		glVertex3f(500, 500, i);
		//		glVertex3f(0, 500, i);
		//		glEnd();

		//		glBegin(GL_LINES);
		//		glVertex3f(0, 0, i);
		//		glVertex3f(0, 500, i);
		//		glEnd();
		//	}
		//	else {
		//		glLineWidth(1.0f);
		//	}



		//}
//画完~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		int t[424];
		int j = 256;
		for (int i = 0; i < 424; i++)
		{
			t[i] = (2500-temporary[i * 512 + j])/2;
		}

		for (int i = 0; i < 424; i++)
		{
			//if (t[i] < 120)
			//{
			//	t[i] += 20;
			//}

			//t[i] = t[i] - 20;

			if ((t[i] <70) || (t[i]>165))
			{
				t[i] = 0;
			}
		}

		//ofstream Signal;
		//Signal.open("Signal.txt", ios::app);

		//if (Signal.is_open())
		//{

		//	Signal << "File Opened successfully!!!. Writing data from array to file" << endl;

		//	for (long i = 0; i < 512; i++)
		//	{
		//		Signal << t[i]; //writing ith character of array in the file
		//		Signal << " ";
		//	}
		//	Signal << "Array data successfully saved into the file test.txt" << endl;
		//}


		for (int i = 0; i < 424; i++)
		{
			if ((t[i] != 0) && (t[i + 1] != 0))
			{
				glBegin(GL_LINES);
				glColor3f(1.0, 0.0, 0.0);
				glVertex3f(i, t[i], 0);
				glVertex3f(i+1, t[i + 1], 0);
				glEnd();

			}
		}

		//for (int j = 0; j < 512; j+=4)
		//{
		//	if ((t[j] != 0) && (t[j + 1] != 0))
		//	{
		//		glBegin(GL_LINES);
		//		glColor3f(0.0, 0.0, 0.0);
		//		glVertex3f(0, t[j+4], j);
		//		glVertex3f(0, t[j + 4]+4, j + 4+t[j]-t[j+4]);
		//		glEnd();

		//	}
		//}

		int count = 0;

		int k = 4;
		for (int i = 0; i < 424; i++)   		
		//int i = 208;
		{
			//int j = 256;
			for (int j = 0; j < 512; j++) 
			{
				
				//since the depth data is the distance between the pixel and the kinect infrared sensor
				// we used a constant to substract the depth data and get the height of the laying down human body
				//float vairaible0 =  temporary[i * 512 + j];

				float vairaible = (2500-temporary[i * 512 + j])/2;
				float vairaible2 = (2500-temporary[i * 512 +1+ j])/2; //要取和Y轴平行的横截面，直接加512


				//we use this to pick the appropriate value for cross-section along x axis/y axis
				if ((vairaible <= 70) || (vairaible >= 165))    //SIDE 200-420//supine 70-165
				{
					vairaible = 0;
				}

				if ((vairaible2 <= 70) || (vairaible2 >= 165))
				{
					vairaible2 = 0;
				}
    

				//the if() function is used to draw the projection of the 3D points into a 2D plane
	
				if ((vairaible != 0) && (vairaible2 != 0))
				{


					//glBegin(GL_LINES);
					//glColor3f(0.0, 1.0, 0.0);
					//glVertex3f(0, vairaible, j);
					//glVertex3f(0, vairaible2, j +=k);
					//glEnd();

					//glBegin(GL_LINES);
					//glColor3f(0.0, 0.0, 0.0);
					//glVertex3f(0, vairaible2, j += 4);
					//glVertex3f(0, vairaible2 + 4, j + 4 + (vairaible - vairaible2));
					//glEnd();

					count++;
					 // glScalef(1.0, 1.0, 1.0);
						//glBegin(GL_LINES);
						//glColor3f(1.0, 0.0, 0.0);
						//glVertex3f(i, vairaible, 0);
						//glVertex3f(i+4, vairaible2, 0);
						//glEnd();

						if ((count % 4) == 0)
						{
							//glPushMatrix();
							////glLoadIdentity();
							////glTranslatef(i + 1, vairaible2,0);
							//glRotatef(90.0, 0, 0, 1);
							//glTranslatef(vairaible2-i, -i-1-vairaible, 0);
							//glBegin(GL_LINES);
							//glColor3f(0.0, 0.0, 0.0);
							//glVertex3f(i, vairaible, 0);
							//glVertex3f(1.05*(i + 1), 1.05*(vairaible2), 0);
							//glEnd();
							//glPopMatrix();

							//glPushMatrix();
							//glScalef(1.1,1.1,0.0);

								/*glBegin(GL_LINES);
								glColor3f(0.0, 0.0, 0.0);
								glVertex3f(i + 4, vairaible2, 0);
								glVertex3f(i + 4 + 2*(vairaible - vairaible2), vairaible2 + 8, 0);
								glEnd();*/


							//glPopMatrix();
						}

			



					//--------------------------------------------draw 3 projections 
					x = i;
					y = vairaible;
					z = j;


					glBegin(GL_POINTS);
					float val = temporary[i * 512 + j] % 255 * 1.0 / 255;
					glColor3f(val, val, val);
					//glVertex3f(x, 0, z);//draw its projection onto the x-z plane
					glEnd();

					glBegin(GL_POINTS);
					glColor3f(0.0, 1.0, 0.0);
					//glVertex3f(0, y, z);//draw its projection onto the y-z plane
					glEnd();

					
					if (i == 208)
					{
						glBegin(GL_POINTS);
						glColor3f(0.0, 1.0, 0.0);
						glVertex3f(0, y, z);//draw its projection onto the y-z plane
						glEnd();
					}


				}

			}
		}

    //            glBegin(GL_LINES);
		  //      glColor3f(1.0, 0.0, 0.0);
				//glVertex3f(100, 100, 0);
				//glVertex3f(200, 200, 0);
				//glEnd();
				//
				//glPushMatrix();
				////glTranslatef(100, 100, 0);
				//glRotatef(90,0,0,1);
				//glTranslatef(100,-300,0);
				//glBegin(GL_LINES);
				//glColor3f(0.0,1.0,0.0);
				//glVertex3f(0,500,0);
				//glVertex3f(0, 0, 0);
				//glEnd();
				//glBegin(GL_LINES);
				//glVertex3f(100,100,0);
				//glVertex3f(200,200, 0);
				//glEnd();
				//glPopMatrix();

				//glBegin(GL_LINES);
				//glColor3f(0.0,0.0,1.0);
				//glVertex3f(200,200,0);
				//glVertex3f(100,300,0);
				//glEnd();


		//-------------------------存数-------------------------------------------
		//long count = 0;

		//int i = 128;
		//for (int j = 0; j < 512; j++)
		//	{
		//		int vairaible = (2500 - temporary[i * 512 + j]) / 2;

		//		if ((vairaible <= 100) || (vairaible >= 400))    //SIDE 200-420//supine 70-165
		//		{
		//			vairaible = 0;
		//		}
		//
		//			FFT_InputArray[count] = vairaible;
		//			count++;
		//		
		//	}


		//char filename[] = "fft.txt"; // 此处写入文件名 
		//ofstream fout(filename);
		//for (int i = 0; i < 512;i++)
		//{
		//	cout << FFT_InputArray[i]<<" ";
		//}

//----------------------------------------------------------------------------------------------------------

		int k1 = 4;
		//This for() function is used to draw these 3D points in different way
		//for (int i = 0; i < 424; i +=k)
		int i = 208;
		{
			for (int j = 0; j < 512; j +=k)
			//int j = 256;
			{

				//get the four vertex value
				float vairaible = (2500-temporary[i * 512 + j])/2;
				float vairaible2 = (2500-temporary[i * 512 + j + k])/2;
				float vairaible3 = (2500-temporary[(i + k) * 512 + j + k])/2;
				float vairaible4 = (2500 - temporary[(i + k) * 512 + j])/2;

				//filter out the outliers
				if ((vairaible <= 0) || (vairaible >= 200))  //supine set from 50-200, minus by 2500 then/2
				{                                               //side sleep 250-1000
					vairaible = 0;
				}

				if ((vairaible2 <= 0) || (vairaible2 >= 200))
				{
					vairaible2 = 0;
				}

				if ((vairaible3 <= 0) || (vairaible3 >= 200))
				{
					vairaible3 = 0;
				}

				if ((vairaible4 <= 0) || (vairaible4 >= 200))
				{
					vairaible4 = 0;
				}

				float VairaibleAverage = (vairaible + vairaible2 + vairaible3 + vairaible4) / 4;

				if ((vairaible != 0) && (vairaible2 != 0) && (vairaible3 != 0) && (vairaible4 != 0))
				{

					x = i;
					y = 0;
					z = j;


					//if we dont't add a ! in front of the "plot", we can get the results of 3d points
					//get average square surface
					if (!plot)
					{
						glBegin(GL_POINTS);	
						glColor3f(0.0, 0.0, 0.0);
						glVertex3f(x, vairaible, z);
						glEnd();
						
					}

					//if we dont't add a ! in front of the "plot", we can get the results of the cross sections
					//get average square surface
					if (!plot)
					{
						glBegin(GL_LINES);
						glVertex3f(x, VairaibleAverage, z);
						glVertex3f(x + k, VairaibleAverage, z);
						glEnd();

						glBegin(GL_LINES);
						glVertex3f(x, VairaibleAverage, z + k);
						glVertex3f(x + k, VairaibleAverage, z + k);
						glEnd();
					}

					//if we dont't add a ! in front of the "plot", we can get the results of the square surface
					//get average square surface
					if (!plot)
					{
						glBegin(GL_LINE_LOOP);
						glVertex3f(x, VairaibleAverage, z);
						glVertex3f(x, VairaibleAverage, z + k);
						glVertex3f(x + k, VairaibleAverage, z + k);
						glVertex3f(x + k, VairaibleAverage, z);
						glEnd();
					}

					//if we dont't add a ! in front of the "plot", we can get the results of the original (four vertex have different value)square surface
					//get original square surface
					if (!plot)
					{
						glBegin(GL_LINE_LOOP);
						glVertex3f(x, vairaible, z);
						glVertex3f(x, vairaible2, z + k);
						glVertex3f(x + k, vairaible3, z + k);
						glVertex3f(x + k, vairaible4, z);
						glEnd();
					}

					//if we dont't add a ! in front of the "plot", we can get the height ploting 
					//plot height or not
					if (!plot)
					{

						glBegin(GL_LINES);
						glColor3f(0.5, 0.0, 0.0);
						glVertex3f(x, vairaible, z);
						glVertex3f(x, 0, z);
						glEnd();

						glBegin(GL_LINES);
						glColor3f(0.5, 0.0, 0.0);
						glVertex3f(x, vairaible2, z + k);
						glVertex3f(x, 0, z + k);
						glEnd();
					}

					
					//if we dont't add a ! in front of the "plot", we can get the results of the triangle surface
					//get triangle surface and fin surface normals
					if (plot)
					{
						//if (j == 256){ glColor3f(0.0, 0.0, 0.0); }
						//else { glColor3f(0.0, 0.0, 0.0); }

						//if (i == 208)
						{
						float x1, x2, y1, y2, z1, z2;
		
						glBegin(GL_LINE_LOOP);
						glColor3f(0.0, 0.0, 0.0);
						glVertex3f(x, vairaible, z);
						glVertex3f(x, vairaible2, z + k);
						glVertex3f(x + k, vairaible3, z + k);
						glEnd();

						x1 = 0;
						y1 = vairaible2 - vairaible;
						z1 = k;

						x2 = -k;
						y2 = vairaible2 - vairaible3;
						z2 = 0;

						
							//normal_vector[j][0] = NormalVector0(x1, y1, z1, x2, y2, z2);
							//normal_vector[j][1] = NormalVector1(x1, y1, z1, x2, y2, z2);
							//normal_vector[j][2] = NormalVector2(x1, y1, z1, x2, y2, z2);
						

						glBegin(GL_LINE_LOOP);
						glColor3f(0.0, 0.0, 0.0);
						glVertex3f(x, vairaible2, z + k);
						glVertex3f(x + k, vairaible3, z + k);
						glVertex3f(x + k, vairaible4, z);
						glEnd();

						x1 = k;
						y1 = vairaible3 - vairaible2;
						z1 = 0;
						x2 = 0;
						y2 = vairaible3 - vairaible4;
						z2 = k;

						}

							//normal_vector[j + 1][0] = NormalVector0(x1, y1, z1, x2, y2, z2);
							//normal_vector[j + 1][1] = NormalVector1(x1, y1, z1, x2, y2, z2);
							//normal_vector[j + 1][2] = NormalVector2(x1, y1, z1, x2, y2, z2);


					}


				
				}


				

			}
		}


		
		//adjust the view for the 3d point cloud environment
		glViewport(0, 0, 1024, 848);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(15, (GLfloat)(512 / 424), -100.0, 500.0);//the first parameter in this function can be used to "see" the object closly or farly
		glMatrixMode(GL_MODELVIEW);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


    // this section of code use function we wrote before to draw the normal sphere
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(500, 500);
	glutCreateWindow("NORMAL SPHERE");
	//glutCreateWindow("X-Axis Cross-Section");
	glClearDepth(0.0f);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);

	glutMainLoop();



	//return 0;
}