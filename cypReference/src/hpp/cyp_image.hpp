#include "cyp_common.hpp"
#include <Windows.h>
#include "gdiplus.h"

#pragma comment(lib, "Gdiplus.lib")

namespace cyp
{
	namespace image
	{
		class ScreenShot
		{
			HDC hdcScr, hdcMem;

			// PC maximum resolution.
			const UINT iXResolution = GetDeviceCaps(hdcScr, HORZRES);
			const UINT iYResolution = GetDeviceCaps(hdcScr, VERTRES);

		private:
			int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

		public:
			enum class imageType
			{
				bmp = 0,
				png = 1,
			};

			void capture(std::string filePath_, imageType type = cyp::image::ScreenShot::imageType::png, UINT startX = 0, UINT startY = 0, UINT endX = 1920, UINT endY = 1080);
		};

	}
}
