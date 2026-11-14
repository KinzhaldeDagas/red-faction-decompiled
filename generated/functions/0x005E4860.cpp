// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4860 rf_vani_player_load_metadata
// UNREALRED VERIFIED [texture-conversion-20261028]: Argumentsname,streamingbyte. Releasespixel/palettebuffers,setsbitmap-1,duration/time0,frameindex+400=-1; copiesNULterminatednameatthisWITHOUTlengthlimit. Setsflags+404=0x10onlyifstreamingbyteexactly1,otherwise0. Defaultswidth/height0,bitsperpixel+76=8,format+80=1,framecount0,framerate15. CallsVANIheaderreader0x5E5040; negativefailure-1. Successframesize+396=ceil(bits/8)*width*height,setsloadedflag0x20,returns0. No releaseofoldbitmaporcloseexistingembeddedvfilehere; namecapacity64bytesbeforeversionfield.
int __thiscall rf_vani_player_load_metadata(int this, char *a2, char a3)
{
  char v3; // al
  _BYTE *v5; // [esp+8h] [ebp-Ch]

  rf_vani_player_release_pixel_palette_buffers((void **)this);
  *(_DWORD *)(this + 112) = 0;
  *(_DWORD *)(this + 116) = 0;
  *(_DWORD *)(this + 92) = -1;
  *(float *)(this + 104) = 0.0;
  *(float *)(this + 108) = 0.0;
  *(_DWORD *)(this + 400) = -1;
  v5 = (_BYTE *)this;
  do
  {
    v3 = *a2;
    *v5++ = *a2++;
  }
  while ( v3 );
  *(_DWORD *)(this + 404) = 0;
  if ( a3 == 1 )
    *(_DWORD *)(this + 404) |= 0x10u;
  *(_DWORD *)(this + 68) = 0;
  *(_DWORD *)(this + 72) = 0;
  *(_DWORD *)(this + 76) = 8;
  *(_DWORD *)(this + 80) = 1;
  *(_DWORD *)(this + 84) = 0;
  *(_DWORD *)(this + 88) = 15;
  if ( rf_vani_player_read_header_metadata(this) < 0 )
    return -1;
  *(_DWORD *)(this + 396) = (*(_DWORD *)(this + 76) + 7) / 8 * *(_DWORD *)(this + 72) * *(_DWORD *)(this + 68);
  *(_DWORD *)(this + 404) |= 0x20u;
  return 0;
}

