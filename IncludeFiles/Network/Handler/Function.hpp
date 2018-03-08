#ifndef		ZL_RULE_HPP_
# define	ZL_RULE_HPP_

namespace ZlNetwork
{
  namespace Handler
  {


    class IFunction
    {
    public:
      bool operator()() { return this->FunctionCall(); }
    protected:
      virtual bool FunctionCall() = 0;
    };


    template <typename T>
    class Function;




    template <typename T, typename U>
    class Function<T (U::*)()> : public IFunction
    {
    public:
      typedef T (U::*memberFct)();

    public:

      Function(U & obj,  memberFct fct)
	:_obj(obj), _fct(fct)
      { }

      virtual ~Function() { }


      virtual bool FunctionCall() { (_obj.*_fct)(); return true; }

      T operator()() { return (_obj.*_fct)(); }

    private:
      Function();

      U & _obj;
      memberFct _fct;

    };


    template <typename U>
    class Function<bool (U::*)()> : public IFunction
    {
    public:
      typedef bool (U::*memberFct)();

    public:

      Function(U & obj,  memberFct fct)
	:_obj(obj), _fct(fct)
      { }

      virtual ~Function() { }


      virtual bool FunctionCall() {  return (_obj.*_fct)();; }

      bool operator()() { return (_obj.*_fct)(); }

    private:
      Function();

      U & _obj;
      memberFct _fct;

    };


	template<int ...>
	struct seq { };

	template<int N, int ...S>
	struct gens : gens<N - 1, N - 1, S...> { };

	template<int ...S>
	struct gens<0, S...> {
		typedef seq<S...> type;
	};

	template <typename T, typename U, typename ...ARGS>
    class Function<T (U::*)(ARGS...)> : public IFunction
    {
    public:
      typedef T (U::*memberFct)(ARGS...);

    public:

      Function(U & obj,  memberFct fct)
		:_obj(obj), _fct(fct)
      { }

      virtual ~Function() { }


	  virtual bool FunctionCall() { delayed_dispatch(); return true; }

	  T operator()() { return delayed_dispatch(); }

	  std::tuple<ARGS...> params;

    private:
      Function();

	  void delayed_dispatch() {
		  callFunc(typename gens<sizeof...(ARGS)>::type());
	  }

	  template<int ...S>
	  void callFunc(seq<S...>) {
		  (_obj.*_fct)(std::get<S>(params) ...);
	  }

      U & _obj;
      memberFct _fct;

    };

  }
}

#endif //!ZL_RULE_HPP_
