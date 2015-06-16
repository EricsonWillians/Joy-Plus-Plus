/*

Joy++ - A general-purpose multimedia engine.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#include "app.h"

class Object
{
public:
    Object(void) {};
    ~Object(void) {};
};

class Image: public Object
{
private:
    path full_path;
    int x;
    int y;
public:
    Image(path p, int x_pos = 0, int y_pos = 0);
    ~Image() {};
    path get_path();
    void set_path(path p);
    img get_image();
    void set_image(img _image);
    int get_x();
    void set_x(int value);
    int get_y();
    void set_y(int value);
    void draw(int flags = 0);
};

#endif // OBJECTS_H_INCLUDED
