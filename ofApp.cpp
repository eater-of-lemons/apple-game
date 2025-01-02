#include "ofApp.h"
#include "ofxCv.h"
#include <time.h>

using namespace std;
using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
//    sets up background, webcam feed, cascade model, and point system

    ofBackground(0, 0, 0);
    
    camGrabber.setVerbose(true);
    camGrabber.setup(1280, 720);
    camImage.allocate(camGrabber.getWidth(), camGrabber.getHeight(), OF_IMAGE_COLOR);
        
    if(!face_cascade.load("/Users/nisan.harmanci/Downloads/haarcascade_frontalface_default.xml")){
        cout<<"Error loading"<<endl;
    } else {
        cout<<"Loaded succesfully"<<endl;
    }
    
    appleImage.load("apple.png");
    appleImage.resize(APPLE_WIDTH, APPLE_HEIGHT);
    
    trashImage.load("applecore.png");
    trashImage.resize(TRASH_WIDTH, TRASH_HEIGHT);
    
    biteSound.load("biteSound.mp3");
    winSound.load("winSound.mp3");
    loseSound.load("loseSound.mp3");
    
    biteSound.setMultiPlay(true);
    winSound.setMultiPlay(true);
    loseSound.setMultiPlay(true);
    
    gameOn = true;
    elapsedTime = 0.0f;
}

//--------------------------------------------------------------
void ofApp::update(){
//    updates webcam feed by fetching each new frame and checking 1) for faces and 2) if face is eating apple/trash 3) if score is out of boundss
    
    camGrabber.update();
        
    if (camGrabber.isFrameNew()){
        camImage.setFromPixels(camGrabber.getPixels());
        camMat = toCv(camImage);
        cvtColor(camMat, grayCamMat, COLOR_BGR2GRAY);
        
        faces.clear();
        
        face_cascade.detectMultiScale(grayCamMat, faces, 1.1, 5, 0|CASCADE_SCALE_IMAGE, cv::Size(30, 30));
        checkFaces();
    }
        
    if (score <= -3 or score >= 10) {
        gameOn = false;
    }

//    for testing:
    cout << "detected " << faces.size() << " faces" << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
//    draws each frame from webcam and while player is playing, indicate faces found on feed
    
    camImage.draw(0, 0);
    
    if (gameOn){
        appleImage.draw(appleX, appleY);
        trashImage.draw(trashX, trashY);
        
        for (int i = 0; i < faces.size(); i++) {
            ofNoFill();
            ofSetColor(0, 255, 0);
            ofDrawRectangle(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
        }

        ofSetColor(255);
        ofDrawBitmapString("Score: " + ofToString(score), 10, 20);
        ofDrawBitmapString("Press any key to reset objects", 10, 60);
        
        elapsedTime += ofGetLastFrameTime();
    }else{
        if(score<0){
            ofDrawBitmapString("You Lose!", 10, 20);
            loseSound.play();
        }else{
            ofDrawBitmapString("You Win!", 10, 20);
            winSound.play();
        }
    }
    
    int sec = static_cast<int>(elapsedTime);
    int min = sec / 60;
    sec %= 60;
    ofDrawBitmapString("Time: " + ofToString(min) + ":" + ofToString(sec), 10, 40);

    ofSetColor(255);
}
//--------------------------------------------------------------
void ofApp::changeApplePos() {
//    custom function to andomise the next position of the apple
    appleX = rand() % (WINDOW_WIDTH - APPLE_WIDTH + 1);
    appleY = rand() % (WINDOW_HEIGHT - APPLE_HEIGHT + 1);
}
//--------------------------------------------------------------
void ofApp::changeTrashPos() {
//    custom function to randomise the next position of the trash
    trashX = rand() % (WINDOW_WIDTH - TRASH_WIDTH + 1);
    trashY = rand() % (WINDOW_HEIGHT - TRASH_HEIGHT + 1);
}
//--------------------------------------------------------------
void ofApp::checkFaces(){
//    custom function to check if face is behind and 'eating' the apple or trash, increase or decrease score accordingly
    
    for (int i = 0; i < faces.size(); ++i){
        const cv::Rect& face = faces[i];
        if (isEaten(face, appleX, appleY, APPLE_WIDTH, APPLE_HEIGHT)){
            biteSound.play();
            changeApplePos();
            changeTrashPos();
            score++;
            break;
        }
        if (isEaten(face, trashX, trashY, TRASH_WIDTH, TRASH_HEIGHT)){
            biteSound.play();
            changeTrashPos();
            changeApplePos();
            score--;
            break;
        }
    }
}
//--------------------------------------------------------------
bool ofApp::isEaten(const cv::Rect& face, int objectX, int objectY, int objectW, int objectH){
//    custom function to check if the apple/trash is well within the boundaries of a face (AKA the centre) and return if object (apple/trash) is actually 'eaten'
    
    int centerX = face.x + 2 * (face.width / 3);
    int centerY = face.y + 2 *(face.height / 3);

    return ((centerX >= objectX && centerX <= (objectX + objectW)) && (centerY >= objectY && centerY <= (objectY + objectH)));
}
//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//    restarts any badly aligned objects by re-randomising positions
    
    changeApplePos();
    changeTrashPos();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
