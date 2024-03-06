//DxLib::DrawStringの第3引数の仕様で、Unicode文字は正常に表示されないので
//プロジェクトの設定から、文字セットをUnicodeからマルチバイト文字セットに変更してから実行する
#include <iostream>
#include <ezNetLib/UDPServer.h>
#include <DxLib.h>
#include <string>
#include <ctime>
#pragma warning(disable : 4996)

std::string result_str;
int str_x = 620;

//"today"を受け取ったときyyyy-mm-ddを表示する
void today_date() {
	std::time_t tm = std::time({});
	char tm_str[std::size("yyyy-mm-dd")];
	std::strftime(std::data(tm_str), std::size(tm_str), "%F", std::localtime(&tm));
	std::cout << tm_str;
	result_str = tm_str;
}

//"now"を受け取ったときhh:mm:ssを表示する
void now_time() {
	std::time_t tm = std::time({});
	char tm_str[std::size("hh:mm:ss")];
	std::strftime(std::data(tm_str), std::size(tm_str), "%T", std::localtime(&tm));
	std::cout << tm_str;
	result_str = tm_str;
}

//受け取った文字列による条件分岐
void udpMsgCallbackFunc(const std::string& msg) {
	str_x = 640;
	std::cout << "recv: [" << msg << "]" << std::endl;
	if (msg == "today") {
		std::cout << "result: [";
		today_date();
		std::cout << "]" << std::endl;
	}
	if (msg == "now") {
		std::cout << "result: [";
		now_time();
		std::cout << "]" << std::endl;
	}
}

//時計マーク描画
void draw_clock() {
	DxLib::DrawCircle(320, 60, 50, GetColor(0, 0, 0));
	DxLib::DrawCircle(320, 60, 45, GetColor(240, 240, 240));
	DxLib::DrawLine(320, 60, 350, 40, GetColor(0, 0, 0));
	DxLib::DrawLine(320, 60, 300, 40, GetColor(0, 0, 0));
}

int main() {
	DxLib::ChangeWindowMode(true);
	DxLib::SetAlwaysRunFlag(true);
	if (DxLib::DxLib_Init() == -1) {
		return -1;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);

	eznetlib::UDPServer udpServer(6000);
	udpServer.mesgFunc(udpMsgCallbackFunc);

	try {
		udpServer.mainLoop();
	}
	catch (...) {
		std::cerr << "exception: UDPServer::mainLoop()" << std::endl;
	}

	DxLib::SetFontSize(150);
	DxLib::ChangeFont("HG丸ｺﾞｼｯｸM-Pro");

	while (DxLib::ProcessMessage() == 0) {
		DxLib::ClearDrawScreen();
		DxLib::DrawBox(0, 0, 640, 480, GetColor(240, 240, 240), true);//背景

		draw_clock();

		DxLib::DrawLine(50, 300, 590, 300, GetColor(200, 200, 200));//下線

		DxLib::DrawFormatString(str_x, 150, GetColor(0, 220, 220), (const TCHAR*)result_str.c_str());//文字列描画
		DxLib::ScreenFlip();
		str_x -= 3;
	}

	DxLib::DxLib_End();
}