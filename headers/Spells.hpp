#pragma once
#include "MapObject.hpp"
#include <string>

class Spell : public MapObject {
    public:
        Spell(int start_x, int start_y, float dir_x, float dir_y, int width, int height, bool noclip);
        virtual ~Spell();
        virtual void draw(int camera_x, int camera_y);
        virtual void move();
        bool transmitted [5]={false, false, false, false, false};
        int counter;
        bool isBorS;
        virtual void set_mouse_down(bool &iamnot);

    float get_dir_x();
    float get_dir_y();
    virtual std::string encode_spell();
    bool get_havechanged();
    void reset_havechanged();
    int get_id();
    protected:
    int id;
    std::string subclass;
    std::string element;
    float dir_x;
    float dir_y;
    bool havechanged;

};