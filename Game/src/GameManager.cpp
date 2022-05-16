#include "GameManager.h"

ClusterEngine::MultiCastDelegate<void> GameManager::OnLost;
Player* GameManager::player;
ClusterEngine::Camera* GameManager::mainCamera;
bool GameManager:: isLost = false;