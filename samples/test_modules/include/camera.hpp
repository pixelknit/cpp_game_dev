#pragma once

#include <iostream>

extern float CAMERA_ZOOM;

struct Camera{
    int id;
    void SetCameraZoom(float zoom_amt);
};