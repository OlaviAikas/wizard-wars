#include "../headers/MapObject.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

MapObject::MapObject(int x, int y, int width, int height, bool noclip, int damage, int heal) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->noclip = noclip;
    this->damage = damage;
    this->heal = heal;
}

int MapObject::get_x() {
    return x;
}

int MapObject::get_y() {
    return y;
}

int MapObject::get_width() {
    return width;
}

int MapObject::get_height() {
    return height;
}

int MapObject::get_damage() {
    return damage;
}

int MapObject::get_heal() {
    return heal;
}

bool MapObject::get_noclip() {
    return noclip;
}


void MapObject::on_collision(MapObject other) {
    
}


bool MapObject::operator==(MapObject other) {
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

void MapObject::draw(int camera_x, int camera_y) {
    al_draw_filled_rectangle(x - camera_x, y - camera_y, x + width - camera_x, y + height - camera_y, al_map_rgb(255, 0, 0));
}

void MapObject::draw_arrow(int mouse_x, int mouse_y) {
        float x1 = i->getX() + (i->getWidth() / 2);
        float y1 = i->getY() + (i->getHeight() / 2);

        float x2 = screenCentreX;
        float y2 = ScreenCentreY;

        float dx = x2 - x1;
        float dy = y2 - y1;
        float hypotSquared = (dx * dx) + (dy * dy);
        float hypot = sqrt(hypotSquared);

        float unitX = dx / hypot;
        float unitY = dy / hypot;

        float rayX = x2 - view->getViewportX();
        float rayY = y2 - view->getViewportY();
        float arrowX = 0;
        float arrowY = 0;

        bool posFound = false;
        while(posFound == false)
        {
            rayX += unitX;
            rayY += unitY;

            if(rayX <= 0 ||
                rayX >= screenWidth ||
                rayY <= 0 ||
                rayY >= screenHeight)
            {
                arrowX = rayX;
                arrowY = rayY;
                posFound = true;
            }
        }

        al_draw_bitmap(sprite, arrowX - spriteWidth, arrowY - spriteHeight, 0);
    }
}
void MapObject::draw_spell(int spell_x, int spell_y) {

}
