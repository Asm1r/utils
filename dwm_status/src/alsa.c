#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

#include <alsa/asoundlib.h>

int64_t get_alsa_volume(void)
{
        int64_t vol;
        int64_t vol_norm;
        int64_t min, max;
        snd_mixer_t *handle;
        snd_mixer_selem_id_t *sid;
        const char *card = "default";
        const char *selem_name = "PCM";

        snd_mixer_open(&handle, 0);
        snd_mixer_attach(handle, card);
        snd_mixer_selem_register(handle, NULL, NULL);
        snd_mixer_load(handle);

        snd_mixer_selem_id_malloc(&sid);
        snd_mixer_selem_id_set_index(sid, 0);
        snd_mixer_selem_id_set_name(sid, selem_name);

        snd_mixer_elem_t *elem = snd_mixer_find_selem(handle, sid);

        if(elem == NULL)
        {
                vol_norm = -1;
        }
        else
        {
                snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
                snd_mixer_selem_get_playback_volume(elem, 0, &vol);

                vol_norm = (100 * (vol - min)) / (max - min);
        }

        snd_mixer_selem_id_free(sid);
        snd_mixer_close(handle);

        return (vol_norm);
}

