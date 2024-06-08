#include "MainScene.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "SoundManager.h"

MainScene::MainScene()
{
	_rect = makeRect(414, 66, 197, 167);
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	SoundManager::getSingleton()->play(static_cast<int>(SoundTypeTag::MainScene), SoundTypeTag::MainScene);
}

void MainScene::Release()
{
}

void MainScene::Update()
{
	SoundManager::getSingleton()->repeatPlay(static_cast<int>(SoundTypeTag::MainScene), SoundTypeTag::MainScene);

	//if (PtInRect(&_rect, ptMouse))
	//{
		if (KeyManager::getSingleton()->isOnceKeyDown(VK_RBUTTON))
		{
			SceneManager::getSingleton()->changeScene(SceneTag::PlayScene);

			SoundManager::getSingleton()->play(static_cast<int>(SoundTypeTag::Click), SoundTypeTag::Click);
			SoundManager::getSingleton()->pause(static_cast<int>(SoundTypeTag::MainScene), true);
		}
	//}
}

void MainScene::Render(HDC hdc)
{
	ImageManager::getSingleton()->findImage("loginSceneBg")->Render(hdc, 0, 0);
}
