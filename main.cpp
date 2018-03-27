
#include <vector>
#include <algorithm>


template<class V,class T>
class TimeSeries {
public:
  typedef typename std::vector<V>::iterator iterator;
  typedef typename std::vector<V>::const_iterator const_iterator;
  
  typedef T timetype;
  typedef V valuetype;
  const V& after(const T& t) const {
    V tmp(t);
    const_iterator it =
      std::upper_bound(_data.begin(), _data.end() ,tmp,V::before);
    return(*it);
   };
  const V& before(const T& t) const {
    V tmp(t);
    const_iterator it =
      std::lower_bound(_data.begin(), _data.end() ,tmp,V::before);
    return(*it);
   };

  const_iterator begin() const {
    return _data.begin();
  }
  const_iterator end() const {
    return _data.end();
  }

private:
  std::vector<V> _data;
};



template<class V>
class Bucket {
  
};



template <class DoubleType=double, class SizeType=int64_t,class TimeType=int64_t>
class Trade {
public:
  bool eligibe() const {
    return true;
  }
  DoubleType notional() const {
    return _price*_size;
  }
  bool isOpen() const {
    return false;
  }
  bool isClose() const {
    return false;
  }
  SizeType getSize() const {
  }
  DoubleType getPrice() const {
  }
  TimeType getTime() const {
    return _time;
  }
  template<class Visitor>
  void accept(Visitor& v) {
    v.visit(*this);
  }
private:
  DoubleType _price;
  SizeType _size;
  TimeType _time;
};


template <class TickType,class DoubleType=double, class SizeType=int64_t>
class TickVisitor {
};


 
template <class A,class B,class C>
class TickVisitor<Trade<A,B,C> > {
  typedef  Trade<A,B,C> TradeType;
public:
  void visit(const TradeType& e)
  {
    count++;
    quantity += e.getSize();
    notional += e.notional();
  }
private:
  typename TradeType::DoubleType notional;
  typename TradeType::SizeType quantity;
  TradeType first;
  TradeType last;
  int64_t count;
};


int main() {
  return 0;
}
