#include "SceneManager.h"
#include "MainScene.h"
#include "PlayScene.h"
SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
    MainScene* mainScene = new MainScene();
    PlayScene* playScene = new PlayScene();
    SceneManager::getSingleton()->registerScene(SceneTag::MainThemeScene, mainScene);
    SceneManager::getSingleton()->registerScene(SceneTag::PlayScene, playScene);
    _currentScene = mainScene;
    _currentScene->Init();
}

Scene* SceneManager::findScene(SceneTag tag)
{
    auto key = _mSceneList.find(tag);
    if (key != _mSceneList.end())
    {
        return key->second;
    }
    return nullptr;
}

void SceneManager::registerScene(SceneTag tag, Scene* scene)
{
    _mSceneList.insert(make_pair(tag, scene));
}


void SceneManager::changeScene(SceneTag tag)
{
    if (auto scene = findScene(tag))
    {
        if (_currentScene)  _currentScene->Release();
        _currentScene = scene;
        _currentScene->Init();
    }
}

void SceneManager::Release()
{
    for (auto& scenePair : _mSceneList)
    {
        if (scenePair.second != nullptr)
        {
            scenePair.second->Release();
            SAFE_DELETE(scenePair.second);
        }
    }
    _mSceneList.clear();
}