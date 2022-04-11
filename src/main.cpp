#include <algorithm>
#include <span>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <jam/math/point_io.hpp>
#include <jam/physics/clock.hpp>
#include <jam/physics/spring_constraint.hpp>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>

using namespace jam::literals;
using namespace std::string_literals;

//=======================================================================================================================
namespace {

template<typename T> constexpr inline T canvas_width = T{ 160 };
template<typename T> constexpr inline T canvas_height = T{ 120 };


constexpr inline jam::force gravity{ 0_F, 9.8_F };

//----------------------------------------------------------------------------------------------------------------------

struct game_state
{
  game_state() { trail_.reserve(maximum_trail_size); }

  void draw_on(ftxui::Canvas &canvas);

  void update(ftxui::Event &event);

private:
  jam::point mouse_position_{ 0_F, 0_F };

  bool mouse_clicked_{ false };

  bool picked_{ false };

  std::size_t score_{ 0 };

  std::vector<jam::particle> thing_{
    jam::particle{ jam::point{ 10_F, 10_F }, jam::infinite_mass },// NOLINT TODO: load these from a file
    jam::particle{ jam::point{ 20_F, 10_F }, 0.1_kg },// NOLINT TODO: load these from a file
    jam::particle{ jam::point{ 20_F, 20_F }, 0.1_kg },// NOLINT TODO: load these from a file
    jam::particle{ jam::point{ 10_F, 20_F }, 0.1_kg },// NOLINT TODO: load these from a file
  };

  constexpr static inline auto spring_constant = 19_F;
  std::vector<jam::spring_constraint> thing_contraints_{
    jam::spring_constraint{ thing_[0], thing_[1], spring_constant },
    jam::spring_constraint{ thing_[1], thing_[2], spring_constant },
    jam::spring_constraint{ thing_[2], thing_[3], spring_constant },
    jam::spring_constraint{ thing_[3], thing_[0], spring_constant },
    // Diagonals:
    jam::spring_constraint{ thing_[0], thing_[2], spring_constant },
    jam::spring_constraint{ thing_[1], thing_[3], spring_constant },
  };

  // TODO: use the `z` suffix once the code base is updated to C++23.
  constexpr static inline std::size_t maximum_trail_size = 200;
  std::vector<jam::particle> trail_;

  jam::clock clock_{};

  void handle_mouse(ftxui::Event &event);

  void tick(jam::time dt);

  void collect_trail_garbage();

  void pick_the_thing();

  void update_the_score();

  void spawn_trail_particles();

  void update_physics(jam::time dt);
};

//----------------------------------------------------------------------------------------------------------------------

void draw_line(ftxui::Canvas &c, jam::point const p0, jam::point const p1, ftxui::Color color = ftxui::Color::Red)
{
  auto const p0x = static_cast<float>(p0.x());
  auto const p0y = static_cast<float>(p0.y());
  auto const p1x = static_cast<float>(p1.x());
  auto const p1y = static_cast<float>(p1.y());
  c.DrawPointLine(static_cast<int>(p0x), static_cast<int>(p0y), static_cast<int>(p1x), static_cast<int>(p1y), color);
}

void draw_shape(ftxui::Canvas &c, std::span<jam::particle const> const particles)
{
  auto const n = particles.size();
  for (std::size_t i = 0; i < n; ++i) { draw_line(c, particles[i].position(), particles[(i + 1) % n].position()); }
}

void draw_text(ftxui::Canvas &c, jam::point const &text_position, std::string const &text)
{
  auto const text_x = static_cast<float>(text_position.x());
  auto const text_y = static_cast<float>(text_position.y());
  c.DrawText(static_cast<int>(text_x), static_cast<int>(text_y), text);
}

void draw_point(ftxui::Canvas &c, jam::point const &position)
{
  auto const x = static_cast<float>(position.x());
  auto const y = static_cast<float>(position.y());
  c.DrawPointOn(static_cast<int>(x), static_cast<int>(y));
}

//----------------------------------------------------------------------------------------------------------------------

void game_state::draw_on(ftxui::Canvas &c)
{
  c.DrawText(canvas_width<int> / 2, canvas_height<int> - 1, fmt::format("Score: {}", score_));

  for (auto const &trail_particle : trail_) { draw_point(c, trail_particle.position()); }

  draw_shape(c, thing_);

  if (picked_) {
    static const auto picked_label = "Drag me aROUND!"s;
    draw_text(c, mouse_position_, picked_label);
  } else {
    draw_line(c, thing_[0].position(), mouse_position_, ftxui::Color::Blue);
    static const auto hint_label = "Pick me!"s;
    draw_text(c, mouse_position_, hint_label);
  }
}

void game_state::update(ftxui::Event &event)
{
  if (event.is_mouse()) {
    handle_mouse(event);
  } else {
    tick(clock_.update());
  }
}

void game_state::handle_mouse(ftxui::Event &event)
{
  mouse_position_ = jam::point{
    jam::scalar{ static_cast<float>(event.mouse().x * 2) },
    jam::scalar{ static_cast<float>(event.mouse().y * 4) },
  };
  mouse_clicked_ = event.mouse().button == ftxui::Mouse::Left;
}

void game_state::tick(jam::time const dt)
{
  collect_trail_garbage();
  pick_the_thing();
  update_the_score();
  spawn_trail_particles();
  update_physics(dt);
}

void game_state::collect_trail_garbage()
{
  if (trail_.size() == maximum_trail_size) {
    auto const first_particle = begin(trail_);
    auto const sentinel = end(trail_);

    trail_.erase(remove_if(first_particle,
                   sentinel,
                   [boundary_of_doom = canvas_height<jam::scalar> - 1_F](
                     jam::particle const &particle) { return particle.y() > boundary_of_doom; }),
      sentinel);
  }
}

void game_state::pick_the_thing()
{
  constexpr auto picking_radius = 8_F;
  picked_ = length(mouse_position_ - thing_[0].position()) < picking_radius && mouse_clicked_;
  if (picked_) { thing_[0].move_to(mouse_position_); }
}

void game_state::update_the_score()
{
  if (picked_) { ++score_; }
}

void game_state::spawn_trail_particles()
{
  constexpr auto score_100 = std::size_t{ 100 };
  if (picked_ && trail_.size() < maximum_trail_size && (score_ % score_100) == std::size_t{ 0 }) {
    trail_.emplace_back(mouse_position_, 0.1_kg);// NOLINT This magical number is self explanatory.
  }
}

void game_state::update_physics(jam::time const dt)
{
  for (auto &p : thing_) { p.apply(gravity); }
  for (auto &s : thing_contraints_) { s.resolve_constraint(); }
  for (auto &p : thing_) { p.update(dt); }

  for (auto &p : trail_) { p.apply(gravity); }
  for (auto &p : trail_) { p.update(dt); }
}

}// namespace

//======================================================================================================================

int main()
{
  game_state game{};

  // NOTE: not going to add it into the game_state yet.

  auto screen = ftxui::ScreenInteractive::FitComponent();

  auto const renderer = ftxui::Renderer([&] {
    auto c = ftxui::Canvas(canvas_width<int>, canvas_height<int>);
    game.draw_on(c);

    // Request new frame ASAP.
    screen.PostEvent(ftxui::Event::Custom);

    return canvas(std::move(c));
  });


  auto const game_loop = ftxui::CatchEvent(renderer, [&](ftxui::Event e) {
    game.update(e);
    return false;
  });

  screen.Loop(game_loop);
}