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

#include "joypp_objects.h"

/*

####################################################################

Definitions follow this order:

1. Static Field Variables.
2. Non-static Field Variables.
3. Static Methods.
4. Constructors.
5. Destructor.
6. Non-static methods.
7. Accessors.
8. Mutators.

Be sure to follow it!

####################################################################

*/

Image::Image(path p, int x_pos, int y_pos) : Object()
{
    App::objects[this->id] = this;
    this->x = x_pos;
    this->y = y_pos;
    this->full_path = p;
    this->image = al_load_bitmap(this->full_path);
    if (!this->image)
    {
        al_show_native_message_box(App::display,
            "Fatal Error!",
            "Failed to load: " ,
            this->full_path,
            nullptr,
            ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(App::display);
    }
}

void Image::draw(int flags)
{
al_draw_bitmap(this->image, this->x, this->y, flags);
}

void Image::move_north(float velocity)
{
    this->y -= velocity;
}

void Image::move_south(float velocity)
{
    this->y += velocity;
}

void Image::move_west(float velocity)
{
    this->x -= velocity;
}

void Image::move_east(float velocity)
{
    this->x += velocity;
}

path Image::get_path()
{
return this->full_path;
}

img Image::get_image()
{
return this->image;
}

int Image::get_x()
{
return this->x;
}

int Image::get_y()
{
return this->y;
}

void Image::set_path(path p)
{
this->full_path = p;
}

void Image::set_image(img image)
{
this->image = image;
}

void Image::set_x(int value)
{
this->x = value;
}

void Image::set_y(int value)
{
this->y = value;
}
