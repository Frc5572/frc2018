/*! \file varopt.h
 *  A set of tools to allow for optional parameters to be unordered. 
 *  Developers planning on using this should look at varopt(), varopt_def(), and varopt_eval()
 */

#ifndef VAROPT_H_
#define VAROPT_H_

#include "cpreprocessor.h"

#include <utility>

/*! \brief define variadic option type
 *  \param v name of option type to use
 */
#define varopt_def(v) namespace varopt_def { struct _##v {\
  template <typename T> inline varopt_val<_##v, T> operator=(T t){\
    return varopt_val<_##v, T>(t);\
  }\
};} __attribute__((unused)) static varopt_def::_##v v;

/*! \brief evaluate variadic option
 *  \param v name of variadic list
 *  \param t name of variadic type. The type must be passed through varopt_def().
 *  \param d default value if variadic option is not explicitly defined
 */
#define varopt_eval(v, t, d) auto t = v.template get<varopt_def::_##t>(d);

/*
 Example for optional parameters
 
 Optional Parameters
 
\f{tabular} {| c | c |}
\hline test & test \\
\hline test & test \\
\hline test & test \\
\hline
\f}
 */

/*! \brief value type for varopt
 */
template <typename N, typename T>
struct varopt_val {
  /*! \brief referencable alias for template parameter N
 */
  typedef N name;
  /*! \brief referencable alias for template parameter T
 */
  typedef T type;
  /*! \brief stored value
 */
  T val;
  /*! \brief constructor initializing val
 */
  inline varopt_val(T t) : val(t) {}
};

/*! \brief generic helper for determining whether or not to use the varopt value or the default
 */
template <class A, class B>
struct varopt_helper {
  template <typename aT, typename bT>
  inline static bT get(__attribute__((unused)) aT value, bT _default){
    return _default;
  }
};


/*! \brief type-specialized helper for determining whether or not to use the varopt value or the default
 */
template <class A>
struct varopt_helper<A,A> {
  template <typename aT, typename bT>
  inline static bT get(aT value, __attribute__((unused)) bT _default){
    return value;
  }
};

/*! \brief list of variadic options
 */
template <typename T, typename ... K>
class varopt_list {
public:
  /*! \brief constructor which takes a list of varopt_val
  */
  varopt_list(T t, K ... k) : val(t), next(k...){}
  /*! \brief gets option given type
   *  \param _default default value for when no option is found to match the type
  */
  template <typename D, typename dT>
  inline dT get(dT _default){
    return varopt_helper<typename decltype(val)::name, D>::get(val.val, next.template get<D, dT>(_default));
  }
private:
  T val;
  varopt_list<K...> next;
};

/*! \brief list of variadic options
 */
template <typename T>
class varopt_list<T> {
public:
  /*! \brief constructor which takes a list of varopt_val
  */
  varopt_list(T t) : val(t){}
  /*! \brief gets option given type
   *  \param _default default value for when no option is found to match the type
  */
  template <typename D, typename dT>
  inline dT get(dT _default){
    return varopt_helper<typename decltype(val)::name, D>::get(val.val, _default);    
  }
private:
  T val;
};

/*! \brief an empty list of variadic options
 */
class varopt_empty_list {
public:
  /*! \brief gets option given type. Always returns _default.
   *  \param _default default value for when no option is found to match the type
  */
  template <typename D, typename dT>
  inline dT get(dT _default){
    return _default;    
  }
};

/*! \brief return varopt list or empty_varopt_list given arguments
 */
template <typename ... T>
inline auto varopt(T... t){
  return varopt_list<T...>(t...);
}

/*! \brief return varopt list or empty_varopt_list given arguments
 */
template <>
inline auto varopt<>(){
  return varopt_empty_list();
}
//*/
#endif