#pragma once
#include <vector>
// 최신 std기능을 이용해볼겁니다.
#include "EnginePath.h"

// 설명 :
class UEngineDirectory : public UEnginePath
{
public:
	// constrcuter destructer
	UEngineDirectory();
	UEngineDirectory(std::string_view _Path);
	~UEngineDirectory();

	// delete Function
	UEngineDirectory(const UEngineDirectory& _Other) = delete;
	UEngineDirectory(UEngineDirectory&& _Other) noexcept = delete;
	UEngineDirectory& operator=(const UEngineDirectory& _Other) = delete;
	UEngineDirectory& operator=(UEngineDirectory&& _Other) noexcept = delete;

	std::vector<class UEngineFile> GetAllFile(bool _IsRecursive = true);


protected:

private:
	void GetAllFileRecursive(std::filesystem::path _Path, std::vector<class UEngineFile>& _Result);

};

