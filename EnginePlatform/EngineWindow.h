#pragma once
// Os Header
#include <Windows.h>

// std Header
#include <map>
#include <string>
#include <functional>

// user header
#include <EngineBase/EngineDelegate.h>

static int ScreenX = GetSystemMetrics(SM_CXSCREEN);
static int ScreenY = GetSystemMetrics(SM_CYSCREEN);

// ���� :
class UEngineWindow
{
public:
	static void EngineWindowInit(HINSTANCE _Instance);
	static void CreateWindowClass(const WNDCLASSEXA& _Class);

	static int WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction);
	// constrcuter destructer
	UEngineWindow();
	~UEngineWindow();

	// delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	void Create(std::string_view _TitleName, std::string_view _ClassName = "Default");
	void Open(std::string_view _TitleName = "Window");
	void SetWindowTopMost();

	inline HDC GetBackBuffer()
	{
		return BackBuffer;
	}

	// �Ƿ��� �������� ���� �����Ϸ��� ���Ѵ�.
	// �ڱ⸸ �ƴ°� �����ó�� ���ϰ�.

	inline void SetWindowTitle(std::string_view Text)
	{
		// WindowAPI�� ��Ģ �����ϰ� �ִ���.
		// ���δ� ������
		SetWindowTextA(WindowHandle, Text.data());
	}

protected:

private:
	static HINSTANCE hInstance;
	static std::map<std::string, WNDCLASSEXA> WindowClasss;


	// WinApi�� �⺻�������� �ٽ���
	// HDC�̴�. HDC�� windowâ�� �׸��� ���� ���� �ڵ��Դϴ�.
	// HDC�� �̹����̸鼭 �� �̹����� ���� ����
	// �� �������� 1���� Main HDC�� �����Ҽ� �ִ�.
	// ���� �̳༮�� BackBuffer��� �θ��ϴ�.

	// ������������ �������� �ȵǰų� ������ �ȵǴ� �ڵ尡 �ȴ�.
	// hwnd => ������ â 1��
	// �����쿡�� ������ �׸����� �Լ��� ��κ��� ù��° ���ڴ� hdc�ϰ��Դϴ�.
	HDC BackBuffer = nullptr;
	HWND WindowHandle = nullptr;
};

