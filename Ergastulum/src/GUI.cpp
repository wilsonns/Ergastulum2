#include "GUI.h"


//Constructors & Destructors
GUI::GUI(float x, float y, float width, float height, sf::Color innerColor
	, sf::Color outlineColor, sf::RenderTarget* window,Engine*engine)
{

	//adcionar as fontes à serem usadas pela GUI
	this->addFont("Arial");
	this->addFont("CloisterBlack");

	this->m_engine = engine;

	//Seta Posição e Tamanho do retangulo basico da GUI
	this->m_panel.setPosition(sf::Vector2f(x, window->getSize().y / 1.5f));

	//Seta cores da borda e do interior do retangulo
	this->m_innerColor = innerColor;
	this->m_panel.setFillColor(m_innerColor);
	this->m_outlineColor = outlineColor;
	this->m_panel.setOutlineColor(m_outlineColor);
	this->m_panel.setOutlineThickness(1.f);
	this->m_panel.setSize(sf::Vector2f(
		window->getSize().x - (this->m_panel.getOutlineThickness())
		, (window->getSize().y / 3.f) - (this->m_panel.getOutlineThickness())));

	this->m_messageBox.setPosition(sf::Vector2f((float)(window->getSize().x / 2)-100
		,(float)this->m_panel.getPosition().y + 16));
	this->m_messageBox.setFillColor(m_innerColor);
	this->m_messageBox.setOutlineColor(m_outlineColor);
	this->m_messageBox.setOutlineThickness(1.f);
	this->m_messageBox.setSize(sf::Vector2f(450, 160));

	//Bar
	this->m_bars.insert(std::make_pair("maxHP", std::make_unique<Bar>(this->m_panel.getGlobalBounds().left + 10, this->m_panel.getGlobalBounds().top + 24,
		200.f, 24.f, 1.f, sf::Color::Color(180,20,20))));
	this->m_bars.emplace(std::make_pair("currentHP", std::make_unique<Bar>(this->m_panel.getGlobalBounds().left + 10, this->m_panel.getGlobalBounds().top + 24,
		200.f, 24.f, 1.f, sf::Color::Red)));
	this->m_bars.emplace(std::make_pair("maxEnergy", std::make_unique<Bar>(this->m_panel.getGlobalBounds().left + 10, this->m_panel.getGlobalBounds().top + 48,
		200.f, 24.f, 1.f, sf::Color::Color(180,180,20))));
	this->m_bars.emplace(std::make_pair("currentEnergy", std::make_unique<Bar>(this->m_panel.getGlobalBounds().left + 10, this->m_panel.getGlobalBounds().top + 48,
		200.f, 24.f, 1.f, sf::Color::Yellow)));


	addMessage("???",font("Arial"), sf::Color::Black);
	addText((m_bars["currentHP"].get()->bar.getPosition().x +
		(m_bars["currentHP"].get()->bar.getPosition().x + m_bars["currentHP"].get()->bar.getSize().x) / 2),
		m_bars["currentHP"].get()->bar.getPosition().y, 12, "HP", "HP:", font("Arial"), sf::Color::Black);

	addText((m_bars["currentEnergy"].get()->bar.getPosition().x +
		(m_bars["currentEnergy"].get()->bar.getPosition().x + m_bars["currentEnergy"].get()->bar.getSize().x) / 2),
		m_bars["currentEnergy"].get()->bar.getPosition().y, 12, "Energy", "Energy:", font("Arial"), sf::Color::Black);
}

GUI::~GUI()
{

}//DTOR


//Accessors
/**Return a sf::Font by its name. If no font is found, returns Arial*/
sf::Font *GUI::font(sf::String font)
{
	if (this->m_fonts.find(font) != this->m_fonts.end())
	{
		return m_fonts[font].get();
	}
	return m_fonts["Arial"].get();
}

//Functions
/**Updates the GUI.*/
void GUI::update(sf::RectangleShape& box, std::vector<std::unique_ptr<Message>>* messages)
{
	float size = box.getSize().y / 16;

	if (messages->size() > size)
	{
		while (messages->size() != size)
		{
			messages->erase(messages->begin());
		}
	}
	int i = 0;
	for (std::vector<std::unique_ptr<Message>>::iterator message = messages->begin();
		message != messages->end();message++, i++)
	{
		message->get()->text()->setPosition(box.getPosition().x + 2, 
			box.getPosition().y + (i * 16));
	}
	float hp = m_engine->player()->currentResource("Health");
	float maxHp = m_engine->player()->maxResource("Health");
	float newWidth = hp / maxHp;
	newWidth *= 200;
	if (newWidth < 0) { newWidth = 0; }
	m_bars["currentHP"].get()->width(newWidth);
	
	float energy = m_engine->player()->currentResource("Energy");
	float maxEnergy = m_engine->player()->maxResource("Energy");
	newWidth = energy / maxEnergy;
	newWidth *= 200;
	if (newWidth < 0) { newWidth = 0; }
	m_bars["currentEnergy"].get()->width(newWidth);

	m_text["HP"].get()->setString("HP:" + std::to_string((int)(hp)) + "/" + std::to_string((int)(maxHp)));
	m_text["Energy"].get()->setString("Energy:" + std::to_string((int)(energy)) + "/" + std::to_string((int)(maxEnergy)));
}

/**Renders the GUI to the window.*/
void GUI::render(sf::RenderTarget* window)
{
	this->update(m_messageBox, &m_messages);
	window->draw(this->m_panel);
	
	window->draw(m_bars["maxHP"].get()->bar);
	window->draw(m_bars["currentHP"].get()->bar);
	window->draw(m_bars["maxEnergy"].get()->bar);
	window->draw(m_bars["currentEnergy"].get()->bar);

	if (m_text.size() > 0)
	{
		for (auto const& text : m_text)
		{
			if (text.second.get()->getString().getSize() > 0)
			{
				window->draw(*text.second.get());
			}
		}
	}
	window->draw(this->m_messageBox);
	for (auto const& message : m_messages)
	{
		message.get()->render(window);
	}
}

/**Adds a new sf:Font from a file to be used in the GUI.*/
bool GUI::addFont(sf::String file)
{
	sf::Font tmp;
	if (this->m_fonts.find(file) == this->m_fonts.end())
	{
		if (tmp.loadFromFile("Assets/Fonts/" + file + ".ttf"))
		{
			this->m_fonts.emplace(file, std::make_unique<sf::Font>(tmp));
			std::cout << "Font loaded!" << std::endl;
			return true;
		}
	}
	else
	{
		std::cout << "Font already exists" << std::endl;
		return false;
	}
}

/**Adds a new sf::Text to be displayed on the GUI.*/
void GUI::addText(float x, float y, int size,sf::String label, sf::String text, sf::Font* font, sf::Color color)
{
	sf::Text tmp(text, *font, size);
	tmp.setFillColor(color);
	tmp.setPosition(x,y);
	m_text.insert(std::make_pair(label, std::make_unique<sf::Text>(tmp)));
}

/**Adds a new Message to be displayed on the messsageBox.*/
void GUI::addMessage(sf::String text,sf::Font* font, sf::Color color)
{
	auto message = std::make_unique<Message>(text, font, color);
	this->m_messages.push_back(std::move(message));
}


