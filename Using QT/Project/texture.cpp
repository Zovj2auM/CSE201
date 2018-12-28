#include "listheaders.h"

Texture::Texture()
{
    path_to_textures = ":/Images/Textures/";

    current_texture = main_texture;

    define_main_texture();

    define_troll_texture_1();
}

void Texture::define_main_texture()
{
    while(texture_names.size() <= main_texture)
    {
        texture_names.push_back("");
    }

    texture_names[main_texture] = "Main_texture/";

    std::vector<std::string> texture_temp;

    while( texture_temp.size() < object_texture_count)
    {
        texture_temp.push_back("");
    }

    texture_temp[basic_player] = "character22.12.png";

    texture_temp[blocks] = "blocks.png";

    texture_temp[small_collectable] = "small_cheese.png";

    texture_temp[big_collectable] = "big_cheese.png";

    texture_temp[power_ups] = "power_ups.png";

    texture_temp[enemy_1] = "thief_walking_casual.png";

    texture_temp[projectiles] = "projectiles.png";

    texture_temp[projectile_vanish_effect] = "explosion.png";

    std::vector<std::string> x;

    while( object_image_from_texure.size() <= main_texture)
    {
        object_image_from_texure.push_back(x);
    }

    object_image_from_texure[main_texture] = texture_temp;

}

void Texture::define_troll_texture_1()
{
    while(texture_names.size() <= troll_texture_1)
    {
        texture_names.push_back("");
    }

    texture_names[troll_texture_1] = "Troll_texture_1/";

    std::vector<std::string> texture_temp;

    while( texture_temp.size() < object_texture_count)
    {
        texture_temp.push_back("");
    }

    texture_temp[basic_player] = "face.png";

    texture_temp[blocks] = "face.png";

    texture_temp[small_collectable] = "face.png";

    texture_temp[big_collectable] = "face.png";

    texture_temp[power_ups] = "face.png";

    texture_temp[enemy_1] = "face.png";

    texture_temp[projectiles] = "face.png";

    texture_temp[projectile_vanish_effect] = "face.png";

    std::vector<std::string> x;

    while( object_image_from_texure.size() <= troll_texture_1)
    {
        object_image_from_texure.push_back(x);
    }

    object_image_from_texure[troll_texture_1] = texture_temp;
}

void Texture::define_background()
{
    names_background[Tsky] = "bg.png";

    names_background[Tmonument] = "eiffel.png";

    names_background[Tbuildings] = "buildings.png";

}

const char* Texture::get_path_to(Object_texture ojb_tex)
{
    return (path_to_textures+texture_names[current_texture]+object_image_from_texure[current_texture][ojb_tex]).c_str();
}

const char* Texture::get_path_to(Backgrounds bg)
{
    return (":Images/background/"+names_background[bg]).c_str();
}

std::vector<QPixmap> Texture::get_qpixmap_of(Object_texture sheet, int start, int length, int size)
{
    QPixmap img(get_path_to(sheet));
    int w = img.width()/size;
    int i{start%w},j{start/w};
    std::vector<QPixmap> res(length);

    for (int k=0; k<length; k++)
    {
        res[k] = img.copy(((i+k)%w)*size, (j+(i+k)/w)*size, size, size);
    }
    return res;
}
