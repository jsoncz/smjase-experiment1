#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){

    width = (float)(3*128) / bands;
	ofBackground(10,32,25);
	ofEnableDepthTest();
	ofSetVerticalSync(true);
	ofEnableLighting();
	ofEnableSmoothing();
	ofEnableDepthTest();
	cam.setFov(60);
	cam.setNearClip(1);
	cam.setFarClip(200);	
	song.load("song.mp3");
	song.play();

}

//--------------------------------------------------------------
void ofApp::update(){
  ofSoundUpdate();
      float * value = ofSoundGetSpectrum(bands);
      for (int i = 0; i < bands; i++){
          fftSmooth[i] *= 0.9f;
          if (fftSmooth[i] < value[i]){
              fftSmooth[i] = value[i];
          }
      }
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
	
	ofSetColor(255, 0, 0);
	ofDrawSphere(ofVec3f(0, 0, 0), 1);
	ofMesh m;	
	//cam.disableMouseInput();
	ofEnableAlphaBlending();  
	float time = ofGetElapsedTimef();

    for (int i = 0;i < bands; i++){
	
 	ofSetColor(250 * sin(i * 0.004 + time),
        5  * sin(i * 0.031 * time),
        180 * sin(i * 0.032 + time));
 	ofNoFill();
	ofSetLineWidth(2.5);
        ofDrawBox(10*fftSmooth[i],width,fftSmooth[i] * 130);    
        ofSetLineWidth(1);
        ofDrawBox(3*fftSmooth[i], time*fftSmooth[i], width*10);
        ofSetLineWidth(.2);
        ofDrawBox(2*fftSmooth[i], time, width*100);
    	//ROTATION CAMERA	
         cam.rotate(fftSmooth[i]/2, cam.getSideDir());  
    	//m.rotate(fftSmooth[i]/2, cam.getUpDir());  
        ofNoFill();
        m.setMode(OF_PRIMITIVE_LINE_LOOP);
	//DRAW SPHERE
	for(int j=0; j<175; j++){
			
		float x = sin( 0.707  * fftSmooth[i]*6);
		float z = cos( j * DEG_TO_RAD ) * time; // shift the ring
			
		m.addVertex( ofVec3f(x, z, 0));
	}
	m.draw();		
	//SET DISTANCE
	cam.setDistance(7*song.getPosition()/4);
	ofSetLineWidth(2);
        ofSetColor(100,
                   220  * sin(i * 0.08 * fftSmooth[i]),
                   100 * sin(i * 0.025 + fftSmooth[i]));
       
        ofFill();
        float rot = 0.5 * ofGetFrameNum(); // ofRotate takes degrees
		ofTranslate(0, 0, fftSmooth[i]);//draw sphere and ring at (0, 0, -100)
		ofRotateX(rot); // draw them with rotation
      //  cam.pan(time /  fftSmooth[i]);
		ofDrawBox(fftSmooth[i]*10, 20*fftSmooth[i], 10);
		ofSetLineWidth(0.5);
		
		ofSetColor(200 * sin(i * 0.002 + time * fftSmooth[i]),
	                    sin(i * 0.001 * fftSmooth[i]),
	                   10* sin(i * 0.004 + time));

		ofNoFill();
		ofSetLineWidth(2.5);
		ofDrawBox(2*fftSmooth[i], time * fftSmooth[i]/2,10);
	 
    }
	   

	cam.end();
	
ofDisableLighting();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
		case '1': song.load("song.mp3");
			song.play();
			break;
		case '2': song.load("song2.mp3");
			song.play();
			break;
		case '3': song.load("song3.mp3");
			song.play();
			break;
		case '4': song.load("song4.mp3");
			song.play();
			break;
	}	
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
	song.stop();
	song.load(dragInfo.files[0]);
	song.play();
}
