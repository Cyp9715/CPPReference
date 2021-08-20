#include "cyp_image.hpp"

namespace cyp
{
	namespace image
	{
		int ScreenShot::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
		{
			UINT  num = 0;          // number of image encoders
			UINT  size = 0;         // size of the image encoder array in bytes

			Gdiplus::GetImageEncodersSize(&num, &size);
			if (size == 0)
				return -1;  // Failure

			Gdiplus::ImageCodecInfo* pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
			if (pImageCodecInfo == NULL)
				return -1;  // Failure

			GetImageEncoders(num, size, pImageCodecInfo);

			for (UINT j = 0; j < num; ++j)
			{
				if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
				{
					*pClsid = pImageCodecInfo[j].Clsid;
					free(pImageCodecInfo);
					return j;  // Success
				}
			}

			free(pImageCodecInfo);
			return -1;  // Failure
		}

		void ScreenShot::capture(std::string filePath_, imageType type, UINT startX, UINT startY, UINT endX, UINT endY)
		{
			std::wstring temp_wString = std::wstring(filePath_.begin(), filePath_.end());
			const wchar_t* filePath = temp_wString.c_str();

			Gdiplus::GdiplusStartupInput gdiplusStartupInput;
			ULONG_PTR gdiplusToken;
			Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

			RECT      rc;
			GetClientRect(GetDesktopWindow(), &rc);

			int w = endX - startX;
			int h = endY - startY;

			if (w <= 0) return;
			if (h <= 0) return;

			HDC     hScreen = GetDC(HWND_DESKTOP);
			HDC     hDc = CreateCompatibleDC(hScreen);
			HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
			HGDIOBJ old_obj = SelectObject(hDc, hBitmap);
			BitBlt(hDc, 0, 0, w, h, hScreen, startX, startY, SRCCOPY);

			Gdiplus::Bitmap bitmap(hBitmap, NULL);
			CLSID clsid;

			switch (type)
			{
			case imageType::bmp:
				GetEncoderClsid(L"image/bmp", &clsid);
				break;
			case imageType::png:
				GetEncoderClsid(L"image/png", &clsid);
				break;
			}

			//GDI+ expects Unicode filenames
			bitmap.Save(filePath, &clsid);

			SelectObject(hDc, old_obj);
			DeleteDC(hDc);
			ReleaseDC(HWND_DESKTOP, hScreen);
			DeleteObject(hBitmap);
		}

	}
}