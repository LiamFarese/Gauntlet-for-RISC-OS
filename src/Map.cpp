#include "Map.hpp"

namespace {

  Tile construct_tile(int tile_id, FloorType floor, WallType wall, SDL_Rect position) {
    TileType tile_type {};
    switch (tile_id){
      case (0):
        tile_type = TileType::Blank; break;
      case (1):
        tile_type = TileType::Floor; break;
      case (2):
        tile_type = TileType::Horizontal; break;
      case (3):
        tile_type = TileType::Verticle; break;
      case (4):
        tile_type = TileType::TopLeftCorner; break;
      case (5):
        tile_type = TileType::TopRightCorner; break;
      case (6):
        tile_type = TileType::BottomLeftCorner; break;
      case (7):
        tile_type = TileType::BottomRightCorner; break;
      default:
        tile_type = TileType::Blank;
    };

    SDL_Rect sprite {0,0,32,32};

    switch(tile_type){
      case(TileType::Floor):
        sprite.y = 0;
        sprite.x = static_cast<Sint16>(floor);
        break;
      case(TileType::Blank):
        sprite.y = 0;
        sprite.x = 0;
        break;
      default:
        sprite.y = static_cast<Sint16>(wall);
        sprite.x = static_cast<Sint16>(tile_type);
    }

    bool is_collidable = false;
    if(tile_type != TileType::Floor){
      is_collidable = true;
    }
    return {position, sprite, is_collidable};
  };

  const std::vector<std::vector<int>> level_1 {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5},
    {3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
    {3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
    {3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
    {3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
    {3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
    {3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
    {3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
    {6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,7},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };
}

Map Level::load_level(int level_number){

  std::vector<std::vector<int>> grid{};
  FloorType floor;
  WallType wall;

  switch (level_number){
    case(1):
      grid = level_1;
      floor = FloorType::Floor1;
      wall = WallType::Wall6;
      break;
  };

  Map map{};
  SDL_Rect position {0,0,32,32};

  for(auto& row : grid){
    std::vector<Tile> level_row;
    for(auto& tile_id : row){
      level_row.push_back(construct_tile(tile_id, floor, wall, position));
      position.x += 32;
    }
    position.x = 0;
    position.y += 32;
    map.tile_map.push_back(level_row);
  }

  return map;
};
