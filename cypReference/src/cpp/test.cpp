#include <cyp_image.hpp>

int main()
{
	cyp::image::ScreenShot* sc = new cyp::image::ScreenShot();
	std::string a = "C:\\Users\\Cyp\\Desktop\\test\\" + std::to_string(49) + ".png";
	sc->capture(a, cyp::image::ScreenShot::imageType::bmp, 0, 0, 2560, 1440);
}