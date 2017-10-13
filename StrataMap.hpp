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

  void set_ribbon(Color);

  Color fcolor;
  Color ribcolor;
  bool covered;
};

class StrataMap {
public:
  StrataMap(int, int);
  ~StrataMap();

  void add_ribbon(int rownumber, Color c);
  void reset_ribbons();

  void set_field_color(int x, int y, Color c);

  bool check();

private:
  int w;
  int h;
  Field** map;
};
