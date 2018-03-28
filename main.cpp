
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



template <class T>
class Trade {
public:
  typedef typename T::DoubleType DoubleType;
  typedef typename T::SizeType SizeType;
  typedef typename T::TimeType TimeType;
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

class TickTraits {
public:
  typedef  double DoubleType;
  typedef unsigned int SizeType ;
  typedef int64_t TimeType;
};


template <class T>
class Quote {
public:
  typedef typename T::DoubleType DoubleType;
  typedef typename T::SizeType SizeType;
  typedef typename T::TimeType TimeType;
  bool eligibe() const {
    return true;
  }
  DoubleType bid() const {
    return _bid;
  }
  DoubleType ask() const {
    return _bid;
  }
  SizeType bidsz() const {
    return _bidsz;
  }
  SizeType asksz() const {
    return _asksz;
  }
  TimeType getTime() const {
    return _time;
  }
  DoubleType spread() const {
    return _ask - _bid;
  }
  template<class Visitor>
  void accept(Visitor& v) {
    v.visit(*this);
  }
private:
  DoubleType _bid;
  DoubleType _ask;
  SizeType _bidsz;
  SizeType _asksz;
  TimeType _time;
};


template <class TickType,class DoubleType=double, class SizeType=int64_t>
class TickVisitor {
};


 
template <class TickTraits>
class TickVisitor<Trade<TickTraits>> {
  typedef  Trade<TickTraits> TradeType;
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


template <class TickTraits>
class TickVisitor<Quote<TickTraits> > {
  typedef  Quote<TickTraits> TickType;
public:
  void visit(const TickType& e)
  {
    if(count==0) {
      first=&e;
      prev=nullptr;
    }
    if(prev) {
      TimeXspread =+ prev.spread() * ( e.getTime() - prev->df.getTime() );
    }
    
     
  }
private:
  typename TickTraits::DoubleType AvgSpread;
  typename TickTraits::DoubleType AvgBidSize;
  typename TickTraits::DoubleType AvgAskSize;
  typename TickTraits::DoubleType AvgBid;
  typename TickTraits::DoubleType AvgAsk;
  typename TickTraits::DoubleType TimeXspread;
  
  TickType* first;
  TickType* last;
  TickType* prev;
  int64_t count;
};




int main() {
  Quote<TickTraits> x;
  TickVisitor<Quote<TickTraits>> y;
  return 0;
}
