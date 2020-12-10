#include "../render.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>

using namespace render;
using namespace std;

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(this->m_vertices, states);
    /*
    int tileNumber  = this->tiles[(int) ceil(this->cursorCoord.x/tileSize.x)*tileSize.x - 1][(int) ceil(this->cursorCoord.y/tileSize.y)*tileSize.y - 1];
    int tu = tileNumber %(m_tileset.getSize().x / tileSize.x);
    int tv = tileNumber /(m_tileset.getSize().y / tileSize.y);


    sf::Texture light;
    light.loadFromFile(this->tileset,sf::IntRect(tv * tileSize.y,tu * tileSize.x,tileSize.x,tileSize.y));
    sf::Sprite spriteLight;
    spriteLight.setTexture(light);
    spriteLight.setPosition(sf::Vector2f((int) ceil((this->cursorCoord.x + this->viewCoord.x)/tileSize.x - 1),(int) ceil((this->cursorCoord.y+ this->viewCoord.y)/tileSize.y - 1)));
    spriteLight.setColor(sf::Color(255, 255, 255, 128));
    target.draw(spriteLight,states);
    */
}

std::vector<std::vector <int > > TileMap :: load_map(std::string fileName){

    std::ifstream infile(fileName);
    std::vector<std::vector <int> > map;
    std::vector<int> lineVector;
    std::string sum="";

    for(std::string line; getline( infile, line );){
        for(char elem : line){
            if (elem == ',' or elem == ' '){
                lineVector.push_back(std::stoi (sum));
                sum = "";
            }else{
                sum+=elem;
            }
        }
        sum = "";
        map.push_back(lineVector);
        lineVector.clear();
    }

    return map;
}


bool TileMap :: load(const std::string& tileset, sf::Vector2u tileSize,std::string fileName)
{

    this->tiles = load_map(fileName);

    // load the tileset texture
    if (!this->m_tileset.loadFromFile(tileset))
        return false;

    this->tileSize = tileSize;
    this->tileset = tileset;
    // resize the vertex array to fit the level size
    this->m_vertices.setPrimitiveType(sf::Quads);
    this->m_vertices.resize(tiles.size() * tiles[0].size()*4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < tiles.size(); ++i)
        for (unsigned int j = 0; j < tiles[i].size(); ++j)
        {
            // get the current tile number
            int tileNumber = this->tiles[i][j];

            // find its position in the tileset texture
            int tu = tileNumber %(m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber /(m_tileset.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * tiles.size()) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(j * tileSize.y, i * tileSize.x);
            quad[1].position = sf::Vector2f((j + 1) * tileSize.y, i * tileSize.x);
            quad[2].position = sf::Vector2f((j + 1) * tileSize.y, (i + 1) * tileSize.x);
            quad[3].position = sf::Vector2f(j * tileSize.y, (i + 1) * tileSize.x);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}

void TileMap::updateCursor(sf::Vector2u cursor,sf::Vector2u view){
    this->cursorCoord = cursor;
    this->viewCoord = view;
}

sf::Vector2u TileMap:: mapSize(){
  sf::Vector2u s;
  s.x=tiles.size()*tileSize.x;
  s.y=tiles[0].size()*tileSize.x;
  return s;
}
