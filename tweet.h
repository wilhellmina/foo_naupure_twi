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

	//?????
	int byteLenGet(const char* multi){
		int i, len;
		int bytelen; 	//�o�C�g��
		int charlen;	//������

		/* ���P�[����jpn(���{)�ɂ��� */
		setlocale(LC_CTYPE, "jan");

		bytelen = (int)strlen(multi);

		charlen = 0;
		i = 0;
		for (i = 0; i < bytelen; i++) {
			/* �e�������Ƃ̃o�C�g�����擾���� */
			len = mblen(&multi[i], MB_CUR_MAX);
			if (len != -1) {
				i += len;
				charlen++;
			}
			else {
				break;
			}
		}
		return bytelen;
	}

	//trash func for mainmanu_commands::execute
	void tweet(file_info_impl track_info) {
		const char* track_artist = track_info.meta_get("artist", 0);
		if (track_artist == nullptr) {
			track_artist = "";
		}
		const char* track_title = track_info.meta_get("title", 0);
		if (track_title == nullptr) {
			track_title = "";
		}
		const char* track_album = track_info.meta_get("album", 0);
		if (track_album == nullptr) {
			track_album = "";
		}
		
		std::string data = std::string(track_title) + ("(") + std::string(track_artist) + (")") + (" / ") + std::string(track_album);
		std::string data_encoded = "https://twitter.com/intent/tweet?text=%23NowPlaying%0A" + percentEnc(data);

		//shellexecute
		HINSTANCE ret = ShellExecuteA(0, "open", data_encoded.c_str(), NULL, NULL, SW_SHOWNORMAL);
		//error handling
	}

	//old dumbest func couldnt handle unique characters and too long also complicated
	void tweet_old_dumb_version(file_info_impl track_info) {
		wchar_t *title;
		wchar_t *album;
		wchar_t *artist;

		const char* track_artist = track_info.meta_get("artist", 0);
		if (track_artist == nullptr) {
			track_artist = "";
		}
		const char* track_title = track_info.meta_get("title", 0);
		if (track_title == nullptr) {
			track_title = "";
		}
		const char* track_album = track_info.meta_get("album", 0);
		if (track_album == nullptr) {
			track_album = "";
		}

		//memory allocation
		title = new wchar_t[_mbstrlen(track_title) + 1];
		album = new wchar_t[_mbstrlen(track_album) + 1];
		artist = new wchar_t[_mbstrlen(track_artist) + 1];

		//narrow to wide
		MultiByteToWideChar(CP_UTF8, 0, track_title, byteLenGet(track_title), title, byteLenGet(track_title) + 1);
		MultiByteToWideChar(CP_UTF8, 0, track_album, byteLenGet(track_album), album, byteLenGet(track_album) + 1);
		MultiByteToWideChar(CP_UTF8, 0, track_artist, byteLenGet(track_artist), artist, byteLenGet(track_artist) + 1);

		//fully utf8 version 
		std::wstring wst;
		wst = _T("https://twitter.com/intent/tweet?text=%23NowPlaying%0A") + std::wstring(title) + _T("(") + std::wstring(artist) + _T(")") + _T(" - ") + std::wstring(album);
		//shellexecute utf8 
		ShellExecuteW(0, _T("open"), wst.c_str(), NULL, NULL, SW_SHOWNORMAL);

		//free memory
		delete title;
		delete album;
		delete artist;
	}
}