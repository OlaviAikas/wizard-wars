#include "../headers/Camera.hpp"
// #include <iostream>

Camera::Camera(int start_x, int start_y) {
    this->x = start_x;
    this->y = start_y;
    this->maxx = 1920; // change with map size
    this->maxy = 1140;
}

int Camera::get_x() {
    return x;
}

int Camera::get_y() {
    return y;
}

void Camera::move_x(int d) {
    // std::cout << "Camera debug x " << x << " " << d << std::endl;
    // std::cout << "Camera debug x cond 1 " << x + d << " " << maxx + 3840 << std::endl;
    // std::cout << "Camera debug x cond 2 " << x + d << " " << -maxx << std::endl;
    if(x + d < this->maxx && x + d > 0) {
        x = x + d;
    }
}

void Camera::move_y(int d) {
    // std::cout << "Camera debug y " << y << " " << d << std::endl;
    // std::cout << "Camera debug y cond 1 " << y + d << " " << maxy + 3840 << std::endl;
    // std::cout << "Camera debug y cond 2 " << y + d << " " << -maxy << std::endl;
    if(y + d < this->maxy && y + d > 0) {
        y = y + d;
    }
}

// void cameraUpdate(int *cameraPosition, int x, int y, int width, int height){
//     cameraPosition[0] = - (screenWidth / 2) + (x + width / 2);
//     cameraPosition[1] = - (screenWidth / 2) + (y + height / 2);
//     if (cameraPosition[0] < 0){
//         cameraPosition[0] = 0;
//     }
//     if (cameraPosition[1] < 0){
//         cameraPosition[1] = 0;
//     }
// }
