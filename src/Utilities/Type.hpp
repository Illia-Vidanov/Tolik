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
	template<bool Condition>
	struct Warning
	{};

	template<>
	struct __attribute__((deprecated)) Warning<false>
	{ constexpr Warning() {} };
} // detail

#define StaticWarn(x, ...) ((void) Warning<x>())


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
using RemoveClassPointerT = typename RemoveClassPointer<T>::type;


namespace detail
{
template<typename T, typename... Args>
struct FunctorTraitsBase
{
	using ReturnType = T;
	constexpr static inline std::size_t arg_count = sizeof...(Args);
	using ArgType = std::tuple_element_t<I, std::tuple<Args...>>;
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

// returnType = return type of a functor
// arg_count = amount of arguments in functor
// ArgT<Index> = type of argument in index (Note: indexing starts at 0)
template<typename T>
struct FunctorTraits : detail::FunctorTraitsImpl<T>
{};


namespace detail
{
	template<typename T, std::size_t N, template<std::size_t> typename F, std::size_t Index = N, T... Args>
	struct GenerateArrayImpl : GenerateArrayImpl<T, N, F, Index - 1, Args..., F<N - Index>::value>
	{};

	template<typename T, std::size_t N, template<std::size_t> typename F, T... Args>
	struct GenerateArrayImpl<T, N, F, 0, Args...>
	{ inline constexpr static std::array<T, N> value = std::array<T, N>{ Args... }; };
} // detail

// Generate std::array<T, N> with value of F<Index>::value
template<typename T, std::size_t N, template<std::size_t> typename F>
struct GenerateArray : detail::GenerateArrayImpl<T, N, F>
{};

// Alias for GenerateArray struct
template<typename T, std::size_t N, template<std::size_t> typename F>
std::array<T, N> generate_array = GenerateArray<T, N, F>::value;

// Used for GenerateArray struct
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
using MakeVoidT = typename MakeVoid<Args...>::type;


// TODO: generic operator check approach

template<typename T, typename U, typename = void>
struct HasModulOperator : std::false_type
{};

template<typename T, typename U>
struct HasModulOperator<T, U, MakeVoidT<decltype(std::declval<T>() % std::declval<U>())>> : std::true_type
{};

template<typename T, typename U>
constexpr inline bool kHasModulOperator = HasModulOperator<T, U>::value;
} // Tolik

#endif // TOLIK_UTILITIES_TYPE_HPP