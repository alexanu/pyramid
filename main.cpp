#include <vector>
#include <algorithm>

template<class V,class T>
class TimeSeries<V,T> {
public:
  typename std::vector<V>::iterator iterator;
  typename std::vector<V>::const_iterator const_iterator;
  typename T timetype;
  typename V valuetype;
  const V& after(const T& t) const {
    V tmp(t);
    const_iterator it =
      std::upper_bound(_data.begin(), _data.end() ,tmp,V::before);
    return(*it)
   };
  const V& before(const T& t) const {
    V tmp(t);
    const_iterator it =
      std::lower_bound(_data.begin(), _data.end() ,tmp,V::before);
    return(*it)
   };

  const_iterator begin() const {
    return _data.begin()
  }
  const_iterator end() const {
    return _data.end()
  }

private:
  std::vector<V> _data;
};



template<class V,class T,class A>
class Bucket<V,T> {



}
