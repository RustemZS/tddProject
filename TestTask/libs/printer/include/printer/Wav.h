#ifndef WAV_H
#define WAV_H

#include <cstdint>
// PCM to WAV function copied from https://gist.github.com/csukuangfj/c1d1d769606260d436f8674c30662450
typedef struct WAVHeader {
    /* RIFF Chunk Descriptor */
    uint8_t riff[4] = { 'R', 'I', 'F', 'F' }; // RIFF Header Magic header
    uint32_t chunkSize = 1;                     // RIFF Chunk Size
    uint8_t wave[4] = { 'W', 'A', 'V', 'E' }; // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t fmt[4] = { 'f', 'm', 't', ' ' }; // FMT header
    uint32_t subchunk1Size = 16;           // Size of the fmt chunk
    uint16_t audioFormat = 1; // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM
    // Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t numOfChan = 1;   // Number of channels 1=Mono 2=Sterio
    uint32_t samplesPerSec = 16000;   // Sampling Frequency in Hz
    uint32_t bytesPerSec = 32000; // bytes per second
    uint16_t blockAlign = 2;          // 2=16-bit mono, 4=16-bit stereo
    uint16_t bitsPerSample = 16;      // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t subchunk2ID[4] = { 'd', 'a', 't', 'a' }; // "data"  string
    uint32_t subchunk2Size = 1;                        // Sampled data length
} wavHdr;

#endif
