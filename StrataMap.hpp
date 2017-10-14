#ifndef STRATAMAP_HPP
#define STRATAMAP_HPP

#include <vector>

enum class Color {
  NONE,
  YELLOW,
  RED,
  PURPLE,
  GREEN,
  ORANGE
};

const char* color_to_string(Color);

struct Field {
  Field(Color = Color::NONE);

  Color color;
};

class StrataMap {
public:
  StrataMap(int, int);
  ~StrataMap();

  void set_field(int x, int y, Color c);

  std::vector<int> remove_row(int rownumber);
  void restore_row(int rownumber, Color c,
                   const std::vector<int>& positions);

  Color check_monocolor(int rownumber);

  int get_nrows() const { return w+h; }
  bool is_empty() const { return !nfields; }

  inline int human_readable_rownumber(int rownumber) const {
    return (rownumber < w) ? (w - rownumber - 1) : rownumber;
  }

private:
  int w;
  int h;
  int nfields;
  Field** map;
};

#endif //STRATAMAP_HPP
