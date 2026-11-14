// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4000 rf_d3d8_sample_bitmap_tile0_wrapped_uv_rgba
// UNREALRED VERIFIED [texture-upload-20261028]: Arguments bitmaphandle,U,V,outputRGBAbytes. LocksGPUtile0directlyvia0x5E3DC0; failurewritesopaque white255/255/255/255 via0x571A00andreturnsoutputpointer. WrapsU,Vwithactualfmod(value,1),adds1ifnegative; roundsindices(int)(dimension*wrapped+0.5) WITHOUTclamping,so UVnear1canindexdimension. Computesrowusingpitch; unconditionallyreadsBOTH16-bitpixelat2*xand32-bitpixelat4*xBEFOREformatswitch. Internalcode2writeswhiteRGB/bytealpha;code4interpretsARGB4444,nibbles*16(max240);code5interpretsARGB1555,alpha0/255,RGB5bits*8(max248);code7extractsARGB32. OthercodeswhiteRGB/alpha0. GPUlockmapsnumericGPUformats26/30tointernal4,and24/25tointernal5; samplerappliesthesamedecodingwithin eachpair. Unlocksvia0x573680andreturnsthatresultcastpointer,NOToutputpointeronsuccess. No tilelayout/fullimagecoordinatehandling,formatappropriatepre-read,bounds
// orfinitechecks. Theoldhypotnamedcalleeactuallyfmod.
_BYTE *__cdecl rf_d3d8_sample_bitmap_tile0_wrapped_uv_rgba(unsigned int a1, float X, float a3, _BYTE *a4)
{
  unsigned __int16 v5; // [esp+18h] [ebp-38h]
  int v6; // [esp+20h] [ebp-30h]
  int v7; // [esp+28h] [ebp-28h]
  unsigned int v8; // [esp+2Ch] [ebp-24h]
  unsigned int v9[8]; // [esp+30h] [ebp-20h] BYREF
  float v10; // [esp+5Ch] [ebp+Ch]
  float v11; // [esp+60h] [ebp+10h]

  if ( !rf_d3d8_bitmap_lock_tile_pixels(a1, 0, v9) )
    return rf_color4_set_bytes_return_destination(a4, 255, 255, 255, 255);
  v10 = rf_fmod_float_wrapper(X, 1.0);
  v11 = rf_fmod_float_wrapper(a3, 1.0);
  if ( v10 < 0.0 )
    v10 = v10 + 1.0;
  if ( v11 < 0.0 )
    v11 = v11 + 1.0;
  v6 = (int)((double)(int)v9[4] * v10 + 0.5);
  v8 = v9[3] + v9[6] * (int)((double)(int)v9[5] * v11 + 0.5);
  v5 = *(_WORD *)(v8 + 2 * v6);
  v7 = *(_DWORD *)(v8 + 4 * v6);
  switch ( v9[2] )
  {
    case 2u:
      rf_color4_set_bytes_return_destination(a4, 255, 255, 255, *(_BYTE *)(v6 + v8));
      break;
    case 4u:
      a4[3] = 16 * ((int)v5 >> 12);
      *a4 = 16 * (HIBYTE(v5) & 0xF);
      a4[1] = 16 * (((int)v5 >> 4) & 0xF);
      a4[2] = 16 * (v5 & 0xF);
      break;
    case 5u:
      a4[3] = -((v5 & 0x8000) != 0);
      *a4 = 8 * (((int)v5 >> 10) & 0x1F);
      a4[1] = 8 * (((int)v5 >> 5) & 0x1F);
      a4[2] = 8 * (v5 & 0x1F);
      break;
    case 7u:
      a4[3] = HIBYTE(v7);
      *a4 = BYTE2(v7);
      a4[1] = BYTE1(v7);
      a4[2] = v7;
      break;
    default:
      rf_color4_set_bytes_return_destination(a4, 255, 255, 255, 0);
      break;
  }
  return (_BYTE *)rf_bitmap_unlock_pixels_backend_dispatch(v9);
}

