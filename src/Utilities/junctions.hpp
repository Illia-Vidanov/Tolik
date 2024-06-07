/*################################################################################
  ##
  ##   Copyright (C) 2016-2024 Keith O'Hara
  ##
  ##   This file is part of the GCE-Math C++ library.
  ##
  ##   Licensed under the Apache License, Version 2.0 (the "License");
  ##   you may not use this file except in compliance with the License.
  ##   You may obtain a copy of the License at
  ##
  ##       http://www.apache.org/licenses/LICENSE-2.0
  ##
  ##   Unless required by applicable law or agreed to in writing, software
  ##   distributed under the License is distributed on an "AS IS" BASIS,
  ##   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  ##   See the License for the specific language governing permissions and
  ##   limitations under the License.
  ##
  ################################################################################*/

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
