// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4670 rf_vani_player_cache_user_bitmap
// UNREALRED VERIFIED [texture-conversion-20261028]: Createsuserbitmap usinginternalformat+80,width+68,height+72,stores handle+92. Computesdurationfloat+104=framecount+84/framerate+88. Returns0unconditionally,evenifbitmapcreationfailed; no zero-framerateguard. Onlythreeargumentspassedtocreatehelperinassembly; doesnotexplicitlyuploadpixel/palettebuffershere.
int __thiscall rf_vani_player_cache_user_bitmap(int this)
{
  *(_DWORD *)(this + 92) = rf_bitmap_create_user_bitmap(
                             *(_DWORD *)(this + 80),
                             *(_DWORD *)(this + 68),
                             *(_DWORD *)(this + 72));
  *(float *)(this + 104) = (double)*(int *)(this + 84) / (double)*(int *)(this + 88);
  return 0;
}

