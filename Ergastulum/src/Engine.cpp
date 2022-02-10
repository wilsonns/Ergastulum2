#include "Engine.h"

//Constructors & Desctructors
Engine::Engine(const int width, const int height, const int guiHeight, unsigned int tileSize, unsigned int tileGap)
{
	this->m_tileSize = tileSize;
	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Ergastulum:Histórias de X e Y");
	texture(loadTexture("Assets/Graphics/Entities/Personagens.png"), "Entidades");
	texture(loadTexture("Assets/Graphics/Terreno/Dummy.png"), "Dummy");
	texture(loadTexture("Assets/Graphics/Terreno/Dummywall.png"), "Dummywall");
	makeTileSet(texture("Dummy"), tileSize, tileGap,m_terrainSprites);
	makeTileSet(texture("Dummywall"), tileSize, tileGap, m_terrainSprites);
	makeTileSet(texture("Entidades"), tileSize, tileGap, m_terrainSprites);
	this->initMap();
	m_gui = new GUI(0, (height-guiHeight), height, guiHeight,sf::Color::White,sf::Color::Black, m_window.get() , this);
		
	return;
}

Engine::~Engine()
{
	return;
}


//Functions
void Engine::update()
{
	this->m_currentMap.get()->update();
		
	return;
}

void Engine::render()
{
	m_window->clear();
	

	m_currentMap->render(m_window.get());
	
	m_gui->render(m_window.get());

	m_window->display();
	return;
}


//Accessors
/**Returns a sf::Texture from the m_textures map.*/
sf::Texture* Engine::texture(std::string st)
{
	if (m_textures.find(st) != m_textures.end())
	{
		return m_textures[st].get();
	}
	std::cout << "Texture not found" << std::endl;
	return m_textures["Dummy"].get();
}

/**Loads and returns a texture from a string representing the directory.
* std::string refers to the directory.
* bool colorKey, if true, gets the background color of the loaded image and swaps it for alpha 0.
*/
sf::Texture Engine::loadTexture(std::string file, bool colorKey)
{
	sf::Image image;
	try
	{
		throw image.loadFromFile(file);
	}
	catch(bool answer)
	{
		if (!answer)
		{
			std::cout << "File not found" << std::endl;
			throw;
		}
	}
	if (colorKey)
	{
		image.createMaskFromColor(image.getPixel(0, 0));
	}
	sf::Texture texture;
	texture.loadFromImage(image);
	return texture;
}

/**Makes and returns an sf::Sprite from a texture and a rectangle.*/
sf::Sprite Engine::makeSprite(sf::Texture *texture, sf::IntRect rect)
{
	sf::Sprite sprite;
	sprite.setTexture(*texture);
	sprite.setTextureRect(rect);
	return sprite;
}

/**Returns a sf::Sprite from a given map.
* int sp is the index.
* map sprites is the map.
*/
sf::Sprite Engine::sprite(unsigned int sp, std::map<unsigned int,std::unique_ptr<sf::Sprite>>sprites)
{
	return *sprites[sp].get();
}


//Mutadores
/**Checks if a texture exists within the texture map. If it doesn't, adds it.*/
void Engine::textura(sf::Texture textura, std::string st)
{
	if (m_texturas.find(st) == m_texturas.end())
	{
		m_texturas.insert(std::make_pair(st, std::make_unique<sf::Texture>(textura)));
	}
	else
	{
		std::cout << "There's already a texture with this name" << std::endl;
	}
}

/**Deprecated*/
void Engine::sprite(sf::String sprite, sf::Texture* textura, sf::IntRect retangulo)
{
	/*sf::Sprite sp;
	sp.setTexture(*textura);
	sp.setTextureRect(retangulo);
	if (m_sprites.find(sprite) == m_sprites.end())
	{
		m_sprites.insert(std::make_pair(sprite, std::make_unique<sf::Sprite>(sp)));
	}
	else
	{
		std::cout << "Sprite com esse nome ja existe!" << std::endl;
	}*/
}

/**
* Makes a tileset from a texture.
* *texture is a pointer to a sf::Texture.
* int tileSize is the size of each tile in pixels.
* int tileGap is the gap between each tile in the texture. 0 if there is no gap.
* map sprites  is a given map to add the sprites to.
*/
void Engine::makeTileSet(sf::Texture* texture, unsigned int tileSize, unsigned int tileGap, std::map<unsigned int, std::unique_ptr<sf::Sprite>>* sprites)
{
	int it = sprites->size();
	int xGap = 1;
	int yGap = 0;
	int tiles = (texture->getSize().x / tileSize) * (texture->getSize().y / tileSize);
	for (int y = 0; y < (texture->getSize().y / tileSize);y++)
	{
		xGap = 1;
		yGap++;
		for (int x = 0; x < (texture->getSize().x / tileSize);x++)
		{
			sf::Sprite sp;
			sp.setTexture(*texture);
			sp.setTextureRect(sf::IntRect((x * tileSize) + (tileGap) ? xGap : 0,
				(y * tileSize) + (tileGap) ? yGap : 0, tileSize, tileSize));
			sprites->emplace(std::make_pair(it, std::make_unique<sf::Sprite>(sp)));
			it++;
			xGap++;
		}
	}
	if (debug)
	{
		sf::RenderTexture tileset;
		tileset.create(24, sprites.size() * tileSize);
		sf::Text text;
		sf::Font arial;
		arial.loadFromFile("Recursos/Arial.ttf");
		text.setFont(arial);
		text.setCharacterSize(7);
		text.setFillColor(sf::Color::White);
		tileset.clear(sf::Color::Black);
		for (int i = 0; i < sprites.size();i++)
		{
			text.setString(std::to_string(i));
			text.setPosition(sf::Vector2f(0, i * tileSize));
			tileset.draw(text);
			sf::Sprite sp = *sprites[i].get();
			sp.setPosition(sf::Vector2f(tileSize, i * tileSize));
			tileset.draw(sp);
		}
		tileset.getTexture().copyToImage().saveToFile("Recursos/Referencia.png");
	}
	return;
}

Mapa* Engine::mapaAtual()
{
	
	return m_mapaAtual.get();
}

void Engine::inicMapa()
{
	m_mapaAtual = std::make_unique<Mapa>(30, 25, *this);
}

void Engine::jogador(Entidade* Jogador)
{
	m_jogador = Jogador;
}

Entidade* Engine::jogador()
{
	return m_jogador;
}