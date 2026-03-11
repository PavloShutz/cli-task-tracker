#ifndef UI_HPP
#define UI_HPP

#include <string_view>

namespace ctt
{
    namespace ui
    {
        void displayHelpInfo_Add();
        void displayHelpInfo_List();
        void displayHelpInfo_Update();
        void displayHelpInfo_MarkInProgress();
        void displayHelpInfo_MarkDone();
        void displayHelpInfo_Delete();
        void displayHelpInfo();
        void displayHelpInfo(const std::string_view command);
    } // namespace ui
} // namespace ctt

#endif // UI_HPP