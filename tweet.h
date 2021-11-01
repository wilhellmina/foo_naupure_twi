#pragma once
#include "stdafx.h"
#include <string>
#include <sstream>
#include <Windows.h>

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

		//for����1byte���X�g���[���ɓ���Ă���
		for (int i = 0; str[i] != 0; i++) {
			//�����񒆂�1byte���̃f�[�^�𐮐��l�Ƃ��đ��
			charCode = (int)(unsigned char)str[i];

			//�G���R�[�h����K�v�̖��������̔���
			if ((NUM_BEGIN_UTF8 <= charCode && charCode <= NUM_BEGIN_UTF8 + 9)
				|| (CAPITAL_BEGIN_UTF8 <= charCode && charCode <= CAPITAL_BEGIN_UTF8 + 25)
				|| (LOWER_BEGIN_UTF8 <= charCode && charCode <= LOWER_BEGIN_UTF8 + 25)
				|| str[i] == '.' || str[i] == '_' || str[i] == '-' || str[i] == '~')
			{
				//�G���R�[�h�̕K�v�����������͂��̂܂܃X�g���[���ɓ����
				out << str[i];
			}
			else {
				//�G���R�[�h����ꍇ��%�L���ƕ����R�[�h��16�i���\�����X�g���[���ɓ����
				out << '%' << std::hex << std::uppercase << charCode;
			}
		}
		//�X�g���[���̕������string�̃C���X�^���X�ɑ����return
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
}