#include "stdafx.h"
#include "pb.h"
#include "ui.h"
#include "tweet.h"


//playback info
file_info_impl track_info;

//PB
unsigned PlaybackCallback::get_flags()
{
	return flag_on_playback_all;
}

void PlaybackCallback::on_playback_new_track(metadb_handle_ptr track)
{
	track->get_info(track_info);
}

play_callback_static_factory_t<PlaybackCallback> playbackCallback;

//UI
t_uint32 Tweet_Button_impl::get_command_count()
{
	return 1;
}

GUID Tweet_Button_impl::get_command(t_uint32 p_index)
{
	switch (p_index)
	{
	case 0:
		return guid_mygroup;
	default:
		uBugCheck();
	}
}

void Tweet_Button_impl::get_name(t_uint32 p_index, pfc::string_base& p_out)
{
	switch (p_index)
	{
	case 0:
		p_out = "Tweet";
		return;
	default:
		uBugCheck();
	}
}

bool Tweet_Button_impl::get_description(t_uint32 /* p_index */, pfc::string_base& p_out)
{
	p_out = "";
	return true;
}

GUID Tweet_Button_impl::get_parent()
{
	return mainmenu_groups::playback;
}

void Tweet_Button_impl::execute(t_uint32 p_index, service_ptr_t<service_base> p_callback)
{
	Kokura_Asahi::tweet(track_info);
}

bool Tweet_Button_impl::get_display(t_uint32 p_index, pfc::string_base& p_out, t_uint32& p_flags)
{
	get_name(p_index, p_out);
	p_flags = sort_priority_dontcare;
	return true;
}

mainmenu_commands_factory_t<Tweet_Button_impl> g_mainmenuCommands;