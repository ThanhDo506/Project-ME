#ifndef RENDERER_MANAGER_H
#define RENDERER_MANAGER_H

#include "Scene.h"
#include "../../Core/common.h"
#include "SceneManager.h"
#include "../Render/Object/Renderer.h"
#include "LightRenderManager.h"
#include <algorithm>
#include <unordered_map>

class SceneRenderer
{

public:
	SceneRenderer(SceneManager* sceneManager);

	bool add_renderer(Renderer* renderer);
	bool remove_renderer(Renderer* renderer);

	LightRenderManager* get_light_render_manager();

	void Update();
	void Render();
private:
	SceneManager*			_sceneManager;
	std::vector<Renderer*>	_renderers;
	LightRenderManager		_lightRenderManager;
};
#endif // !RENDER_MANAGER_H
