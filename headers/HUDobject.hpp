#pragma once

class HUDobject {
    public:
        HUDobject(int win_x, int win_y);

        virtual void draw();

    protected:
        int x;
        int y;
        int sx;
        int sy;
};