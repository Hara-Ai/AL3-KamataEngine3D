#include "CameraController.h"
#include "Enemy.h"
#include "GameScene.h"
#include "ObjectColor.h"
#include "Player.h"
#include "Skydome.h"
#include "TextureManager.h"
#include "ClearScene.h"

ClearScene::ClearScene() {}

ClearScene::~ClearScene() { delete clearModel_; }

