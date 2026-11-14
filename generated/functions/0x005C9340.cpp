// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C9340 rf_material_initialize
// UNREALRED VERIFIED [material-animation-20260903]: Initializes one 200-byte runtime material: constructs two 52-byte texture slots, sets their handles to -1, initializes white RGBA state, sets the shared curve rate +0x78 to 15, and clears transition, self-illumination, and alpha curve counts/pointers.
void __thiscall rf_material_initialize(char *this)
{
  int i; // [esp+8h] [ebp-10h]

  rf_rgba8_default_construct_noop(this + 9);
  `eh vector constructor iterator'(
    this + 16,
    0x34u,
    2,
    rf_receiver_identity_constructor_noop_5C90D0,
    rf_saved_receiver_noop_5C90E0);
  *(_DWORD *)this = -1;
  *((_DWORD *)this + 1) = 0;
  rf_color4_set_bytes_return_destination(this + 9, 255, 255, 255, 255);
  for ( i = 0; i < 2; ++i )
    *((_DWORD *)this + 13 * i + 4) = -1;
  *((_DWORD *)this + 30) = 15;
  *((_DWORD *)this + 31) = 0;
  *((_DWORD *)this + 32) = 0;
  *((float *)this + 33) = 0.0;
  *((float *)this + 34) = 0.0;
  *((float *)this + 35) = 0.0;
  *(this + 144) = 0;
  *((_DWORD *)this + 45) = -1;
  *((_DWORD *)this + 46) = 0;
  *((_DWORD *)this + 47) = 0;
  *((_DWORD *)this + 48) = 0;
  *((_DWORD *)this + 49) = 0;
}

