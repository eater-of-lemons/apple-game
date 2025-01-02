#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
    
//    custom functions and variables and constants below for game logic and better designed software
    
        void changeApplePos();
        void changeTrashPos();
    
        void checkFaces();
        bool isEaten(const cv::Rect& face, int objectX, int objectY, int objectW, int objectH);
    
        ofVideoGrabber camGrabber;
        ofImage camImage;
        Mat camMat;
        Mat grayCamMat;
    
        CascadeClassifier face_cascade;
        vector<cv::Rect> faces;
    
        ofImage appleImage;
        const int APPLE_WIDTH = 150;
        const int APPLE_HEIGHT = 100;
        int appleX;
        int appleY;

        ofImage trashImage;
        const int TRASH_WIDTH = 150;
        const int TRASH_HEIGHT = 100;
        int trashX;
        int trashY;

        const int WINDOW_WIDTH = 1280;
        const int WINDOW_HEIGHT = 720;

        int score = 0;
        bool gameOn;
        float elapsedTime;
        ofSoundPlayer biteSound;
        ofSoundPlayer winSound;
        ofSoundPlayer loseSound;
    
//    deprecated:
//        ofxPanel gui;
//        ofxIntSlider brushSize;
};
