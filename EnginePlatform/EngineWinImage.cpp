#include "PreCompile.h"
#include "EngineWinImage.h"
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EnginePath.h>
#include <EngineBase/EngineString.h>

#include <objidl.h>
#include <gdiplus.h>


#pragma comment(lib, "Msimg32.lib")

#pragma comment(lib, "Gdiplus.lib")

UEngineWinImage::UEngineWinImage()
{
}

UEngineWinImage::~UEngineWinImage()
{
			if (nullptr != hBitMap)
	{
		DeleteObject(hBitMap);
		hBitMap = nullptr;
	}

	if (nullptr != ImageDC)
	{
		DeleteDC(ImageDC);
		ImageDC = nullptr;
	}

}

void UEngineWinImage::Create(UEngineWinImage* _TargetImage,  FVector2D _Scale)
{
	if (nullptr == _TargetImage)
	{
		MSGASSERT("Main windowDC를 넣지않고 이미지를 생성하려고 했습니다");
		return;
	}

				
				
	
	
	HBITMAP NewBitmap = static_cast<HBITMAP>(CreateCompatibleBitmap(_TargetImage->GetDC(), _Scale.iX(), _Scale.iY()));

				
		HDC NewImageDC = CreateCompatibleDC(_TargetImage->GetDC());

		
		HBITMAP OldBitMap = static_cast<HBITMAP>(SelectObject(NewImageDC, NewBitmap));
			DeleteObject(OldBitMap);

	hBitMap = NewBitmap;
	ImageDC = NewImageDC;

	GetObject(hBitMap, sizeof(BITMAP), &Info);
}

void UEngineWinImage::CopyToBit(UEngineWinImage* _TargetImage, const FTransform& _Trans)
{
	if (nullptr == _TargetImage)
	{
		MSGASSERT("복사받을 대상이 존재하지 않습니다");
	}

	HDC CopyDC = ImageDC;
	HDC TargetDC = _TargetImage->ImageDC;
				
	//HDC hdc, 카피 받을 대상 <= 여기에다가 복사해라
	//int x, <= 위치x
	//int y, <= 위치y
	//int cx, <= 크기x
	//int cy, <= 크기x
				
	FVector2D LeftTop = _Trans.CenterLeftTop();
	FVector2D RightBot = _Trans.CenterRightBottom();

		BitBlt(
		TargetDC,
		LeftTop.iX(),
		LeftTop.iY(),
		_Trans.Scale.iX(),
		_Trans.Scale.iY(),
		CopyDC,
		0,
		0,
		SRCCOPY);

	
	FVector2D Vector;
}

void UEngineWinImage::CopyToTrans(UEngineWinImage* _TargetImage, const FTransform& _RenderTrans, const FTransform& _LTImageTrans, UColor _Color /*= UColor(255, 0, 255, 255)*/)
{
	
		
	HDC CopyDC = ImageDC;
	HDC TargetDC = _TargetImage->ImageDC;

    //_In_ HDC hdcDest, 여기에다가 카피해라
    //_In_ int xoriginDest, 그려지는 위치
    //_In_ int yoriginDest, 그려지는 위치
    //_In_ int wDest, 그려지는 크기
    //_In_ int hDest, 그려지는 크기
    //_In_ HDC hdcSrc, 복사될 이미지 => 여러분들이 로드한 이미지
    //_In_ int xoriginSrc, 이미지 이부분 
    //_In_ int yoriginSrc, int X
    //_In_ int wSrc,
    //_In_ int hSrc,
    //_In_ UINT crTransparent

	FVector2D LeftTop = _RenderTrans.CenterLeftTop();

	TransparentBlt(
		TargetDC,
		LeftTop.iX(),
		LeftTop.iY(),
		_RenderTrans.Scale.iX(),
		_RenderTrans.Scale.iY(),
		CopyDC,
		_LTImageTrans.Location.iX(),
		_LTImageTrans.Location.iY(),
		_LTImageTrans.Scale.iX(),
		_LTImageTrans.Scale.iY(),
		_Color.Color
	);
}

void UEngineWinImage::CopyToAlpha(UEngineWinImage* _TargetImage,
	const FTransform& _RenderTrans,
	const FTransform& _LTImageTrans,
	unsigned char _Alpha)
{

				
					
	BLENDFUNCTION BLEND;
	BLEND.BlendOp = AC_SRC_OVER;
	BLEND.BlendFlags = 0;
	BLEND.AlphaFormat = AC_SRC_ALPHA;
	BLEND.SourceConstantAlpha = _Alpha;

	HDC CopyDC = ImageDC;
	HDC TargetDC = _TargetImage->ImageDC;
	FVector2D LeftTop = _RenderTrans.CenterLeftTop();

	AlphaBlend(
		TargetDC,
		LeftTop.iX(),
		LeftTop.iY(),
		_RenderTrans.Scale.iX(),
		_RenderTrans.Scale.iY(),
		CopyDC,
		_LTImageTrans.Location.iX(),
		_LTImageTrans.Location.iY(),
		_LTImageTrans.Scale.iX(),
		_LTImageTrans.Scale.iY(),
		BLEND
	);
}

void UEngineWinImage::Load(UEngineWinImage* _TargetImage, std::string_view _Path)
{
					
									
		
						
	UEnginePath Path = _Path;

	std::string UpperExt = UEngineString::ToUpper(Path.GetExtension());

	HBITMAP NewBitmap = nullptr;

	if (".PNG" == UpperExt)
	{
						
				ULONG_PTR gidplustoken = 0;

				Gdiplus::GdiplusStartupInput StartupInput;
		Gdiplus::GdiplusStartup(&gidplustoken, &StartupInput, nullptr);


		std::wstring WidePath = UEngineString::AnsiToUnicode(_Path);

				Gdiplus::Image* pImage = Gdiplus::Image::FromFile(WidePath.c_str());

				Gdiplus::Bitmap* pBitMap = reinterpret_cast<Gdiplus::Bitmap*>(pImage->Clone());

		Gdiplus::Status stat = pBitMap->GetHBITMAP(Gdiplus::Color(255, 255, 0, 255), &NewBitmap);

		if (Gdiplus::Status::Ok != stat)
		{
			MSGASSERT("Png 이미지 로드에 실패했습니다." + std::string(_Path));
			return;
		}

				delete pBitMap;
		delete pImage;
	}
	else if (".BMP" == UpperExt)
	{
		HANDLE NewHandle = LoadImageA(nullptr, _Path.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		NewBitmap = reinterpret_cast<HBITMAP>(NewHandle);
	}

	if (nullptr == NewBitmap)
	{
		MSGASSERT("이미지 로딩에 실패했습니다");
		return;
	}

		HDC NewImageDC = CreateCompatibleDC(_TargetImage->GetDC());

	HBITMAP OldBitMap = static_cast<HBITMAP>(SelectObject(NewImageDC, NewBitmap));
	DeleteObject(OldBitMap);

	hBitMap = NewBitmap;
	ImageDC = NewImageDC;

	GetObject(hBitMap, sizeof(BITMAP), &Info);
}

UColor UEngineWinImage::GetColor(FIntPoint _Point, UColor _DefaultColor = UColor::WHITE)
{
	if (0 > _Point.X)
	{
		return _DefaultColor;
	}

	if (0 > _Point.Y)
	{
		return _DefaultColor;
	}

	if (Info.bmWidth <= _Point.X)
	{
		return _DefaultColor;
	}

	if (Info.bmHeight <= _Point.Y)
	{
		return _DefaultColor;
	}

		
			UColor ResultColor = ::GetPixel(ImageDC, _Point.X, _Point.Y);
	return ResultColor;
}