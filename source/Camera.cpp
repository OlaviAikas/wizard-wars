#include "../headers/Camera.hpp"

Camera::Camera(int start_x, int start_y) {
    this->x = start_x;
    this->y = start_y;
}

int Camera::get_x() {
    return x;
}

int Camera::get_y() {
    return y;
}

void Camera::move_x(int d) {
    x = x + d;
}

void Camera::move_y(int d) {
    y = y + d;
}