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

#include "objects.h"

Image::Image(path p, int x_pos, int y_pos)
{
    x = x_pos;
    y = y_pos;
    full_path = p;
    image = al_load_bitmap(full_path);
    if (!image)
    {
        al_show_native_message_box(App::display,
            "Fatal Error!",
            "Failed to load: " ,
            full_path,
            nullptr,
            ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(App::display);
    }
}

path Image::get_path() { return full_path; }
void Image::set_path(path p) { full_path = p; }
img Image::get_image() { return image; }
void Image::set_image(img _image) { image = _image; }
int Image::get_x() { return x; }
void Image::set_x(int value) { x = value; }
int Image::get_y() { return y; }
void Image::set_y(int value) { y = value; }
void Image::draw(int flags) { al_draw_bitmap(image, x, y, flags); }
