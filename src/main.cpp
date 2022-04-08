#include "jam/physics/mass.hpp"
#include <chrono>
#include <span>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <jam/math/point_io.hpp>
#include <jam/physics/clock.hpp>
#include <jam/physics/spring_constraint.hpp>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>

void draw_line(ftxui::Canvas &c, jam::point const p0, jam::point const p1)
{
  auto const p0x = static_cast<float>(p0.x());
  auto const p0y = static_cast<float>(p0.y());
  auto const p1x = static_cast<float>(p1.x());
  auto const p1y = static_cast<float>(p1.y());
  c.DrawPointLine(
    static_cast<int>(p0x), static_cast<int>(p0y), static_cast<int>(p1x), static_cast<int>(p1y), ftxui::Color::Red);
}

void draw_shape(ftxui::Canvas &c, std::span<jam::particle> const particles)
{
  auto const n = particles.size();
  for (std::size_t i = 0; i < n; ++i) { draw_line(c, particles[i].position(), particles[(i + 1) % n].position()); }
}

int main()
{
  int mouse_x = 0;
  int mouse_y = 0;

  using namespace jam::literals;

  std::vector<jam::particle> particles;
  particles.emplace_back(jam::point{ 10_F, 10_F }, jam::infinite_mass);// NOLINT
  particles.emplace_back(jam::point{ 20_F, 10_F }, 0.1_kg);// NOLINT
  particles.emplace_back(jam::point{ 20_F, 20_F }, 0.1_kg);// NOLINT
  particles.emplace_back(jam::point{ 10_F, 20_F }, 0.1_kg);// NOLINT
  std::vector<jam::spring_constraint> springs;
  springs.emplace_back(particles[0], particles[1], 19_F);// NOLINT
  springs.emplace_back(particles[1], particles[2], 19_F);// NOLINT
  springs.emplace_back(particles[2], particles[3], 19_F);// NOLINT
  springs.emplace_back(particles[3], particles[0], 19_F);// NOLINT
  // Diagonals:
  springs.emplace_back(particles[0], particles[2], 19_F);// NOLINT
  springs.emplace_back(particles[1], particles[3], 19_F);// NOLINT

  bool picked = false;

  jam::force gravity{ 0_F, 9.8_F };// NOLINT

  auto screen = ftxui::ScreenInteractive::FitComponent();

  auto const renderer = ftxui::Renderer([&] {
    constexpr int canvas_width = 160;
    constexpr int canvas_height = 120;

    auto c = ftxui::Canvas(canvas_width, canvas_height);

    draw_shape(c, particles);
    if (picked) { c.DrawText(mouse_x, mouse_y, "Picked"); }

    screen.PostEvent(ftxui::Event::Custom);

    return canvas(std::move(c));
  });

  jam::clock clock;

  auto const game_loop = ftxui::CatchEvent(renderer, [&](ftxui::Event e) {
    if (e.is_mouse()) {
      picked = false;

      mouse_x = e.mouse().x * 2;
      mouse_y = e.mouse().y * 4;

      if (e.mouse().button == ftxui::Mouse::Left) {
        auto const particle_x = static_cast<float>(mouse_x);
        auto const particle_y = static_cast<float>(mouse_y);
        jam::point mouse_point{ jam::scalar{ particle_x }, jam::scalar{ particle_y } };
        constexpr auto picking_radius = 8_F;
        picked = length(mouse_point - particles[0].position()) < picking_radius;
        if (picked) { particles[0].move_to(jam::scalar{ particle_x }, jam::scalar{ particle_y }); }
      }
    }


    if (e == ftxui::Event::Custom) {
      auto const dt = clock.update();
      for (auto &p : particles) { p.apply(gravity); }
      for (auto &s : springs) { s.resolve_constraint(); }
      for (auto &p : particles) { p.update(dt); }
    }

    return false;
  });

  screen.Loop(game_loop);
}