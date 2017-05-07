﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "PointVector.hpp"

namespace s3d
{
	struct Line
	{
		using position_type = Vec2;

		using value_type = position_type::value_type;
		
		/// <summary>
		/// 線分の開始位置
		/// </summary>
		position_type begin;
		
		/// <summary>
		/// 線分の終点位置
		/// </summary>
		position_type end;
		
		Line() = default;
		
		constexpr Line(value_type x0, value_type y0, value_type x1, value_type y1) noexcept
			: begin(x0, y0)
			, end(x1, y1) {}
		
		constexpr Line(const position_type& p0, value_type x1, value_type y1) noexcept
			: begin(p0)
			, end(x1, y1) {}
		
		constexpr Line(value_type x0, value_type y0, const position_type& p1) noexcept
			: begin(x0, y0)
			, end(p1) {}
		
		constexpr Line(const position_type& p0, const position_type& p1) noexcept
			: begin(p0)
			, end(p1) {}
		
		constexpr bool operator ==(const Line& line) const noexcept
		{
			return begin == line.begin
				&& end == line.end;
		}
		
		constexpr bool operator !=(const Line& line) const noexcept
		{
			return !(*this == line);
		}
		
		constexpr Line& set(value_type x0, value_type y0, value_type x1, value_type y1) noexcept
		{
			begin.set(x0, y0);
			end.set(x1, y1);
			return *this;
		}
		
		constexpr Line& set(const position_type& p0, value_type x1, value_type y1) noexcept
		{
			return set(p0.x, p0.y, x1, y1);
		}
		
		constexpr Line& set(value_type x0, value_type y0, const position_type& p1) noexcept
		{
			return set(x0, y0, p1.x, p1.y);
		}
		
		constexpr Line& set(const position_type& p0, const position_type& p1) noexcept
		{
			return set(p0.x, p0.y, p1.x, p1.y);
		}
		
		constexpr Line& set(const Line& line) noexcept
		{
			return *this = line;
		}
		
		constexpr Line movedBy(value_type x, value_type y) const noexcept
		{
			return{ begin.movedBy(x, y), end.movedBy(x, y) };
		}
		
		constexpr Line movedBy(const position_type& v) const noexcept
		{
			return movedBy(v.x, v.y);
		}
		
		constexpr Line& moveBy(value_type x, value_type y) noexcept
		{
			begin.moveBy(x, y);
			end.moveBy(x, y);
			return *this;
		}
		
		constexpr Line& moveBy(const position_type& v) noexcept
		{
			return moveBy(v.x, v.y);
		}
		
		constexpr position_type vector() const noexcept
		{
			return end - begin;
		}
		
		constexpr Line& reverse() noexcept
		{
			const position_type t = begin;
			begin = end;
			end = t;
			return *this;
		}
		
		constexpr Line reversed() const noexcept
		{
			return{ end, begin };
		}
		
		value_type length() const noexcept
		{
			return begin.distanceFrom(end);
		}
		
		constexpr value_type lengthSq() const noexcept
		{
			return begin.distanceFromSq(end);
		}
		
		constexpr position_type center() const noexcept
		{
			return (begin + end) * 0.5;
		}
		
		position_type closest(const position_type& pos) const noexcept;

		template <class Shape2DType>
		bool intersects(const Shape2DType& shape) const noexcept(noexcept(Geometry2D::Intersect(*this, shape)))
		{
			return Geometry2D::Intersect(*this, shape);
		}
		
		Optional<position_type> intersectsAt(const Line& line) const;

		Optional<position_type> intersectsAtPrecise(const Line& line) const;

		// rotated
		
		// rotatedAt
		
		// paint
		
		// paintArrow
		
		// overpaint
		
		// overpaintArrow
		
		const Line& draw(const ColorF& color = Palette::White) const
		{
			return draw(1.0, color);
		}

		const Line& draw(const ColorF(&colors)[2]) const
		{
			return draw(1.0, colors);
		}

		const Line& draw(double thickness, const ColorF& color = Palette::White) const;

		const Line& draw(double thickness, const ColorF(&colors)[2]) const;
		
		// drawArrow
		
		// asPolygon;
	};
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting Line
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[x] istream
//	[x] wistream
//	[x] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	inline void Formatter(FormatData& formatData, const Line& value)
	{
		Formatter(formatData, Vec4(value.begin.x, value.begin.y, value.end.x, value.end.y));
	}

	/// <summary>
	/// 出力ストリームに線分を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="line">
	/// 線分
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const Line& line)
	{
		return	os << CharType('(')
			<< line.begin.x << CharType(',')
			<< line.begin.y << CharType(',')
			<< line.end.x << CharType(',')
			<< line.end.y << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに線分を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="rect">
	/// 線分
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, Line& line)
	{
		CharType unused;
		return	is >> unused
			>> line.begin.x >> unused
			>> line.begin.y >> unused
			>> line.end.x >> unused
			>> line.end.y >> unused;
	}
}

namespace fmt
{
	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::Line& line)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = L"({" + tag + L"},{" + tag + L"},{" + tag + L"},{" + tag + L"})";

		f.writer().write(fmt, line.begin.x, line.begin.y, line.end.x, line.end.y);
	}
}
//
//////////////////////////////////////////////////////////////////////////////
