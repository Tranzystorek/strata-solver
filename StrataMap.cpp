#include "StrataMap.hpp"

void StrataMap::set_field(int x, int y, Color c) {
  map[x][y].color = c;

  if(c != Color::NONE)
    ++nfields;
}

std::vector<int> StrataMap::remove_row(int rownumber) {
  std::vector<int> ret;

  if(rownumber < w) {
    for(int i=0;i<h;++i) {
      Field& f = map[rownumber][i];

      if(f.color != Color::NONE) {
        ret.push_back(i);
        f.color = Color::NONE;
      }
    }
  } else {
    rownumber -= w;

    for(int i=0;i<w;++i) {
      Field& f = map[i][rownumber];

      if(f.color != Color::NONE) {
        ret.push_back(i);
        f.color = Color::NONE;
      }
    }
  }//if-else

  nfields -= ret.size();

  return ret;
}

void StrataMap::restore_row(int rownumber, Color c,
                            const std::vector<int>& positions) {
  if(rownumber < w) {
    for(auto& p : positions)
      set_field(rownumber, p, c);
  } else {
    rownumber -= w;

    for(auto& p : positions) {
      set_field(p, rownumber, c);
    }
  }//if-else
}

Color StrataMap::check_monocolor(int rownumber) const {
  Color col = Color::NONE;

  if(rownumber < w) {
    for(int i=0;i<h;++i) {
      Field& f = map[rownumber][i];

      if(f.color != Color::NONE) {
        if(col == Color::NONE)
          col = f.color;
        else if(f.color != col)
          return Color::NONE;
      }
    }//for
  } else {
    rownumber -= w;

    for(int i=0;i<w;++i) {
      Field& f = map[i][rownumber];

      if(f.color != Color::NONE) {
        if(col == Color::NONE)
          col = f.color;
        else if(f.color != col)
          return Color::NONE;
      }
    }//for
  }//if-else

  return col;
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

Field::Field(Color c) : color(c) {

}

StrataMap::StrataMap(int w, int h)
  : w(w),
    h(h),
    nfields(0) {
  map = new Field*[w];

  for(int i=0;i<w;++i)
    map[i] = new Field[h]();
}

StrataMap::~StrataMap() {
  for(int i=0;i<w;++i)
    delete[] map[i];

  delete[] map;
}
