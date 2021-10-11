#include "camera.h"
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

int closeMorphological(Mat& image)
{
    // Reading the Image


    // Check if the image is
    // created successfully or not
    if (!image.data) {
        cout << "Could not open or"
             << " find the image\n";

        return 0;
    }
    // Create a structuring element
    Mat element = getStructuringElement(MORPH_RECT,Size(10,10),Point(-1,-1));
    //Mat output;

    // Opening
    morphologyEx(image, image, MORPH_CLOSE, element,Point(-1, -1), 2);

    // Display the image
    //imshow("source", image);
    //imshow("Opening", output);
    //waitKey();

    return 0;
}

Camera::Camera()
{
	m_fps = 30;
}

bool Camera::open(std::string filename)
{
	m_fileName = filename;

	// Convert filename to number if you want to
	// open webcam stream
	std::istringstream iss(filename.c_str());
	int devid;
	bool isOpen;
	if(!(iss >> devid))
	{
		isOpen = m_cap.open(filename.c_str());
	}
	else
	{
		isOpen = m_cap.open(devid);
	}

	if(!isOpen)
	{
		std::cerr << "Unable to open video file." << std::endl;
		return false;
	}

	// set framerate, if unable to read framerate, set it to 30
	m_fps = m_cap.get(CAP_PROP_FPS);
	if(m_fps == 0)
		m_fps = 30;
}

void Camera::play()
{
	// Create main window
	//namedWindow("Video", WINDOW_AUTOSIZE);
	bool isReading = true;
	// Compute time to wait to obtain wanted framerate
	int timeToWait = 1000/m_fps;

	int c=0;

	while(isReading)
	{
		c++;

		// Get frame from stream
		isReading = m_cap.read(m_frame);

		if(isReading)
		{
			// Show frame in main window
			//imshow("Video",m_frame);

			if(c==160){

				Mat original = m_frame.clone();

				//imshow("Source", m_frame);
				int rows = m_frame.rows;
				int cols = m_frame.cols;

				for (int i=cols/3-10;i<=2*cols/3-10;i++)
					for (int j=rows/2;j<rows;j++){
						m_frame.ptr(j,i)[0]=0;
						m_frame.ptr(j,i)[1]=0;
						m_frame.ptr(j,i)[2]=0;
					}

				imshow("Source", m_frame);

				Mat droite = m_frame.clone();
				for (int i=0;i<=cols/2+35;i++)
					for (int j=0;j<rows;j++){
						droite.ptr(j,i)[0]=0;
						droite.ptr(j,i)[1]=0;
						droite.ptr(j,i)[2]=0;
					}

				imshow("droites", droite);

				Mat gauche = m_frame.clone();
				for (int i=cols/2-35;i<=cols;i++)
					for (int j=0;j<rows;j++){
						gauche.ptr(j,i)[0]=0;
						gauche.ptr(j,i)[1]=0;
						gauche.ptr(j,i)[2]=0;
					}

				imshow("gauche", gauche);

				Mat gauche_channel[3];
				split(gauche, gauche_channel);
				imshow("Blue_left", gauche_channel[2]);

				Mat droite_channel[3];
				split(droite, droite_channel);
				imshow("Blue_right", droite_channel[2]);

				Mat gauche_bin,droite_bin,gauche_canny,droite_canny;

				threshold(gauche_channel[2],gauche_bin,220,255,THRESH_BINARY);
				imshow("bin_left",gauche_bin);
				//closeMorphological(gauche_bin);
				//imshow("close_left",gauche_bin);

				Canny(gauche_bin, gauche_canny, 350, 500, 3);
				imshow("gauche_Canny", gauche_canny);

				vector<Vec2f> lines; // will hold the results of the detection
				HoughLines(gauche_canny, lines, 1, CV_PI/180/5, 200, 00,0);

				for( size_t i = 0; i < lines.size(); i++ )
				{
					float rho = lines[i][0], theta = lines[i][1];
					Point pt1, pt2;
					double a = cos(theta), b = sin(theta);
					double x0 = a*rho, y0 = b*rho;
					pt1.x = cvRound(x0 + 1000*(-b));
					pt1.y = cvRound(y0 + 1000*(a));
					pt2.x = cvRound(x0 - 1000*(-b));
					pt2.y = cvRound(y0 - 1000*(a));
					line(original, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);

				}



				threshold(droite_channel[2],droite_bin,195,255,THRESH_BINARY);
				imshow("bin_droite",droite_bin);
				//closeMorphological(gauche_bin);
				//imshow("close_left",gauche_bin);

				Canny(droite_bin, droite_canny, 350, 500, 3);
				imshow("droite_Canny", droite_canny);

				vector<Vec2f> lines2; // will hold the results of the detection
				HoughLines(droite_canny, lines2, 2, CV_PI/180/10, 100, 00,0);

				int lines_tem[lines2.size()] = {0};
				for( size_t i = 0; i < lines2.size(); i++ )
				{
					if (lines_tem[i]==0){
						float rho = lines2[i][0], theta = lines2[i][1];
						for (size_t j=0;j<lines2.size();j++){
							if(abs(lines2[i][0]-lines2[j][0]) < 50 && i!=j){
								lines_tem[j]=1;
							}
						}
						Point pt1, pt2;
						double a = cos(theta), b = sin(theta);
						double x0 = a*rho, y0 = b*rho;
						pt1.x = cvRound(x0 + 1000*(-b));
						pt1.y = cvRound(y0 + 1000*(a));
						pt2.x = cvRound(x0 - 1000*(-b));
						pt2.y = cvRound(y0 - 1000*(a));
						line(original, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
					}
				}

				vector<Vec2f> lines_res;

				imshow("lignes", original);

				waitKey(0);

			}




			/// --------------------------------
		}
		else
		{
			std::cerr << "Unable to read device" << std::endl;
		}

		// If escape key is pressed, quit the program
		if(waitKey(timeToWait)%256 == 27)
		{
			std::cerr << "Stopped by user" << std::endl;
			isReading = false;
		}
	}
}

bool Camera::close()
{
	// Close the stream
	m_cap.release();

	// Close all the windows
	destroyAllWindows();
	usleep(100000);
}
