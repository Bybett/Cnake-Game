#include "asset_loader.h"

Texture load_asset(char *path) {
  Image image = LoadImage(path);
  Texture asset = LoadTextureFromImage(image);
  return asset;
}

