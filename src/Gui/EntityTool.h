#ifndef ENTITYTOOL_H_INCLUDED
#define ENTITYTOOL_H_INCLUDED
#include "Tool.h"

class EntityTool: public ITool
{
public:


    EntityTool(const std::map<std::string,Sakura::Entity>& entityList, const std::string&);
    EntityTool(const std::string& );
    virtual ~EntityTool();



    void LoadEntities(const std::map<std::string,Sakura::Entity>& entityList);
    virtual void Render(void);
    virtual std::string GetName(void);

    uint32_t selectedItem;

private:
    std::vector<std::string> entityNames;
    std::vector<Sakura::Entity> entityDefs;
    char* searchBuffer;
    const size_t searchBufferSize=64;
    std::string toolHeader;   //we use the same one for entities and triggers
};

#endif // ENTITYTOOL_H_INCLUDED
