#pragma once

class HUDobject {
    public:
        HUDobject(int x, int y, int sx, int sy, int border);
        virtual ~HUDobject();

        virtual void draw();

    protected:
        int x;
        int y;
        int sx;
        int sy;
        int border;
};