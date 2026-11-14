// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005915B0 rf_audio_get_3d_mode_byte
// UNREALRED VERIFIED [dsound-playback-20261028]: Returns raw globalbyte0x193BBE0. No normalization or hardware query. Other code often requires EXACTLY1 for3D-capable descriptors,so arbitrary nonzero values are not uniformly equivalent.
char rf_audio_get_3d_mode_byte()
{
  return unk_193BBE0;
}

