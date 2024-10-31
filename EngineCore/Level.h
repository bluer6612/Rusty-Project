#pragma once
#include "GameMode.h"

// 설명 :
class ULevel
{
public:
	friend class USpriteRenderer;
	friend class UEngineAPICore;
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);
	void Render();

	template<typename ActorType>
	ActorType* SpawnActor()
	{
		ActorType* NewActor = new ActorType();

		AActor* ActorPtr = dynamic_cast<AActor*>(NewActor);
		// 내가 널 만든 레벨이야.
		ActorPtr->World = this;

		NewActor->BeginPlay();
		AllActors.push_back(NewActor);
		return NewActor;
	}

protected:

private:
	void ScreenClear();
	void DoubleBuffering();


	// 게임레벨과 메인폰을 만들어서 게임을 준비시키는 함수로도 만들었다.
	template<typename GameModeType, typename MainPawnType>
	void CreateGameMode()
	{
		GameMode = new GameModeType();

		// 화면을 바라봐주는 카메라라고 생각하고 만드셔도 됩니다.
		MainPawn = new MainPawnType();

		// 월드세팅이 먼저되는것이 굉장히 중요하다.
		MainPawn->World = this;
		GameMode->World = this;

		GameMode->BeginPlay();
		MainPawn->BeginPlay();

		AllActors.push_back(GameMode);
		AllActors.push_back(MainPawn);
	}


	// 아무나 함부로 호출하지 못하게 하기 위해서 private 이어야 한다.
	void PushRenderer(class USpriteRenderer* _Renderer);

	// 헝가리안 표기법
	// 이름은 마음대로
	// 맴버변수의 이름은 대문자
	// 음역하지마세요
	// dujumsaigury
	// 영어의미로 해주시면 됩니다.
	// 맨앞만 
	class AGameMode* GameMode = nullptr;

	// 주인공
	class AActor* MainPawn = nullptr;

	std::list<AActor*> AllActors;

	// 오더링을 할것이다.
	std::map<int, std::list<class USpriteRenderer*>> Renderers;
};