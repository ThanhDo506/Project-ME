#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Manager.h"
#include <unordered_map>
#include "../Render/Object/Texture.h"
#include "../common.h"
#include <string>

class Texture;

class TextureManager
{
	friend class GUI;
	SINGLETON(TextureManager);

public:
	static void add_new_texture_to_registry(Texture* texture, const std::string& name);
	static void remove_texture_from_registry(Texture* texture);
	static void remove_texture_from_registry(const std::string& name);
	static bool has_texture(const std::string& name);
	static Texture* get_texture(const std::string& name);
	static void clean();

private:
	std::unordered_map<std::string, Texture*> _textureRegistry;
};

#endif // !TEXTURE_MANAGER_H
