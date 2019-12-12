//#define DEBUG_MODE
#include "../headers/MapObject.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

MapObject::MapObject(int x, int y, int width, int height, bool noclip) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->noclip = noclip;
}

void MapObject::move() { std::cout << "momove" << std::endl; };

int MapObject::get_x() const {
    return x;
}

int MapObject::get_y() const {
    return y;
}

int MapObject::get_width() const {
    return width;
}

int MapObject::get_height() const {
    return height;
}

bool MapObject::get_noclip() const {
    return noclip;
}


void MapObject::on_collision(MapObject &other) {
    // To retrieve from balavoine branch
    std::cout << "(!) WARN: generic on_collision called for MapObject at " << this << std::endl;
}


bool MapObject::operator==(const MapObject &other) const {
#ifdef DEBUG_MODE
    std::cout << "Equality operator at " << this << " vs " << &other << std::endl;
#endif
    return ((*this <= other) | (other <= *this));
}

bool MapObject::operator<=(const MapObject &other) const {
#ifdef DEBUG_MODE
    std::cout << "Equality operator at " << this << " vs " << &other << std::endl;
#endif
    if (this->x >= other.get_x() && this->x <= other.get_x() + other.get_width()) {
        if (this->y >= other.get_y() && this->y <= other.get_y() + other.get_height()) {
            return true;
        }
    }
    if (this->x + this->width >= other.get_x() && this->x + this->width <= other.get_x() + other.get_width()) {
        if (this->y >= other.get_y() && this->y <= other.get_y() + other.get_height()) {
            return true;
        }
    }
    if (this->x >= other.get_x() && this->x <= other.get_x() + other.get_width()) {
        if (this->y + this->height >= other.get_y() && this->y + this->height <= other.get_y() + other.get_height()) {
            return true;
        }
    }
    if (this->x + this->width >= other.get_x() && this->x + this->width <= other.get_x() + other.get_width()) {
        if (this->y + this->height >= other.get_y() && this->y + this->height <= other.get_y() + other.get_height()) {
            return true;
        }
    }
    return false;
}


void MapObject::draw(int camera_x, int camera_y) {}
