// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00598920 rf_audio_property_extension_clear_ready_cache
// UNREALRED VERIFIED [dsound-playback-20261028]: Returns prior ready byte0x1BCA304. If nonzero,clearsready andcached interface0x1BCA300=NULL WITHOUT Release. Leaves mode0x193BBE2,main property pointer0x19514D4 andcachedfield0x1BCA2FC unchanged. Successful path treats cached interface as borrowed.
int rf_audio_property_extension_clear_ready_cache()
{
  int result; // eax

  result = byte_1BCA304[0];
  if ( byte_1BCA304[0] )
  {
    byte_1BCA304[0] = 0;
    dword_1BCA300 = nullptr;
  }
  return result;
}

