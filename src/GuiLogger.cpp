/**
 * @file GuiLogger.cpp
 * @author TheRetikGM
 * @brief Implementation of GuiLogger
 */
#include "GuiLogger.h"
#include "imgui.h"
#include "ren_utils/basic.h"

using namespace ImWidgets;

GuiLogger::GuiLogger(unsigned log_count, bool auto_scroll, bool pause_logging)
    : m_AutoScroll(auto_scroll), m_PauseLogging(pause_logging),
      m_logs(log_count) {}

void GuiLogger::OnLog(const ren_utils::LogInfo &log) {
  if (m_PauseLogging)
    return;
  m_logs.PushBack({ren_utils::TimeInfo(), log});
  if (m_AutoScroll)
    m_scrollBottom = true;
}

void GuiLogger::Draw() {
  ImGui::Begin("Logger");
  ImVec2 a_size = ImGui::GetContentRegionMax();
  ImGuiTableFlags flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY |
                          ImGuiTableFlags_RowBg |
                          ImGuiTableFlags_SizingFixedFit |
                          ImGuiTableFlags_Hideable;
  if (ImGui::BeginTable(
          "table_log", 4, flags,
          ImVec2(0.0f, a_size.y - ImGui::GetTextLineHeight() * 2.0f))) {
    if (ImGui::BeginPopupContextWindow()) {
      ImGui::MenuItem("Autoscroll", "", &m_AutoScroll);
      ImGui::MenuItem("Pause logging", "", &m_PauseLogging);
      ImGui::Separator();
      if (ImGui::Selectable("Clear logs"))
        m_logs.Clear();
      ImGui::EndPopup();
    }
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableSetupColumn("Timestamp");
    ImGui::TableSetupColumn("File");
    ImGui::TableSetupColumn("Type");
    ImGui::TableSetupColumn("Log");
    ImGui::TableHeadersRow();

    ImGuiListClipper clipper;
    clipper.Begin((int)m_logs.Size());
    while (clipper.Step()) {
      for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++) {
        LogEntry &e = m_logs[i];

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("%4i-%02i-%02i %02i:%02i:%02i",
            e.timestamp.m_Year, e.timestamp.m_Month, e.timestamp.m_Day,
            e.timestamp.m_Hour, e.timestamp.m_Minute, e.timestamp.m_Second
            );

        ImGui::TableNextColumn();
        ImGui::Text("%s:%i", e.entry.file.filename().string().c_str(),
                    e.entry.line);

        ImGui::TableNextColumn();
        switch (e.entry.level) {
        case ren_utils::LogLevel::info:
          ImGui::TextColored({0, 1, 1, 1}, "%s", ren_utils::LOG_LEVEL_STRINGS[(int)e.entry.level]);
          break;
        case ren_utils::LogLevel::status:
          ImGui::TextColored({1, 0, 1, 1}, "%s", ren_utils::LOG_LEVEL_STRINGS[(int)e.entry.level]);
          break;
        case ren_utils::LogLevel::warning:
          ImGui::TextColored({1, 1, 0, 1}, "%s", ren_utils::LOG_LEVEL_STRINGS[(int)e.entry.level]);
          break;
        case ren_utils::LogLevel::error:
          ImGui::TextColored({1, 0, 0, 1}, "%s", ren_utils::LOG_LEVEL_STRINGS[(int)e.entry.level]);
          break;
        case ren_utils::LogLevel::critical:
          ImGui::TextColored({1, 0, 1, 0}, "%s", ren_utils::LOG_LEVEL_STRINGS[(int)e.entry.level]);
          break;
        }

        ImGui::TableNextColumn();
        ImGui::Text("%s", e.entry.message.c_str());
      }
    }

    if (m_scrollBottom && m_AutoScroll)
      ImGui::SetScrollHereY(1.0f);
    m_scrollBottom = false;

    ImGui::EndTable();
  }
  ImGui::End();
}
