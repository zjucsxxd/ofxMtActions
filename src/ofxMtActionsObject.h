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

#ifndef _OFXMTACTIONS_OBJ
#define _OFXMTACTIONS_OBJ

#include "ofxMtObject.h"
#include "ofMain.h"
#include "ofxMtActionTouch.h"


class ofxMtActionsObject : public ofxMtObject{
	
	public:
		static const int FIXE = 0;
		static const int DRAGGING = 1;
		static const int ROTATESCALE = 2;
		static const int DEBUG = false;
	
		ofxMtActionsObject(bool _draggable=false, bool _scalable=false, bool _rotatable=false);
		virtual ~ofxMtActionsObject();
	
		void update();
		void render();
	
		virtual void drawContent();
		virtual void updateContent();
		virtual void tapContent(ofVec2f position);
		
		virtual bool ownTouchCursor(int touchId);
	
		int getSessionID();
		
		void setPriorityLevel(int _pLevel);
		int getPriorityLevel();
		
		void setIsDraggable(bool _draggable, int *_nbOfTouchForDrag=NULL, int arrSize=NULL, bool _horizontal=true, bool _vertical=true );
		void setIsScalable(bool _scalable, int *_nbOfTouchForScale=NULL, int arrSize=NULL  );
		void setIsRotatable(bool _rotatable, int *_nbOfTouchForRotate=NULL, int arrSize=NULL  );
    void setIsTappable(bool _tappable);
		bool isDraggable();
		bool isScalable();
		bool isRotatable();
		bool isTappable();
		
		virtual void actionTouchDown(float x, float y, int touchId);
		virtual void actionTouchMoved(float x, float y, int touchId);
		virtual void actionTouchUp(float x, float y, int touchId);
	
	protected:
		int state;
	
		//Spec of the interaction
		//How many touches/fingers to trigger an action
		//i.e. drag could be done using 1 finger or 3+ fingers [3+ would be defined by a negative value -3].
		bool draggable, scalable, rotatable, tappable;
		int* nbOfTouchForDrag;
		int* nbOfTouchForScale;
		int* nbOfTouchForRotate;
		
		int dragSpecLength;
		int scaleSpecLength;
		int rotateSpecLength;
	
		bool draggableH, draggableV;
		
		//List fo the touches currently interacting on this object.
		map<int,ofxMtActionTouch> touches;
	
		// lower the value is higher the priority
		// if two objects are on top of each other
		// the one with the higher priority will consume/interact with the tuioCursor in contact.
		int priorityLevel;
		
		// Is equal to the highest sessionID of the tuioCursors in contact with the object
		// Used to define the place of the object in the display stack managed by the action hub.
		int highestSessionID;
	
		float rotation;
		
		float contentWidth;
		float contentHeight;
		ofVec2f acceleration;
		float rotationalAcceleration;
		int lastNumberOfTouches;
		
		ofVec2f centroid;
		
		float accelerationSmoothing;
		float decelerationSmoothing;
		bool stopActionOnRollOut;
		bool limitToScreen;
		bool drawTouchCounts;
		float rotationalSmoothing;
		float scaleSmoothing;
		float minSize;
		float maxSize;
	
		// a cache of the last local coordinate
		// that tested positive in a hitTest
		ofVec2f lastHit;
	
		//utils
		virtual bool actionTouchHitTest(float _x, float _y);
	
		void updateState();
		void transform(ofVec2f vec, float angle, float _scale);

	
};

#endif
