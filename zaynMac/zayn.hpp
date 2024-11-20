//
//  zayn.hpp
//  zaynMac
//
//  Created by socki on 11/18/24.
//

#pragma once
#import "camera.hpp"


struct ZaynMemory
{
    CameraData* cameraData;
    
    Camera camera;
};

void ZaynInit();
