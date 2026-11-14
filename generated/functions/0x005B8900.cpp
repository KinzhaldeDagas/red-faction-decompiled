// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B8900 rf_v3c_mesh_metadata100_construct_defaults
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mesh initializers, binary reader stores, caller layouts and signature classification): 100-byte metadata initializer: leaves DWORD0 untouched; zeroes floats4,8,12; writes FLT_MAX (0x7F7FFFFF) to16,20,24; clears three24-byte blocks starting28,52,76. No allocation, pointers or count initialization beyond these exact stores. EAX exits with ECX despite existing void declaration.
void __thiscall rf_v3c_mesh_metadata100_construct_defaults(float *this)
{
  float *v1; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < 3; ++i )
  {
    *(this + i + 1) = 0.0;
    *(this + i + 4) = 3.4028235e38;
    v1 = this + 6 * i + 7;
    *v1 = 0.0;
    v1[1] = 0.0;
    v1[2] = 0.0;
    v1[3] = 0.0;
    v1[4] = 0.0;
    v1[5] = 0.0;
  }
}

