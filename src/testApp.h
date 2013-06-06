#pragma once

#include "ofMain.h"
#include "ofxJSONElement.h"


class testApp : public ofBaseApp{
    
public:
    
    
    struct station{
        float lon;
        float lat;
        int name;
        vector<int> bikeCount;
        vector<int> slotCount;
        int currentCount;
        int currentSlot;
    };
    
    struct bikeEvent{
        string type;
        long time;
        string loc;
    };
    
    
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void urlResponse(ofHttpResponse & response);
    void parseUpdates(string json);
    void parseStations(string stations);
    void geoToPixel(float lat, float lon);

    string url_Stations;
    string url_Update;
    
    float mapLonLeft, mapLonRight, mapLonDelta;
    float mapLatTop, mapLatBottom, mapLatBottomDegree;
    float scaleX, scaleY;
    
    int mapWidth, mapHeight;

    ofxJSONElement stations;
    ofxJSONElement updates;

    map<int, station> stationMap;
    map<string, bikeEvent> eventMap;
    vector<int> stationIds;
    float lastUpdate, worldTime;
};
