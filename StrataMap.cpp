#include "StrataMap.hpp"

void StrataMap::set_field_color(int x, int y, Color c) {
  map[x][y].fcolor = c;
}

const char* color_to_string(Color c) {
  switch(c) {
  case Color::YELLOW:
    return "Yellow";

  case Color::RED:
    return "Red";

  case Color::GREEN:
    return "Green";

  case Color::PURPLE:
    return "Purple";

  case Color::ORANGE:
    return "Orange";
  }
}

bool StrataMap::check() {
  for(int i=0;i<w;++i)
    for(int j=0;j<h;++j) {
      const Field& f = map[i][j];

      if(f.fcolor != Color::NONE &&
         f.fcolor != f.ribcolor)
        return false;
    }

  return true;
}

void StrataMap::reset_ribbons() {
  for(int i=0;i<w;++i)
    for(int j=0;j<h;++j) {
      Field& f = map[i][j];

      f.ribcolor = Color::NONE;
      f.covered = false;
    }
}

void Field::set_ribbon(Color c) {
  if(covered)
    ribcolor = c;
  else
    covered = true;
}

bool StrataMap::add_ribbon(int rownumber, Color c) {
  if(rownumber < w) {
    for(int i=0;i<h;++i) {
      Field& f = map[rownumber][i];

      f.set_ribbon(c);

      if(f.ribcolor != Color::NONE &&
         f.fcolor != Color::NONE &&
         f.fcolor != f.ribcolor)
        return false;
    }
  } else {
    rownumber -= w;

    for(int i=0;i<w;++i) {
      Field& f = map[i][rownumber];

      f.set_ribbon(c);

      if(f.ribcolor != Color::NONE &&
         f.fcolor != Color::NONE &&
         f.fcolor != f.ribcolor)
        return false;
    }
  }

  return true;
}

Field::Field(Color c)
  : fcolor(c),
    ribcolor(Color::NONE),
    covered(false) {

}

StrataMap::StrataMap(int w, int h)
  : w(w),
    h(h) {
  map = new Field*[w];

  for(int i=0;i<w;++i)
    map[i] = new Field[h]{};
}

StrataMap::~StrataMap() {
  for(int i=0;i<w;++i)
    delete[] map[i];

  delete[] map;
}
