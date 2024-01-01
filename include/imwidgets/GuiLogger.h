/**
 * @file GuiLogger.h
 * @author TheRetikGM
 * @date 1/1/2024
 */
#pragma once
#include "ren_utils/RingBuffer.hpp"
#include "ren_utils/logging.hpp"

namespace ImWidgets {
  class GuiLogger : public ren_utils::LogListener {
    struct LogEntry { std::string timestamp; ren_utils::LogInfo entry; };
  public:
    /// Auto scroll to the last log.
    bool m_AutoScroll = true;
    /// Pause logging output.
    /// @note Logs emitted when paused are lost.
    bool m_PauseLogging = false;

    /**
     * @brief Construct a new instance of GuiLogger
     * @param log_count Number of logs to display. When this limit is rached, then the oldest ons are discarded.
     * @param auto_scroll Automatically scroll to the last log.
     * @param pause_logging Do not register any logs. This can be undone by setting the m_PuaseLogging field.
     */
    GuiLogger(unsigned log_count = 1000, bool auto_scroll = true, bool pause_logging = false);

    void OnLog(const ren_utils::LogInfo& log) override;

    /// Draw the ImGui window.
    void Draw();

  private:
    bool m_scrollBottom = false;
    ren_utils::RingBuffer<LogEntry> m_logs;
  };
} // namespace ImWidgets
