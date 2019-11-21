#pragma once

class MapObject {
    public:
        MapObject(int x, int y, int width, int height, bool noclip, int damage, int heal);
        void draw(int camera_x, int camera_y);
        void move();
        void draw_spell(int spell_x, int spell_y)
        void on_collision(MapObject other);

        int get_x();
        int get_y();
        int get_width();
        int get_height();
        int get_damage();
        int get_heal();
        bool get_noclip();
        
        bool operator==(MapObject other);

    protected:
        bool noclip;

        int x;
        int y;
        int width;
        int height;
        int damage;
        int healing;
};
