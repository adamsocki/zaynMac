//
//  time.hpp
//  zaynMac
//
//  Created by socki on 11/19/24.
//



struct ZaynTime
{
    real32 startTime;

    real32 systemTime;
    real32 prevSystemTime;

    real32 zaynTime;

    real32 deltaTime;
    real32 totalTime;

    int32 frameCount;
    real32 fpsTimer;
    
    real32 timeSinceRender;
    
    timespec spec;
    
//    real32 frameRate;
    
};
