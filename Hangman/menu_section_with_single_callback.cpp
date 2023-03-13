#include "menu_section_with_single_callback.h"

MenuSectionWithSingleCallback::MenuSectionWithSingleCallback(const Rect& sectionRect) : MenuSection {sectionRect}
{
}

void MenuSectionWithSingleCallback::executeCurrentEntry()
{
    if (callback) {
        callback(getCurrentEntry());
    }
}

void MenuSectionWithSingleCallback::setCallback( MenuEntryCallback callback_)
{
    callback = callback_;
}
