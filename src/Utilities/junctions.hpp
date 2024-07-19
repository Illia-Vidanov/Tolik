#ifndef _gcem_junctions_HPP
#define _gcem_junctions_HPP

/**
 * Implementation of std::conjunction in c++11
 * Forms the logical conjunction of the type traits Args..., effectively performing a logical AND on the sequence of traits.
 *
 * @param Args... a pack of bool type parametrs.
 * @return result of logical AND operation between all bool type parametrs.
 */

template<bool... Args>
struct
conjunction
: std::false_type
{};

template<bool B>
struct
conjunction<B>
: std::integral_constant<bool, B>
{};

template<bool B, bool... Args>
struct
conjunction<B, Args...>
: std::integral_constant<bool, B && Conjunction<Args...>::value>
{};

/**
 * Implementation of std::disjunction in c++11
 * Forms the logical disjunction of the type traits Args..., effectively performing a logical OR on the sequence of traits.
 *
 * @param Args... a pack of bool type parametrs.
 * @return result of logical AND operation between all bool type parametrs.
 */

template<bool... Args>
struct
disjunction
: std::false_type
{};

template<bool B>
struct
disjunction<B>
: std::integral_constant<bool, B>
{};

template<bool B, bool... Args>
struct
disjunction<B, Args...>
: std::integral_constant<bool, B || Conjunction<Args...>::value>
{};

#endif // _gcem_junctions_HPP
