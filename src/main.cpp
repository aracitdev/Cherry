#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-sfml.h>
#include <Sakura/Map.h>
#include <Sakura/EntityLoader.h>
#include "Utility/SpriteExtraction.h"
#include "GUI/EntityTool.h"
#include "GUI/ToolSelection.h"
#include "GUI/LevelRender.h"
#include "Utility/Config.h"
#include <Sakura/FileFunctions.h>
#include "Utility/Tiler.h"
#include "Utility/Logger.h"
#include "Gui/MapRender.h"
#include "Gui/EntityRenderDef.h"
#include "GUI/ViewController.h"


std::string FindCelestePath(void)
{
    if(Sakura::FileExists("C:\\Program Files\\Epic Games\\Celeste"))    //default epic games
        return "C:\\Program Files\\Epic Games\\Celeste";
    if(Sakura::FileExists("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Celeste"))    //default steam
        return "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Celeste";
    return std::string("");
}


bool SetIcon(sf::RenderWindow& window, const std::string& file)
{
    sf::Image im;
    if(!im.loadFromFile(file))
        return false;
    window.setIcon(im.getSize().x, im.getSize().y, im.getPixelsPtr());
    return true;
}

bool LoadCelesteContent(sf::Texture& atlasTexture, std::map<std::string,Sprite>& sprites, std::map<std::string,Sakura::Entity>& entities, std::map<std::string,Sakura::Entity>& triggers,
                        std::map<char,Tileset>& fgTiles, std::map<char,Tileset>& bgTiles, std::map<std::string,std::vector<EntityRenderDef>>& renderAtlas)
{
    std::string celestePath = Config::GetInstance().Get("celeste_path",FindCelestePath());
    if(!Sakura::FileExists(celestePath))
    {
        Logger::GetInstance().Log("Failed to find celeste path " + celestePath + ". Searching...", Logger::ERROR);
        celestePath=Config::GetInstance().Set("celeste_path",FindCelestePath());
    }
    std::string atlasPath = celestePath + "\\Content\\Graphics\\Atlases";
    Logger::GetInstance().Log("Found celeste path " + celestePath, Logger::INFO);
    Logger::GetInstance().Log("Startup... Loading Atlas file...", Logger::INFO);
    if(!LoadAtlas(atlasPath + "\\gameplay0.data","resources/gameplay.png",atlasPath + "\\gameplay.meta",sprites,atlasTexture))
    {
        Logger::GetInstance().Log("Failed to load the gameplay atlas", Logger::ERROR);
        return false;
    }
    if(!Sakura::LoadEntityXML("resources/defaultEntities.xml",entities))
    {
        Logger::GetInstance().Log("Failed to load default entities resources/defaultEntities.xml", Logger::ERROR);
        return false;
    }
    Sakura::LoadEntityXML("resources/defaultTriggers.xml",triggers);

    LoadEntityRenderDefs("resources/defaultEntityRenders.xml",sprites, renderAtlas);
    LoadTileXML(celestePath + "\\Content\\Graphics\\ForegroundTiles.xml", fgTiles, sprites);
    LoadTileXML(celestePath + "\\Content\\Graphics\\BackgroundTiles.xml", bgTiles, sprites);
    return true;
}


int main(int argc, char* argv[])
{
    sf::Clock c;
    Logger::GetInstance().CoutLog=Logger::DEBUG;
    sf::Texture atlasTexture;
    std::map<std::string,Sprite> sprites;
    std::map<std::string,Sakura::Entity> triggers, entities;
    std::map<char,Tileset> fgTiles,bgTiles;
    std::map<std::string,std::vector<EntityRenderDef>> renderDefs;
    LoadCelesteContent(atlasTexture,sprites,entities,triggers,fgTiles,bgTiles,renderDefs);

    Sakura::Map mp;
    mp.LoadFromBin("resources/7-Summit.bin");
    mp.SaveToXML("resources/7-Summit.xml");
    MapRender render(&mp);
    ToolSelection selection;
    selection.tools.push_back(new EntityTool(entities,"Entities"));
    selection.tools.push_back(new EntityTool(triggers,"Triggers"));


    ViewController view(sf::Vector2f(mp.rooms[1]->x, mp.rooms[1]->y),sf::Vector2f(0.75*800,600*0.9), sf::FloatRect(0,0.1,0.75,1.0));


    sf::RenderWindow mainWindow(sf::VideoMode(800,600),"Cherry");
    sf::Vector2u windowSize = mainWindow.getSize();
    ImGui::SFML::Init(mainWindow);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
    SetIcon(mainWindow, "resources/cherry.png");
    mainWindow.setFramerateLimit(15);

    mainWindow.resetGLStates();
    sf::Clock timer;

    sf::Sprite* testSprite = fgTiles['a'].Get(0b11100101);
    if(testSprite == nullptr)
        std::cout <<"Failed to load test sprite.\n";
    testSprite->setPosition(sf::Vector2f(300,300));
    testSprite->setScale(sf::Vector2f(20,20));

    while(mainWindow.isOpen())
    {
        ImGui::SFML::Update(mainWindow,timer.restart());
        mainWindow.clear();
        view.SetWindowView(mainWindow);
        render.Render(fgTiles, bgTiles, sprites, mainWindow, renderDefs);
        mainWindow.setView(mainWindow.getDefaultView());
        ImGui::SetNextWindowPos({windowSize.x * 3.0f/4.0f,0.0f});
        ImGui::SetNextWindowSize({windowSize.x/4.0f, (float)windowSize.y});
        ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_NoDecoration);
        selection.Render();
        ImGui::End();
        ImGui::SFML::Render(mainWindow);
        mainWindow.display();

        sf::Event ev;
        if(mainWindow.pollEvent(ev))
        {
            ImGui::SFML::ProcessEvent(ev);
            if(ev.type == sf::Event::Closed)
                mainWindow.close();
            if(ev.type == sf::Event::Resized)
            {
                windowSize = mainWindow.getSize();
                view.OnUpdate(windowSize);
            }
            view.ProcessEvent(ev);
        }
    }

    ImGui::SFML::Shutdown();
    Config::GetInstance().Save();
    return 0;
}
