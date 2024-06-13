#ifndef TOLIK_UTILITIES_TYPE_HPP
#define TOLIK_UTILITIES_TYPE_HPP

#include <type_traits>
#include <array>
#include <tuple>

#include "Setup.hpp"

namespace Tolik
{
namespace detail
{
	template<bool Condition> struct Warning{};
	template<> struct __attribute__((deprecated)) Warning<false> { constexpr Warning() {} };
} // detail

#define StaticWarn(x, ...) ((void) Warning<x>())


struct Empty { template<typename... Args> constexpr Empty(const Args&... args) {} };


namespace detail
{
template<typename T>
struct RemoveClassPointerImpl;

template<typename T, typename... Args>
struct RemoveClassPointerImpl<T(Args...)>
{ using type = T(Args...); };

template<typename T, typename U, typename... Args>
struct RemoveClassPointerImpl<T(U::*)(Args...)>
{ using type = T(Args...); };
} // detail

template<typename T>
struct RemoveClassPointer
{ using type = typename detail::RemoveClassPointerImpl<T>::type; };

template<typename T>
using HelperRemoveClassPointer = typename RemoveClassPointer<T>::type;


namespace detail
{
template<typename ReturnType, typename... Args>
struct FunctorTraitsBase
{
	using return_type = ReturnType;
	constexpr static inline std::size_t arg_count = sizeof...(Args);

	template<std::size_t I>
	struct arg
	{
		using type = std::tuple_element_t<I, std::tuple<Args...>>;
	};
};
	
template<typename T, typename... Args>
struct FunctorTraitsImpl : FunctorTraitsImpl<decltype(&T::operator())>
{};

template<typename ClassType, typename ReturnType, typename... Args>
struct FunctorTraitsImpl<ReturnType(ClassType::*)(Args...) const> : FunctorTraitsBase<ReturnType, Args...>
{};

template<typename ClassType, typename ReturnType, typename... Args>
struct FunctorTraitsImpl<ReturnType(ClassType::*)(Args...)> : FunctorTraitsBase<ReturnType, Args...>
{};

template<typename ReturnType, typename... Args>
struct FunctorTraitsImpl<ReturnType(*)(Args...)> : FunctorTraitsBase<ReturnType, Args...>
{};

template<typename ReturnType, typename... Args>
struct FunctorTraitsImpl<ReturnType(&)(Args...)> : FunctorTraitsBase<ReturnType, Args...>
{};
} // detail

template<typename T>
struct FunctorTraits : detail::FunctorTraitsImpl<T>
{};


namespace detail
{
	template<typename T, std::size_t N, template<std::size_t> typename F, std::size_t Index = N, T... Args>
	struct GenerateArrayImpl
	{ inline constexpr static std::array<T, N> value = GenerateArrayImpl<T, N, F, Index - 1, Args..., F<N - Index>::value>::value; };

	template<typename T, std::size_t N, template<std::size_t> typename F, T... Args>
	struct GenerateArrayImpl<T, N, F, 0, Args...>
	{ inline constexpr static std::array<T, N> value = std::array<T, N>{ Args... }; };
} // detail

template<typename T, std::size_t N, template<std::size_t>typename F>
struct GenerateArray
{ inline constexpr static std::array<T, N> value = detail::GenerateArrayImpl<T, N, F>::value; };

template<typename T, std::size_t N, template<std::size_t> typename F>
std::array<T, N> HelperGenerateArray = GenerateArray<T, N, F>::value;

// Used for Generate Array function
template<std::size_t N>
struct ArrayConstant
{
	template<std::size_t>
	struct type
	{
		static constexpr inline std::size_t value = N;
	};
};


template<typename... Args>
struct MakeVoid
{ using type = void; };

template<typename... Args>
using HelperMakeVoid = typename MakeVoid<Args...>::type;


template<typename T, typename U, typename = void>
struct HasModulOperator : std::false_type
{};

template<typename T, typename U>
struct HasModulOperator<T, U, HelperMakeVoid<decltype(std::declval<T>() % std::declval<U>())>> : std::true_type
{};

template<typename T, typename U>
constexpr inline bool HelperHasModulOperator = HasModulOperator<T, U>::value;
} // Tolik

#endif // TOLIK_UTILITIES_TYPE_HPP