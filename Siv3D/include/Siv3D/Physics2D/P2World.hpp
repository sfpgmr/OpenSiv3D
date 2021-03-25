﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "../Common.hpp"
# include "../PointVector.hpp"
# include "../HashTable.hpp"
# include "../Scene.hpp"
# include "P2Fwd.hpp"
# include "P2BodyType.hpp"
# include "P2Material.hpp"
# include "P2Filter.hpp"
# include "P2Body.hpp"
# include "P2PivotJoint.hpp"
# include "P2DistanceJoint.hpp"
# include "P2SliderJoint.hpp"
# include "P2WheelJoint.hpp"

namespace s3d
{
	/// @brief 2D 物理演算を行うワールド
	class P2World
	{
	public:

		/// @brief 2D 物理演算を行うワールドを作成します。
		/// @param gravity 重力加速度 (cm/s^2)
		SIV3D_NODISCARD_CXX20
		explicit P2World(double gravity = 980);

		/// @brief 2D 物理演算を行うワールドを作成します。
		/// @param gravity 重力加速度のベクトル (cm/s^2)
		SIV3D_NODISCARD_CXX20
		explicit P2World(Vec2 gravity);

		/// @brief 2D 物理演算のワールドの状態を更新します。
		/// @param timeStep タイムステップ（秒）
		/// @param velocityIterations 物体の衝突時の速度の補正の回数
		/// @param positionIterations 物体の衝突時の位置の補正の回数
		void update(double timeStep = Scene::DeltaTime(), int32 velocityIterations = 6, int32 positionIterations = 2) const;

		/// @brief ワールド内の物体がスリープ状態になることを許可・不許可を設定します（デフォルトでは許可）。
		/// @param enabled 許可する場合 true, 許可しない場合 false
		void setSleepEnabled(bool enabled);

		/// @brief ワールド内の物体がスリープ状態になることを許可しているかの現在の設定を返します。
		/// @return スリープを許可している場合 true, 許可していない場合 false
		[[nodiscard]]
		bool getSleepEnabled() const;

		/// @brief 重力加速度 (cm/s^2) を設定します。
		/// @remark `setGravity(Vec2{ 0, gravity })` と同じです。
		/// @param gravity 重力加速度 (cm/s^2)
		void setGravity(double gravity);

		/// @brief 重力加速度 (cm/s^2) を設定します。
		/// @param gravity 重力加速度のベクトル (cm/s^2)
		void setGravity(const Vec2& gravity);

		/// @brief 現在の重力加速度の設定を返します。
		/// @return 現在の重力加速度の設定 (cm/s^2)
		[[nodiscard]]
		Vec2 getGravity() const;

		/// @brief ワールドの物体全ての座標をシフトします。
		/// @param newOrigin シフト量
		void shiftOrigin(const Vec2& newOrigin);

		[[nodiscard]]
		P2Body createPlaceholder(P2BodyType bodyType, const Vec2& worldPos);

		[[nodiscard]]
		P2Body createLine(P2BodyType bodyType, const Vec2& worldPos, const Line& localPos, OneSided oneSided = OneSided::No, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createLineString(P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, OneSided oneSided = OneSided::No, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createClosedLineString(P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, OneSided oneSided = OneSided::No, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createCircle(P2BodyType bodyType, const Vec2& worldPos, double r, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createCircle(P2BodyType bodyType, const Vec2& worldPos, const Circle& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createRect(P2BodyType bodyType, const Vec2& worldPos, double size, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createRect(P2BodyType bodyType, const Vec2& worldPos, const SizeF& size, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createRect(P2BodyType bodyType, const Vec2& worldPos, const RectF& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createTriangle(P2BodyType bodyType, const Vec2& worldPos, const Triangle& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createQuad(P2BodyType bodyType, const Vec2& worldPos, const Quad& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createPolygon(P2BodyType bodyType, const Vec2& worldPos, const Polygon& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createPolygons(P2BodyType bodyType, const Vec2& worldPos, const MultiPolygon& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2PivotJoint createPivotJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos);
		
		[[nodiscard]]
		P2DistanceJoint createDistanceJoint(const P2Body& bodyA, const Vec2& worldAnchorPosA, const P2Body& bodyB, const Vec2& worldAnchorPosB, double length);

		[[nodiscard]]
		P2SliderJoint createSliderJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const Vec2& normalizedAxis);

		[[nodiscard]]
		P2WheelJoint createWheelJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos, const Vec2& axis);

		[[nodiscard]]
		const HashTable<P2ContactPair, P2Collision>& getCollisions() const noexcept;

	private:

		std::shared_ptr<detail::P2WorldDetail> pImpl;
	};
}
