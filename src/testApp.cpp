#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofRegisterURLNotification(this);
    url_Stations = "http://appservices.citibikenyc.com/data2/stations.php";
    url_Update = "http://appservices.citibikenyc.com/data2/stations.php?updateOnly=true";
    ofLoadURLAsync(url_Update, "update");
    ofLoadURLAsync(url_Stations, "stations");
    lastUpdate = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void testApp::update(){
    worldTime = ofGetElapsedTimef();
    if(worldTime - lastUpdate > 4){
        lastUpdate = ofGetElapsedTimef();
        cout<<"update Stations"<<endl;
        ofLoadURLAsync(url_Update, "update");
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
}

void testApp::urlResponse(ofHttpResponse & response){
    if(response.status < 300){
        if(response.request.name == "update"){
            parseUpdates(ofToString(response.data));
        }
        if(response.request.name == "stations"){
            parseStations(ofToString(response.data));
        }
    }
}


void testApp::parseStations(string json){
    if(stations.parse(json)){
        //cout<<json<<endl;
        ofxJSONElement data = stations["results"];
        //cout<<data.size()<<endl;
        for(int i = 0; i < data.size(); i++){
            ofxJSONElement row = data[i];
            station foo;
            foo.name = row["id"].asInt();
            foo.lon = row["longitude"].asDouble();
            foo.lat = row["latitude"].asDouble();
            
            cout<<foo.name<<endl;
            cout<<foo.lat<<endl;
            cout<<foo.lon<<endl;
            
            stationMap[foo.name] = foo;
            
            stationIds.push_back(foo.name);
        }
        
    }else{
        
    }
}

void testApp::parseUpdates(string json){
    if(updates.parse(json)){
        //cout<<json<<endl;
        //{"id":116,"status":"Active","availableBikes":7,"availableDocks":31}
        ofxJSONElement data = updates["results"];
        for(int i = 0; i < data.size(); i++){
            station & foo = stationMap[data[i]["id"].asInt()];
            foo.bikeCount = data[i]["availableBikes"].asInt();
            foo.slotCount = data[i]["availableDocks"].asInt();
        }
    }else{
        
    }
}



//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}