#pragma once

namespace sf
{
	class Texture;
	class Font;
}

enum class Textures { MenuScreen, Background, Tiles };
enum class Fonts { Main };

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts> FontHolder;
