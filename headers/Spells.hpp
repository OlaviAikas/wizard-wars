#pragma once

class Spell : protected MapObject {
    public:
        Spell(int x, int y, int width, int height, bool noclip, int damage, int heal);
        void draw(int camera_x, int camera_y);
        int get_damage();
        int get_heal();
    protected:
        int damage;
        int healing;
}