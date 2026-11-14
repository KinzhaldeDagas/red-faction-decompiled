// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005916E0 rf_sound_sample_riff_size_rate_estimate
// UNREALRED VERIFIED [dsound-playback-20261028]: Unsigned sample index>=4096 returnsfloat0. Otherwise returns float-rounded(sample unsignedDWORD+572 / (output WAVEFORMAT bits+14/8.0) / output sampleRateDWORD+4). Field+572 is parent RIFF MMCKINFO cksize,NOT data-chunk remaining+552. Formula omits channel count,so it is not a general accurate playback-duration calculation for multichannel orcompressed input. No null output-format pointer,zero bitdepth/rate or occupancy check; does not inspect current playback cursor.
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Speech duration query must preserve RF estimate, not generic UE PCM playback duration. Unsigned sampleID>=4096=>0. Otherwise float-round parent RIFF cksize(sample+572) / (outputWaveFormat bitsPerSample/8.0) / outputSampleRate, OMITTING channel count and using parent RIFF size rather than data chunk. Output-format conversion must be proved for compressed codecs; reject an unsupported host codec/domain explicitly instead of silently substituting actual PCM duration.
double __cdecl rf_sound_sample_riff_size_rate_estimate(unsigned int a1)
{
  if ( a1 >= 0x1000 )
    return 0.0;
  return (float)((double)*((unsigned int *)&unk_1951808 + 148 * a1 + 143)
               / ((double)*(unsigned __int16 *)(*((_DWORD *)&unk_1951808 + 148 * a1 + 134) + 14)
                / 8.0)
               / (double)*(unsigned int *)(*((_DWORD *)&unk_1951808 + 148 * a1 + 134) + 4));
}

