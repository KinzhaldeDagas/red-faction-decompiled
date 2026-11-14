// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043E0F0 rf_spawn_gray_particle_and_vclip
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(required position3f,opaque arg1,opaque arg2,FLOAT input), void. First40CFF0 computes FLOAT32-rounded
// sqrt(input), storesFLOAT32 local; no negative/NaN/finite guard.76-byte particle constructor is NO-OP. Explicit descriptor writes ONLY: position0..8 copied from source,
// velocity12..20=0, size24=round32(storedSqrt*DOUBLE0.05000000074505806),
// FLOAT28=0,FLOAT32=0,lifeFLOAT40=0.5,DWORD44=global661548,DWORD48=global66154C,RGBA52=(127,127,127,255),DWORD60=0,DWORD64=0. Offsets36,56,68,72 remain uninitialized stack data;
// constructor does not provide zero defaults, including second color56. Call4CD100(pool0,&descriptor,arg1,arg2,parent-1,emitterNULL,lastDWORD0), ignore returned particle pointer.
// Then ALWAYS448DC0(global6E622C,arg1,arg2,ORIGINAL position pointer,FLOAT0.25,FLOAT0,DWORD0), regardless particle failure. Shared VClip helper may spawn presentation and still
// invokes radial delegate with anonymous source-1/type3; zero damage-scale is passed, no own damage-success/finite policy. Position is copied for particle but reread through original
// pointer by suffix. No source/null/radius/room/authority check, full descriptor memset, result normalization or rollback between the two calls.
void __cdecl rf_spawn_gray_particle_and_vclip(float *source, int a2, int a3, float a4)
{
  float copy_result[3]; // [esp+Ch] [ebp-60h] BYREF
  float v5; // [esp+18h] [ebp-54h]
  float destination[3]; // [esp+1Ch] [ebp-50h] BYREF
  float v7[10]; // [esp+28h] [ebp-44h] BYREF
  _BYTE v8[8]; // [esp+50h] [ebp-1Ch] BYREF
  int v9; // [esp+58h] [ebp-14h]
  int v10; // [esp+5Ch] [ebp-10h]

  v5 = rf_sqrt_float(a4);
  rf_particle_descriptor76_construct_noop((int)destination);
  rf_vector_copy(destination, copy_result, source);
  v7[7] = 0.5;
  rf_color4_set_bytes_return_destination(v8, 127, 127, 127, 255);
  v7[3] = v5 * 0.05000000074505806;
  LODWORD(v7[8]) = dword_661548;
  LODWORD(v7[9]) = dword_66154C;
  rf_vector3_zero_return_destination(v7);
  v9 = 0;
  v10 = 0;
  v7[4] = 0.0;
  v7[5] = 0.0;
  rf_particle_allocate_and_initialize(0, (int)destination, a2, a3, -1, nullptr, 0);
  sub_448DC0(unk_6E622C, a2, a3, source, 0.25, 0.0, 0);
}

