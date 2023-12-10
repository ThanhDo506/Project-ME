#include "TextureManager.h"

TextureManager& TextureManager::instance() {
	static TextureManager tm;
	return tm;
}

void TextureManager::add_new_texture_to_registry(Texture* texture, const std::string& name)
{
	TextureManager& tm = TextureManager::instance();

	if (!tm.has_texture(name)) {
		tm._textureRegistry.insert(std::make_pair(name, texture));
		APP_INFO("[TEXTURE] Added texture %s to registry", name.c_str());
	}
	else {
		std::string n = name + " (1)";
		tm._textureRegistry.insert(std::make_pair(n, texture));
		APP_WARN("[TEXTURE] Texture name %s existed in registry. New texture 'll be renamed to %s", name.c_str(), n.c_str());
	}
}

void TextureManager::remove_texture_from_registry(Texture* texture)
{
	TextureManager& tm = TextureManager::instance();
	for (auto it = tm._textureRegistry.begin(); it != tm._textureRegistry.end(); it++) {
		if (it->second == texture) {
			Texture* t=  it->second;
			std::string name = it->first;
			tm._textureRegistry.erase(it);
			delete t;
			APP_INFO("[TEXTURE] Removed and free texture %s from registry", name.c_str());
			return;
		}
	}
	APP_WARN("[TEXTURE] No texture (0x%p) in registry", texture);
}

void TextureManager::remove_texture_from_registry(const std::string& name)
{
	TextureManager& tm = TextureManager::instance();
	auto it = tm._textureRegistry.find(name);
	if (it != tm._textureRegistry.end()) {
		Texture* t = tm._textureRegistry[name];
		tm._textureRegistry.erase(it);
		delete t;
		APP_INFO("[TEXTURE] Removed texture %s from registry.", name.c_str());
		return;
	}
	APP_WARN("[TEXTURE] Remove texture failure. No texture name %s from registry.", name.c_str());
}

bool TextureManager::has_texture(const std::string& name)
{
	TextureManager& tm = TextureManager::instance();
	auto it = tm._textureRegistry.find(name);
	if (it != tm._textureRegistry.end()) {
		return true;
	}
	return false;
}

Texture* TextureManager::get_texture(const std::string& name)
{
	TextureManager& tm = TextureManager::instance();
	auto it = tm._textureRegistry.find(name);
	if (it != tm._textureRegistry.end()) {
		return it->second;
	}
	APP_ERROR("[TEXTURE] No texture name %s", name.c_str());
	return NULL;
}

void TextureManager::clean()
{
	TextureManager& tm = TextureManager::instance();
	unsigned int c = 0;
	for (auto it = tm._textureRegistry.begin(); it != tm._textureRegistry.end(); it++) {
		delete it->second;
		c++;
	}
	tm._textureRegistry.clear();
	APP_INFO("[TEXTURE] Free %d texture(s)", c);
}
