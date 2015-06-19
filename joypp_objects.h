/*

####################################################################

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

####################################################################

*/

#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#include "joypp_app.h"

/*

####################################################################

Member declarations follow this order:

1. Static Field Variables.
2. Non-static Field Variables.
3. Static Methods.
4. Constructors.
5. Destructor.
6. Non-static methods.
7. Accessors.
8. Mutators.

The order applies individually for each access specifier.
Be sure to follow it!

####################################################################

*/

class Image: public Object

/*

####################################################################

The Image class provides a general image object, and abstracts basic
image operations (such as scaling, translating and rotating).

####################################################################

*/

{
private:
    path full_path;
    int x;
    int y;
    img image;
public:
    Image(path p, int x_pos = 0, int y_pos = 0);
    ~Image(void) {};

    void draw(int flags = 0);
    void move_north(float velocity);
    void move_south(float velocity);
    void move_west(float velocity);
    void move_east(float velocity);

    path get_path(void);
    img get_image(void);
    int get_x(void);
    int get_y(void);
    void set_path(path p);
    void set_image(img _image);
    void set_x(int value);
    void set_y(int value);
};

#endif // OBJECTS_H_INCLUDED
