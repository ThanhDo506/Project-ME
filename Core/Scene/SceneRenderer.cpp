#include "SceneRenderer.h"

SceneRenderer::SceneRenderer(SceneManager* sceneManager)
	: _sceneManager(sceneManager)
{
}

bool SceneRenderer::add_renderer(Renderer* renderer)
{
	auto it = std::find(_renderers.begin(), _renderers.end(), renderer);
	if (it != _renderers.end()) {
		APP_WARN("Renderer has been added to manager.");
		return false;
	}
	_renderers.push_back(renderer);
	return true;
}

bool SceneRenderer::remove_renderer(Renderer* renderer)
{
	auto it = std::find(_renderers.begin(), _renderers.end(), renderer);
	if (it == _renderers.end()) {
		APP_WARN("Renderer (address: %p) hasn't been added to manager.", renderer);
		return false;
	}
	_renderers.erase(it);
	return true;
}

LightRenderManager* SceneRenderer::get_light_render_manager()
{
	return &_lightRenderManager;
}

void SceneRenderer::Update()
{
	for (auto renderer : _renderers) {
		renderer->material->shader.Active();
		// Update Lighting
		_lightRenderManager.Update(renderer->material->shader);

		// Update Material
		renderer->update_shader();
	}
}

void SceneRenderer::Render()
{
	for (auto render : _renderers) {
		render->Render();
	}
}
