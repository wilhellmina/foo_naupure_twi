#pragma once
#include "stdafx.h"

class PlaybackCallback : public play_callback_static
{
public:
	unsigned get_flags() override;
	void on_playback_starting(play_control::t_track_command cmd, bool paused) override{}
	void on_playback_new_track(metadb_handle_ptr track) override;
	void on_playback_stop(play_control::t_stop_reason reason) override {};
	void on_playback_seek(double time) override {};
	void on_playback_pause(bool state) override {};
	void on_playback_edited(metadb_handle_ptr track) override {};
	void on_playback_dynamic_info(const file_info& info) override{}
	void on_playback_dynamic_info_track(const file_info& info) override {};
	void on_playback_time(double time) override {};
	void on_volume_change(float p_new_val) override{}
private:
	void on_playback_changed(metadb_handle_ptr track = metadb_handle_ptr()) {};
	bool needPresenceRefresh_ = false;
};

