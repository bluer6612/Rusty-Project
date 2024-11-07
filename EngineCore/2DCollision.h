#pragma once
#include "SceneComponent.h"

class U2DCollision : public USceneComponent
{
public:
		U2DCollision();
	~U2DCollision();

		U2DCollision(const U2DCollision& _Other) = delete;
	U2DCollision(U2DCollision&& _Other) noexcept = delete;
	U2DCollision& operator=(const U2DCollision& _Other) = delete;
	U2DCollision& operator=(U2DCollision&& _Other) noexcept = delete;

	void BeginPlay() override;

	void ComponentTick(float _DeltaTime) override;

	template<typename EnumType>
	EnumType GetGroup()
	{
		return static_cast<EnumType>(CollisionGroup);
	}

	int GetGroup()
	{
		return CollisionGroup;
	}

			template<typename EnumType>
	void SetCollisionGroup(EnumType _CollisionGroup)
	{
		SetCollisionGroup(static_cast<int>(_CollisionGroup));
	}

	void SetCollisionGroup(int _CollisionGroup)
	{
		CollisionGroup = _CollisionGroup;
	}

	template<typename EnumType>
	bool IsCollision(EnumType _OtherCollisionGroup)
	{
		return IsCollision(static_cast<int>(_OtherCollisionGroup));
	}

	template<typename EnumType>
	U2DCollision* CollisionOnce(EnumType _OtherCollisionGroup)
	{
		return CollisionOnce(static_cast<int>(_OtherCollisionGroup));
	}

	template<typename EnumType>
	bool Collision(EnumType _OtherCollisionGroup, std::vector<U2DCollision*>* _Result = nullptr)
	{
		return Collision(static_cast<int>(_OtherCollisionGroup), _Result);
	}

	bool IsCollision(int _OtherCollisionGroup);
	U2DCollision* Collision(int _OtherCollisionGroup);
		bool Collision(int _OtherCollisionGroup, std::vector<U2DCollision*>* _Result = nullptr);


protected:

private:
					int CollisionGroup = -1;
};



