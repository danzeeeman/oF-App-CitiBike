#include "testApp.h"


//latitude    = 41.145556; // (φ)
//longitude   = -73.995;   // (λ)
//
//mapWidth    = 200;
//mapHeight   = 100;
//
//// get x value
//x = (mapWidth*(180+longitude)/360)%mapWidth+(mapWidth/2);
//
//// convert from degrees to radians
//latRad = latitude*PI/180;
//
//// get y value
//mercN = log(tan((PI/4)+(latRad/2)));
//y     = (mapHeight/2)-(mapWidth*mercN/(2*PI));
//
//

//$mapLonLeft = 9.8;
//$mapLonRight = 10.2;
//$mapLonDelta = $mapLonRight - $mapLonLeft;
//
//$mapLatBottom = 53.45;
//$mapLatBottomDegree = $mapLatBottom * M_PI / 180;


//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofRegisterURLNotification(this);
    //ofSetBackgroundAuto(false);
    url_Stations = "http://appservices.citibikenyc.com/data2/stations.php";
    url_Update = "http://appservices.citibikenyc.com/data2/stations.php?updateOnly=true";
    ofLoadURLAsync(url_Update, "update");
    ofLoadURLAsync(url_Stations, "stations");
    lastUpdate = ofGetElapsedTimef();
    ofBackground(4, 5, 6);
    
    
    mapWidth = ofGetWindowWidth();
    mapHeight = ofGetWindowHeight();
    
    mapLonLeft = -74.2;
    mapLonRight = -73.7;
    mapLonDelta = mapLonRight - mapLonLeft;
    
    
    
    mapLatBottom = 40.6;
    mapLatTop = 40.8;
    mapLatBottomDegree = mapLatBottom * PI/180;

}


void testApp::geoToPixel(float lat, float lon){
    

}

//--------------------------------------------------------------
void testApp::update(){
    worldTime = ofGetElapsedTimef();
    if(worldTime - lastUpdate > 1){
        lastUpdate = ofGetElapsedTimef();
        ofLoadURLAsync(url_Update, "update");
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofNoFill();
    //ofBackground(0);

	ofSetColor(255, 255, 255);
    for(int i = 0; i < stationIds.size(); i++){
//        
//        float x = (stationMap[stationIds[i]].lon - mapLonLeft) * (mapWidth / mapLonDelta);
//        
//        float latDegree = stationMap[stationIds[i]].lat * PI / 180;
//        float worldMapWidth = ((mapWidth / mapLonDelta) * 360) / (2 * PI);
//        float mapOffsetY = (worldMapWidth / 2 * log((1 + sin(mapLatBottomDegree)) / (1 - sin(mapLatBottomDegree))));
//        float y = mapHeight - ((worldMapWidth / 2 * log((1 + sin(stationMap[stationIds[i]].lat)) / (1 - sin(stationMap[stationIds[i]].lat)))) - mapOffsetY);
//        cout<<"x: "<<x<<endl;
//        cout<<"y: "<<y<<endl;
    
        
        float x = ofMap(stationMap[stationIds[i]].lon, mapLonLeft, mapLonRight, 0, ofGetWindowWidth());
        float y = ofMap(stationMap[stationIds[i]].lat, mapLatTop, mapLatBottom, 0, ofGetWindowHeight());
        ofSetColor(0, 255, 0);
        ofCircle(x,y, stationMap[stationIds[i]].currentCount*.1);
        ofSetColor(255, 0, 0);
        ofCircle(x, y, stationMap[stationIds[i]].currentSlot*.1);
    }
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
            foo.bikeCount.push_back(data[i]["availableBikes"].asInt());
            foo.slotCount.push_back(data[i]["availableDocks"].asInt());
            
            
            foo.currentCount = data[i]["availableBikes"].asInt();
            foo.currentSlot = data[i]["availableDocks"].asInt();
        }
        cout<<"update Stations"<<endl;
    }else{
        cout<<"update failed"<<endl;
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
    mapWidth = ofGetWindowWidth();
    mapHeight = ofGetWindowHeight();
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}