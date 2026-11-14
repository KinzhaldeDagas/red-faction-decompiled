// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057B920 rf_vfile_initialize_roots_and_optional_vpp_mounts
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl optional data-root cstring and mount-VPP flag. If initialized byte189CE90 nonzero returns that raw byte, does no work. Otherwise unbounded-copies provided root and appends backslash if final byte differs (empty provided root reads root[-1]); null root uses GetModuleFileNameA(NULL,local256,255), ignores result/termination then copies and writes NUL just after last backslash without NULL check. Clears root/extension pointers in512 records, leaves record flags. Initializes legacy global vector/quaternion/matrix, sets initialized byte1 BEFORE lookup init5928D0 and optional VPP init. Registers shutdown57B840 with atexit and returns atexit result (normally0), distinct from repeated-call return1. No
// partial-failure unwind or prefix normalization.
int __cdecl rf_vfile_initialize_roots_and_optional_vpp_mounts(char *a1, int a2)
{
  int result; // eax
  CHAR v3; // [esp+3h] [ebp-13Dh]
  char *v4; // [esp+8h] [ebp-138h]
  CHAR *v5; // [esp+Ch] [ebp-134h]
  char *v6; // [esp+1Ch] [ebp-124h]
  char v7; // [esp+23h] [ebp-11Dh]
  char *v8; // [esp+28h] [ebp-118h]
  char *v9; // [esp+2Ch] [ebp-114h]
  CHAR Filename[256]; // [esp+38h] [ebp-108h] BYREF
  int i; // [esp+13Ch] [ebp-4h]

  result = byte_189CE90[0];
  if ( !byte_189CE90[0] )
  {
    unk_189CD90 = 0;
    if ( a1 )
    {
      v9 = a1;
      v8 = &unk_189CD90;
      do
      {
        v7 = *v9;
        *v8++ = *v9++;
      }
      while ( v7 );
      v6 = &unk_189CD90 + strlen(&unk_189CD90) + 1;
      if ( unk_189CD8F[v6 - (char *)&unk_189CD91] != 92 )
      {
        *(&unk_189CD90 + v6 - (char *)&unk_189CD91) = 92;
        *v6 = 0;
      }
    }
    else
    {
      GetModuleFileNameA(nullptr, Filename, 0xFFu);
      v5 = Filename;
      v4 = &unk_189CD90;
      do
      {
        v3 = *v5;
        *v4++ = *v5++;
      }
      while ( v3 );
      rf_cstring_find_last_char_wrapper(&unk_189CD90, 92)[1] = 0;
    }
    for ( i = 0; i < 512; ++i )
    {
      dword_1897490[3 * i] = 0;
      dword_1897494[3 * i] = 0;
    }
    rf_vector3_zero_return_destination(unk_1C8FBDC);
    rf_quaternion_set_identity_return_this(unk_1C8FC3C);
    rf_identity_orientation_matrix(unk_1C8FC18);
    byte_189CE90[0] = 1;
    rf_vfile_loose_lookup_clear_bucket_heads();
    if ( a2 )
      rf_vpackfile_init();
    return atexit(rf_vfile_shutdown_roots_and_lookup_tables);
  }
  return result;
}

