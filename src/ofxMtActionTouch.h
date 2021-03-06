/*
 MultitouchActions for openFrameworks 
 Copyright (c) 2010 Hugues Bruyère - <http://www.smallfly.com>
 
 Some parts based on source code by Marek Bereza - <http://www.mrkbrz.com/>
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _OFX_MTACTIONTOUCH
#define _OFX_MTACTIONTOUCH

#ifndef _OFX_MULTITOUCHCUSTOMDATA_SF
#define _OFX_MULTITOUCHCUSTOMDATA_SF

struct ofxMultiTouchCustomDataSF : ofxMultiTouchCustomData {
	int sessionID;
};

#endif

class ofxMtActionTouch: public ofVec2f {
	public:
		ofVec2f last;
		bool isNew;
		int sessionID;
		
		// centroid here refers to the vector
		// between this this touch and the centre
		// of all the touches on the RotatableScalable
		
		ofVec2f centroidDelta;
		ofVec2f lastCentroidDelta;
		float centroidDistance;
		float lastCentroidDistance;
    int timestamp;
		ofxMtActionTouch() {
		
		}
		
		ofxMtActionTouch(int _sessionID, float _x, float _y) {
			sessionID = _sessionID;
			x = _x;
			y = _y;
			last = ofVec2f(_x, _y);
			isNew = true;
			centroidDelta			= ofVec2f(0,0);
			lastCentroidDelta		= ofVec2f(0,0);
			centroidDistance		= 0;
			lastCentroidDistance	= 0;
      timestamp = ofGetElapsedTimeMillis();
		}
		
		void setCentroid(ofVec2f centroid) {
			centroidDelta = ofVec2f(x, y) - centroid;
			centroidDistance = centroidDelta.length();
		}
		void setLastCentroid(ofVec2f centroid) {
			lastCentroidDelta = ofVec2f(x, y) - centroid;
			lastCentroidDistance = lastCentroidDelta.length();
		}
		
		// save the last coordinates
		// so we can calculate a delta
		void push() {
			last.x = x;
			last.y = y;
			lastCentroidDelta = centroidDelta;
			isNew = false;
			lastCentroidDistance = centroidDistance;
		}
		
		// tells you how far it's rotated since the last frame
		float angleDelta() {
			return centroidDelta.angleRad(lastCentroidDelta);
		}
		
		// tells you how much it's scaled since the last frame
		float scaleDelta() {
			return centroidDistance/lastCentroidDistance;
		}
		
		// tells you how far it's moved
		// since it was pushed
		ofVec2f delta() {
			return ofVec2f(x, y) - last;
		}
};

#endif
