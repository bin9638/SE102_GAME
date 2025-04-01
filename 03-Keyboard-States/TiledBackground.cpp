#include "TiledBackground.h"

void CTiledBackground::Render()
{
    CGame* game = CGame::GetInstance();
    float cameraX, cameraY;
    game->GetCamPos(cameraX, cameraY);

    int screenWidth = game->GetBackBufferWidth();
    int screenHeight = game->GetBackBufferHeight();

    // Tính toán tile bắt đầu dựa trên vị trí camera
    int startTileX = (int)(cameraX / tileWidth);
    int startTileY = (int)(cameraY / tileHeight);

    // Tính số lượng tile cần để phủ màn hình
    int tilesNeededX = (screenWidth / tileWidth) + 2; // +2 để đảm bảo không có khoảng trống
    int tilesNeededY = (screenHeight / tileHeight) + 2;

    // Vẽ các tile cần thiết
    for (int y = 0; y < tilesNeededY; y++) {
        for (int x = 0; x < tilesNeededX; x++) {
            // Vị trí thực tế trong thế giới game
            float worldPosX = (startTileX + x) * tileWidth;
            float worldPosY = (startTileY + y) * tileHeight;

            backgroundSprite->Draw(worldPosX, worldPosY);
        }
    }
}