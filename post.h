#pragma once
#include "stdafx.h"
#include <string>
#include <sstream>
#include <Windows.h>

#include <stdio.h>
#include <sys/stat.h>

#include "tweet.h"
#include "webclient.h"
#include "oauth.h"
#include "base64.h"


namespace Kokura_Asahi
{
	//encode UTF8 to URI with percents 
	//RFC3986
	std::string percentEnc(std::string str) {
		const int NUM_BEGIN_UTF8 = 48;
		const int CAPITAL_BEGIN_UTF8 = 65;
		const int LOWER_BEGIN_UTF8 = 97;

		int charCode = -1;
		std::string encoded;
		std::stringstream out;

		//for文で1byteずつストリームに入れていく
		for (int i = 0; str[i] != 0; i++) {
			//文字列中の1byte分のデータを整数値として代入
			charCode = (int)(unsigned char)str[i];

			//エンコードする必要の無い文字の判定
			if ((NUM_BEGIN_UTF8 <= charCode && charCode <= NUM_BEGIN_UTF8 + 9)
				|| (CAPITAL_BEGIN_UTF8 <= charCode && charCode <= CAPITAL_BEGIN_UTF8 + 25)
				|| (LOWER_BEGIN_UTF8 <= charCode && charCode <= LOWER_BEGIN_UTF8 + 25)
				|| str[i] == '.' || str[i] == '_' || str[i] == '-' || str[i] == '~')
			{
				//エンコードの必要が無い文字はそのままストリームに入れる
				out << str[i];
			}
			else {
				//エンコードする場合は%記号と文字コードの16進数表示をストリームに入れる
				out << '%' << std::hex << std::uppercase << charCode;
			}
		}
		//ストリームの文字列をstringのインスタンスに代入しreturn
		encoded = out.str();
		return encoded;
	}	


	void tweet(file_info_impl *track_info) {
		std::string something_new;
		

		const char* track_artist = track_info->meta_get("artist", 0);
		if (track_artist == nullptr) {
			track_artist = "";
		}
		const char* track_title = track_info->meta_get("title", 0);
		if (track_title == nullptr) {
			track_title = "";
		}
		const char* track_album = track_info->meta_get("album", 0);
		if (track_album == nullptr) {
			track_album = "";
		}
		
		std::string data = std::string(track_title) + ("(") + std::string(track_artist) + (")") + (" / ") + std::string(track_album);
		std::string data_encoded = "https://twitter.com/intent/tweet?text=%23NowPlaying%0A" + percentEnc(data);



		//shellexecute
		HINSTANCE ret = ShellExecuteA(0, "open", data_encoded.c_str(), NULL, NULL, SW_SHOWNORMAL);
		//error handling
	}

	void postVIAPI(file_info_impl *track_info) {
		static const char consumer_key[] = { "4rdXQNvIFFFPS7alwvm1gntWD" };
		static const char consumer_sec[] = { "reLF2XqLRsbjNpnPn340iOFvPM8x9d4MF4R2pr3T42m0YSfLQ8" };
		static const char accesstoken[] = { "1041854270381776896-EZixmsAEYnAgwVxbVEFdhWXuKY8Fqs" };
		static const char accesstoken_sec[] = { "44uX5uwz7EjxNcESxJjslonQqdzsv3E8Xu8nlkdpNoEwU" };


		WebClient::initialize();
		TwitterClient tc(consumer_key, consumer_sec, accesstoken, accesstoken_sec);

		std::string nowplaying;

		const char* track_artist = track_info->meta_get("artist", 0);
		if (track_artist == nullptr) {
			track_artist = "";
		}
		const char* track_title = track_info->meta_get("title", 0);
		if (track_title == nullptr) {
			track_title = "";
		}
		const char* track_album = track_info->meta_get("album", 0);
		if (track_album == nullptr) {
			track_album = "";
		}

		nowplaying = std::string(track_title) + ("(") + std::string(track_artist) + (")") + (" / ") + std::string(track_album);

		tc.tweet(nowplaying);
	}
}