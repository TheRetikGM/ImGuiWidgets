/**
 * @file FpsPlot.h
 * @author TheRetikGM
 * @date 1/1/2024
 */
#pragma once
#include <imgui.h>
#include <ren_utils/AvgSampler.hpp>
#include <glm/glm.hpp>

namespace ImWidgets {
  template <typename T> class FpsPlot {
    using ValueArr = ren_utils::RingBuffer<T>;
    ren_utils::AvgSampler<T> &m_sampler;
  public:
    bool m_LockPos = false;
    float m_ScaleMax = 200.0f;
    float m_PlotWidth = 80.0f;
    FpsPlot(ren_utils::AvgSampler<T> &sampler_ref) : m_sampler(sampler_ref) {}

    void DrawWindow(glm::uvec2 win_size) {
      ImGuiWindowFlags window_flags =
          ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
          ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
          ImGuiWindowFlags_NoNav;
      ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
      if (m_LockPos)
        ImGui::SetNextWindowPos(ImVec2(10.0f, win_size.y - 105.0f));
      if (ImGui::Begin("FpsPlot::FpsCounter", nullptr, window_flags))
        DrawPlot();
      ImGui::End();
    }

    void DrawPlot() {
      struct Funcs {
        static float value_getter(void *p_arr, int i) {
          ValueArr *arr = (ValueArr *)p_arr;
          return (*arr)[i];
        }
      };

      // ImGui::Text("FPS: %.1f", m_fps);
      char avg_fps[20];
      std::sprintf(avg_fps, "avg. %.1f", m_sampler.GetAvg());
      ImGui::PlotLines("FPS", &Funcs::value_getter, const_cast<ValueArr*>(&m_sampler.GetAvgBuf()), m_sampler.GetAvgBuf().Size(), 0,
                       avg_fps, 0.0f, m_ScaleMax, ImVec2(0.0f, m_PlotWidth));

      if (ImGui::BeginPopupContextWindow()) {
        ImGui::MenuItem("Lock position", NULL, &m_LockPos);
        ImGui::EndPopup();
      }
    }
  };
} // namespace ImWidgets
