#pragma once
#include "Singleton.h"
#include "Scene.h"

class SceneManager : public Singleton<SceneManager>
{
private:
    map<SceneTag, Scene*> _mSceneList;
    Scene* _currentScene;

public:
    SceneManager();
    ~SceneManager();

    void Init();
    void Release();

    void registerScene(SceneTag tag, Scene* scene);
    void changeScene(SceneTag tag);
    Scene* findScene(SceneTag tag);

    void Render(HDC hdc) { if (_currentScene) _currentScene->Render(hdc); }
    void Update() { _currentScene->Update(); }
};