#include "stdafx.hpp"

#include "LoadedSound.hpp"

namespace ZoneTool::IW5::Dumper
{
	void dump(LoadedSound* asset)
	{
        const bool ADPCM = asset->sound.info.format == 17;
        const auto folder = ADPCM ? "loaded_sound_adpcm/"s : "loaded_sound/"s;

        auto sound = asset;
        auto fp = FileSystem::FileOpen(folder + asset->name, "wb");

        // Ensure file opened successfully
        if (!fp)
            return;

        char chunkID[] = { 'R', 'I', 'F', 'F' };
        fwrite(chunkID, 4, 1, fp);

        // Determine Subchunk1Size
        int subchunk1Size = 16; // Default PCM
        if (sound->sound.info.format == 17) // ADPCM
            subchunk1Size = 20; // ADPCM has extra 4 bytes

        int subchunk2Size = sound->sound.info.data_len;
        int chunkSize = 4 + (8 + subchunk1Size) + (8 + subchunk2Size);
        fwrite(&chunkSize, 4, 1, fp);

        // Format
        char format[] = { 'W', 'A', 'V', 'E' };
        fwrite(format, 4, 1, fp);

        // --- FMT SUBCHUNK ---
        char subchunk1ID[] = { 'f', 'm', 't', ' ' };
        fwrite(subchunk1ID, 4, 1, fp);

        fwrite(&subchunk1Size, 4, 1, fp);

        // AudioFormat
        short audioFormat = sound->sound.info.format;
        fwrite(&audioFormat, 2, 1, fp);

        // NumChannels
        short numChannels = sound->sound.info.channels;
        fwrite(&numChannels, 2, 1, fp);

        // SampleRate
        int sampleRate = sound->sound.info.rate;
        fwrite(&sampleRate, 4, 1, fp);

        // ByteRate
        int byteRate = sound->sound.info.rate * sound->sound.info.channels * sound->sound.info.bits / 8;
        fwrite(&byteRate, 4, 1, fp);

        // BlockAlign
        short blockAlign = sound->sound.info.block_size;
        fwrite(&blockAlign, 2, 1, fp);

        // BitsPerSample
        short bitsPerSample = sound->sound.info.bits;
        fwrite(&bitsPerSample, 2, 1, fp);

        if (asset->sound.info.format == 17) // ADPCM
        {
            // ExtraSize
            short numExtraBytes = 2;
            fwrite(&numExtraBytes, 2, 1, fp);

            // Samples Per Block
            short samplesPerBlock = blockAlign * 8 / 4;
            fwrite(&samplesPerBlock, 2, 1, fp);
        }

        // --- DATA SUBCHUNK ---
        char subchunk2ID[] = { 'd', 'a', 't', 'a' };
        fwrite(subchunk2ID, 4, 1, fp);

        fwrite(&subchunk2Size, 4, 1, fp);

        // Write audio data
        fwrite(sound->sound.data, sound->sound.info.data_len, 1, fp);

        FileSystem::FileClose(fp);
	}
}