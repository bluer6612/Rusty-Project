#include "PreCompile.h"
#include "EduContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineDirectory.h>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>

#include "TitleGameMode.h"
#include "PlayGameMode.h"
#include "Player.h"


EduContentsCore::EduContentsCore()
{
}

EduContentsCore::~EduContentsCore()
{
}

// 엔진이 실행되고 단 1번 실행된다.
void EduContentsCore::BeginPlay()
{
	// UEngineDirectory Dir = "C:\\AAA";

	UEngineDirectory Dir;

	// 상대경로가 중요하다.
	// 상대 경로의 핵심은 이것이다.
	// 내가 어디서 실행됐는지는 중요하지 않아야 한다.
	// 선생님은 게임이 없기 때문이고.
	// 여려분들은 레벨에서 하는걸 권장합니다.
	// Global / 레벨에 관련된 

	// 상대경로 어디든 내 프로젝트의 폴더 안에 있는 Resources찾는 방식으로 처리했다.
	// 
	// if (false == Dir.MoveParentToDirectory("fasdjklfadsjklf"))
	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
		return;
	}

	// 모든 파일 다 얻어낸다음
	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
	}

	// 일반 텍스처가 다 로딩되면
	// 자르는 작업을 아래서 해주는게 좋다.

	UImageManager::GetInst().CuttingSprite("Player_Right.png", {128, 128});

	{

		UEngineDirectory BombDir;
		BombDir.MoveParentToDirectory("Resources");
		BombDir.Append("bomb");

		UImageManager::GetInst().LoadFolder(BombDir.GetPathToString());

	}

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("EduWindow");
	
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale("EduWindow", { 0, 0 }, { ScreenX, ScreenY });

	//UEngineAPICore::GetCore()->GetMainWindow().SetWindowAlpha();

	UEngineAPICore::GetCore()->GetSubWindow().SetWindowTitle("SubWindow");

	//UEngineAPICore::GetCore()->GetSubWindow().SetWindowPosAndScale("SubWindow", { 0, (ScreenY - (ScreenY / 3)) - 10 - 30 }, { static_cast<long>(ScreenX), static_cast<long>(ScreenY / 3) });
	UEngineAPICore::GetCore()->GetSubWindow().SetWindowPosAndScale("SubWindow", { 1000, 10 }, { 10000, 10 });

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");

	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	//UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->OpenLevel("Title");

}

void EduContentsCore::Tick()
{
	// 지금 전혀 용도를 찾지 못해서 사용하지 않는 함수입니다.
}