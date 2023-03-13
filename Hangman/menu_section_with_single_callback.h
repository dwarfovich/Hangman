#pragma once

#include "menu_section.h"
#include "menu_entry_callback.h"

class MenuSectionWithSingleCallback : public MenuSection
{
public:
    MenuSectionWithSingleCallback() = default;
    MenuSectionWithSingleCallback(const Rect& sectionRect);

    void executeCurrentEntry();
    void setCallback( MenuEntryCallback callback);

private:
    MenuEntryCallback callback;
};
