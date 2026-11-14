// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005745A0 rf_bitmap_manager_initialize_storage
// UNREALRED VERIFIED [bitmap-loading-20261028]: Runs unless initialized byte0x189744F equals1. Sets generation limit0x1897348=0x10000000/slotcount0x663F14; allocates 108*slotcount records and 4*(slotcount+1) hash pointers, fatal on allocation failure. Initializes active/free ordinary sentinels and links all records, zeroes hash pointers, recycles each slot through0x574890. Initializes 3000 fixed 36-byte animation-entry free-list links at0x187CD40 and empty active-animation sentinel0x1897320. Allocates3072-byte 32x32 three-byte placeholder image at0x1897450: grid rows/columns where coordinate&7==0 use64/64/64, others142/121/121. Registers manager release0x5740E0 with atexit, marks initialized1. Does not validate positive slot count or placeholder allocation; repeated initialization after release registers another exit callback. Return previous initialized byte or atexit result.
int rf_bitmap_manager_initialize_storage()
{
  int result; // eax
  int n; // [esp+Ch] [ebp-10h]
  int ii; // [esp+10h] [ebp-Ch]
  _BYTE *v3; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]
  int j; // [esp+18h] [ebp-4h]
  int k; // [esp+18h] [ebp-4h]
  int m; // [esp+18h] [ebp-4h]

  result = byte_189744F[0];
  if ( byte_189744F[0] != 1 )
  {
    unk_1897348 = 0x10000000u / dword_663F14;
    dword_1897344 = (int)operator new(108 * dword_663F14);
    dword_189734C = operator new(4 * (dword_663F14 + 1));
    if ( !dword_1897344 || !dword_189734C )
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\vsdk\\bmpman\\bmpman.cpp",
        2043,
        "Unable to allocate memory for bitmaps.");
    dword_1897434 = (int)&unk_18973E0;
    unk_1897438 = &unk_18973E0;
    unk_18973A4 = &unk_1897350;
    unk_18973A8 = &unk_1897350;
    for ( i = 0; i < dword_663F14; ++i )
    {
      *(_DWORD *)(dword_1897344 + 108 * i + 88) = unk_1897438;
      *(_DWORD *)(dword_1897344 + 108 * i + 84) = &unk_18973E0;
      *(_DWORD *)(unk_1897438 + 84) = dword_1897344 + 108 * i;
      unk_1897438 = dword_1897344 + 108 * i;
    }
    for ( j = 0; j < dword_663F14 + 1; ++j )
      *((_DWORD *)dword_189734C + j) = 0;
    for ( k = 0; k < dword_663F14; ++k )
      rf_bitmap_slot_recycle_without_freeing_pixels(k);
    dword_18973C0 = (int)&unk_18973BC;
    unk_18973C4 = &unk_18973BC;
    dword_1897324 = (int)&unk_1897320;
    unk_1897328 = &unk_1897320;
    for ( m = 0; m < 3000; ++m )
    {
      unk_187CD48[9 * m] = unk_18973C4;
      unk_187CD44[9 * m] = (int)&unk_18973BC;
      *(_DWORD *)(unk_18973C4 + 4) = &unk_187CD40[9 * m];
      unk_18973C4 = &unk_187CD40[9 * m];
    }
    *(_DWORD *)&byte_189744F[1] = operator new(0xC00u);
    v3 = *(_BYTE **)&byte_189744F[1];
    for ( n = 0; n < 32; ++n )
    {
      for ( ii = 0; ii < 32; ++ii )
      {
        if ( (ii & 7) != 0 && (n & 7) != 0 )
        {
          *v3 = -114;
          v3[1] = 121;
          v3[2] = 121;
        }
        else
        {
          *v3 = 64;
          v3[1] = 64;
          v3[2] = 64;
        }
        v3 += 3;
      }
    }
    result = atexit(rf_bitmap_manager_release_active_storage);
    byte_189744F[0] = 1;
  }
  return result;
}

