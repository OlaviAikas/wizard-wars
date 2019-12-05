#include "../headers/Camera.hpp"


Camera::Camera(int start_x, int start_y) {
    this->x = start_x;
    this->y = start_y;
    this->maxx = 960
    this->maxy = 540
}

int Camera::get_x() {
    return x;
}

int Camera::get_y() {
    return y;
}

void Camera::move_x(int d) {
    if(x + d < this-> 3840 + maxx or x + d < -this->maxx){
        x = x + d;
    }
}

void Camera::move_y(int d) {
    if(y + d < this-> 2160 + maxy or y + d < - this->maxy){
        y = y + d;
    }
}