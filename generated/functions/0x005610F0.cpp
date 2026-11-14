// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005610F0 rf_string_format_float_fixed_precision
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Cdecl output object, float value, signed precision. Promotes float to double for sprintf("%.*f",precision,value) into a fixed stack buffer. Constructs/copies/destroys RF temporary and returns output. No precision bound or bounded formatter; large requested precision or large fixed-point result can exceed local buffer.
_DWORD *__cdecl rf_string_format_float_fixed_precision(_DWORD *a1, float a2, int a3)
{
  char *v4[2]; // [esp+10h] [ebp-44h] BYREF
  char Buffer[44]; // [esp+18h] [ebp-3Ch] BYREF
  int v6; // [esp+50h] [ebp-4h]

  sprintf(Buffer, "%.*f", a3, a2);
  rf_string_construct_from_cstr(v4, Buffer);
  v6 = 1;
  rf_string_copy_construct_from_object(a1, v4);
  LOBYTE(v6) = 0;
  rf_string_destroy_buffer(v4);
  return a1;
}

