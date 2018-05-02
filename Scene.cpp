#include "Scene.h"

void Scene::setPaused(bool paused)
{
    b_paused = paused;
}

bool Scene::getPauseState()
{
    return b_paused;
}

void Scene::setFirstRenderState(bool first)
{
    b_first_render = first;
}
