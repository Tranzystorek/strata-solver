#include "StrataMap.hpp"

void StrataMap::set_field(int x, int y, Color c) {
  map_[x][y].color = c;

  if(c != Color::NONE)
    ++nfields_;
}

std::vector<int> StrataMap::remove_row(int rownumber) {
  std::vector<int> ret;

  if(rownumber < w_) {
    for(int i=0;i<h_;++i) {
      Field& f = map_[rownumber][i];

      if(f.color != Color::NONE) {
        ret.push_back(i);
        f.color = Color::NONE;
      }
    }
  } else {
    rownumber -= w_;

    for(int i=0;i<w_;++i) {
      Field& f = map_[i][rownumber];

      if(f.color != Color::NONE) {
        ret.push_back(i);
        f.color = Color::NONE;
      }
    }
  }//if-else

  nfields_ -= ret.size();

  return ret;
}

void StrataMap::restore_row(int rownumber, Color c,
                            const std::vector<int>& positions) {
  if(rownumber < w_) {
    for(auto& p : positions)
      set_field(rownumber, p, c);
  } else {
    rownumber -= w_;

    for(auto& p : positions) {
      set_field(p, rownumber, c);
    }
  }//if-else
}

Color StrataMap::check_monocolor(int rownumber) const {
  Color col = Color::NONE;

  if(rownumber < w_) {
    for(int i=0;i<h_;++i) {
      Field& f = map_[rownumber][i];

      if(f.color != Color::NONE) {
        if(col == Color::NONE)
          col = f.color;
        else if(f.color != col)
          return Color::NONE;
      }
    }//for
  } else {
    rownumber -= w_;

    for(int i=0;i<w_;++i) {
      Field& f = map_[i][rownumber];

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
  : w_(w),
    h_(h),
    nfields_(0) {
  int size = w_ * h_;

  storage_ = new Field[size]();
  map_ = new Field*[w_];

  Field* end = storage_ + size;
  Field** it = map_;

  for(Field* ptr = storage_;
      ptr < end; ptr += h_, ++it)
    *it = ptr;
}

StrataMap::~StrataMap() {
  delete[] map_;
  delete[] storage_;
}
