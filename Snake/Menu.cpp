#include "Menu.h"
#include <cassert>

namespace Menu
{
    void InitMenuItem(MenuItem& item)
    {
        for (auto& child : item.children)
        {
            child->parent = &item;
            InitMenuItem(*child);
        }
    }

    void SelectMenuItem(Menu& menu, MenuItem* item)
    {
        assert(item != &menu.rootItem);

        if (menu.selectedItem == item)
        {
            return;
        }

        if (item && !item->isEnabled)
        {
            return;
        }

        if (menu.selectedItem)
        {
            menu.selectedItem->text.setFillColor(menu.selectedItem->deselectedColor);
        }

        menu.selectedItem = item;

        if (menu.selectedItem)
        {
            menu.selectedItem->text.setFillColor(menu.selectedItem->selectedColor);
        }
    }

    bool SelectPreviousMenuItem(Menu& menu)
    {
        if (menu.selectedItem)
        {
            MenuItem* parent = menu.selectedItem->parent;
            assert(parent); 

            auto it = std::find(parent->children.begin(), parent->children.end(), menu.selectedItem);
            if (it != parent->children.begin())
            {
                SelectMenuItem(menu, *(--it));

                return true;
            }
        }

        return false;
    }

    bool SelectNextMenuItem(Menu& menu)
    {
        if (menu.selectedItem)
        {
            MenuItem* parent = menu.selectedItem->parent;
            assert(parent); 

            auto it = std::find(parent->children.begin(), parent->children.end(), menu.selectedItem);
            if (it != parent->children.end() - 1)
            {
                SelectMenuItem(menu, *(++it));

                return true;
            }
        }
        return false;
    }

    bool ExpandSelectedItem(Menu& menu)
    {
        if (menu.selectedItem && menu.selectedItem->children.size() > 0)
        {
            SelectMenuItem(menu, menu.selectedItem->children.front());

            return true;
        }

        return false;
    }

    bool CollapseSelectedItem(Menu& menu)
    {
        if (menu.selectedItem && menu.selectedItem->parent && menu.selectedItem->parent != &menu.rootItem)
        {
            SelectMenuItem(menu, menu.selectedItem->parent);

            return true;
        }
        return false;
    }

    void SelectSwitchSetting(MenuItem& menu, Core_Game::Game& game)
    {
        if (menu.text.getString() == "Music")
        {
            menu.switchText.setString(game.GetSettingInString("music"));
        }
        else if (menu.text.getString() == "Sound")
        {
            menu.switchText.setString(game.GetSettingInString("sound"));
        }
    }

    MenuItem* GetCurrentMenuContext(Menu& menu)
    {
        return menu.selectedItem ? menu.selectedItem->parent : &menu.rootItem;
    }

    void DrawMenu(Menu& menu, sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin)
    {
        MenuItem* expandedItem = GetCurrentMenuContext(menu);

        std::vector<sf::Text*> texts;
        texts.reserve(expandedItem->children.size());

        for (auto& child : expandedItem->children)
        {
            if (child->isEnabled)
            {
                texts.push_back(&child->text);
            }
        }

        DrawItemsList(window, texts, expandedItem->childrenSpacing, expandedItem->childrenOrientation, expandedItem->childrenAlignment, position, origin);
    }
}